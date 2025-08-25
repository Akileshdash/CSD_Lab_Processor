`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/25/2025 04:54:01 PM
// Design Name: 
// Module Name: multiplier_32bit
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


// multiplier_32bit.v - 32-bit signed/unsigned multiplier
// Can be implemented as combinational (single cycle) or sequential (multi-cycle)

`timescale 1ns / 1ps

// multiplier_32bit.v - 32-bit signed/unsigned multiplier
// Can be implemented as combinational (single cycle) or sequential (multi-cycle)

module multiplier_32bit (
    input wire clk,
    input wire reset,
    input wire enable,                    // Start multiplication
    input wire [31:0] multiplicand,       // First operand
    input wire [31:0] multiplier,         // Second operand  
    output reg [63:0] product,            // 64-bit result
    output reg ready                      // Multiplication complete
);

parameter IMPLEMENTATION = 0;  // 0 = COMBINATIONAL, 1 = SEQUENTIAL

generate
    if (IMPLEMENTATION == 0) begin : combinational_mul
        // Single-cycle multiplication
        always @(*) begin
            product = multiplicand * multiplier;
        end
        
        always @(posedge clk) begin
            if (reset) begin
                ready <= 1'b0;
            end else begin
                ready <= enable;  // Ready next cycle after enable
            end
        end
        
    end else begin : sequential_mul
        // Multi-cycle multiplication (shift-add method)
        
        reg [31:0] multiplicand_reg;
        reg [31:0] multiplier_reg;
        reg [63:0] accumulator;
        reg [5:0] cycle_count;
        reg [1:0] state;
        
        localparam IDLE = 2'd0;
        localparam MULTIPLY = 2'd1;
        localparam DONE = 2'd2;
        
        always @(posedge clk) begin
            if (reset) begin
                state <= IDLE;
                ready <= 1'b0;
                product <= 64'h0;
                cycle_count <= 6'd0;
                accumulator <= 64'h0;
            end else begin
                case (state)
                    IDLE: begin
                        ready <= 1'b0;
                        if (enable) begin
                            multiplicand_reg <= multiplicand;
                            multiplier_reg <= multiplier;
                            accumulator <= 64'h0;
                            cycle_count <= 6'd0;
                            state <= MULTIPLY;
                        end
                    end
                    
                    MULTIPLY: begin
                        if (multiplier_reg[0]) begin
                            accumulator <= accumulator + ({32'h0, multiplicand_reg} << cycle_count);
                        end
                        multiplier_reg <= multiplier_reg >> 1;
                        cycle_count <= cycle_count + 1;
                        
                        if (cycle_count == 6'd31) begin
                            product <= accumulator;
                            state <= DONE;
                        end
                    end
                    
                    DONE: begin
                        ready <= 1'b1;
                        state <= IDLE;
                    end
                endcase
            end
        end
    end
endgenerate

endmodule


// High-performance DSP-based multiplier (pipelined)
module dsp_multiplier_32bit (
    input wire clk,
    input wire reset,
    input wire enable,
    input wire [31:0] a,          // Multiplicand
    input wire [31:0] b,          // Multiplier
    output reg [63:0] product,    // Product
    output reg ready
);

reg [31:0] a_reg, b_reg;
reg [63:0] product_reg;
reg [1:0] pipeline_stage;

always @(posedge clk) begin
    if (reset) begin
        a_reg <= 32'h0;
        b_reg <= 32'h0;
        product_reg <= 64'h0;
        product <= 64'h0;
        pipeline_stage <= 2'b00;
        ready <= 1'b0;
    end else if (enable) begin
        case (pipeline_stage)
            2'b00: begin
                a_reg <= a;
                b_reg <= b;
                pipeline_stage <= 2'b01;
                ready <= 1'b0;
            end
            2'b01: begin
                product_reg <= a_reg * b_reg;  // DSP slices
                pipeline_stage <= 2'b10;
            end
            2'b10: begin
                product <= product_reg;
                ready <= 1'b1;
                pipeline_stage <= 2'b00;
            end
        endcase
    end else begin
        ready <= 1'b0;
    end
end

endmodule
