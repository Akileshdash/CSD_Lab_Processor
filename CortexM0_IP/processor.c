#include "processor.h"
#include "stages.h"
#include "execute.h"
#include "decode.h"
#include "regfile.h"
#include "stdio.h"

#define OS_START_ADDR 0x00000000

static inline int thumb_writes_register(thumb_operation_t op) {
    switch (op) {
        // Register-writing arithmetic and data-processing
        case THUMB_MOV_REG:
        case THUMB_MOV_IMM:
        case THUMB_MOV_HIGH:
        case THUMB_LSL_IMM:
        case THUMB_LSL_REG:
        case THUMB_LSR_IMM:
        case THUMB_LSR_REG:
        case THUMB_ASR_IMM:
        case THUMB_ASR_REG:
        case THUMB_ADD_REG:
        case THUMB_ADD_IMM3:
        case THUMB_ADD_IMM8:
        case THUMB_ADD_SP_IMM:
        case THUMB_ADD_SP_IMM7:
        case THUMB_ADD_HIGH:  
        case THUMB_ADD_PC_IMM:
        case THUMB_SUB_REG:
        case THUMB_SUB_IMM3:
        case THUMB_SUB_IMM8:
        case THUMB_SUB_SP_IMM7:
        case THUMB_ADR:
        case THUMB_NEG:
        case THUMB_AND:
        case THUMB_EOR:
        case THUMB_ORR:
        case THUMB_BIC:
        case THUMB_MVN:
        case THUMB_ADC:
        case THUMB_SBC:
        case THUMB_RSB:
        case THUMB_ROR:
        case THUMB_MUL:
        case THUMB_SXTB:
        case THUMB_SXTH:
        case THUMB_UXTB:
        case THUMB_UXTH:
        case THUMB_REV:
        case THUMB_REV16:
        case THUMB_REVSH:
            return 1;

        // Memory loads (write to Rd)
        case THUMB_LDR_REG:
        case THUMB_LDR_IMM:
        case THUMB_LDR_LIT:
        case THUMB_LDR_SP:
        case THUMB_LDRB_REG:
        case THUMB_LDRB_IMM:
        case THUMB_LDRH_REG:
        case THUMB_LDRH_IMM:
        case THUMB_LDRSB_REG:
        case THUMB_LDRSH_REG:
        case THUMB_LDMIA:
        case THUMB_POP:
            return 1;

        // Branch with link writes LR
        case THUMB_BL:
            return 1;

        default:
            return 0;
    }
}

static inline int is_load_instruction(thumb_operation_t op) {
    switch (op) {
        case THUMB_LDR_REG:
        case THUMB_LDR_IMM:
        case THUMB_LDR_LIT:
        case THUMB_LDR_SP:
        case THUMB_LDRB_REG:
        case THUMB_LDRB_IMM:
        case THUMB_LDRH_REG:
        case THUMB_LDRH_IMM:
        case THUMB_LDRSB_REG:
        case THUMB_LDRSH_REG:
        case THUMB_LDMIA:
        case THUMB_POP:
            return 1;
        default:
            return 0;
    }
}

static inline int is_store_instruction(thumb_operation_t op) {
    switch (op) {
        case THUMB_STR_REG:
        case THUMB_STR_IMM:
        case THUMB_STR_SP:
        case THUMB_STRB_REG:
        case THUMB_STRB_IMM:
        case THUMB_STRH_REG:
        case THUMB_STRH_IMM:
        case THUMB_STMIA:
        case THUMB_PUSH:
            return 1;
        default:
            return 0;
    }
}

static int cycle = 0;

int is_32bit_thumb(uint16_t hw) {
    return ((hw & 0xF800) == 0xE800) ||   // 11101
           ((hw & 0xF800) == 0xF000) ||   // 11110
           ((hw & 0xF800) == 0xF800);     // 11111
}

// Hazard Detection Unit
typedef struct {
    int stall;              // 1 = insert bubble (stall IF and ID)
    int flush_ID;           // 1 = flush ID stage
    int flush_EX;           // 1 = flush EX stage
    int flush_MEM;          // 1 = flush MEM stage
} hazard_control_t;

// -------- Hazard Detection -------
hazard_control_t detect_hazards(ID_stage ID, EX_stage EX, MEM_stage MEM, WB_stage WB) {
    hazard_control_t ctrl;
    ctrl.stall = 0;
    ctrl.flush_ID = 0;
    ctrl.flush_EX = 0;
    ctrl.flush_MEM = 0;

    // Branch handling strategy:
    // - Unconditional branches (B, BX, BL): Flush pipeline as they advance
    // - Conditional branches (B_COND): DON'T flush - let them execute and only flush if taken
    // - Branch target is calculated in EX, taken in WB
    
    // Check if it's an UNCONDITIONAL branch (not B_COND)
    int is_unconditional_branch_WB = (WB.opcode == THUMB_B || WB.opcode == THUMB_BX || WB.opcode == THUMB_BL);
    int is_unconditional_branch_MEM = (MEM.opcode == THUMB_B || MEM.opcode == THUMB_BX || MEM.opcode == THUMB_BL);
    int is_unconditional_branch_EX = (EX.opcode == THUMB_B || EX.opcode == THUMB_BX || EX.opcode == THUMB_BL);
    
    if (is_unconditional_branch_WB) {
        // Unconditional branch about to be taken - flush all speculative work
        ctrl.flush_ID = 1;
        ctrl.flush_EX = 1;
        ctrl.flush_MEM = 1;
        printf("[HAZARD] Unconditional branch in WB - flushing pipeline.\n");
    }
    else if (is_unconditional_branch_MEM) {
        // Unconditional branch in MEM - flush speculative instructions
        ctrl.flush_ID = 1;
        ctrl.flush_EX = 1;
        printf("[HAZARD] Unconditional branch in MEM - flushing ID, EX.\n");
    }
    else if (is_unconditional_branch_EX) {
        // Unconditional branch in EX - flush speculative instruction
        ctrl.flush_ID = 1;
        printf("[HAZARD] Unconditional branch in EX - flushing ID.\n");
    }
    
    // For CONDITIONAL branches (B_COND), we don't flush the pipeline preemptively
    // The branch decision is made in EX stage, and if taken, we handle it in WB
    // No flushing needed here - the WB stage will handle it if the branch is actually taken

    // Load-Use Hazard Detection (only check if not flushing)
    if (!ctrl.flush_ID && is_load_instruction(EX.opcode) && thumb_writes_register(EX.opcode)) {
        if ((EX.rd == ID.rs1 || EX.rd == ID.rs2)) {
            ctrl.stall = 1;
            printf("[HAZARD] Load-Use hazard - stalling.\n");
        }
    }

    return ctrl;
}

