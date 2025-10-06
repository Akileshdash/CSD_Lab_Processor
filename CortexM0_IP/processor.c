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

static int cycle = 0;

int is_32bit_thumb(uint16_t hw) {
    return ((hw & 0xF800) == 0xE800) ||   // 11101
           ((hw & 0xF800) == 0xF000) ||   // 11110
           ((hw & 0xF800) == 0xF800);     // 11111
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

        // Reset MEM stage
        MEM.opcode = THUMB_INVALID;
        MEM.alu_result = 0;
        MEM.mem_data = 0;
        MEM.rd = 0;

        // Reset WB stage
        WB.opcode = THUMB_INVALID;
        WB.write_data = 0;
        WB.rd = 0;
        
        // Initialize core registers according to ARM spec
        // MSP loaded from address 0x00000000, PC from 0x00000004
        uint32_t msp_init = data_mem[0];  // Stack pointer initial value
        
        // Initialize PC and SP
        regfile_init(&core_regs, OS_START_ADDR, msp_init);

        // // Set initial PC for pipeline
        // IF.pc = regfile_get_pc(&core_regs);
        
        // **Convert PC from byte address to word index for IF stage**
        IF.pc = regfile_get_pc(&core_regs) >> 2;  
        return;
    }

    cycle++;
    printf("\n================ Cycle %d ==================\n", cycle);

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

    printf("[WB]  opcode=%d | rd=%d | write_data=0x%08X\n",next_WB.opcode, next_WB.rd, next_WB.write_data);

    // -------- Memory Stage --------
    next_MEM.opcode = EX.opcode;
    next_MEM.rd = EX.rd;
    next_MEM.alu_result = EX.alu_result;
    next_MEM.mem_data = EX.alu_result; // default value
    next_MEM.link = EX.link;           // forward link register for BL/BLX

    // ---------- Load instructions ----------
    if(EX.opcode == THUMB_LDR_IMM  || EX.opcode == THUMB_LDR_REG  ||
    EX.opcode == THUMB_LDRB_IMM || EX.opcode == THUMB_LDRB_REG ||
    EX.opcode == THUMB_LDRH_IMM || EX.opcode == THUMB_LDRH_REG ||
    EX.opcode == THUMB_LDRSB_REG|| EX.opcode == THUMB_LDRSH_REG ||
    EX.opcode == THUMB_LDR_LIT) 
    {
        next_MEM.mem_data = data_mem[EX.alu_result]; // read from memory
    }

    // ---------- Store instructions ----------
    else if(EX.opcode == THUMB_STR_IMM  || EX.opcode == THUMB_STR_REG  ||
            EX.opcode == THUMB_STRB_IMM || EX.opcode == THUMB_STRB_REG ||
            EX.opcode == THUMB_STRH_IMM || EX.opcode == THUMB_STRH_REG ||
            EX.opcode == THUMB_STR_SP) 
    {
        data_mem[EX.alu_result] = EX.reg_data2; // write to memory
    }

    // ---------- Branch with Link (BL) ----------
    else if (EX.opcode == THUMB_BL)
    {
        next_MEM.mem_data = EX.alu_result; // target PC
        next_MEM.link = EX.link;           // return address for LR
    }

    // ---------- Other Branches ----------
    else if (EX.opcode == THUMB_B || EX.opcode == THUMB_B_COND || EX.opcode == THUMB_BX)
    {
        next_MEM.mem_data = EX.alu_result; // branch target
        next_MEM.link = 0;                 // no link register update
    }

    printf("[MEM] opcode=%d | rd=%d | alu_result=0x%08X | mem_data=0x%08X | link=0x%08X\n",
        next_MEM.opcode, next_MEM.rd, next_MEM.alu_result, next_MEM.mem_data, next_MEM.link);

    // -------- Execute Stage -------
    EX_input_t ex_input;
    ex_input.opcode = ID.opcode;
    ex_input.rd = ID.rd;
    ex_input.reg_data1 = ID.reg_data1;

    printf("[EX PROCESSOR DEBUG] ADD | reg_data1=0x%08X | reg_data2=0x%08X | imm_flag=%d\n",
        ex_input.reg_data1, ex_input.reg_data2,ID.immediate_flag);

    if(ID.immediate_flag) {
        ex_input.reg_data2 = ID.imm_value;
    } else {
        ex_input.reg_data2 = ID.reg_data2;
    }

    printf("[EX PROCESSOR DEBUG] ADD | reg_data1=0x%08X | reg_data2=0x%08X \n",
        ex_input.reg_data1, ex_input.reg_data2);

    EX_output_t ex_output = execute(ex_input, &core_regs);

    next_EX.opcode = ID.opcode;
    next_EX.rd = ID.rd;
    next_EX.reg_data2 = ex_input.reg_data2;  // pass along for memory/store
    next_EX.alu_result = ex_output.alu_result;
    next_EX.link = ex_output.link;           // new

    printf("[EX]  opcode=%d | rd=%d | alu_result=0x%08X | reg_data2=0x%08X\n",
        next_EX.opcode, next_EX.rd, next_EX.alu_result, next_EX.reg_data2);


    // -------- Instruction Decode Stage --------
    next_ID.pc = IF.pc;
    uint16_t instr16_ID = IF.instr;

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
    // Use our Thumb instruction decoder
    // decode_result_t dres = decode_thumb_instruction(IF.instr);

    if (!dres.valid) {
        // Unknown/invalid instruction — you might want to stall, trap, or NOP
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
    printf("[ID]  instr16=0x%04X | is32bit=%d\n",
            instr16_ID, is32bit);

    if (is32bit) {
        printf("     full_instr=0x%08X \n", next_ID.instr);
    } else {
        printf("     16-bit instr=0x%04X \n", next_ID.instr);
    }

    printf("     Decoded: opcode=%d, rd=%d, rs1=%d, rs2=%d, imm_flag=%d, imm=0x%08X\n",
           next_ID.opcode, next_ID.rd, next_ID.rs1, next_ID.rs2,
           next_ID.immediate_flag, next_ID.imm_value);


    // -------- Instruction Fetch Stage --------

    // IF stage: fetch 16-bit Thumb instruction
    uint32_t word_index = IF.pc >> 1;   // divide by 2: 2 halfwords per 32-bit word
    uint32_t word = instr_mem[word_index];  // read full 32-bit word from DDR

    uint16_t instr16;
    if ((IF.pc & 1) == 0) {
        // Even halfword → next halfword is upper 16 bits of the same word
        instr16 = word & 0xFFFF;
    } else {
        // odd halfword → upper 16 bits
        instr16 = (word >> 16) & 0xFFFF;
    }

    // pass instruction to ID stage
    next_IF.instr = instr16;

    // ---- Use override from ID if available ----
    next_IF.pc = IF.pc + 1;

    // update PC in regfile in bytes
    regfile_set_pc(OS_START_ADDR + next_IF.pc * 2, &core_regs);

    //   --- DEBUG STATEMENT ---
    printf("[IF]  pc=%d (halfword) | word_index=%d | instr16=0x%04X | next_pc=%d | regfile_PC=0x%08X\n",
           IF.pc, word_index, instr16, next_IF.pc, regfile_get_pc(&core_regs));

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
    
    // Additional debug outputs (if reg_out array is large enough)
    // reg_out[16] = regfile_get_psr(&core_regs);   // Program Status Register
    // reg_out[17] = regfile_get_control(&core_regs); // CONTROL register
    // reg_out[18] = core_regs.primask;             // PRIMASK register

    printf("[REGFILE] R0-R12:\n");
    for(int i = 0; i < 13; i++) {
        printf(" R%-2d=0x%08X", i, reg_out[i]);
        if ((i+1) % 4 == 0) printf("\n");
    }
    printf(" SP=0x%08X | LR=0x%08X | PC=0x%08X\n",
           reg_out[13], reg_out[14], reg_out[15]);

}