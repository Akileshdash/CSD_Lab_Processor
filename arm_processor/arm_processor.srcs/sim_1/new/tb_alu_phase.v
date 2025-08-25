`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/25/2025 04:20:58 PM
// Design Name: 
// Module Name: tb_alu_phase
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


`timescale 1ns / 1ps

module tb_alu_phase;

// Testbench signals
reg clk;
reg reset;
reg [3:0] opcode;
reg [4:0] shift_amount;
reg update_flags;
reg enable;
reg [31:0] operand_a;
reg [31:0] operand_b;
reg [31:0] operand_c;
reg [3:0] flags_in;

wire [31:0] result;
wire [3:0] flags_out;
wire valid;
wire stall;

// Instruction opcodes (same as in main module)
localparam OP_LSR = 4'b0001;
localparam OP_ASR = 4'b0010;
localparam OP_EOR = 4'b0011;
localparam OP_BIC = 4'b0100;
localparam OP_MVN = 4'b0101;
localparam OP_MUL = 4'b0110;

// Flag positions
localparam N_FLAG = 3, Z_FLAG = 2, C_FLAG = 1, V_FLAG = 0;

// Instantiate the module under test
alu_phase uut (
    .clk(clk),
    .reset(reset),
    .opcode(opcode),
    .shift_amount(shift_amount),
    .update_flags(update_flags),
    .enable(enable),
    .operand_a(operand_a),
    .operand_b(operand_b),
    .operand_c(operand_c),
    .flags_in(flags_in),
    .result(result),
    .flags_out(flags_out),
    .valid(valid),
    .stall(stall)
);

// Clock generation - 100MHz
initial begin
    clk = 0;
    forever #5 clk = ~clk;
end

// Test sequence
initial begin
    $display("=== Instruction Execute Unit Test ===");
    
    // Initialize inputs
    reset = 1;
    enable = 0;
    opcode = 4'b0000;
    shift_amount = 5'd0;
    update_flags = 1;
    operand_a = 32'h0;
    operand_b = 32'h0;
    operand_c = 32'h0;
    flags_in = 4'b0000;
    
    // Reset sequence
    #20;
    reset = 0;
    enable = 1;
    #10;
    
    // Test 1: LSR - Logical Shift Right
    $display("\n--- Test 1: LSR (Logical Shift Right) ---");
    test_lsr();
    
    // Test 2: ASR - Arithmetic Shift Right  
    $display("\n--- Test 2: ASR (Arithmetic Shift Right) ---");
    test_asr();
    
    // Test 3: EOR - Exclusive OR
    $display("\n--- Test 3: EOR (Exclusive OR) ---");
    test_eor();
    
    // Test 4: BIC - Bit Clear
    $display("\n--- Test 4: BIC (Bit Clear) ---");
    test_bic();
    
    // Test 5: MVN - Move NOT
    $display("\n--- Test 5: MVN (Move NOT) ---");  
    test_mvn();
    
    // Test 6: MUL - Multiply
    $display("\n--- Test 6: MUL (Multiply) ---");
    test_mul();
    
    $display("\n=== All Tests Complete ===");
    #100;
    $finish;
end

// Task: Test LSR instruction
task test_lsr;
begin
    opcode = OP_LSR;
    
    // Test case 1: LSR #4 on 0x12345678
    operand_a = 32'h12345678;
    shift_amount = 5'd4;
    #10;
    $display("LSR: 0x%h >> %d = 0x%h (Expected: 0x01234567)", 
             operand_a, shift_amount, result);
    check_flags("LSR #4", 0, 0); // Not negative, not zero
    
    // Test case 2: LSR #1 on 0x80000001 (test carry)
    operand_a = 32'h80000001;
    shift_amount = 5'd1;
    #10;
    $display("LSR: 0x%h >> %d = 0x%h (Expected: 0x40000000)", 
             operand_a, shift_amount, result);
    check_flags("LSR #1", 0, 0); // Positive, not zero
    
    // Test case 3: LSR #32 (shift all bits out)
    operand_a = 32'hFFFFFFFF;
    shift_amount = 5'd31;
    #10;
    $display("LSR: 0x%h >> %d = 0x%h (Expected: 0x00000001)", 
             operand_a, shift_amount, result);
end
endtask

// Task: Test ASR instruction  
task test_asr;
begin
    opcode = OP_ASR;
    
    // Test case 1: ASR #4 on positive number
    operand_a = 32'h12345678;
    shift_amount = 5'd4;
    #10;
    $display("ASR: 0x%h >> %d = 0x%h (Expected: 0x01234567)", 
             operand_a, shift_amount, result);
    
    // Test case 2: ASR #4 on negative number (sign extend)
    operand_a = 32'h87654321;  // Negative number
    shift_amount = 5'd4;
    #10;
    $display("ASR: 0x%h >> %d = 0x%h (Expected: 0xF8765432)", 
             operand_a, shift_amount, result);
    check_flags("ASR negative", 1, 0); // Negative, not zero
    
    // Test case 3: ASR #1 on -1
    operand_a = 32'hFFFFFFFF;
    shift_amount = 5'd1;
    #10;
    $display("ASR: 0x%h >> %d = 0x%h (Expected: 0xFFFFFFFF)", 
             operand_a, shift_amount, result);
    check_flags("ASR -1", 1, 0); // Negative, not zero
