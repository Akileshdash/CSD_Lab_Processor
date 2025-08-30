`timescale 1ns/1ps
module tb_immediate_generator;

  reg  [15:0] instr;
  reg  [1:0]  imm_type;
  wire [31:0] imm32;
  wire [4:0]  shamt5;

  // Instantiate the DUT
  immediate_generator uut (
    .instr(instr),
    .imm_type(imm_type),
    .imm32(imm32),
    .shamt5(shamt5)
  );

  initial begin
    $display("=== Immediate Generator Test ===");

    // IMM_NONE
    instr = 16'b1010_1010_1010_1010;
    imm_type = 2'd0;
    #10;
    $display("IMM_NONE -> imm32=%d shamt5=%d", imm32, shamt5);

    // IMM_IMM8
    instr = 16'b1111_0000_1010_0101; // imm8 = 0xA5
    imm_type = 2'd1;
    #10;
    $display("IMM_IMM8 -> imm32=0x%h (decimal=%d)", imm32, imm32);

    // IMM_SHIFT5
    instr = 16'b0000_0111_1100_0000; // imm5 = bits[10:6] = 11110 (30)
    imm_type = 2'd2;
    #10;
    $display("IMM_SHIFT5 -> imm32=%d shamt5=%d", imm32, shamt5);

    // Another IMM_IMM8
    instr = 16'b0000_0000_1111_1111; // imm8 = 0xFF
    imm_type = 2'd1;
    #10;
    $display("IMM_IMM8 (max) -> imm32=0x%h (decimal=%d)", imm32, imm32);

    $finish;
  end

endmodule
