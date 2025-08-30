`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/30/2025 04:28:30 PM
// Design Name: 
// Module Name: orr_operation
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

module orr_operation(
    input  [31:0] A,
    input  [31:0] B,
    output [31:0] result
);
    assign result = A | B;
endmodule
