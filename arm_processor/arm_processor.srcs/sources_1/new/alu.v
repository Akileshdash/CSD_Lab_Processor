`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/30/2025 01:52:06 PM
// Design Name: 
// Module Name: alu
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

module alu(
    input wire [31:0] A,
    input wire [31:0] B,
    input wire [4:0]  shift_amt,
    input wire [2:0]  shift_type,
    input wire [4:0]  opcode,
    input wire        carry_in,
    input wire        set_flags,
    
    output reg  [31:0] result,
    output reg         N,
    output reg         Z,
    output reg         C,
    output reg         V 
);

    // ADD wires
    wire [31:0] add_res;
    wire add_carry, add_overflow;

    // SUB wires
    wire [31:0] sub_res;
    wire sub_carry, sub_overflow;

    // MOV wires
    wire [31:0] mov_res;
    wire mov_N, mov_Z;

    // CMP wires
    wire cmp_N, cmp_Z, cmp_C, cmp_V;
    
    wire [31:0] eor_res, bic_res, mvn_res, mul_res;
    wire [31:0] lsr_res, asr_res;
    wire lsr_carry, asr_carry;


    // instantiate submodules
    add_operation u_add (
        .operand_a(A),
        .operand_b(B),
        .result(add_res),
        .carry_out(add_carry),
        .overflow(add_overflow)
    );

    sub_operation u_sub (
        .operand_a(A),
        .operand_b(B),
        .result(sub_res),
        .carry_out(sub_carry),
        .overflow(sub_overflow)
    );

    cmp_operation u_cmp (
        .A(A), .B(B),
        .N(cmp_N), .Z(cmp_Z), .C(cmp_C), .V(cmp_V)
    );

    mov_operation u_mov (
        .B(B),
        .Rd(mov_res),
        .N(mov_N), .Z(mov_Z)
    );
    
    eor_operation u_eor(.A(A), .B(B), .result(eor_res));
    bic_operation u_bic(.A(A), .B(B), .result(bic_res));
    mvn_operation u_mvn(.B(B), .result(mvn_res));
    mul_operation u_mul(.A(A), .B(B), .result(mul_res));

    lsr_operation u_lsr(.value(A), .shift_amt(shift_amt), .result(lsr_res), .carry_out(lsr_carry));
    asr_operation u_asr(.value(A), .shift_amt(shift_amt), .result(asr_res), .carry_out(asr_carry));
    
    and_operation u_and(.A(A), .B(B), .result(and_res));
    orr_operation u_orr(.A(A), .B(B), .result(orr_res));
    // ALU control logic
    always @* begin
        // defaults
        result = 32'b0;
        N = 0; Z = 0; C = 0; V = 0;

        case (opcode)
            5'h0: begin // ADD
                result = add_res;
                if (set_flags) begin
                    N = result[31];
                    Z = (result == 0);
                    C = add_carry;
                    V = add_overflow;
                end
            end
            5'h1: begin // CMP
                result = A - B; // not used. can be passed to bus.
                if (set_flags) begin
                    N = cmp_N;
                    Z = cmp_Z;
                    C = cmp_C;
                    V = cmp_V;
                end
            end
            5'h2: begin // MOV
                result = mov_res;
                if (set_flags) begin
                    N = mov_N;
                    Z = mov_Z;
                    C = 0;
                    V = 0;
                end
            end
            5'h3: begin // SUB
                result = sub_res;
                if(set_flags) begin
                    N = result[31];
                    Z = (result == 0);
                    C = sub_carry;
                    V = sub_overflow;
                end
            end
                        5'h4: begin // EOR
                result = eor_res;
                if(set_flags) begin
                    N = result[31];
                    Z = (result == 0);
                end
            end

            5'h5: begin // BIC
                result = bic_res;
                if(set_flags) begin
                    N = result[31];
                    Z = (result == 0);
                end
            end

            5'h6: begin // MVN
                result = mvn_res;
                if(set_flags) begin
                    N = result[31];
                    Z = (result == 0);
                end
            end

            5'h7: begin // MUL
                result = mul_res;
                if(set_flags) begin
                    N = result[31];
                    Z = (result == 0);
                end
            end

            5'h8: begin // LSR
                result = lsr_res;
                if(set_flags) begin
                    N = result[31];
                    Z = (result == 0);
                    C = lsr_carry;
                end
            end

            5'h9: begin // ASR
                result = asr_res;
                if(set_flags) begin
                    N = result[31];
                    Z = (result == 0);
                    C = asr_carry;
                end
            end
            5'hA: begin // AND
                result = and_res;
                if(set_flags) begin
                    N = result[31];
                    Z = (result == 0);
                end
            end
            5'hB: begin // ORR
                result = orr_res;
                if(set_flags) begin
                    N = result[31];
                    Z = (result == 0);
                end
            end
            default: begin
                result = 32'hDEADBEEF; // debug value
            end
        endcase
    end

endmodule

