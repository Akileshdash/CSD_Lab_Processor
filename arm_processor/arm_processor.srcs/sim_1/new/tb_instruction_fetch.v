`timescale 1ns / 1ps

module tb_instruction_fetch;

reg clk;
reg reset;
reg pc_enable;
reg branch_taken;
reg jump_taken;
reg [31:0] branch_target;
reg [31:0] jump_target;

wire [31:0] pc_current;
wire [31:0] pc_plus_4;
wire [31:0] instruction;

// Instantiate the instruction fetch module
instruction_fetch uut (
    .clk(clk),
    .reset(reset),
    .pc_enable(pc_enable),
    .branch_taken(branch_taken),
    .jump_taken(jump_taken),
    .branch_target(branch_target),
    .jump_target(jump_target),
    .pc_current(pc_current),
    .pc_plus_4(pc_plus_4),
    .instruction(instruction)
);

// Clock generation
initial begin
    clk = 0;
    forever #5 clk = ~clk;  // 100MHz clock
end

// Test sequence
initial begin
    // Initialize inputs
    reset = 1;
    pc_enable = 1;
    branch_taken = 0;
    jump_taken = 0;
    branch_target = 32'h00000100;
    jump_target = 32'h00000200;
    
    // Reset phase
    #20;          // Wait 20ns
    reset = 0;    // Release reset
    
    // Normal operation - fetch sequential instructions
    #100;         // Let it run normally for 100ns
    
    // Test branch
    branch_taken = 1;  // Press "branch" button
    #10;               // Wait 10ns
    branch_taken = 0;  // Release "branch" button
    
    #50;          // Wait and observe
    
    // Test jump
    jump_taken = 1;    // Press "jump" button
    #10;               // Wait 10ns
    jump_taken = 0;    // Release "jump" button
    
    #100;         // Wait and observe
    
    $finish;      // End simulation
end

// Monitor outputs
initial begin
    $monitor("Time=%0t, PC=%h, PC+4=%h, Instruction=%h", 
             $time, pc_current, pc_plus_4, instruction);
end

endmodule