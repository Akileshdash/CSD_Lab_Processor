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
} hazard_control_t;

hazard_control_t detect_hazards(ID_stage ID, EX_stage EX, MEM_stage MEM) {
    hazard_control_t ctrl;
    ctrl.stall = 0;
    ctrl.flush_ID = 0;

    // Load-Use Hazard Detection
    // If EX stage has a load instruction that writes to a register
    // and ID stage needs that register, we must stall
    if (is_load_instruction(EX.opcode) && thumb_writes_register(EX.opcode)) {
        // Check if ID stage uses EX.rd as source operand
        if ((EX.rd == ID.rs1 || EX.rd == ID.rs2) && EX.rd != 0) {
            ctrl.stall = 1;
            printf("[HAZARD] Load-Use detected! EX.rd=%d matches ID source register. STALLING.\n", EX.rd);
        }
    }

    return ctrl;
}

// Data Forwarding Unit
typedef struct {
    uint32_t forward_data1;  // Forwarded data for rs1
    uint32_t forward_data2;  // Forwarded data for rs2
    int forward_src1;        // 0=no forward, 1=from EX, 2=from MEM, 3=from WB
    int forward_src2;        // 0=no forward, 1=from EX, 2=from MEM, 3=from WB
} forward_control_t;

forward_control_t detect_forwarding(ID_stage ID, EX_stage EX, MEM_stage MEM, WB_stage WB) {
    forward_control_t fwd;
    fwd.forward_data1 = ID.reg_data1;
    fwd.forward_data2 = ID.reg_data2;
    fwd.forward_src1 = 0;
    fwd.forward_src2 = 0;

    // Forward rs1
    if (ID.rs1 != 0) {
        // EX hazard (highest priority - most recent)
        if (thumb_writes_register(EX.opcode) && EX.rd == ID.rs1 && EX.rd != 0) {
            // For loads, we can't forward yet (data not available)
            if (!is_load_instruction(EX.opcode)) {
                fwd.forward_data1 = EX.alu_result;
                fwd.forward_src1 = 1;
                printf("[FORWARD] EX->ID forwarding for rs1=%d, data=0x%08X\n", ID.rs1, EX.alu_result);
            }
        }
        // MEM hazard
        else if (thumb_writes_register(MEM.opcode) && MEM.rd == ID.rs1 && MEM.rd != 0) {
            fwd.forward_data1 = MEM.mem_data;
            fwd.forward_src1 = 2;
            printf("[FORWARD] MEM->ID forwarding for rs1=%d, data=0x%08X\n", ID.rs1, MEM.mem_data);
        }
        // WB hazard (lowest priority)
        else if (thumb_writes_register(WB.opcode) && WB.rd == ID.rs1 && WB.rd != 0) {
            fwd.forward_data1 = WB.write_data;
            fwd.forward_src1 = 3;
            printf("[FORWARD] WB->ID forwarding for rs1=%d, data=0x%08X\n", ID.rs1, WB.write_data);
        }
    }

    // Forward rs2
    if (ID.rs2 != 0) {
        // EX hazard (highest priority)
        if (thumb_writes_register(EX.opcode) && EX.rd == ID.rs2 && EX.rd != 0) {
            // For loads, we can't forward yet (data not available)
            if (!is_load_instruction(EX.opcode)) {
                fwd.forward_data2 = EX.alu_result;
                fwd.forward_src2 = 1;
                printf("[FORWARD] EX->ID forwarding for rs2=%d, data=0x%08X\n", ID.rs2, EX.alu_result);
            }
        }
        // MEM hazard
        else if (thumb_writes_register(MEM.opcode) && MEM.rd == ID.rs2 && MEM.rd != 0) {
            fwd.forward_data2 = MEM.mem_data;
            fwd.forward_src2 = 2;
            printf("[FORWARD] MEM->ID forwarding for rs2=%d, data=0x%08X\n", ID.rs2, MEM.mem_data);
        }
        // WB hazard (lowest priority)
        else if (thumb_writes_register(WB.opcode) && WB.rd == ID.rs2 && WB.rd != 0) {
            fwd.forward_data2 = WB.write_data;
            fwd.forward_src2 = 3;
            printf("[FORWARD] WB->ID forwarding for rs2=%d, data=0x%08X\n", ID.rs2, WB.write_data);
        }
    }

    return fwd;
}

