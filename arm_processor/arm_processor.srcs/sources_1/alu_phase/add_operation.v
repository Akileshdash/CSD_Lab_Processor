`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: add_operation
// Description: Addition operation module for ARM ALU
// Operation: result = operand_a + operand_b
//////////////////////////////////////////////////////////////////////////////////

module add_operation(
    input  wire [31:0] operand_a,    // First operand
    input  wire [31:0] operand_b,    // Second operand
    
    output wire [31:0] result,       // Addition result
    output wire        carry_out,    // Carry flag
    output wire        overflow      // Overflow flag
);

// 33-bit addition to capture carry
wire [32:0] add_result;

assign add_result = {1'b0, operand_a} + {1'b0, operand_b};
assign result     = add_result[31:0];
assign carry_out  = add_result[32];

// Signed overflow detection:
// Overflow occurs when both operands have same sign but result has different sign
assign overflow = (~operand_a[31] & ~operand_b[31] & result[31]) |  // pos + pos = neg
                  (operand_a[31] & operand_b[31] & ~result[31]);    // neg + neg = pos

endmodule