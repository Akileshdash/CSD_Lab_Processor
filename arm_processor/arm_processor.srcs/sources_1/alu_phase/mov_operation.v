module mov_operation (
    input  [31:0] B,           // source
    output [31:0] Rd,          // destination
    output        N, Z         // flags (if S is set)
);
    assign Rd = B;

    assign N = B[31];          // Negative flag
    assign Z = (B == 0);       // Zero flag
endmodule
