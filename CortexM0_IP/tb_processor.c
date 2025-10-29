#include "processor.h"
#include "decode.h"
#include "regfile.h"
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>

#define MEM_SIZE 128

// Helper macro for printing register states
#define PRINT_REGS(regs) do { \
    printf("R0=%08X R1=%08X R2=%08X R3=%08X R4=%08X R5=%08X R6=%08X R7=%08X\n", \
        regs[0], regs[1], regs[2], regs[3], regs[4], regs[5], regs[6], regs[7]); \
    printf("SP=%08X LR=%08X PC=%08X\n", regs[13], regs[14], regs[15]); \
} while(0)

void test_max_of_three() {
    printf("\n=== TEST: MAX OF THREE ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    instr_mem[0] = 0x200F | (0x2119 << 16);  // MOVS R0, #15; MOVS R1, #25
    instr_mem[1] = 0x220A | (0x001B << 16);  // MOVS R2, #10; MOVS R3, R0
    instr_mem[2] = 0x4299 | (0xD902 << 16);  // CMP R1, R3; BLS skip1
    instr_mem[3] = 0x000B | (0x429A << 16);  // MOVS R3, R1; CMP R2, R3
    instr_mem[4] = 0xD900 | (0x46C0 << 16);  // BLS end; NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);  // Reset
    for (int i = 0; i < 25; i++)
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);

    PRINT_REGS(reg_out);

    printf("Expected R3 (max) = 25, Actual R3 = %u\n", reg_out[3]);
}

void test_absolute_value() {
    printf("\n=== TEST: ABSOLUTE VALUE ===\n");
    
    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Calculate |R0|: if R0 < 0, negate it
    // MOVS R0, #10       ; test with positive
    // NEGS R0, R0        ; R0 = -10
    // CMP R0, #0         ; if (R0 < 0)
    // BPL skip           ; branch if positive
    // NEGS R0, R0        ; R0 = -R0 (make positive)
    // skip:
    
    instr_mem[0] = 0x200A | (0x4240 << 16);  // MOVS R0,#10 | NEGS R0,R0
    instr_mem[1] = 0x2800 | (0xD500 << 16);  // CMP R0,#0 | BPL +0 (skip)
    instr_mem[2] = 0x4240 | (0xBF00 << 16);  // NEGS R0,R0 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 15; i++)
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);

    PRINT_REGS(reg_out);
    printf("Expected R0 (|-10|) = 10, Actual R0 = %u\n", reg_out[0]);
    assert(reg_out[0] == 10);
    printf("✅ ABSOLUTE VALUE test passed!\n");
}

void test_sum_array() {
    printf("\n=== TEST: SUM OF ARRAY ===\n");
    
    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Sum three numbers: 10 + 20 + 30 = 60
    // MOVS R0, #10       ; R0 = 10
    // MOVS R1, #20       ; R1 = 20  
    // MOVS R2, #30       ; R2 = 30
    // MOVS R3, #0        ; R3 = 0
    // ADDS R3, R3, R0    ; R3 = R3 + R0 = 0 + 10 = 10
    // NOP
    // ADDS R3, R3, R1    ; R3 = R3 + R1 = 10 + 20 = 30
    // NOP
    // ADDS R3, R3, R2    ; R3 = R3 + R2 = 30 + 30 = 60
    // NOP
    
    instr_mem[0] = 0x200A | (0x2114 << 16);  // MOVS R0,#10 | MOVS R1,#20
    instr_mem[1] = 0x221E | (0x2300 << 16);  // MOVS R2,#30 | MOVS R3,#0
    instr_mem[2] = 0x181B | (0xBF00 << 16);  // ADDS R3,R3,R0 | NOP (FIXED!)
    instr_mem[3] = 0x185B | (0xBF00 << 16);  // ADDS R3,R3,R1 | NOP
    instr_mem[4] = 0x189B | (0xBF00 << 16);  // ADDS R3,R3,R2 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 20; i++)
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);

    printf("Expected R3 (sum) = 60, Actual R3 = %u\n", reg_out[3]);
    assert(reg_out[3] == 60);
    printf("✅ SUM OF ARRAY test passed!\n");
}

