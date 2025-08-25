module program_counter (
    input wire clk,              // Clock signal
    input wire reset,            // Reset button
    input wire pc_enable,        // Enable/disable counting
    input wire [31:0] pc_next,   // What value to load next
    output reg [31:0] pc_current // Current counter value
);

always @(posedge clk or posedge reset) begin
    if (reset) begin
        pc_current <= 32'h00000000;  // Reset PC to 0
    end else if (pc_enable) begin
        pc_current <= pc_next;
    end
end

endmodule

