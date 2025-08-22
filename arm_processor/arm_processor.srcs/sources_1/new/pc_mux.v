module pc_mux (
    input wire [31:0] pc_plus_4,    // Normal next address
    input wire [31:0] branch_target, // Jump here if branching
    input wire [31:0] jump_target,   // Jump here if jumping
    input wire branch_taken,         // Should we branch?
    input wire jump_taken,           // Should we jump?
    output reg [31:0] pc_next        // Final decision
);

always @(*) begin
    if (jump_taken) begin
        pc_next = jump_target;
    end else if (branch_taken) begin
        pc_next = branch_target;
    end else begin
        pc_next = pc_plus_4;
    end
end

endmodule