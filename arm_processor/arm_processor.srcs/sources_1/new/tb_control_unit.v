`timescale 1ns/1ps
module tb_control_unit;

  reg  [4:0] dec_alu_op;
  reg  [1:0] imm_sel;
  reg        is_reg_form;

  wire [4:0] alu_op;
  wire       reg_write;
  wire       flag_write;
  wire       srcB_from_imm;
  wire [1:0] imm_type;

  // Instantiate DUT
  control_unit uut (
    .dec_alu_op(dec_alu_op),
    .imm_sel(imm_sel),
    .is_reg_form(is_reg_form),
    .alu_op(alu_op),
    .reg_write(reg_write),
    .flag_write(flag_write),
    .srcB_from_imm(srcB_from_imm),
    .imm_type(imm_type)
  );

  initial begin
    $display("=== Control Unit Test ===");
    
    // Default inputs
    imm_sel     = 2'b00;
    is_reg_form = 1'b1;

    // Test ADD
    dec_alu_op = 5'd1; // ALU_ADD
    #10 $display("ADD: reg_write=%b alu_op=%d flag_write=%b", reg_write, alu_op, flag_write);

    // Test SUB
    dec_alu_op = 5'd2; // ALU_SUB
    #10 $display("SUB: reg_write=%b alu_op=%d flag_write=%b", reg_write, alu_op, flag_write);

    // Test MOV
    dec_alu_op = 5'd3; // ALU_MOV
    #10 $display("MOV: reg_write=%b alu_op=%d flag_write=%b", reg_write, alu_op, flag_write);

    // Test CMP
    dec_alu_op = 5'd4; // ALU_CMP
    #10 $display("CMP: reg_write=%b alu_op=%d flag_write=%b", reg_write, alu_op, flag_write);

    // Test MUL
    dec_alu_op = 5'd14; // ALU_MUL
    #10 $display("MUL: reg_write=%b alu_op=%d flag_write=%b", reg_write, alu_op, flag_write);

    $finish;
  end

endmodule
