`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: alu_phase
// Description: Execute/ALU stage supporting LSR, ASR, EOR, BIC, MVN, MUL
//////////////////////////////////////////////////////////////////////////////////

module alu_phase(
    input  wire        clk,
    input  wire        reset,

    // Control signals
    input  wire [3:0]  opcode,           // Operation code
    input  wire [4:0]  shift_amount,     // For shift operations
    input  wire        update_flags,     // Update CPSR flags
    input  wire        enable,           // Pipeline enable

    // Data inputs
    input  wire [31:0] operand_a,        // First operand (Rn)
    input  wire [31:0] operand_b,        // Second operand (Rm)
    input  wire [31:0] operand_c,        // Third operand (unused here; reserved)

    // Current processor flags: {N,Z,C,V}
    input  wire [3:0]  flags_in,

    // Outputs
    output reg  [31:0] result,           // Registered ALU result
    output reg  [3:0]  flags_out,        // Combinational flags based on alu_result
    output reg         valid,            // Result valid pulse

    // Pipeline control
    output reg         stall             // Stall request (for MUL)
);

//////////////////////////////////////////////
// Opcodes
//////////////////////////////////////////////
localparam OP_LSR = 4'b0001;    // Logical Shift Right
localparam OP_ASR = 4'b0010;    // Arithmetic Shift Right
localparam OP_EOR = 4'b0011;    // Exclusive OR
localparam OP_BIC = 4'b0100;    // Bit Clear
localparam OP_MVN = 4'b0101;    // Move NOT
localparam OP_MUL = 4'b0110;    // Multiply

//////////////////////////////////////////////
// Flag bit positions
//////////////////////////////////////////////
localparam N_FLAG = 3;  // Negative
localparam Z_FLAG = 2;  // Zero
localparam C_FLAG = 1;  // Carry
localparam V_FLAG = 0;  // Overflow

//////////////////////////////////////////////
// Internal signals
//////////////////////////////////////////////
reg  [31:0] alu_result;            // combinational ALU result
reg  [4:0]  actual_shift_amount;   // bounded shift amount
reg         carry_out;             // final carry used in flags

// From barrel shifter (must be wires - driven by module output)
wire [31:0] shift_result;
wire        shifter_carry_out;

// From multiplier (must be wires - driven by module output)
wire [63:0] mul_product;
wire        mul_ready;

//////////////////////////////////////////////
// Barrel shifter instance (LSR/ASR)
//////////////////////////////////////////////
// NOTE: Ensure your barrel shifter module is named `barrel_shifting`
// and has matching ports. `shift_type`: 0=LSR, 1=ASR
barrel_shifting shifter_inst (
    .data_in     (operand_a),
    .shift_amount(actual_shift_amount),
    .shift_type  (opcode[0]),          // 0=LSR, 1=ASR
    .data_out    (shift_result),
    .carry_out   (shifter_carry_out)
);

//////////////////////////////////////////////
// Multiplier instance (MUL)
//////////////////////////////////////////////
multiplier_32bit mul_inst (
    .clk         (clk),
    .reset       (reset),
    .enable      (enable && (opcode == OP_MUL)),
    .multiplicand(operand_a),
    .multiplier  (operand_b),
    .product     (mul_product),        // wire
    .ready       (mul_ready)           // wire
);

//////////////////////////////////////////////
// Main combinational ALU path
//////////////////////////////////////////////
always @(*) begin
    // Defaults
    alu_result           = 32'h0;
    carry_out            = flags_in[C_FLAG];  // default carry keeps prior C
    stall                = 1'b0;
    actual_shift_amount  = shift_amount;

    // Bound shift to [0..31]
    if (shift_amount > 5'd31) begin
        actual_shift_amount = 5'd31;
    end

    case (opcode)
        OP_LSR: begin
            // Logical shift right
            alu_result = shift_result;
            carry_out  = shifter_carry_out;   // take C from shifter
        end

        OP_ASR: begin
            // Arithmetic shift right
            alu_result = shift_result;
            carry_out  = shifter_carry_out;   // take C from shifter
        end

        OP_EOR: begin
            alu_result = operand_a ^ operand_b;
            // carry_out unchanged
        end

        OP_BIC: begin
            alu_result = operand_a & (~operand_b);
            // carry_out unchanged
        end

        OP_MVN: begin
            alu_result = ~operand_b;
            // carry_out unchanged
        end

        OP_MUL: begin
            // Lower 32 bits of product; stall until ready
            alu_result = mul_product[31:0];
            stall      = ~mul_ready;
            // carry_out not defined by MUL; leave as default/prior C (flags logic handles it)
        end

        default: begin
            alu_result = 32'h0;
            // carry_out keeps flags_in[C_FLAG]
        end
    endcase
end

//////////////////////////////////////////////
// Flags (combinational)
//////////////////////////////////////////////
always @(*) begin
    flags_out = flags_in;  // start from current flags

    if (update_flags && !stall) begin
        // N: sign bit of result
        flags_out[N_FLAG] = alu_result[31];

        // Z: result is zero
        flags_out[Z_FLAG] = (alu_result == 32'h0000_0000);

        // C: per-opcode behavior
        case (opcode)
            OP_LSR,
            OP_ASR: flags_out[C_FLAG] = carry_out;      // from shifter
            OP_EOR,
            OP_BIC,
            OP_MVN: flags_out[C_FLAG] = flags_in[C_FLAG]; // unchanged
            OP_MUL: flags_out[C_FLAG] = 1'b0;           // defined here as 0
            default: flags_out[C_FLAG] = flags_in[C_FLAG];
        endcase

        // V: unchanged for these ops
        flags_out[V_FLAG] = flags_in[V_FLAG];
    end
end

//////////////////////////////////////////////
// Registered outputs
//////////////////////////////////////////////
always @(posedge clk) begin
    if (reset) begin
        result <= 32'h0;
        valid  <= 1'b0;
    end else if (enable && !stall) begin
        result <= alu_result;
        valid  <= 1'b1;
    end else if (stall) begin
        valid  <= 1'b0;
    end else begin
        // hold last result, deassert valid if not enabled
        valid  <= 1'b0;
    end
end

endmodule
