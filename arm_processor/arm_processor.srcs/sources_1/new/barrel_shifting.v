`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/25/2025 04:50:47 PM
// Design Name: 
// Module Name: barrel_shifting
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


// barrel_shifter.v - High-speed barrel shifter for LSR and ASR operations

module barrel_shifting (
    input wire [31:0] data_in,        // Data to be shifted
    input wire [4:0] shift_amount,    // How many positions to shift (0-31)
    input wire shift_type,            // 0=LSR (logical), 1=ASR (arithmetic)
    output reg [31:0] data_out,       // Shifted result
    output reg carry_out              // Carry bit from shift operation
);

// Internal signals for multi-stage shifting
wire [31:0] stage0, stage1, stage2, stage3, stage4;
wire [31:0] fill_bits;

// Determine fill pattern based on shift type
assign fill_bits = shift_type ? {32{data_in[31]}} : 32'h00000000;
//                  ASR: sign extend    LSR: zero fill

// 5-stage barrel shifter (can shift 0-31 positions in one cycle)
// Each stage can shift by 2^n positions

// Stage 0: Shift by 1 if shift_amount[0] = 1
assign stage0 = shift_amount[0] ? {fill_bits[0], data_in[31:1]} : data_in;

// Stage 1: Shift by 2 if shift_amount[1] = 1  
assign stage1 = shift_amount[1] ? {fill_bits[1:0], stage0[31:2]} : stage0;

// Stage 2: Shift by 4 if shift_amount[2] = 1
assign stage2 = shift_amount[2] ? {fill_bits[3:0], stage1[31:4]} : stage1;

// Stage 3: Shift by 8 if shift_amount[3] = 1
assign stage3 = shift_amount[3] ? {fill_bits[7:0], stage2[31:8]} : stage2;

// Stage 4: Shift by 16 if shift_amount[4] = 1
assign stage4 = shift_amount[4] ? {fill_bits[15:0], stage3[31:16]} : stage3;

// Output assignment
always @(*) begin
    data_out = stage4;
    
    // Carry out calculation - last bit shifted out
    if (shift_amount == 5'b00000) begin
        // No shift - carry unchanged (use existing carry)
        carry_out = 1'b0;  // Or could be input carry
    end else if (shift_amount > 5'd31) begin
        // Shift amount too large
        if (shift_type) begin
            // ASR: result is all sign bits, carry is sign bit
            data_out = fill_bits;
            carry_out = data_in[31];
        end else begin
            // LSR: result is all zeros, carry is 0
            data_out = 32'h00000000;
            carry_out = 1'b0;
        end
    end else begin
        // Normal case - carry is the last bit shifted out
        carry_out = data_in[shift_amount - 1];
    end
end

endmodule

// Alternative implementation using case statement (more readable but larger)
/*
module barrel_shifter_case (
    input wire [31:0] data_in,
    input wire [4:0] shift_amount,
    input wire shift_type,
    output reg [31:0] data_out,
    output reg carry_out
);

always @(*) begin
    case (shift_amount)
        5'd0:  begin data_out = data_in; carry_out = 1'b0; end
        5'd1:  begin 
            if (shift_type) data_out = {data_in[31], data_in[31:1]};      // ASR
            else            data_out = {1'b0, data_in[31:1]};             // LSR
            carry_out = data_in[0];
        end
        5'd2:  begin 
            if (shift_type) data_out = {{2{data_in[31]}}, data_in[31:2]};
            else            data_out = {2'b00, data_in[31:2]};
            carry_out = data_in[1];
        end
        // ... continue for all 32 cases
        default: begin
            data_out = shift_type ? {32{data_in[31]}} : 32'h00000000;
            carry_out = shift_type ? data_in[31] : 1'b0;
        end
    endcase
end

endmodule
*/