// id_stage/control_unit.v
`timescale 1ns/1ps

module control_unit (
    input  [4:0] dec_alu_op,
    input  [1:0] imm_sel,
    input        is_reg_form,
    output reg [4:0] alu_op,
    output reg       reg_write,
    output reg       flag_write,
    output reg       srcB_from_imm,
    output reg [1:0] imm_type
);

    // ALU operation codes
    localparam [4:0]
        ALU_INVALID = 5'd0,
        ALU_ADD     = 5'd1,
        ALU_SUB     = 5'd2,
        ALU_MOV     = 5'd3,
        ALU_CMP     = 5'd4,
        ALU_TST     = 5'd5,
        ALU_AND     = 5'd6,
        ALU_ORR     = 5'd7,
        ALU_LSL     = 5'd8,
        ALU_LSR     = 5'd9,
        ALU_ASR     = 5'd10,
        ALU_EOR     = 5'd11,
        ALU_BIC     = 5'd12,
        ALU_MVN     = 5'd13,
        ALU_MUL     = 5'd14;

    // Immediate selection types
    localparam [1:0]
        IMM_NONE   = 2'd0,
        IMM_IMM8   = 2'd1,
        IMM_SHIFT5 = 2'd2;

    always @* begin
        // Default assignments
        alu_op        = dec_alu_op;
        reg_write     = 1'b0;
        flag_write    = 1'b0;
        srcB_from_imm = (imm_sel != IMM_NONE);
        imm_type      = imm_sel;

        case (dec_alu_op)
            ALU_ADD, ALU_SUB, ALU_AND, ALU_ORR,
            ALU_EOR, ALU_BIC, ALU_LSL, ALU_LSR,
            ALU_ASR, ALU_MVN, ALU_MOV: begin
                reg_write  = 1'b1;
                flag_write = 1'b1;
            end

            ALU_MUL: begin
                reg_write  = 1'b1;
                flag_write = 1'b1;
            end

            ALU_TST, ALU_CMP: begin
                reg_write  = 1'b0;
                flag_write = 1'b1;
            end
        endcase
    end

endmodule
