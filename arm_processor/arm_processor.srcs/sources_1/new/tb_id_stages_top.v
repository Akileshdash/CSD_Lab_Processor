`timescale 1ns/1ps
module tb_id_stages_top;

  reg  [15:0] instr;
  wire [2:0]  rd, rs, rn;
  wire [31:0] imm32;
  wire [4:0]  shamt5;
  wire [4:0]  alu_op;
  wire        reg_write, flag_write, srcB_from_imm, valid;

  // Instantiate the DUT
  id_stages_top uut (
    .instr(instr),
    .rd(rd), .rs(rs), .rn(rn),
    .imm32(imm32), .shamt5(shamt5),
    .alu_op(alu_op), .reg_write(reg_write),
    .flag_write(flag_write), .srcB_from_imm(srcB_from_imm),
    .valid(valid)
  );

  initial begin
    $display("=== ID Stages Top Test ===");

    // Test 1: ADD (example encoding, depends on your decoder spec!)
    instr = 16'b0000_000_001_010_011;  
    #10;
    $display("ADD: instr=%b rd=%d rs=%d rn=%d alu_op=%d reg_write=%b flag_write=%b imm32=%h shamt5=%d valid=%b",
             instr, rd, rs, rn, alu_op, reg_write, flag_write, imm32, shamt5, valid);

    // Test 2: SUB
    instr = 16'b0001_000_001_100_101;
    #10;
    $display("SUB: instr=%b rd=%d rs=%d rn=%d alu_op=%d reg_write=%b flag_write=%b imm32=%h shamt5=%d valid=%b",
             instr, rd, rs, rn, alu_op, reg_write, flag_write, imm32, shamt5, valid);

    // Test 3: MOV with immediate
    instr = 16'b0010_000_1111_1111;  // imm8 = 0xFF
    #10;
    $display("MOV: instr=%b rd=%d alu_op=%d reg_write=%b imm32=%h valid=%b",
             instr, rd, alu_op, reg_write, imm32, valid);

    // Test 4: CMP
    instr = 16'b0011_000_001_000_001;
    #10;
    $display("CMP: instr=%b rs=%d rn=%d alu_op=%d reg_write=%b flag_write=%b valid=%b",
             instr, rs, rn, alu_op, reg_write, flag_write, valid);

    // Test 5: MUL
    instr = 16'b0100_000_010_011_100;
    #10;
    $display("MUL: instr=%b rd=%d rs=%d rn=%d alu_op=%d reg_write=%b flag_write=%b valid=%b",
             instr, rd, rs, rn, alu_op, reg_write, flag_write, valid);

    $finish;
  end

endmodule
