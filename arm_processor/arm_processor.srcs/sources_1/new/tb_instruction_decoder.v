`timescale 1ns/1ps
module tb_instruction_decoder;

  reg  [15:0] instr;
  wire [2:0]  rd, rs, rn;
  wire [4:0]  imm5;
  wire [7:0]  imm8;
  wire [4:0]  dec_alu_op;
  wire [1:0]  imm_sel;
  wire        is_valid;
  wire        is_reg_form;

  // Instantiate the DUT
  instruction_decoder uut (
    .instr(instr),
    .rd(rd),
    .rs(rs),
    .rn(rn),
    .imm5(imm5),
    .imm8(imm8),
    .dec_alu_op(dec_alu_op),
    .imm_sel(imm_sel),
    .is_valid(is_valid),
    .is_reg_form(is_reg_form)
  );

  initial begin
    $display("=== Instruction Decoder Test ===");

    // Example 1: MOV immediate
    instr = 16'b0010_0000_0110_0000;
    #10;
    $display("MOV -> alu_op=%0d rd=%0d rn=%0d imm8=%0d valid=%b reg_form=%b",
             dec_alu_op, rd, rn, imm8, is_valid, is_reg_form);

    // Example 2: CMP immediate
    instr = 16'b0010_1000_0110_0001;
    #10;
    $display("CMP -> alu_op=%0d rn=%0d imm8=%0d valid=%b", 
             dec_alu_op, rn, imm8, is_valid);

    // Example 3: ADD immediate
    instr = 16'b0010_1000_0010_0011;
    #10;
    $display("ADD -> alu_op=%0d rd=%0d rn=%0d imm8=%0d", 
             dec_alu_op, rd, rn, imm8);

    // Example 4: shift with imm5
    instr = 16'b0000_0100_0010_0011;
    #10;
    $display("LSL/LSR/ASR -> alu_op=%0d rd=%0d rs=%0d imm5=%0d", 
             dec_alu_op, rd, rs, imm5);

    // Example 5: register form (AND/ORR/MUL etc.)
    instr = 16'b0100_0000_0110_0010;
    #10;
    $display("RegForm -> alu_op=%0d rd=%0d rs=%0d valid=%b", 
             dec_alu_op, rd, rs, is_valid);

    $finish;
  end

endmodule
