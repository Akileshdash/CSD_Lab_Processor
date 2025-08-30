`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/30/2025 03:56:35 PM
// Design Name: 
// Module Name: asr_operation
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module asr_operation (
    input  wire [31:0] value,
    input  wire [4:0]  shift_amt,
    output wire [31:0] result,
    output wire        carry_out
);
    assign {carry_out, result} = (shift_amt == 0) ? {1'b0, value} : {value[shift_amt-1], $signed(value) >>> shift_amt};
endmodule