// Data Forwarding Unit
typedef struct {
    uint32_t forward_data1;
    uint32_t forward_data2;
    uint32_t forward_cpsr;     
    int forward_src1;
    int forward_src2;
    int forward_cpsr_src;
} forward_control_t;

forward_control_t detect_forwarding(ID_stage ID, EX_stage EX, MEM_stage MEM, WB_stage WB, cortex_m0_registers_t* core_regs) {
    forward_control_t fwd;
    // fwd.forward_data1 = ID.reg_data1;
    fwd.forward_data1 = regfile_read(ID.rs1, core_regs);
    fwd.forward_data2 = regfile_read(ID.rs2, core_regs);
    fwd.forward_cpsr = core_regs->apsr;  // Read fresh CPSR
    fwd.forward_src1 = 0;
    fwd.forward_src2 = 0;
    fwd.forward_cpsr_src = 0;  

    // Forward CPSR from comparison instructions
    // Check MEM stage first (most recent)
    if (MEM.opcode == THUMB_CMP_REG || MEM.opcode == THUMB_CMP_IMM || 
        MEM.opcode == THUMB_CMP_HIGH || MEM.opcode == THUMB_TST || 
        MEM.opcode == THUMB_CMN) {
        fwd.forward_cpsr = MEM.cpsr;
        fwd.forward_cpsr_src = 2;
        printf("[FORWARD] MEM->ID forwarding CPSR=0x%08X\n", MEM.cpsr);
    }
    // Check EX stage next
    else if (EX.opcode == THUMB_CMP_REG || EX.opcode == THUMB_CMP_IMM || 
             EX.opcode == THUMB_CMP_HIGH || EX.opcode == THUMB_TST || 
             EX.opcode == THUMB_CMN) {
        fwd.forward_cpsr = EX.cpsr;
        fwd.forward_cpsr_src = 1;
        printf("[FORWARD] EX->ID forwarding CPSR=0x%08X\n", EX.cpsr);
    }
    // Check WB stage last
    else if (WB.opcode == THUMB_CMP_REG || WB.opcode == THUMB_CMP_IMM || 
             WB.opcode == THUMB_CMP_HIGH || WB.opcode == THUMB_TST || 
             WB.opcode == THUMB_CMN) {
        fwd.forward_cpsr = WB.cpsr;
        fwd.forward_cpsr_src = 3;
        printf("[FORWARD] WB->ID forwarding CPSR=0x%08X\n", WB.cpsr);
    }

    // Forward rs1
    // NOTE: rs1 CAN be 0 (R0 is a valid register), so don't skip based on rs1 value
    // Only forward if this instruction actually uses rs1
    if (ID.rs1 >= 0 && ID.rs1 <= 15) {
        // printf("[FORWARD DEBUG] Checking rs1=%d forwarding:\n", ID.rs1);
        // printf("[FORWARD DEBUG]   EX: opcode=%d, rd=%d, writes=%d\n", EX.opcode, EX.rd, thumb_writes_register(EX.opcode));
        // printf("[FORWARD DEBUG]   MEM: opcode=%d, rd=%d, writes=%d\n", MEM.opcode, MEM.rd, thumb_writes_register(MEM.opcode));
        // printf("[FORWARD DEBUG]   WB: opcode=%d, rd=%d, writes=%d\n", WB.opcode, WB.rd, thumb_writes_register(WB.opcode));    
        if (thumb_writes_register(EX.opcode) && EX.rd == ID.rs1) {
            if (!is_load_instruction(EX.opcode)) {
                fwd.forward_data1 = EX.alu_result;
                fwd.forward_src1 = 1;
                printf("[FORWARD] EX->ID forwarding for rs1=%d, data=0x%08X\n", ID.rs1, EX.alu_result);
            }
        }
        else if (thumb_writes_register(MEM.opcode) && MEM.rd == ID.rs1 ) {
            fwd.forward_data1 = MEM.mem_data;
            fwd.forward_src1 = 2;
            printf("[FORWARD DEBUG] MEM->ID for rs1: MEM.rd=%d, ID.rs1=%d, MEM.opcode=%d, match=%d\n",
                MEM.rd, ID.rs1, MEM.opcode, (MEM.rd == ID.rs1));
            printf("[FORWARD] MEM->ID forwarding for rs1=%d, data=0x%08X\n", ID.rs1, MEM.mem_data);
        }
        else if (thumb_writes_register(WB.opcode) && WB.rd == ID.rs1 ) {
            fwd.forward_data1 = WB.write_data;
            fwd.forward_src1 = 3;
            printf("[FORWARD] WB->ID forwarding for rs1=%d, data=0x%08X\n", ID.rs1, WB.write_data);
        }
        else {
            printf("[FORWARD DEBUG] NO FORWARDING for rs1=%d\n", ID.rs1);
        }
    }

    // Forward rs2
    // NOTE: rs2 CAN be 0 (R0 is a valid register), so don't skip based on rs2 value
    if (ID.rs2 >= 0 && ID.rs2 <= 15) {  // Valid register number
        if (thumb_writes_register(EX.opcode) && EX.rd == ID.rs2) {
            if (!is_load_instruction(EX.opcode)) {
                fwd.forward_data2 = EX.alu_result;
                fwd.forward_src2 = 1;
                printf("[FORWARD] EX->ID forwarding for rs2=%d, data=0x%08X\n", ID.rs2, EX.alu_result);
            }
        }
        else if (thumb_writes_register(MEM.opcode) && MEM.rd == ID.rs2 ) {
            fwd.forward_data2 = MEM.mem_data;
            fwd.forward_src2 = 2;
            printf("[FORWARD] MEM->ID forwarding for rs2=%d, data=0x%08X\n", ID.rs2, MEM.mem_data);
        }
        else if (thumb_writes_register(WB.opcode) && WB.rd == ID.rs2 ) {
            fwd.forward_data2 = WB.write_data;
            fwd.forward_src2 = 3;
            printf("[FORWARD] WB->ID forwarding for rs2=%d, data=0x%08X\n", ID.rs2, WB.write_data);
        }
    }

    return fwd;
}

