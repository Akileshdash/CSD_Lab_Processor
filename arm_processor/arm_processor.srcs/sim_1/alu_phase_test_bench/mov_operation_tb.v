`timescale 1ns/1ps
module mov_operation_tb;
    reg  [31:0] B;
    wire [31:0] Rd;
    wire N, Z;

    mov_operation uut (B, Rd, N, Z);

    initial begin
        $monitor("Time=%0t B=%d | Rd=%d N=%b Z=%b",
                  $time, B, Rd, N, Z);

        B = 0;    #10;   // expect Z=1
        B = 32'hFFFFFFFF; #10; // expect N=1
        B = 123;  #10;   // simple copy
        $finish;
    end
endmodule