void cortex_m0_top(
    volatile uint32_t* instr_mem,
    volatile uint32_t* data_mem,
    volatile uint32_t* reg_out,
    int reset,
    int clk
) {
#pragma HLS INTERFACE m_axi port=instr_mem offset=slave bundle=INSTR_BUS
#pragma HLS INTERFACE m_axi port=data_mem offset=slave bundle=DATA_BUS
#pragma HLS INTERFACE s_axilite port=reg_out bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=reset bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=clk bundle=CTRL_BUS
#pragma HLS INTERFACE ap_ctrl_none port=return

    static IF_stage IF;
    static ID_stage ID;
    static EX_stage EX;
    static MEM_stage MEM;
    static WB_stage WB;
    static cortex_m0_registers_t core_regs;

    if(reset) {
        // Reset IF stage
        IF.pc = 0;
        IF.instr = 0;

        // Reset ID stage
        ID.pc = 0;
        ID.instr = 0;
        ID.reg_data1 = 0;
        ID.reg_data2 = 0;
        ID.opcode = THUMB_INVALID;
        ID.rd = 0;
        ID.rs1 = 0;
        ID.rs2 = 0;
        ID.immediate_flag = 0;
        ID.imm_value = 0;

        // Reset EX stage
        EX.opcode = THUMB_INVALID;
        EX.alu_result = 0;
        EX.reg_data2 = 0;
        EX.rd = 0;
        EX.link = 0;

        // Reset MEM stage
        MEM.opcode = THUMB_INVALID;
        MEM.alu_result = 0;
        MEM.mem_data = 0;
        MEM.rd = 0;
        MEM.link = 0;

        // Reset WB stage
        WB.opcode = THUMB_INVALID;
        WB.write_data = 0;
        WB.rd = 0;
        
        // Initialize core registers according to ARM spec
        uint32_t msp_init = data_mem[0];  // Stack pointer initial value
        
        // Initialize PC and SP
        regfile_init(&core_regs, OS_START_ADDR, msp_init);

        // **Convert PC from byte address to word index for IF stage**
        IF.pc = regfile_get_pc(&core_regs) >> 2;  
        
        cycle = 0;  // Reset cycle counter
        return;
    }

    cycle++;
    printf("\n================ Cycle %d ==================\n", cycle);

    // -------- Hazard Detection --------
    hazard_control_t hazard = detect_hazards(ID, EX, MEM);

    // -------- Data Forwarding --------
    forward_control_t forward = detect_forwarding(ID, EX, MEM, WB);

    // -------- Next-stage temporary registers --------
    IF_stage next_IF = IF;
    ID_stage next_ID = ID;
    EX_stage next_EX = EX;
    MEM_stage next_MEM = MEM;
    WB_stage next_WB = WB;

    // -------- Write Back Stage --------
    switch (WB.opcode) {
        // ---- Branches ----
        case THUMB_B:
        case THUMB_BX:
        case THUMB_B_COND:
        case THUMB_BL:
            // PC update
            regfile_set_pc(WB.write_data, &core_regs);
            IF.pc = WB.write_data >> 2;   // convert byte addr → word index
            break;

        // ---- Normal register-writing instructions ----
        default:
            if (thumb_writes_register(WB.opcode) && WB.rd != 0) {
                if (WB.rd == 15) {
                    // Special case: write PC
                    regfile_set_pc(WB.write_data, &core_regs);
                    IF.pc = WB.write_data >> 2;
                } else {
                    // General-purpose register write
                    regfile_write(WB.rd, WB.write_data, &core_regs);
                }
            }
            break;
    }

    printf("[WB]  opcode=%d | rd=%d | write_data=0x%08X\n", WB.opcode, WB.rd, WB.write_data);

    // -------- Memory Stage --------
    next_MEM.opcode = EX.opcode;
    next_MEM.rd = EX.rd;
    next_MEM.alu_result = EX.alu_result;
    next_MEM.link = EX.link;

    // Default: pass ALU result as mem_data
    next_MEM.mem_data = EX.alu_result; 

    // ---------- Load instructions ----------
    if(EX.opcode == THUMB_LDR_IMM  || EX.opcode == THUMB_LDR_REG  ||
       EX.opcode == THUMB_LDRB_IMM || EX.opcode == THUMB_LDRB_REG ||
       EX.opcode == THUMB_LDRH_IMM || EX.opcode == THUMB_LDRH_REG ||
       EX.opcode == THUMB_LDRSB_REG|| EX.opcode == THUMB_LDRSH_REG ||
       EX.opcode == THUMB_LDR_LIT) 
    {
        // For loads, mem_data comes from memory
        uint32_t addr = EX.alu_result >> 2;  // Convert byte address to word index
        next_MEM.mem_data = data_mem[addr];
    }

    // ---------- Store instructions ----------
    else if(EX.opcode == THUMB_STR_IMM  || EX.opcode == THUMB_STR_REG  ||
            EX.opcode == THUMB_STRB_IMM || EX.opcode == THUMB_STRB_REG ||
            EX.opcode == THUMB_STRH_IMM || EX.opcode == THUMB_STRH_REG ||
            EX.opcode == THUMB_STR_SP) 
    {
        uint32_t addr = EX.alu_result >> 2;  // Convert byte address to word index
        data_mem[addr] = EX.reg_data2;       // write to memory
    }

    // ---------- Branch with Link (BL) ----------
    else if (EX.opcode == THUMB_BL)
    {
        next_MEM.mem_data = EX.alu_result; // target PC
        next_MEM.link = EX.link;           // return address for LR
    }

    printf("[MEM] opcode=%d | rd=%d | alu_result=0x%08X | mem_data=0x%08X | link=0x%08X\n",
        next_MEM.opcode, next_MEM.rd, next_MEM.alu_result, next_MEM.mem_data, next_MEM.link);

    // -------- Execute Stage -------
    // If stalling, insert bubble in EX stage
    if (hazard.stall) {
        next_EX.opcode = THUMB_INVALID;
        next_EX.rd = 0;
        next_EX.alu_result = 0;
        next_EX.reg_data2 = 0;
        next_EX.link = 0;
        printf("[EX]  **BUBBLE INSERTED DUE TO STALL**\n");
    } else {
        EX_input_t ex_input;
        ex_input.opcode = ID.opcode;
        ex_input.rd = ID.rd;
        
        // Apply forwarding for reg_data1
        ex_input.reg_data1 = forward.forward_data1;
        
        // **FIX: For MOV_REG, reg_data2 should be the source register (rs1), not immediate**
        if(ID.opcode == THUMB_MOV_REG) {
            // MOV Rd, Rs - the source is in rs1, passed as reg_data2 to execute
            ex_input.reg_data2 = forward.forward_data1;  // Use forwarded rs1 value
        }
        else if(ID.immediate_flag) {
            ex_input.reg_data2 = ID.imm_value;
        } else {
            ex_input.reg_data2 = forward.forward_data2;
        }

        printf("[EX PROCESSOR DEBUG] | reg_data1=0x%08X | reg_data2=0x%08X | imm_flag=%d\n",
            ex_input.reg_data1, ex_input.reg_data2, ID.immediate_flag);

        EX_output_t ex_output = execute(ex_input, &core_regs);

        next_EX.opcode = ID.opcode;
        next_EX.rd = ID.rd;
        next_EX.reg_data2 = ex_input.reg_data2;  // pass along for memory/store
        next_EX.alu_result = ex_output.alu_result;
        next_EX.link = ex_output.link;

        printf("[EX]  opcode=%d | rd=%d | alu_result=0x%08X | reg_data2=0x%08X\n",
            next_EX.opcode, next_EX.rd, next_EX.alu_result, next_EX.reg_data2);
    }

    // -------- Instruction Decode Stage --------
    // If stalling, keep ID stage frozen (don't advance)
    if (hazard.stall) {
        // Keep ID stage unchanged
        next_ID = ID;
        printf("[ID]  **STALLED - REPEATING CURRENT INSTRUCTION**\n");
    } else if (hazard.flush_ID) {
        // Insert bubble in ID stage
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
        printf("[ID]  **BUBBLE INSERTED (FLUSH)**\n");
    } else {
        next_ID.pc = IF.pc;
        uint16_t instr16_ID = IF.instr;

        // Debug decode bits
        uint16_t bits_15_13 = (instr16_ID >> 13) & 0x7;
        uint16_t bits_15_12 = (instr16_ID >> 12) & 0xF;
        uint16_t bits_15_11 = (instr16_ID >> 11) & 0x1F;
        uint16_t bits_15_10 = (instr16_ID >> 10) & 0x3F;
        uint16_t bits_15_9  = (instr16_ID >> 9) & 0x7F;
        uint16_t bits_15_8  = (instr16_ID >> 8) & 0xFF;
        uint16_t bits_15_6  = (instr16_ID >> 6) & 0x3FF;
        
        printf("[DECODE DEBUG] instr=0x%04X | bits_15_13=0x%X | bits_15_12=0x%X | bits_15_11=0x%X | bits_15_10=0x%X | bits_15_9=0x%X | bits_15_8=0x%X | bits_15_6=0x%X\n",
               instr16_ID, bits_15_13, bits_15_12, bits_15_11, bits_15_10, bits_15_9, bits_15_8, bits_15_6);

        // Check if this halfword starts a 32-bit instruction
        int is32bit = is_32bit_thumb(instr16_ID);
        decode_result_t dres;
        if (is32bit) {
            // Fetch the next halfword
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
            // Normal 16-bit Thumb instruction
            next_ID.instr = instr16_ID;

            dres = decode_thumb16_instruction(instr16_ID);
        }

        if (!dres.valid) {
            // Unknown/invalid instruction
            next_ID.opcode = THUMB_INVALID;
            next_ID.rd = 0;
            next_ID.rs1 = 0;
            next_ID.rs2 = 0;
            next_ID.immediate_flag = 0;
            next_ID.imm_value = 0;
            next_ID.reg_data1 = 0;
            next_ID.reg_data2 = 0;
        } else {
            // Fill ID stage with decoded values
            next_ID.opcode = dres.operation;
            next_ID.rd     = dres.rd;
            next_ID.rs1    = dres.rs1;
            next_ID.rs2    = dres.rs2;
            next_ID.immediate_flag = dres.immediate_flag;
            next_ID.imm_value      = dres.imm_value;

            // Read operands from register file
            next_ID.reg_data1 = regfile_read(dres.rs1, &core_regs);

            if (dres.immediate_flag) {
                next_ID.reg_data2 = dres.imm_value;
            } else {
                next_ID.reg_data2 = regfile_read(dres.rs2, &core_regs);
            }
        }

        // -------- DEBUG STATEMENT for ID stage --------
        printf("[ID]  instr16=0x%04X | is32bit=%d\n", instr16_ID, is32bit);

        if (is32bit) {
            printf("     full_instr=0x%08X \n", next_ID.instr);
        } else {
            printf("     16-bit instr=0x%04X \n", next_ID.instr);
        }

        printf("     Decoded: opcode=%d, rd=%d, rs1=%d, rs2=%d, imm_flag=%d, imm=0x%08X\n",
               next_ID.opcode, next_ID.rd, next_ID.rs1, next_ID.rs2,
               next_ID.immediate_flag, next_ID.imm_value);
    }

    // -------- Instruction Fetch Stage --------
    // If stalling, keep IF stage frozen (don't fetch new instruction)
    if (hazard.stall) {
        // Keep IF stage unchanged
        next_IF = IF;
        printf("[IF]  **STALLED - NOT FETCHING NEW INSTRUCTION**\n");
    } else {
        // IF stage: fetch 16-bit Thumb instruction
        uint32_t word_index = IF.pc >> 1;   // divide by 2: 2 halfwords per 32-bit word
        uint32_t word = instr_mem[word_index];  // read full 32-bit word from DDR

        uint16_t instr16;
        if ((IF.pc & 1) == 0) {
            // Even halfword → lower 16 bits
            instr16 = word & 0xFFFF;
        } else {
            // odd halfword → upper 16 bits
            instr16 = (word >> 16) & 0xFFFF;
        }

        // pass instruction to ID stage
        next_IF.instr = instr16;

        // Increment PC
        next_IF.pc = IF.pc + 1;

        // update PC in regfile in bytes
        regfile_set_pc(OS_START_ADDR + next_IF.pc * 2, &core_regs);

        printf("[IF]  pc=%d (halfword) | word_index=%d | instr16=0x%04X | next_pc=%d | regfile_PC=0x%08X\n",
               IF.pc, word_index, instr16, next_IF.pc, regfile_get_pc(&core_regs));
    }

    // -------- Update WB Stage --------
    next_WB.opcode = MEM.opcode;
    next_WB.rd = MEM.rd;
    next_WB.write_data = MEM.mem_data;

    // -------- Commit all stage updates --------
    IF = next_IF;
    ID = next_ID;
    EX = next_EX;
    MEM = next_MEM;
    WB = next_WB;

    // -------- Update debug output --------
    // Output general-purpose registers R0-R12
    for(int i = 0; i < 13; i++) {
        reg_out[i] = core_regs.gpr[i];
    }
    
    // Output special registers
    reg_out[13] = regfile_get_sp(&core_regs);    // Current stack pointer
    reg_out[14] = core_regs.lr;                  // Link register
    reg_out[15] = regfile_get_pc(&core_regs);    // Program counter

    printf("[REGFILE] R0-R12:\n");
    for(int i = 0; i < 13; i++) {
        printf(" R%-2d=0x%08X", i, reg_out[i]);
        if ((i+1) % 4 == 0) printf("\n");
    }
    printf(" SP=0x%08X | LR=0x%08X | PC=0x%08X\n",
           reg_out[13], reg_out[14], reg_out[15]);
}