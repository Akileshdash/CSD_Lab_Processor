#include "processor.h"
#include "stages.h"
#include "alu.h"
#include "execute.h"
#include "decode.h"
#include "regfile.h"

static inline int thumb_writes_register(thumb_operation_t op) {
    switch (op) {
        // Arithmetic / data-processing (that write Rd)
        case THUMB_MOV_REG:
        case THUMB_MOV_IMM:
        case THUMB_ADD_REG:
        case THUMB_ADD_IMM3:
        case THUMB_ADD_IMM8:
        case THUMB_SUB_REG:
        case THUMB_SUB_IMM3:
        case THUMB_SUB_IMM8:
        case THUMB_AND:
        case THUMB_EOR:
        case THUMB_ORR:
        case THUMB_BIC:
        case THUMB_MVN:
        case THUMB_LSL_IMM:
        case THUMB_LSR_IMM:
        case THUMB_ASR_IMM:
        case THUMB_LSL_REG:
        case THUMB_LSR_REG:
        case THUMB_ASR_REG:
        case THUMB_ADC:
        case THUMB_SBC:
        case THUMB_ROR:
        case THUMB_RSB:
            return 1;

        // Memory loads
        case THUMB_LDR_IMM:
        case THUMB_LDR_REG:
        case THUMB_LDRB_IMM:
        case THUMB_LDRB_REG:
        case THUMB_LDRH_IMM:
        case THUMB_LDRH_REG:
        case THUMB_LDRSB_REG:
        case THUMB_LDRSH_REG:
        case THUMB_LDR_LIT:
            return 1;

        // Special high register ops
        case THUMB_MOV_HIGH:
        case THUMB_ADD_HIGH:
            return 1;

        // Branches / PC-affecting ops handled separately in WB stage
        case THUMB_B:
        case THUMB_BCC:
        case THUMB_BX:
        case THUMB_BLX_REG:
        case THUMB_POP:
            return 0;

        default:
            return 0;
    }
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
        uint32_t reset_vector = instr_mem[1];  // Reset vector from address 0x00000004
        
        regfile_init(&core_regs, reset_vector, msp_init);

        // // Set initial PC for pipeline
        // IF.pc = regfile_get_pc(&core_regs);
        
        // **Convert PC from byte address to word index for IF stage**
        IF.pc = regfile_get_pc(&core_regs) >> 2;  
        return;
    }

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
        case THUMB_BCC:
        case THUMB_BX:
        case THUMB_BLX_REG:
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


    // -------- Memory Stage --------
    next_MEM.opcode = EX.opcode;
    next_MEM.rd = EX.rd;
    next_MEM.alu_result = EX.alu_result;
    next_MEM.mem_data = EX.alu_result; // default

    if(EX.opcode == 2) {          // LOAD
        next_MEM.mem_data = data_mem[EX.alu_result];
    } else if(EX.opcode == 3) {   // STORE
        data_mem[EX.alu_result] = EX.reg_data2;
    }

    // -------- Execute Stage -------
    EX_input_t ex_input;
    ex_input.opcode = ID.opcode;
    ex_input.rd = ID.rd;
    ex_input.reg_data1 = ID.reg_data1;

    // Use immediate if the instruction has it
    if(ID.immediate_flag) {
        ex_input.reg_data2 = ID.imm_value;
    } else {
        ex_input.reg_data2 = ID.reg_data2;
    }

    EX_output_t ex_output = execute(ex_input, &core_regs);

    next_EX.opcode = ID.opcode;
    next_EX.rd = ID.rd;
    next_EX.reg_data2 = ex_input.reg_data2;  // pass along for memory/store
    next_EX.alu_result = ex_output.alu_result;

    // -------- Instruction Decode Stage --------
    next_ID.pc = IF.pc;
    next_ID.instr = IF.instr;

    // Use our Thumb instruction decoder
    decode_result_t dres = decode_thumb_instruction(IF.instr);

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

    // -------- Instruction Fetch Stage --------
    
    next_IF.instr = instr_mem[IF.pc];
    next_IF.pc = IF.pc + 1;
    
    // Update PC in register file
    regfile_set_pc(next_IF.pc * 4, &core_regs);  // Convert word address to byte address

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
}