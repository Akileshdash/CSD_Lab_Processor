`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/30/2025 03:57:18 PM
// Design Name: 
// Module Name: eor_operation
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


module eor_operation (
    input  wire [31:0] A,
    input  wire [31:0] B,
    output wire [31:0] result
);
    assign result = A ^ B;
endmodule

