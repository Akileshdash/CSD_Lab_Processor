`timescale 1ns / 1ps

module sub_operation_tb;

    // Inputs
    reg  [31:0] operand_a;
    reg  [31:0] operand_b;

    // Outputs
    wire [31:0] result;
    wire        carry_out;
    wire        overflow;

    // Instantiate the Unit Under Test (UUT)
    sub_operation uut (
        .operand_a(operand_a),
        .operand_b(operand_b),
        .result(result),
        .carry_out(carry_out),
        .overflow(overflow)
    );

    initial begin
        // Display header
        $display("Time\tA\t\tB\t\tResult\tCarry\tOverflow");

        // Test Case 1: 10 - 5
        operand_a = 32'd10;
        operand_b = 32'd5;
        #10 $display("%0t\t%d - %d = %d | C=%b O=%b", $time, operand_a, operand_b, result, carry_out, overflow);

        // Test Case 2: 5 - 10 (borrow expected)
        operand_a = 32'd5;
        operand_b = 32'd10;
        #10 $display("%0t\t%d - %d = %d | C=%b O=%b", $time, operand_a, operand_b, result, carry_out, overflow);

        // Test Case 3: Same values (result = 0)
        operand_a = 32'd1234;
        operand_b = 32'd1234;
        #10 $display("%0t\t%d - %d = %d | C=%b O=%b", $time, operand_a, operand_b, result, carry_out, overflow);

        // End simulation
        #20 $finish;
    end

endmodule