// Helper function: Extract memory data based on size and sign extension
static uint32_t process_mem_data(uint32_t raw_data, uint32_t address, int mem_size, int sign_extend) {
    uint32_t result = 0;
    
    switch (mem_size) {
        case 1:  // Byte
        {
            uint8_t byte_val = (raw_data >> ((address & 3) * 8)) & 0xFF;
            if (sign_extend) {
                result = (int32_t)(int8_t)byte_val;
            } else {
                result = byte_val;
            }
            break;
        }
        case 2:  // Halfword
        {
            uint16_t hw_val = (raw_data >> ((address & 2) * 8)) & 0xFFFF;
            if (sign_extend) {
                result = (int32_t)(int16_t)hw_val;
            } else {
                result = hw_val;
            }
            break;
        }
        case 4:  // Word
        default:
            result = raw_data;
            break;
    }
    
    return result;
}

void cortex_m0_top(
    volatile uint32_t* instr_mem,
    volatile uint32_t* data_mem,
    // volatile uint32_t* reg_out,
    int* pc_out
) {
#pragma HLS INTERFACE m_axi port=instr_mem offset=slave bundle=INSTR_BUS
#pragma HLS INTERFACE m_axi port=data_mem offset=slave bundle=DATA_BUS
#pragma HLS INTERFACE ap_none port=pc_out
// #pragma HLS INTERFACE m_axi port=reg_out   offset=slave bundle=REG_BUS
#pragma HLS INTERFACE ap_ctrl_none port=return



    static IF_stage IF;
    static ID_stage ID;
    static EX_stage EX;
    static MEM_stage MEM;
    static WB_stage WB;
    static cortex_m0_registers_t core_regs;
    static bool init_done = false;

        // Reset all stages
        #pragma HLS RESET variable=IF.pc
        #pragma HLS RESET variable=IF.instr 
        #pragma HLS RESET variable=ID.pc 
        #pragma HLS RESET variable=ID.instr 
        #pragma HLS RESET variable=ID.reg_data1
        #pragma HLS RESET variable=ID.reg_data2 
        #pragma HLS RESET variable=ID.opcode 
        #pragma HLS RESET variable=ID.rd 
        #pragma HLS RESET variable=ID.rs1 
        #pragma HLS RESET variable=ID.rs2 
        #pragma HLS RESET variable=ID.immediate_flag 
        #pragma HLS RESET variable=ID.imm_value 
        #pragma HLS RESET variable=ID.condition 
        #pragma HLS RESET variable=ID.cpsr 
        #pragma HLS RESET variable=EX.opcode 
        #pragma HLS RESET variable=EX.alu_result 
        #pragma HLS RESET variable=EX.reg_data2 
        #pragma HLS RESET variable=EX.rd 
        #pragma HLS RESET variable=EX.link 
        #pragma HLS RESET variable=EX.cpsr 
        #pragma HLS RESET variable=EX.pc 
        #pragma HLS RESET variable=MEM.opcode
        #pragma HLS RESET variable=MEM.alu_result
        #pragma HLS RESET variable=MEM.mem_data
        #pragma HLS RESET variable=MEM.rd 
        #pragma HLS RESET variable=MEM.link 
        #pragma HLS RESET variable=MEM.cpsr 
        #pragma HLS RESET variable=WB.opcode 
        #pragma HLS RESET variable=WB.write_data 
        #pragma HLS RESET variable=WB.rd 
        #pragma HLS RESET variable=WB.link 
        #pragma HLS RESET variable=WB.cpsr
        #pragma HLS RESET variable=init_done

    if(!init_done) {
        // Initialize register file
        uint32_t msp_init = data_mem[0];
        uint32_t reset_vector = data_mem[1];  // Read reset vector from address 0x00000004
        regfile_init(&core_regs, reset_vector, msp_init);
        
        // Set PC to reset vector for first instruction fetch
        IF.pc = (reset_vector & 0xFFFFFFFE) >> 1;  // Convert byte address to halfword index
        
        cycle = 0;
        
        printf("\n========== PROCESSOR RESET ==========\n");
        printf("MSP initialized to: 0x%08X\n", msp_init);
        printf("Reset Vector: 0x%08X\n", reset_vector);
        printf("Starting PC (halfword): %d (byte addr: 0x%08X)\n", IF.pc, reset_vector & 0xFFFFFFFE);
        printf("=====================================\n");
        init_done = true;
         
    }
    *pc_out = regfile_get_pc(&core_regs);
    cycle++;
    printf("\n================ Cycle %d ==================\n", cycle);

    // -------- Hazard Detection --------
    hazard_control_t hazard = detect_hazards(ID, EX, MEM, WB);

    // -------- Data Forwarding --------
    forward_control_t forward = detect_forwarding(ID, EX, MEM, WB, &core_regs);

    // -------- Next-stage temporary registers --------
    IF_stage next_IF = IF;
    ID_stage next_ID = ID;
    EX_stage next_EX = EX;
    MEM_stage next_MEM = MEM;
    WB_stage next_WB = WB;

    // -------- Write Back Stage --------
    int branch_taken = 0;
    uint32_t branch_target = 0;

    // -------- Update APSR flags from CMP instructions --------
    // CMP instructions set flags but don't write to a destination register
    // Update APSR if this is a CMP instruction
    if (WB.opcode == THUMB_CMP_REG || WB.opcode == THUMB_CMP_IMM || 
        WB.opcode == THUMB_CMP_HIGH || WB.opcode == THUMB_TST || 
        WB.opcode == THUMB_CMN) {
        core_regs.apsr = WB.cpsr;
        printf("[WB] Updated APSR=0x%08X from CMP instruction\n", WB.cpsr);
    }

    switch (WB.opcode) {
        case THUMB_BL:
            // BL: Branch with Link - set LR and branch
            branch_taken = 1;
            branch_target = WB.write_data;
            regfile_set_pc(branch_target, &core_regs);
            next_IF.pc = branch_target >> 1;
            
            // Write link register
            if (WB.link != 0) {
                core_regs.lr = WB.link;
                printf("[WB] BL: Setting LR=0x%08X\n", WB.link);
            }
            
            printf("[WB] BL TAKEN! Target PC=0x%08X, LR=0x%08X\n", branch_target, WB.link);
            break;

        case THUMB_B:
        case THUMB_BX:
            // Unconditional branches - always taken
            branch_taken = 1;
            branch_target = WB.write_data;
            regfile_set_pc(branch_target, &core_regs);
            next_IF.pc = branch_target >> 1;
            printf("[WB] BRANCH TAKEN! Target PC=0x%08X (halfword=%d)\n", branch_target, next_IF.pc);
            break;
        case THUMB_B_COND:
        {
            // Check if branch was actually taken by comparing write_data with sequential PC
            uint32_t sequential_pc = regfile_get_pc(&core_regs);
            
            // If the computed target differs from where we naturally are, branch was taken
            if (WB.write_data != sequential_pc) {
                branch_taken = 1;
                branch_target = WB.write_data;
                regfile_set_pc(branch_target, &core_regs);
                next_IF.pc = branch_target >> 1;
                printf("[WB] CONDITIONAL BRANCH TAKEN! Target PC=0x%08X (halfword=%d)\n", 
                    branch_target, next_IF.pc);
            } else {
                printf("[WB] CONDITIONAL BRANCH NOT TAKEN - continuing at PC=0x%08X\n", sequential_pc);
            }
        }
            break;
        case THUMB_CBZ:
        case THUMB_CBNZ:
        {
            // Check if branch was taken by comparing write_data with sequential PC
            uint32_t sequential_pc = regfile_get_pc(&core_regs);
            
            if (WB.write_data != sequential_pc) {
                branch_taken = 1;
                branch_target = WB.write_data;
                regfile_set_pc(branch_target, &core_regs);
                next_IF.pc = branch_target >> 1;
                printf("[WB] CBZ/CBNZ BRANCH TAKEN! Target PC=0x%08X\n", branch_target);
            } else {
                printf("[WB] CBZ/CBNZ BRANCH NOT TAKEN - continuing at PC=0x%08X\n", sequential_pc);
            }
        }
            break;


        default:
            // Write to register if instruction writes to a register
            if (thumb_writes_register(WB.opcode)) {
                if (WB.rd == 15) {
                    // Writing to PC
                    regfile_set_pc(WB.write_data, &core_regs);
                    next_IF.pc = WB.write_data >> 1;  // Convert byte address to halfword index
                } else if (WB.opcode != THUMB_INVALID) {
                    // Write to any register (including R0)
                    // Note: R0 is a normal register in ARM, not a zero register
                    regfile_write(WB.rd, WB.write_data, &core_regs);
                }
            }
            break;
    }

    printf("[WB]  opcode=%d | rd=%d | write_data=0x%08X\n", WB.opcode, WB.rd, WB.write_data);

    // -------- Memory Stage --------
    if (hazard.flush_MEM) {
        next_MEM.opcode = THUMB_INVALID;
        next_MEM.rd = 0;
        next_MEM.alu_result = 0;
        next_MEM.mem_data = 0;
        next_MEM.link = 0;
        next_MEM.cpsr = 0;
        next_MEM.mem_size = 0;
        next_MEM.sign_extend = 0;
        printf("[MEM] **FLUSHED DUE TO BRANCH**\n");
    } else {
        next_MEM.opcode = EX.opcode;
        next_MEM.rd = EX.rd;
        next_MEM.alu_result = EX.alu_result;
        next_MEM.link = EX.link;
        next_MEM.mem_size = EX.mem_size;
        next_MEM.sign_extend = EX.sign_extend;
        next_MEM.cpsr = EX.cpsr;

        // PUSH/POP INSTRUCTIONS
        if (EX.opcode == THUMB_PUSH) {
            // PUSH: Store registers to stack
            uint32_t reglist = EX.mem_size;  // Register list from EX stage
            uint32_t num_regs = __builtin_popcount(reglist);
            
            // Count if R bit is set (LR included)
            uint32_t r_bit = (EX.rd >> 4) & 1;  // Extract from encoded value
            if (r_bit) num_regs++;
            
            // Get current SP
            uint32_t sp_value = regfile_get_sp(&core_regs);
            uint32_t start_addr = sp_value - (num_regs * 4);
            uint32_t address = start_addr;
            
            printf("[MEM] PUSH START: SP=0x%08X, reglist=0x%02X, r_bit=%d, num_regs=%d, start_addr=0x%08X\n",
                sp_value, reglist, r_bit, num_regs, start_addr);
            
            // Write each register to stack in order (R0 to R7)
            for (int i = 0; i < 8; i++) {
                if (reglist & (1 << i)) {
                    uint32_t reg_val = regfile_read(i, &core_regs);
                    uint32_t addr_word = address >> 2;
                    data_mem[addr_word] = reg_val;
                    printf("[MEM] PUSH: R%d (0x%08X) -> addr 0x%08X\n", i, reg_val, address);
                    address += 4;
                }
            }
            
            // If R bit set, push LR
            if (r_bit) {
                uint32_t lr_val = core_regs.lr;
                uint32_t addr_word = address >> 2;
                data_mem[addr_word] = lr_val;
                printf("[MEM] PUSH: LR (0x%08X) -> addr 0x%08X\n", lr_val, address);
                address += 4;
            }
            
            // Update SP in register file
            regfile_set_sp(start_addr, &core_regs);
            printf("[MEM] PUSH END: New SP=0x%08X\n", start_addr);
            
            next_MEM.mem_data = 0;  // No data to return
        }
        else if (EX.opcode == THUMB_POP) {
            // POP: Load registers from stack
            uint32_t reglist = EX.mem_size;  // Register list from EX stage
            uint32_t num_regs = __builtin_popcount(reglist);
            
            // Count if R bit is set (PC included)
            uint32_t r_bit = (EX.rd >> 4) & 1;  // Extract from encoded value
            if (r_bit) num_regs++;
            
            // Get current SP
            uint32_t sp_value = regfile_get_sp(&core_regs);
            uint32_t address = sp_value;
            
            printf("[MEM] POP START: SP=0x%08X, reglist=0x%02X, r_bit=%d, num_regs=%d\n",
                sp_value, reglist, r_bit, num_regs);
            
            // Read each register from stack in order (R0 to R7)
            for (int i = 0; i < 8; i++) {
                if (reglist & (1 << i)) {
                    uint32_t addr_word = address >> 2;
                    uint32_t reg_val = data_mem[addr_word];
                    regfile_write(i, reg_val, &core_regs);
                    printf("[MEM] POP: addr 0x%08X -> R%d (0x%08X)\n", address, i, reg_val);
                    address += 4;
                }
            }
            
            // If R bit set, pop to PC (function return)
            if (r_bit) {
                uint32_t addr_word = address >> 2;
                uint32_t pc_val = data_mem[addr_word];
                regfile_set_pc(pc_val, &core_regs);
                printf("[MEM] POP: addr 0x%08X -> PC (0x%08X)\n", address, pc_val);
                address += 4;
            }
            
            // Update SP
            uint32_t new_sp = sp_value + (num_regs * 4);
            regfile_set_sp(new_sp, &core_regs);
            printf("[MEM] POP END: New SP=0x%08X\n", new_sp);
            
            next_MEM.mem_data = 0;  // No data to return
        }

        // LOAD INSTRUCTIONS: Read from memory
        else if(EX.opcode == THUMB_LDR_IMM  || EX.opcode == THUMB_LDR_REG  ||
           EX.opcode == THUMB_LDR_LIT  || EX.opcode == THUMB_LDR_SP) 
        {
            uint32_t addr = EX.alu_result >> 2;
            uint32_t raw_data = data_mem[addr];
            next_MEM.mem_data = process_mem_data(raw_data, EX.alu_result, 4, 0);
            printf("[MEM] LOAD WORD: addr=0x%08X, data=0x%08X\n", EX.alu_result, next_MEM.mem_data);
        }
        else if(EX.opcode == THUMB_LDRB_IMM || EX.opcode == THUMB_LDRB_REG)
        {
            uint32_t addr = EX.alu_result >> 2;
            uint32_t raw_data = data_mem[addr];
            next_MEM.mem_data = process_mem_data(raw_data, EX.alu_result, 1, 0);
            printf("[MEM] LOAD BYTE: addr=0x%08X, data=0x%08X\n", EX.alu_result, next_MEM.mem_data);
        }
        else if(EX.opcode == THUMB_LDRSB_REG)
        {
            uint32_t addr = EX.alu_result >> 2;
            uint32_t raw_data = data_mem[addr];
            next_MEM.mem_data = process_mem_data(raw_data, EX.alu_result, 1, 1);
            printf("[MEM] LOAD SIGNED BYTE: addr=0x%08X, data=0x%08X\n", EX.alu_result, next_MEM.mem_data);
        }
        else if(EX.opcode == THUMB_LDRH_IMM || EX.opcode == THUMB_LDRH_REG)
        {
            uint32_t addr = EX.alu_result >> 2;
            uint32_t raw_data = data_mem[addr];
            next_MEM.mem_data = process_mem_data(raw_data, EX.alu_result, 2, 0);
            printf("[MEM] LOAD HALFWORD: addr=0x%08X, data=0x%08X\n", EX.alu_result, next_MEM.mem_data);
        }
        else if(EX.opcode == THUMB_LDRSH_REG)
        {
            uint32_t addr = EX.alu_result >> 2;
            uint32_t raw_data = data_mem[addr];
            next_MEM.mem_data = process_mem_data(raw_data, EX.alu_result, 2, 1);
            printf("[MEM] LOAD SIGNED HALFWORD: addr=0x%08X, data=0x%08X\n", EX.alu_result, next_MEM.mem_data);
        }
        // STORE INSTRUCTIONS: Write to memory
        else if(EX.opcode == THUMB_STR_IMM  || EX.opcode == THUMB_STR_REG ||
                EX.opcode == THUMB_STR_SP) 
        {
            uint32_t addr = EX.alu_result >> 2;
            
            // Check if value to store was just computed
            uint32_t value_to_store;
            if (WB.opcode != THUMB_INVALID && thumb_writes_register(WB.opcode) && WB.rd == EX.rd) {
                // Value is being written back THIS cycle - use the new value
                value_to_store = WB.write_data;
                printf("[MEM] STORE: Using WB-forwarded value (R%d = 0x%08X)\n", EX.rd, value_to_store);
            }
            else {
                // Otherwise read from register file  
                value_to_store = regfile_read(EX.rd, &core_regs);
            }
            
            data_mem[addr] = value_to_store;
            next_MEM.mem_data = value_to_store;
            printf("[MEM] STORE WORD: addr=0x%08X, value=0x%08X (from R%d)\n", 
                EX.alu_result, value_to_store, EX.rd);
        }
        // BYTE STORE
        else if(EX.opcode == THUMB_STRB_IMM || EX.opcode == THUMB_STRB_REG)
        {
            uint32_t addr = EX.alu_result >> 2;
            // Read the VALUE to store from Rd register (not from reg_data2!)
            uint32_t value_to_store = regfile_read(EX.rd, &core_regs);
            uint32_t byte_pos = (EX.alu_result & 3) * 8;
            uint32_t mask = ~(0xFF << byte_pos);
            data_mem[addr] = (data_mem[addr] & mask) | ((value_to_store & 0xFF) << byte_pos);
            next_MEM.mem_data = value_to_store & 0xFF;
            printf("[MEM] STORE BYTE: addr=0x%08X, byte_pos=%d, data=0x%02X (from R%d=0x%08X)\n", 
                   EX.alu_result, byte_pos, value_to_store & 0xFF, EX.rd, value_to_store);
        }
        // HALFWORD STORE
        else if(EX.opcode == THUMB_STRH_IMM || EX.opcode == THUMB_STRH_REG)
        {
            uint32_t addr = EX.alu_result >> 2;
            // Read the VALUE to store from Rd register (not from reg_data2!)
            uint32_t value_to_store = regfile_read(EX.rd, &core_regs);
            uint32_t hw_pos = ((EX.alu_result >> 1) & 1) * 16;
            uint32_t mask = ~(0xFFFF << hw_pos);
            data_mem[addr] = (data_mem[addr] & mask) | ((value_to_store & 0xFFFF) << hw_pos);
            next_MEM.mem_data = value_to_store & 0xFFFF;
            printf("[MEM] STORE HALFWORD: addr=0x%08X, data=0x%04X (from R%d)\n", 
                   EX.alu_result, value_to_store & 0xFFFF, EX.rd);
        }
        else if (EX.opcode == THUMB_BL)
        {
            next_MEM.mem_data = EX.alu_result;
            next_MEM.link = EX.link;
        }
        else
        {
            next_MEM.mem_data = EX.alu_result;
        }
        printf("[MEM] opcode=%d | rd=%d | alu_result=0x%08X | mem_data=0x%08X\n",
            next_MEM.opcode, next_MEM.rd, next_MEM.alu_result, next_MEM.mem_data);
    }
    
    // -------- Update WB Stage (AFTER MEM stage processing) --------
    next_WB.opcode = next_MEM.opcode;      // Use next_MEM instead of MEM
    next_WB.rd = next_MEM.rd;
    next_WB.write_data = next_MEM.mem_data;
    next_WB.link = next_MEM.link;  // *** ADD THIS: Propagate link value ***
    next_WB.cpsr = next_MEM.cpsr;

    // -------- Execute Stage -------
    if (hazard.stall || hazard.flush_EX) {
        next_EX.opcode = THUMB_INVALID;
        next_EX.rd = 0;
        next_EX.alu_result = 0;
        next_EX.reg_data2 = 0;
        next_EX.link = 0;
        next_EX.pc = 0;
        next_EX.cpsr = 0;
        next_EX.mem_size = 0;
        next_EX.sign_extend = 0;
        if (hazard.stall) {
            printf("[EX]  **BUBBLE INSERTED DUE TO STALL**\n");
        } else {
            printf("[EX]  **FLUSHED DUE TO BRANCH**\n");
        }
    } else {
        EX_input_t ex_input;
        ex_input.opcode = ID.opcode;
        ex_input.rd = ID.rd;
        ex_input.pc = ID.pc << 1;  // Convert halfword index to byte address

        // ALWAYS use forwarded data for rs1 (base address register)
        ex_input.reg_data1 = forward.forward_data1;
        ex_input.condition = ID.condition;  // ← PASS CONDITION TO EXECUTE
        ex_input.cpsr = forward.forward_cpsr;            

        if (is_store_instruction(ID.opcode)) {
            // For stores, determine if this is immediate or register offset
            if (ID.immediate_flag) {
                // Immediate offset store: reg_data2 is the offset value
                ex_input.reg_data2 = ID.imm_value;
            } else if (ID.rs2 >= 0 && ID.rs2 <= 15) {
                // Register offset store: rs2 contains the offset register value
                // Check if the offset register value needs forwarding...
                if (thumb_writes_register(MEM.opcode) && MEM.rd == ID.rs2) {
                    ex_input.reg_data2 = MEM.mem_data;
                } else if (thumb_writes_register(EX.opcode) && EX.rd == ID.rs2) {
                    if (!is_load_instruction(EX.opcode)) {
                        ex_input.reg_data2 = EX.alu_result;
                    }
                } else {
                    ex_input.reg_data2 = ID.reg_data2;
                }
            }
        }
        else if(ID.opcode == THUMB_MOV_REG) {
            ex_input.reg_data2 = forward.forward_data1;
        }
        else if(ID.immediate_flag) {
            ex_input.reg_data2 = ID.imm_value;
        } else {
            ex_input.reg_data2 = forward.forward_data2;
        }

        printf("[EX PROCESSOR DEBUG] | reg_data1=0x%08X | reg_data2=0x%08X | imm_flag=%d | pc=0x%08X\n",
            ex_input.reg_data1, ex_input.reg_data2, ID.immediate_flag, ex_input.pc);

        EX_output_t ex_output = execute(ex_input, &core_regs);

        next_EX.opcode = ID.opcode;
        next_EX.rd = ID.rd;
        next_EX.cpsr = ex_output.cpsr;  // Capture flags from execution
        next_EX.reg_data2 = ex_input.reg_data2;
        next_EX.alu_result = ex_output.alu_result;
        next_EX.link = ex_output.link;
        next_EX.mem_size = ex_output.mem_size;
        next_EX.sign_extend = ex_output.sign_extend;
        next_EX.r_bit = ID.r_bit;
        
        printf("[EX]  opcode=%d | rd=%d | alu_result=0x%08X | reg_data2=0x%08X\n",
            next_EX.opcode, next_EX.rd, next_EX.alu_result, next_EX.reg_data2);
    }

    // -------- Instruction Decode Stage --------
    if (hazard.stall) {
        next_ID = ID;
        printf("[ID]  **STALLED - REPEATING CURRENT INSTRUCTION**\n");
    } else if (hazard.flush_ID) {
        next_ID.pc = IF.pc;
        next_ID.instr = 0;
        next_ID.opcode = THUMB_INVALID;
        next_ID.rd = 0;
        next_ID.rs1 = 0;
        next_ID.rs2 = 0;
        next_ID.immediate_flag = 0;
        next_ID.imm_value = 0;
        next_ID.reg_data1 = 0;
        next_ID.reg_data2 = 0;
        next_ID.condition = 0;
        next_ID.cpsr = 0;
        next_ID.r_bit = 0;
        printf("[ID]  **FLUSHED DUE TO BRANCH**\n");
    } else {
        next_ID.pc = IF.pc-1;
        uint16_t instr16_ID = IF.instr;

        int is32bit = is_32bit_thumb(instr16_ID);
        decode_result_t dres;
        
        if (is32bit) {
            uint32_t word_index = (IF.pc) >> 1;
            uint32_t word = instr_mem[word_index];
            uint16_t instr16_next;

            if (((IF.pc) & 1) == 0) {
                instr16_next = word & 0xFFFF;
            } else {
                instr16_next = (word >> 16) & 0xFFFF;
            }

            uint32_t full_instr = (instr16_ID << 16) | instr16_next;
            next_ID.instr = full_instr;
            dres = decode_thumb32_instruction(full_instr);
        } else {
            next_ID.instr = instr16_ID;
            dres = decode_thumb16_instruction(instr16_ID);
        }

        if (!dres.valid) {
            next_ID.opcode = THUMB_INVALID;
            next_ID.rd = 0;
            next_ID.rs1 = 0;
            next_ID.rs2 = 0;
            next_ID.immediate_flag = 0;
            next_ID.imm_value = 0;
            next_ID.reg_data1 = 0;
            next_ID.reg_data2 = 0;
            next_ID.condition = 0;  // ← ADD THIS
            next_ID.cpsr = EX.cpsr;  // ← PROPAGATE CPSR FROM EX (for B_COND)
            next_ID.r_bit = 0;
        } else {
            next_ID.opcode = dres.operation;
            next_ID.rd     = dres.rd;
            next_ID.rs1    = dres.rs1;
            next_ID.rs2    = dres.rs2;
            next_ID.immediate_flag = dres.immediate_flag;
            next_ID.imm_value      = dres.imm_value;
            next_ID.condition = dres.condition;  // ← STORE CONDITION FROM DECODE

            // Store R bit for PUSH/POP
            if (dres.operation == THUMB_PUSH || dres.operation == THUMB_POP) {
                next_ID.r_bit = dres.r_bit;  // Store the R bit
            } else {
                next_ID.r_bit = 0;
            }
            // ← USE FORWARDED CPSR (includes MEM/EX/WB forwarding)
            next_ID.cpsr = forward.forward_cpsr;

            // next_ID.reg_data1 = regfile_read(dres.rs1, &core_regs);
            // if (dres.immediate_flag) {
            //     next_ID.reg_data2 = dres.imm_value;
            // } else {
            //     next_ID.reg_data2 = regfile_read(dres.rs2, &core_regs);
            // }
            // Read rs1 from register file
            uint32_t rs1_regfile = regfile_read(dres.rs1, &core_regs);
            
            // Check if forwarding is available for rs1
            if (forward.forward_src1 > 0) {
                next_ID.reg_data1 = forward.forward_data1;
                printf("[ID] Forwarding rs1=%d from stage %d: 0x%08X (bypassing regfile 0x%08X)\n", 
                       dres.rs1, forward.forward_src1, forward.forward_data1, rs1_regfile);
            } else {
                next_ID.reg_data1 = rs1_regfile;
                printf("[ID] Reading rs1=%d from regfile: 0x%08X\n", dres.rs1, rs1_regfile);
            }
            
            // Read rs2 from register file (or use immediate)
            if (dres.immediate_flag) {
                next_ID.reg_data2 = dres.imm_value;
                printf("[ID] Using immediate for rs2: 0x%08X\n", dres.imm_value);
            } else {
                uint32_t rs2_regfile = regfile_read(dres.rs2, &core_regs);
                
                // Check if forwarding is available for rs2
                if (forward.forward_src2 > 0) {
                    next_ID.reg_data2 = forward.forward_data2;
                    printf("[ID] Forwarding rs2=%d from stage %d: 0x%08X (bypassing regfile 0x%08X)\n", 
                           dres.rs2, forward.forward_src2, forward.forward_data2, rs2_regfile);
                } else {
                    next_ID.reg_data2 = rs2_regfile;
                    printf("[ID] Reading rs2=%d from regfile: 0x%08X\n", dres.rs2, rs2_regfile);
                }
            }
        }

        printf("[ID]  instr16=0x%04X | is32bit=%d | opcode=%u | rd=%d | rs1=%d | rs2=%d\n",
               instr16_ID, is32bit, next_ID.opcode, next_ID.rd, next_ID.rs1, next_ID.rs2);
    }

    // -------- Instruction Fetch Stage --------
    if (hazard.stall) {
        next_IF = IF;
        printf("[IF]  **STALLED - NOT FETCHING NEW INSTRUCTION**\n");
    } else if (branch_taken) {
        // Branch was taken in WB, IF.pc already updated
        uint32_t word_index = next_IF.pc >> 1;
        uint32_t word = instr_mem[word_index];
        uint16_t instr16;

        if ((next_IF.pc & 1) == 0) {
            instr16 = word & 0xFFFF;
        } else {
            instr16 = (word >> 16) & 0xFFFF;
        }

        next_IF.instr = instr16;
        next_IF.pc = next_IF.pc + 1;
        regfile_set_pc(OS_START_ADDR + next_IF.pc * 2, &core_regs);

        printf("[IF]  BRANCH TARGET FETCH | pc=%d | instr16=0x%04X | next_pc=%d\n",
               next_IF.pc - 1, instr16, next_IF.pc);
    } else {
        uint32_t word_index = IF.pc >> 1;
        uint32_t word = instr_mem[word_index];
        uint16_t instr16;

        if ((IF.pc & 1) == 0) {
            instr16 = word & 0xFFFF;
        } else {
            instr16 = (word >> 16) & 0xFFFF;
        }

        next_IF.instr = instr16;
        
        int is32bit = is_32bit_thumb(instr16);
        if (is32bit) {
            next_IF.pc = IF.pc + 2;   // skip both halfwords (4 bytes)
        } else {
            next_IF.pc = IF.pc + 1;   // normal 16-bit instruction
        }

        // Update PC in architectural register file (convert to byte address)
        regfile_set_pc(OS_START_ADDR + next_IF.pc * 2, &core_regs);

        printf("[IF]  pc=%d | word_index=%d | instr16=0x%04X | next_pc=%d\n",
               IF.pc, word_index, instr16, next_IF.pc);
    }

    // -------- Commit all stage updates --------
    IF = next_IF;
    ID = next_ID;
    EX = next_EX;
    MEM = next_MEM;
    WB = next_WB;

    // // -------- Update debug output --------
    // for(int i = 0; i < 13; i++) {
    //     reg_out[i] = core_regs.gpr[i];
    // }
    
    // reg_out[13] = regfile_get_sp(&core_regs);
    // reg_out[14] = core_regs.lr;
    // reg_out[15] = regfile_get_pc(&core_regs);

    // printf("[REGFILE] R0-R12:\n");
    // for(int i = 0; i < 13; i++) {
    //     printf(" R%-2d=0x%08X", i, reg_out[i]);
    //     if ((i+1) % 4 == 0) printf("\n");
    // }
    // printf(" SP=0x%08X | LR=0x%08X | PC=0x%08X\n",
    //        reg_out[13], reg_out[14], reg_out[15]);
}