module instruction_memory (
    input wire clk,
    input wire [31:0] address,      // PC address
    output reg [31:0] instruction   // Fetched instruction
);

// Simple instruction memory (can be replaced with BRAM)
reg [31:0] memory [0:1023];  // 1024 instructions (4KB)

// Initialize with sample instructions for testing
initial begin
    // Sample RISC-V instructions for testing
    memory[0] = 32'h00000013;   // NOP (addi x0, x0, 0)
    memory[1] = 32'h00100093;   // addi x1, x0, 1
    memory[2] = 32'h00200113;   // addi x2, x0, 2
    memory[3] = 32'h002081b3;   // add x3, x1, x2
    // Add more instructions as needed
end

always @(posedge clk) begin
    instruction <= memory[address[31:2]];  // Word-aligned access
end

endmodule
