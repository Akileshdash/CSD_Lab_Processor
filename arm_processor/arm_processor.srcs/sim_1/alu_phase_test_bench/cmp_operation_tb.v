//`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////////
//// Company: 
//// Engineer: 
//// 
//// Create Date: 08/30/2025 12:45:07 PM
//// Design Name: 
//// Module Name: cmp_operation_tb
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


//module cmp_operation_tb(

//    );
//endmodule
`timescale 1ns/1ps
module cmp_operation_tb;
    reg  [31:0] A, B;
    wire N, Z, C, V;

    cmp_operation uut (A, B, N, Z, C, V);

    initial begin
        $monitor("Time=%0t A=%d B=%d | N=%b Z=%b C=%b V=%b",
                  $time, A, B, N, Z, C, V);

        A = 10; B = 10; #10;   // expect Z=1
        A = 15; B = 10; #10;   // expect positive result
        A = 10; B = 15; #10;   // expect negative result
        A = -5; B = 5;  #10;   // expect negative + overflow case
        $finish;
    end
endmodule
