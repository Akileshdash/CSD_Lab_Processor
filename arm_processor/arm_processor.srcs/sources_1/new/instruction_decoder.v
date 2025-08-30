// id_stage/instruction_decoder.v
`timescale 1ns/1ps

module instruction_decoder (
    input  [15:0] instr,

    // Register specifiers
    output reg [2:0] rd,
    output reg [2:0] rs,
    output reg [2:0] rn,

    // Raw fields
    output reg [4:0] imm5,
    output reg [7:0] imm8,

    // Classification
    output reg [4:0] dec_alu_op,
    output reg [1:0] imm_sel,
    output reg       is_valid,
    output reg       is_reg_form
);

    // ALU op encodings
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

    // Convenience slices
    wire [2:0] rd_001      = instr[10:8];
    wire [7:0] imm8_w      = instr[7:0];
    wire [2:0] rd_000      = instr[2:0];
    wire [2:0] rs_000      = instr[5:3];
    wire [4:0] sh_imm      = instr[10:6];
    wire [3:0] op_010000   = instr[9:6];
    wire       is_shift_imm = (instr[15:13] == 3'b000);
    wire       is_001_group = (instr[15:13] == 3'b001);
    wire       is_dp_reg    = (instr[15:10] == 6'b010000);
    wire [1:0] op_001       = instr[12:11];

    always @* begin
        // Default values
        rd         = 3'd0;
        rs         = 3'd0;
        rn         = 3'd0;
        imm5       = 5'd0;
        imm8       = 8'd0;
        dec_alu_op = ALU_INVALID;
        imm_sel    = IMM_NONE;
        is_valid   = 1'b0;
        is_reg_form = 1'b0;

        // Shift immediate instructions
        if (is_shift_imm) begin
            rd         = rd_000;
            rs         = rs_000;
            imm5       = sh_imm;
            imm_sel    = IMM_SHIFT5;
            is_valid   = 1'b1;
            is_reg_form = 1'b1;

            case (instr[12:11])
                2'b00: dec_alu_op = ALU_LSL;
                2'b01: dec_alu_op = ALU_LSR;
                2'b10: dec_alu_op = ALU_ASR;
                default: is_valid = 1'b0;
            endcase
        end

        // Immediate instructions
        else if (is_001_group) begin
            rd         = rd_001;
            rn         = rd_001;
            imm8       = imm8_w;
            imm_sel    = IMM_IMM8;
            is_valid   = 1'b1;

            case (op_001)
                2'b00: dec_alu_op = ALU_MOV;
                2'b01: dec_alu_op = ALU_CMP;
                2'b10: dec_alu_op = ALU_ADD;
                2'b11: dec_alu_op = ALU_SUB;
            endcase
        end

        // Data processing (register) instructions
        else if (is_dp_reg) begin
            rd         = rd_000;
            rs         = rs_000;
            is_valid   = 1'b1;
            is_reg_form = 1'b1;

            case (op_010000)
                4'b0000: dec_alu_op = ALU_AND;
                4'b0001: dec_alu_op = ALU_EOR;
                4'b1000: dec_alu_op = ALU_TST;
                4'b1010: dec_alu_op = ALU_CMP;
                4'b1100: dec_alu_op = ALU_ORR;
                4'b1101: dec_alu_op = ALU_MUL;
                4'b1110: dec_alu_op = ALU_BIC;
                4'b1111: dec_alu_op = ALU_MVN;
                default: is_valid   = 1'b0;
            endcase
        end
    end

endmodule
