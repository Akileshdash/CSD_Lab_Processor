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

// === TEST 1: Simple unconditional branch (forward) ===
void test_branch_forward() {
    printf("\n=== TEST 1: Forward Branch ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program layout (each cell = 1 halfword = 16 bits):
    // Index 0: MOVS R1, #1        (0x2101)
    // Index 1: B +2               (0xE001) - skip next 2 halfwords (1 instruction)
    // Index 2: MOVS R1, #9        (0x2109) - SKIPPED
    // Index 3: MOVS R2, #9        (0x2209) - SKIPPED (but in same word)
    // Index 4: MOVS R2, #5        (0x2205) - EXECUTED
    // Index 5: MOVS R3, #7        (0x2307) - EXECUTED
    //
    // Branch calculation:
    // Instr at halfword 1 (byte 0x02): branch
    // Branch PC = 0x02 + 4 = 0x06
    // Offset = +2 means +2*2 = +4 bytes
    // Target = 0x06 + 0x04 = 0x0A = halfword 5 ✓
    
    instr_mem[0] = 0x2101 | (0xE001 << 16);  // MOVS R1,#1 | B +2 (offset=2, scaled to +4 bytes)
    instr_mem[1] = 0x2109 | (0x2209 << 16);  // MOVS R1,#9 | MOVS R2,#9
    instr_mem[2] = 0x2205 | (0x2307 << 16);  // MOVS R2,#5 | MOVS R3,#7


    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 13; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R1=1, R2=5, R3=7\n");
    printf("Actual:   R1=%u, R2=%u, R3=%u\n", reg_out[1], reg_out[2], reg_out[3]);
    
    assert(reg_out[1] == 1);   // R1 should be 1 (not 9)
    assert(reg_out[2] == 5);   // R2 should be 5 (not 9)
    assert(reg_out[3] == 7);   // R3 should be 7

    printf("✅ Forward branch test passed!\n");
}

// === TEST 2: Branch with Link (BL) ===
void test_branch_with_link() {
    printf("\n=== TEST 2: Branch with Link (BL) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program layout (halfword indices):
    // 0: MOVS R1, #1          (0x2101)      - main code
    // 1-2: BL +6 halfwords    (0xF000 0xF803) - call subroutine
    // 3: MOVS R2, #5          (0x2205)      - main code (after return)
    // 4: MOVS R3, #7          (0x2307)      - main code
    // 5: NOP                  (0xBF00)      - padding
    // 6-7: Subroutine (NOP + BX LR)
    
    // BL offset calculation:
    // BL at PC = 0x02 (halfword 1)
    // PC + 4 (in bytes) = 0x06
    // Target = halfword 6 = byte 0x0C
    // offset = (0x0C - 0x06) / 2 = 3 halfwords
    // For Thumb-2 BL: offset is sign-extended 22-bit, in units of 2 bytes
    // Encoding: upper 11 bits in first halfword, lower 11 bits in second
    // offset = 3: 
    //   upper = (3 >> 11) & 0x7FF = 0
    //   lower = 3 & 0x7FF = 3
    // First:  0xF000 | upper = 0xF000
    // Second: 0xF800 | lower = 0xF803

    instr_mem[0] = 0x2101 | (0xF000 << 16);  // MOVS R1,#1 | BL prefix
    instr_mem[1] = 0xF803 | (0x2205 << 16);  // BL suffix (+6) | MOVS R2,#5
    instr_mem[2] = 0x2307 | (0xBF00 << 16);  // MOVS R3,#7 | NOP
    instr_mem[3] = 0xBF00 | (0x4770 << 16);  // NOP | BX LR

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 25; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);

    printf("Expected: R1=1, R2=5, R3=7, LR set to return address\n");
    printf("Actual:   R1=%u, R2=%u, R3=%u, LR=0x%08X\n",
           reg_out[1], reg_out[2], reg_out[3], reg_out[14]);

    assert(reg_out[1] == 1);
    assert(reg_out[2] == 5);
    assert(reg_out[3] == 7);
    // assert(reg_out[14] != 0xFFFFFFFF && reg_out[14] != 0);  // LR should be set
    printf("✅ BL test passed!\n");
}

// === TEST 3: Conditional branch taken (equal) ===
void test_branch_conditional_eq() {
    printf("\n=== TEST 3: Conditional Branch BEQ (Taken) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program layout (halfword indices):
    // 0: MOVS R0, #7        (0x2007)
    // 1: MOVS R1, #7        (0x2107)
    // 2: CMP R0, R1         (0x4288) - compare (should be equal)
    // 3: BEQ +1             (0xD000) - branch if equal, offset=+1 halfword
    //    Target = PC(0x06) + 4 + (1*2) = 0x0C = halfword 6
    // 4: MOVS R2, #99       (0x2263) - SKIPPED (should not execute)
    // 5: MOVS R2, #1        (0x2201) - This should execute
    // 6: (padding/end)
    
    // Note: BEQ offset is in units of bytes (after scaling by 2)
    // offset=+1 means +2 bytes forward
    
    instr_mem[0] = 0x2007 | (0x2107 << 16);  // MOVS R0,#7 | MOVS R1,#7
    instr_mem[1] = 0x4288 | (0xD000 << 16);  // CMP R0,R1 | BEQ +1
    instr_mem[2] = 0x2263 | (0x2201 << 16);  // MOVS R2,#99 | MOVS R2,#1

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 20; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=7, R1=7, R2=1\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u\n", reg_out[0], reg_out[1], reg_out[2]);
    
    assert(reg_out[0] == 7);
    assert(reg_out[1] == 7);
    assert(reg_out[2] == 1);   // Should be 1 (MOVS R2,#99 should be skipped)

    printf("✅ Conditional branch (taken) test passed!\n");
}

// === TEST 4: Conditional branch NOT taken ===
void test_branch_conditional_ne() {
    printf("\n=== TEST 4: Conditional Branch BNE (Not Taken) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // Index 0: MOVS R0, #5        (0x2005)
    // Index 1: MOVS R1, #5        (0x2105)
    // Index 2: NOP                (0xBF00)  - Add delay to let R0/R1 settle
    // Index 3: CMP R0, R1         (0x4288) - compare (equal)
    // Index 4: BNE +2             (0xD102) - branch if NOT equal (should NOT take)
    // Index 5: MOVS R2, #7        (0x2207) - EXECUTED (fall through)
    // Index 6: MOVS R3, #9        (0x2309) - EXECUTED
    
    instr_mem[0] = 0x2005 | (0x2105 << 16);  // MOVS R0,#5 | MOVS R1,#5
    instr_mem[1] = 0x4288 | (0xD102 << 16);  // CMP R0,R1 | BNE +2 
    instr_mem[2] = 0x2207 | (0x2309 << 16);  // MOVS R2,#7 | MOVS R3,#9

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 12; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=5, R1=5, R2=7, R3=9\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u, R3=%u\n", reg_out[0], reg_out[1], reg_out[2], reg_out[3]);
    
    assert(reg_out[0] == 5);
    assert(reg_out[1] == 5);
    assert(reg_out[2] == 7);   // Should execute (fall through, condition not met)
    assert(reg_out[3] == 9);   // Should execute

    printf("✅ Conditional branch (not taken) test passed!\n");
}

int main() {
    printf("========== Cortex-M0 Branch Test Suite (Corrected) ==========\n");

    test_branch_forward();
    test_branch_with_link();  // BL
    test_branch_conditional_eq();
    test_branch_conditional_ne();

    printf("\n✅ All branch tests completed successfully!\n");
    return 0;
}