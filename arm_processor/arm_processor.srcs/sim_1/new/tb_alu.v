`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/30/2025 03:35:49 PM
// Design Name: 
// Module Name: tb_alu
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


module tb_alu;

    // DUT inputs
    reg  [31:0] A, B;
    reg  [4:0]  shift_amt;
    reg  [2:0]  shift_type;
    reg  [4:0]  opcode;
    reg         carry_in;
    reg         set_flags;

    // DUT outputs
    wire [31:0] result;
    wire        N, Z, C, V;

    // Instantiate the ALU
    alu dut (
        .A(A),
        .B(B),
        .shift_amt(shift_amt),
        .shift_type(shift_type),
        .opcode(opcode),
        .carry_in(carry_in),
        .set_flags(set_flags),
        .result(result),
        .N(N), .Z(Z), .C(C), .V(V)
    );

    initial begin
        // Initialize
        A = 0; B = 0;
        shift_amt = 0; shift_type = 0;
        opcode = 0; carry_in = 0; set_flags = 1;

        #10;

        // --- ADD tests ---
        A = 32'h0000_0001; B = 32'h0000_0001; opcode = 5'h0; #10;
        $display("ADD: %h + %h = %h | N=%b Z=%b C=%b V=%b",
                  A, B, result, N, Z, C, V);

        A = 32'h7FFF_FFFF; B = 32'h0000_0001; opcode = 5'h0; #10;
        $display("ADD Overflow: %h + %h = %h | N=%b Z=%b C=%b V=%b",
                  A, B, result, N, Z, C, V);

        // --- CMP tests ---
        A = 32'h0000_0005; B = 32'h0000_0005; opcode = 5'h1; #10;
        $display("CMP Equal: %h - %h | N=%b Z=%b C=%b V=%b",
                  A, B, N, Z, C, V);

        A = 32'h0000_0002; B = 32'h0000_0005; opcode = 5'h1; #10;
        $display("CMP Less: %h - %h | N=%b Z=%b C=%b V=%b",
                  A, B, N, Z, C, V);

        // --- MOV tests ---
        A = 32'h0; B = 32'hDEADBEEF; opcode = 5'h2; #10;
        $display("MOV: B=%h -> result=%h | N=%b Z=%b",
                  B, result, N, Z);

        // --- SUB tests ---
        A = 32'h0000_0005; B = 32'h0000_0003; opcode = 5'h3; #10;
        $display("SUB: %h - %h = %h | N=%b Z=%b C=%b V=%b",
                  A, B, result, N, Z, C, V);

        A = 32'h0000_0003; B = 32'h0000_0005; opcode = 5'h3; #10;
        $display("SUB Negative: %h - %h = %h | N=%b Z=%b C=%b V=%b",
                  A, B, result, N, Z, C, V);

        // --- LSR tests ---
        A = 32'h0; B = 32'hF000_0000; shift_amt = 4; shift_type = 3'b001; opcode = 5'h4; #10;
        $display("LSR: %h >> %0d = %h | C=%b", B, shift_amt, result, C);

        // --- ASR tests ---
        A = 32'h0; B = 32'hF000_0000; shift_amt = 4; shift_type = 3'b010; opcode = 5'h5; #10;
        $display("ASR: %h >>> %0d = %h | C=%b", B, shift_amt, result, C);

        // --- EOR tests ---
        A = 32'hAAAA_FFFF; B = 32'h5555_0000; opcode = 5'h6; #10;
        $display("EOR: %h ^ %h = %h | N=%b Z=%b", A, B, result, N, Z);

        // --- BIC tests ---
        A = 32'hFFFF_0000; B = 32'h00FF_FFFF; opcode = 5'h7; #10;
        $display("BIC: %h & ~%h = %h | N=%b Z=%b", A, B, result, N, Z);

        // --- MVN tests ---
        A = 32'h0; B = 32'h1234_ABCD; opcode = 5'h8; #10;
        $display("MVN: ~%h = %h | N=%b Z=%b", B, result, N, Z);

        // --- MUL tests ---
        A = 32'h0000_000A; B = 32'h0000_000B; opcode = 5'h9; #10;
        $display("MUL: %h * %h = %h | N=%b Z=%b", A, B, result, N, Z);

        A = 32'hFFFF_FFFF; B = 32'h2; opcode = 5'h9; #10;
        $display("MUL Negative: %h * %h = %h | N=%b Z=%b", A, B, result, N, Z);

        // --- ORR tests ---
        A = 32'hAAAA_0000; B = 32'h5555_FFFF; opcode = 5'hA; #10;
        $display("ORR: %h | %h = %h | N=%b Z=%b", A, B, result, N, Z);

        A = 32'h0000_0000; B = 32'h0000_0000; opcode = 5'hA; #10;
        $display("ORR Zero: %h | %h = %h | N=%b Z=%b", A, B, result, N, Z);

        A = 32'h8000_0000; B = 32'h0000_0001; opcode = 5'hA; #10;
        $display("ORR Mixed: %h | %h = %h | N=%b Z=%b", A, B, result, N, Z);

        // Finish
        $display("All tests complete.");
        #20 $finish;
    end

endmodule
