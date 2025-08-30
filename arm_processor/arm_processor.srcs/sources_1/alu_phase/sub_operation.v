`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/30/2025
// Design Name: ARM ALU Subtraction
// Module Name: sub_operation
// Project Name: ARM Processor
// Target Devices: 
// Tool Versions: 
// Description: Subtraction operation module for ARM ALU
//              result = operand_a - operand_b
//
// ARM Convention for flags:
//   - carry_out : 1 = no borrow, 0 = borrow occurred
//   - overflow  : 1 = signed overflow occurred
//
// Dependencies: None
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module sub_operation(
    input  wire [31:0] operand_a,    // Minuend (first operand)
    input  wire [31:0] operand_b,    // Subtrahend (second operand)
    
    output wire [31:0] result,       // Subtraction result
    output wire        carry_out,    // No-borrow flag (ARM convention)
    output wire        overflow      // Overflow flag
);

    // Perform subtraction with extended precision
    wire [32:0] sub_result;
    assign sub_result = {1'b0, operand_a} - {1'b0, operand_b};

    // Subtraction result
    assign result = sub_result[31:0];

    // Carry flag (ARM defines it as "NOT borrow")
    // Carry = 1 when no borrow occurs
    assign carry_out = ~sub_result[32];

    // Signed overflow detection
    assign overflow = (operand_a[31] ^ operand_b[31]) & 
                      (operand_a[31] ^ result[31]);

endmodule
