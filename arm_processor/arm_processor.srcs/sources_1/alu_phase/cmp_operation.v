//`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////////
//// Company: 
//// Engineer: 
//// 
//// Create Date: 08/30/2025 12:44:12 PM
//// Design Name: 
//// Module Name: cmp_operation
//// Project Name: 
//// Target Devices: 
//// Tool Versions: 
//// Description: 
//// 
//// Dependencies: 
//// 
//// Revision:
//// Revision 0.01 - File Created
//// Additional Comments:
//// 
////////////////////////////////////////////////////////////////////////////////////


//module cmp_operation(

//    );
//endmodule
module cmp_operation (
    input  [31:0] A, B,        // operands
    output        N, Z, C, V   // flags
);
    wire [31:0] result;
    wire cout;

    // subtraction
    assign {cout, result} = A - B;

    // flags
    assign N = result[31];             // Negative flag
    assign Z = (result == 0);          // Zero flag
    assign C = ~cout;                  // Carry flag (in SUB = NOT borrow)
    assign V = (A[31] ^ B[31]) & (A[31] ^ result[31]);  // Overflow
endmodule