void test_factorial() {
    printf("\n=== TEST: FACTORIAL ===\n");
    
    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Calculate 5! = 5 × 4 × 3 × 2 × 1 = 120
    instr_mem[0] = 0x2001 | (0x2105 << 16);  // MOVS R0,#1 | MOVS R1,#5
    instr_mem[1] = 0x4348 | (0x3901 << 16);  // MULS R0,R1 | SUBS R1,#1  ← loop:
    instr_mem[2] = 0x2901 | (0xD8FB << 16);  // CMP R1,#1 | BHI -5 (FIXED!)
    instr_mem[3] = 0xBF00 | (0xBF00 << 16);  // NOP | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 30; i++)
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);

    PRINT_REGS(reg_out);
    printf("Expected R0 (5!) = 120, Actual R0 = %u\n", reg_out[0]);
    assert(reg_out[0] == 120);
    printf("✅ FACTORIAL test passed!\n");
}

void test_find_max() {
    printf("\n=== TEST: FIND MAXIMUM ===\n");
    
    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Find maximum of 4 numbers: 15, 42, 8, 23
    // Expected max = 42
    
    instr_mem[0] = 0x200F | (0x212A << 16);  // MOVS R0,#15 | MOVS R1,#42
    instr_mem[1] = 0x4288 | (0xD800 << 16);  // CMP R0,R1 | BHI +0 (skip next)
    instr_mem[2] = 0x4608 | (0x2208 << 16);  // MOV R0,R1 | MOVS R2,#8
    instr_mem[3] = 0x4290 | (0xD800 << 16);  // CMP R0,R2 | BHI +0 (skip next)
    instr_mem[4] = 0x4610 | (0x2317 << 16);  // MOV R0,R2 | MOVS R3,#23
    instr_mem[5] = 0x4298 | (0xD800 << 16);  // CMP R0,R3 | BHI +0 (skip next)
    instr_mem[6] = 0x4618 | (0xBF00 << 16);  // MOV R0,R3 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 25; i++)
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);

    PRINT_REGS(reg_out);
    printf("Expected R0 (max) = 42, Actual R0 = %u\n", reg_out[0]);
    assert(reg_out[0] == 42);
    printf("✅ FIND MAXIMUM test passed!\n");
}

void test_swap_values() {
    printf("\n=== TEST: SWAP TWO VALUES ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // MOVS R0, #5        ; R0 = 5
    // MOVS R1, #9        ; R1 = 9
    // MOV  R2, R0        ; temp = R0
    // MOV  R0, R1        ; R0 = R1
    // MOV  R1, R2        ; R1 = temp
    // NOP

    instr_mem[0] = 0x2005 | (0x2109 << 16);  // MOVS R0,#5 | MOVS R1,#9
    instr_mem[1] = 0x4602 | (0x4608 << 16);  // MOV R2,R0 | MOV R0,R1
    instr_mem[2] = 0x460A | (0xBF00 << 16);  // MOV R1,R2 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1); // Reset
    for (int i = 0; i < 15; i++)
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);

    PRINT_REGS(reg_out);

    printf("Expected: R0=9, R1=5 (swapped)\n");
    printf("Actual:   R0=%u, R1=%u\n", reg_out[0], reg_out[1]);
    assert(reg_out[0] == 9);
    assert(reg_out[1] == 5);
    printf("✅ SWAP TWO VALUES test passed!\n");
}


// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

int main() {       
    // test_max_of_three(); // Passsed
    // test_sum_array(); // Passed
    // test_factorial(); // Passed
    // test_absolute_value(); // Passed   
    test_swap_values();
    return 0;
}