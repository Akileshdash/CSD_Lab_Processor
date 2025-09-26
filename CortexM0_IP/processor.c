#include "processor.h"
#include "stages.h"
#include "alu.h"
#include "execute.h"
#include "decode.h"
#include "regfile.h"

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
        // Reset all pipeline stages
        IF.pc = 0;
        ID = (ID_stage){0};
        EX = (EX_stage){0};
        MEM = (MEM_stage){0};
        WB = (WB_stage){0};
        
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
    if(WB.rd != 0) {  // Don't write to R0 if it's supposed to be hardwired zero (optional)
        regfile_write(WB.rd, WB.write_data, &core_regs);
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
    next_ID.opcode = (IF.instr >> 28) & 0xF;
    next_ID.rd     = (IF.instr >> 24) & 0xF;
    next_ID.rs1    = (IF.instr >> 20) & 0xF;
    next_ID.rs2    = (IF.instr >> 16) & 0xF;

    // Determine if instruction has an immediate operand
    // Let's assume lower 16 bits hold immediate if bit 16 of instruction is 1
    next_ID.immediate_flag = ((IF.instr >> 15) & 0x1); 
    next_ID.imm_value      = IF.instr & 0xFFFF;

    // Read operand1 from register file
    next_ID.reg_data1 = regfile_read(next_ID.rs1, &core_regs);

    // Select operand2: either from register or immediate
    if(next_ID.immediate_flag) {
        next_ID.reg_data2 = next_ID.imm_value;
    } else {
        next_ID.reg_data2 = regfile_read(next_ID.rs2, &core_regs);
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