end
endtask

// Task: Test EOR instruction
task test_eor;
begin
    opcode = OP_EOR;
    
    // Test case 1: Basic XOR
    operand_a = 32'h12345678;
    operand_b = 32'h87654321;
    #10;
    $display("EOR: 0x%h ^ 0x%h = 0x%h (Expected: 0x95511559)", 
             operand_a, operand_b, result);
    
    // Test case 2: XOR with self (should be zero)
    operand_a = 32'h12345678;
    operand_b = 32'h12345678;
    #10;
    $display("EOR: 0x%h ^ 0x%h = 0x%h (Expected: 0x00000000)", 
             operand_a, operand_b, result);
    check_flags("EOR self", 0, 1); // Not negative, is zero
    
    // Test case 3: Bit toggling
    operand_a = 32'h00000000;
    operand_b = 32'hFFFFFFFF;
    #10;
    $display("EOR: 0x%h ^ 0x%h = 0x%h (Expected: 0xFFFFFFFF)", 
             operand_a, operand_b, result);
    check_flags("EOR toggle", 1, 0); // Negative, not zero
end
endtask

// Task: Test BIC instruction
task test_bic;
begin
    opcode = OP_BIC;
    
    // Test case 1: Clear specific bits
    operand_a = 32'hFFFFFFFF;
    operand_b = 32'h0000FF00;  // Clear bits 8-15
    #10;
    $display("BIC: 0x%h & ~0x%h = 0x%h (Expected: 0xFFFF00FF)", 
             operand_a, operand_b, result);
    
    // Test case 2: Clear all bits  
    operand_a = 32'h12345678;
    operand_b = 32'hFFFFFFFF;
    #10;
    $display("BIC: 0x%h & ~0x%h = 0x%h (Expected: 0x00000000)", 
             operand_a, operand_b, result);
    check_flags("BIC all", 0, 1); // Not negative, is zero
    
    // Test case 3: Clear no bits
    operand_a = 32'h12345678;
    operand_b = 32'h00000000;
    #10;
    $display("BIC: 0x%h & ~0x%h = 0x%h (Expected: 0x12345678)", 
             operand_a, operand_b, result);
end
endtask

// Task: Test MVN instruction
task test_mvn;
begin
    opcode = OP_MVN;
    
    // Test case 1: Complement of all 1s
    operand_b = 32'hFFFFFFFF;
    #10;
    $display("MVN: ~0x%h = 0x%h (Expected: 0x00000000)", 
             operand_b, result);
    check_flags("MVN all 1s", 0, 1); // Not negative, is zero
    
    // Test case 2: Complement of all 0s
    operand_b = 32'h00000000;
    #10;
    $display("MVN: ~0x%h = 0x%h (Expected: 0xFFFFFFFF)", 
             operand_b, result);
    check_flags("MVN all 0s", 1, 0); // Negative, not zero
    
    // Test case 3: Complement of pattern
    operand_b = 32'h12345678;
    #10;
    $display("MVN: ~0x%h = 0x%h (Expected: 0xEDCBA987)", 
             operand_b, result);
end
endtask

// Task: Test MUL instruction
task test_mul;
begin
    opcode = OP_MUL;
    
    // Test case 1: Simple multiplication
    operand_a = 32'd1234;
    operand_b = 32'd5678;
    #10;
    wait(!stall);  // Wait for multiplication to complete
    #10;
    $display("MUL: %d * %d = %d (Expected: %d)", 
             operand_a, operand_b, result, 1234 * 5678);
    
    // Test case 2: Multiplication by zero
    operand_a = 32'd12345;
    operand_b = 32'd0;
    #10;
    wait(!stall);
    #10;
    $display("MUL: %d * %d = %d (Expected: 0)", 
             operand_a, operand_b, result);
    check_flags("MUL by zero", 0, 1); // Not negative, is zero
    
    // Test case 3: Large numbers
    operand_a = 32'h0000FFFF;  // 65535
    operand_b = 32'h0000FFFF;  // 65535  
    #10;
    wait(!stall);
    #10;
    $display("MUL: 0x%h * 0x%h = 0x%h (Expected: 0xFFFE0001)", 
             operand_a, operand_b, result);
end
endtask

// Task: Check flag values
task check_flags;
input [63:0] test_name;
input expected_n;
input expected_z;
begin
    if (flags_out[N_FLAG] !== expected_n) 
        $display("ERROR in %s: N flag = %b, expected %b", test_name, flags_out[N_FLAG], expected_n);
    if (flags_out[Z_FLAG] !== expected_z)
        $display("ERROR in %s: Z flag = %b, expected %b", test_name, flags_out[Z_FLAG], expected_z);
    if (flags_out[N_FLAG] === expected_n && flags_out[Z_FLAG] === expected_z)
        $display("PASS: %s flags correct (N=%b, Z=%b)", test_name, flags_out[N_FLAG], flags_out[Z_FLAG]);
end
endtask

// Monitor all outputs
initial begin
    $monitor("Time=%0t: Op=%b, A=0x%h, B=0x%h, Result=0x%h, Flags=%b, Valid=%b, Stall=%b", 
             $time, opcode, operand_a, operand_b, result, flags_out, valid, stall);
end

endmodule