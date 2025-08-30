// id_stages/id_stages_top.v
`timescale 1ns/1ps

module id_stages_top (
    input  [15:0] instr,
    output [2:0]  rd,
    output [2:0]  rs,
    output [2:0]  rn,
    output [31:0] imm32,
    output [4:0]  shamt5,
    output [4:0]  alu_op,
    output        reg_write,
    output        flag_write,
    output        srcB_from_imm,
    output        valid
);

    // Internal wires
    wire [4:0] dec_alu_op;
    wire [1:0] dec_imm_sel;
    wire       is_reg_form;
    wire [4:0] w_imm5;
    wire [7:0] w_imm8;
    wire [1:0] imm_type;

    // Instruction Decoder
    instruction_decoder u_dec (
        .instr       (instr),
        .rd          (rd),
        .rs          (rs),
        .rn          (rn),
        .imm5        (w_imm5),
        .imm8        (w_imm8),
        .dec_alu_op  (dec_alu_op),
        .imm_sel     (dec_imm_sel),
        .is_valid    (valid),
        .is_reg_form (is_reg_form)
    );

    // Control Unit
    control_unit u_ctl (
        .dec_alu_op     (dec_alu_op),
        .imm_sel        (dec_imm_sel),
        .is_reg_form    (is_reg_form),
        .alu_op         (alu_op),
        .reg_write      (reg_write),
        .flag_write     (flag_write),
        .srcB_from_imm  (srcB_from_imm),
        .imm_type       (imm_type)
    );

    // Immediate Generator
    immediate_generator u_imm (
        .instr    (instr),
        .imm_type (imm_type),
        .imm32    (imm32),
        .shamt5   (shamt5)
    );

endmodule
