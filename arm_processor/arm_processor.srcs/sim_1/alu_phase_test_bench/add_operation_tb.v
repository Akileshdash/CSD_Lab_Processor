//`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////////
//// Company: 
//// Engineer: 
//// 
//// Create Date: 08/30/2025 12:10:45 PM
//// Design Name: 
//// Module Name: add_operation_tb
//// Project Name: 
//// Target Devices: 
//// Tool Versions: 
//// Description: 
//// 
//// Dependencies: 
//// 
//// Revision:
//// Revision 0.01 - File Created
//// Additional Comments:
//// 
////////////////////////////////////////////////////////////////////////////////////


//module add_operation_tb(

//    );
//endmodule
`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Testbench Name: add_operation_tb
// Description: Comprehensive testbench for add_operation module
// Location: alu_phase_testbench/add_operation_tb.v
// Tests Module: alu_phase/add_operation.v
//////////////////////////////////////////////////////////////////////////////////

module add_operation_tb;

//////////////////////////////////////////////
// Testbench signals
//////////////////////////////////////////////
reg  [31:0] operand_a;
reg  [31:0] operand_b;
wire [31:0] result;
wire        carry_out;
wire        overflow;

// Expected results for verification
reg [31:0] expected_result;
reg        expected_carry;
reg        expected_overflow;

// Test counters
integer test_count;
integer pass_count;
integer fail_count;

//////////////////////////////////////////////
// Instantiate Unit Under Test (UUT)
// Note: Module is located in ../alu_phase/add_operation.v
//////////////////////////////////////////////
add_operation uut (
    .operand_a(operand_a),
    .operand_b(operand_b),
    .result(result),
    .carry_out(carry_out),
    .overflow(overflow)
);

//////////////////////////////////////////////
// Test task for easier verification
//////////////////////////////////////////////
task test_addition;
    input [31:0] a, b;
    input [31:0] exp_result;
    input exp_carry, exp_overflow;
    input [200:0] test_name;  // String for test description
begin
    operand_a = a;
    operand_b = b;
    expected_result = exp_result;
    expected_carry = exp_carry;
    expected_overflow = exp_overflow;
    
    #10; // Wait for combinational logic to settle
    
    test_count = test_count + 1;
    
    // Check results
    if (result == expected_result && carry_out == expected_carry && overflow == expected_overflow) begin
        $display("PASS: %s", test_name);
        $display("      A=%h, B=%h => Result=%h, C=%b, V=%b", a, b, result, carry_out, overflow);
        pass_count = pass_count + 1;
    end else begin
        $display("FAIL: %s", test_name);
        $display("      A=%h, B=%h", a, b);
        $display("      Expected: Result=%h, C=%b, V=%b", expected_result, expected_carry, expected_overflow);
        $display("      Got:      Result=%h, C=%b, V=%b", result, carry_out, overflow);
        fail_count = fail_count + 1;
    end
    $display(""); // Blank line for readability
end
endtask

//////////////////////////////////////////////
// Main test sequence
//////////////////////////////////////////////
initial begin
    // Initialize
    operand_a = 0;
    operand_b = 0;
    test_count = 0;
    pass_count = 0;
    fail_count = 0;
    
    // Wait a bit for simulation to start
    #1;
    
    $display("=== ADD OPERATION TESTBENCH ===");
    $display("Module Location: alu_phase/add_operation.v");
    $display("Testbench Location: alu_phase_testbench/add_operation_tb.v");
    $display("Testing add_operation module");
    $display("Time: %0t", $time);
    $display("");
    
    //////////////////////////////////////////////
    // Test Category 1: Basic Addition
    //////////////////////////////////////////////
    $display("--- Basic Addition Tests ---");
    
    // Simple positive numbers
    test_addition(32'h00000001, 32'h00000001, 32'h00000002, 1'b0, 1'b0, "1 + 1 = 2");
    test_addition(32'h00000005, 32'h00000003, 32'h00000008, 1'b0, 1'b0, "5 + 3 = 8");
    test_addition(32'h12345678, 32'h87654321, 32'h99999999, 1'b0, 1'b0, "Large positive numbers");
    
    // Zero cases
    test_addition(32'h00000000, 32'h00000000, 32'h00000000, 1'b0, 1'b0, "0 + 0 = 0");
    test_addition(32'h12345678, 32'h00000000, 32'h12345678, 1'b0, 1'b0, "A + 0 = A");
    test_addition(32'h00000000, 32'h87654321, 32'h87654321, 1'b0, 1'b0, "0 + B = B");
    
    //////////////////////////////////////////////
    // Test Category 2: Carry Generation
    //////////////////////////////////////////////
    $display("--- Carry Generation Tests ---");
    
    // Maximum values that generate carry
    test_addition(32'hFFFFFFFF, 32'h00000001, 32'h00000000, 1'b1, 1'b0, "0xFFFFFFFF + 1 (carry)");
    test_addition(32'hFFFFFFFF, 32'hFFFFFFFF, 32'hFFFFFFFE, 1'b1, 1'b0, "0xFFFFFFFF + 0xFFFFFFFF");
    test_addition(32'h80000000, 32'h80000000, 32'h00000000, 1'b1, 1'b1, "0x80000000 + 0x80000000 (carry+overflow)");
    
    // Edge cases around carry boundary
    test_addition(32'hFFFFFFFE, 32'h00000001, 32'hFFFFFFFF, 1'b0, 1'b0, "0xFFFFFFFE + 1 (no carry)");
    test_addition(32'h7FFFFFFF, 32'h80000000, 32'hFFFFFFFF, 1'b0, 1'b0, "0x7FFFFFFF + 0x80000000");
    
    //////////////////////////////////////////////
    // Test Category 3: Signed Overflow
    //////////////////////////////////////////////
    $display("--- Signed Overflow Tests ---");
    
    // Positive + Positive = Negative (overflow)
    test_addition(32'h7FFFFFFF, 32'h00000001, 32'h80000000, 1'b0, 1'b1, "0x7FFFFFFF + 1 (pos overflow)");
    test_addition(32'h7FFFFFFF, 32'h7FFFFFFF, 32'hFFFFFFFE, 1'b0, 1'b1, "0x7FFFFFFF + 0x7FFFFFFF");
    test_addition(32'h40000000, 32'h40000000, 32'h80000000, 1'b0, 1'b1, "0x40000000 + 0x40000000");
    
    // Negative + Negative = Positive (overflow)  
    test_addition(32'h80000000, 32'h80000000, 32'h00000000, 1'b1, 1'b1, "0x80000000 + 0x80000000 (neg overflow)");
    test_addition(32'h80000001, 32'h80000001, 32'h00000002, 1'b1, 1'b1, "0x80000001 + 0x80000001");
    
    // Cases that should NOT overflow
    test_addition(32'h7FFFFFFF, 32'h80000000, 32'hFFFFFFFF, 1'b0, 1'b0, "0x7FFFFFFF + 0x80000000 (no overflow)");
    test_addition(32'h80000000, 32'h7FFFFFFF, 32'hFFFFFFFF, 1'b0, 1'b0, "0x80000000 + 0x7FFFFFFF (no overflow)");
    
    //////////////////////////////////////////////
    // Test Category 4: Edge Cases
    //////////////////////////////////////////////
    $display("--- Edge Cases ---");
    
    // Maximum positive + minimum negative
    test_addition(32'h7FFFFFFF, 32'h80000001, 32'h00000000, 1'b1, 1'b0, "MAX_POS + (MIN_NEG+1)");
    
    // Powers of 2
    test_addition(32'h00000001, 32'h00000001, 32'h00000002, 1'b0, 1'b0, "2^0 + 2^0");
    test_addition(32'h00008000, 32'h00008000, 32'h00010000, 1'b0, 1'b0, "2^15 + 2^15");
    test_addition(32'h40000000, 32'h40000000, 32'h80000000, 1'b0, 1'b1, "2^30 + 2^30");
    
    //////////////////////////////////////////////
    // Test Category 5: Random Test Cases
    //////////////////////////////////////////////
    $display("--- Random Test Cases ---");
    
    // Some random values to test general functionality (fixed expected result)
    test_addition(32'h12345678, 32'hABCDEF01, 32'hBE024579, 1'b0, 1'b0, "Random case 1");
    test_addition(32'hDEADBEEF, 32'hCAFEBABE, 32'hA9AC79AD, 1'b1, 1'b0, "Random case 2");
    test_addition(32'h55555555, 32'hAAAAAAAA, 32'hFFFFFFFF, 1'b0, 1'b0, "Alternating bits");
    
    //////////////////////////////////////////////
    // Test Summary
    //////////////////////////////////////////////
    $display("");
    $display("=== TEST SUMMARY ===");
    $display("Total Tests: %d", test_count);
    $display("Passed:      %d", pass_count);
    $display("Failed:      %d", fail_count);
    $display("Time: %0t", $time);
    
    if (fail_count == 0) begin
        $display("");
        $display("*** ALL TESTS PASSED! ***");
        $display("*** ADD OPERATION MODULE VERIFIED ***");
    end else begin
        $display("");
        $display("*** %d TESTS FAILED ***", fail_count);
        $display("*** CHECK RESULTS ABOVE ***");
    end
    
    $display("");
    $display("Simulation completed at time %0t", $time);
    
    // Force the simulation to run a bit longer to ensure all output is flushed
    #100;
    $finish;
end

//////////////////////////////////////////////
// Optional: Monitor for debugging
//////////////////////////////////////////////
initial begin
    $monitor("Time=%0t: A=%h, B=%h => Result=%h, Carry=%b, Overflow=%b", 
             $time, operand_a, operand_b, result, carry_out, overflow);
end

endmodule