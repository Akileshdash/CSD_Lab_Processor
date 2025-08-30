// id_stage/immediate_generator.v
`timescale 1ns/1ps

module immediate_generator (
    input  [15:0] instr,
    input  [1:0]  imm_type,
    output reg [31:0] imm32,
    output reg [4:0]  shamt5
);

    // Immediate selection types
    localparam [1:0]
        IMM_NONE   = 2'd0,
        IMM_IMM8   = 2'd1,
        IMM_SHIFT5 = 2'd2;

    // Extracted fields
    wire [7:0] imm8 = instr[7:0];
    wire [4:0] imm5 = instr[10:6];

    always @* begin
        // Defaults
        imm32  = 32'd0;
        shamt5 = 5'd0;

        case (imm_type)
            IMM_IMM8:   imm32  = {24'd0, imm8}; // Zero-extend 8-bit immediate
            IMM_SHIFT5: shamt5 = imm5;          // Shift amount
        endcase
    end

endmodule
