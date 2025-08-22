module instruction_fetch (
    input wire clk,
    input wire reset,
    input wire pc_enable,           // Stall control
    input wire branch_taken,        // From execute stage
    input wire jump_taken,          // From execute stage
    input wire [31:0] branch_target,
    input wire [31:0] jump_target,
    output wire [31:0] pc_current,
    output wire [31:0] pc_plus_4,
    output wire [31:0] instruction
);

wire [31:0] pc_next;

// Program Counter
program_counter pc_inst (
    .clk(clk),
    .reset(reset),
    .pc_enable(pc_enable),
    .pc_next(pc_next),
    .pc_current(pc_current)
);

// PC + 4 Adder
pc_adder adder_inst (
    .pc_current(pc_current),
    .pc_plus_4(pc_plus_4)
);

// PC Multiplexer
pc_mux mux_inst (
    .pc_plus_4(pc_plus_4),
    .branch_target(branch_target),
    .jump_target(jump_target),
    .branch_taken(branch_taken),
    .jump_taken(jump_taken),
    .pc_next(pc_next)
);

// Instruction Memory
instruction_memory imem_inst (
    .clk(clk),
    .address(pc_current),
    .instruction(instruction)
);

endmodule