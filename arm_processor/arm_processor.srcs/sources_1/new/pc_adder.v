module pc_adder (
    input wire [31:0] pc_current,
    output wire [31:0] pc_plus_4
);

assign pc_plus_4 = pc_current + 32'd4;  // Increment PC by 4 bytes

endmodule