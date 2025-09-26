#include "decode.h"
#include <stdint.h>

// helper: check if opcode is immediate type (adjust based on your ISA)
static int is_immediate(uint8_t opcode) {
    // Example: suppose opcodes 0x08–0x0F are immediate type
    return (opcode >= 0x08 && opcode <= 0x0F);
}

ID_output_t decode(ID_input_t IF, cortex_m0_registers_t*core_regs) {
    ID_output_t ID;

    ID.pc     = IF.pc;
    ID.instr  = IF.instr & 0xFFFF;       // ensure 16-bit
    ID.opcode = (IF.instr >> 9) & 0x1F;  // bits 13:9

    // Default init
    ID.rd  = 0;
    ID.rs1 = 0;
    ID.rs2 = 0;
    ID.immediate_flag = 0;
    ID.imm_value = 0;

    // Decode based on opcode type
    if (is_immediate(ID.opcode)) {
        // Example I-type format:
        // [13:9] opcode | [8:6] rd | [5:3] rs1 | [2:0] imm3
        ID.rd  = (IF.instr >> 6) & 0x7;
        ID.rs1 = (IF.instr >> 3) & 0x7;
        ID.imm_value = (int16_t)(IF.instr & 0x7); // sign-extend if needed
        ID.immediate_flag = 1;
    } else {
        // Example R-type format:
        // [13:9] opcode | [8:6] rd | [5:3] rs1 | [2:0] rs2
        ID.rd  = (IF.instr >> 6) & 0x7;
        ID.rs1 = (IF.instr >> 3) & 0x7;
        ID.rs2 = (IF.instr >> 0) & 0x7;
    }

    // Register reads
    ID.reg_data1 = regfile_read(ID.rs1, core_regs);

    if (ID.immediate_flag) {
        ID.reg_data2 = ID.imm_value;
    } else {
        ID.reg_data2 = regfile_read(ID.rs2, core_regs);
    }

    return ID;
}
