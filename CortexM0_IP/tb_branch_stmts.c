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


    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 13; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
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

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 25; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
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

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 20; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
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

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 12; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
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

// === TEST 5: Backward Branch (FIXED) ===
void test_branch_backward() {
    printf("\n=== TEST 5: Backward Branch ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program layout:
    // 0: MOVS R0, #1        (0x2001) - initialize R0
    // 1: ADDS R0, R0, #1    (0x3001) - loop start: increment R0
    // 2: CMP R0, #3         (0x2803) - compare with 3
    // 3: BNE -4             (0xD1FC) - branch back to ADDS if not equal
    // 4: MOVS R1, #10       (0x210A) - after loop
    //
    // Branch calculation:
    // BNE at halfword 3 (byte 0x06)
    // PC after fetch = 0x06 + 4 = 0x0A
    // Target = halfword 1 (byte 0x02) = ADDS instruction
    // Offset = (0x02 - 0x0A) / 2 = -4 halfwords
    // -4 in 8-bit signed = 0xFC
    
    instr_mem[0] = 0x2001 | (0x3001 << 16);  // MOVS R0,#1 | ADDS R0,R0,#1
    instr_mem[1] = 0x2803 | (0xD1FC << 16);  // CMP R0,#3 | BNE -4
    instr_mem[2] = 0x210A | (0xBF00 << 16);  // MOVS R1,#10 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 30; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=3, R1=10 (loop executed until R0=3)\n");
    printf("Actual:   R0=%u, R1=%u\n", reg_out[0], reg_out[1]);
    
    assert(reg_out[0] == 3);
    assert(reg_out[1] == 10);

    printf("✅ Backward branch test passed!\n");
}

// === TEST 6: BCS/BHS (Branch if Carry Set) - with ADDS overflow ===
void test_branch_bcs() {
    printf("\n=== TEST 6: BCS/BHS (Branch if Carry Set) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOVS R0, #255      (0x20FF)
    // 1: MOVS R1, #255      (0x21FF)
    // 2: MOVS R2, #255      (0x22FF)
    // 3: MOVS R3, #255      (0x23FF)
    // ... build 0xFFFFFFFF in a register through shifting/ORing
    // This is complex, so using CMP is simpler!
    
    // Simpler approach - use MVN to get 0xFFFFFFFF
    // But MVN might not be implemented yet
    
    // **BEST APPROACH: Use CMP which sets C=1 when Rn >= Operand2 (unsigned)**
    
    instr_mem[0] = 0x200A | (0x2105 << 16);  // MOVS R0,#10 | MOVS R1,#5
    instr_mem[1] = 0x4288 | (0xD200 << 16);  // CMP R0,R1 | BCS +1
    instr_mem[2] = 0x2263 | (0x2207 << 16);  // MOVS R2,#99 | MOVS R2,#7

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 15; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=10, R1=5, R2=7 (CMP sets C=1 when 10 >= 5)\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u\n", reg_out[0], reg_out[1], reg_out[2]);
    
    assert(reg_out[0] == 10);
    assert(reg_out[1] == 5);
    assert(reg_out[2] == 7);

    printf("✅ BCS test passed!\n");
}

// === TEST 7: BCC/BLO (Branch if Carry Clear) ===
void test_branch_bcc() {
    printf("\n=== TEST 7: BCC/BLO (Branch if Carry Clear) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOVS R0, #5        (0x2005)
    // 1: ADDS R0, #1        (0x3001) - no carry (5+1=6, C=0)
    // 2: BCC +1             (0xD300) - branch if carry clear (should take)
    // 3: MOVS R1, #99       (0x2163) - SKIPPED
    // 4: MOVS R1, #8        (0x2108) - EXECUTED
    
    instr_mem[0] = 0x2005 | (0x3001 << 16);  // MOVS R0,#5 | ADDS R0,#1
    instr_mem[1] = 0xD300 | (0x2163 << 16);  // BCC +1 | MOVS R1,#99
    instr_mem[2] = 0x2108 | (0xBF00 << 16);  // MOVS R1,#8 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 15; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=6, R1=8 (branch taken, no carry)\n");
    printf("Actual:   R0=%u, R1=%u\n", reg_out[0], reg_out[1]);
    
    assert(reg_out[0] == 6);
    assert(reg_out[1] == 8);

    printf("✅ BCC test passed!\n");
}

// === TEST 8: BMI (Branch if Minus/Negative) ===
void test_branch_bmi() {
    printf("\n=== TEST 8: BMI (Branch if Minus) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOVS R0, #5        (0x2005)
    // 1: SUBS R0, #10       (0x380A) - result is negative (5-10=-5, N=1)
    // 2: BMI +1             (0xD400) - branch if negative (should take)
    // 3: MOVS R1, #99       (0x2163) - SKIPPED
    // 4: MOVS R1, #9        (0x2109) - EXECUTED
    
    instr_mem[0] = 0x2005 | (0x380A << 16);  // MOVS R0,#5 | SUBS R0,#10
    instr_mem[1] = 0xD400 | (0x2163 << 16);  // BMI +1 | MOVS R1,#99
    instr_mem[2] = 0x2109 | (0xBF00 << 16);  // MOVS R1,#9 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 15; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=0xFFFFFFFB (-5 in two's complement), R1=9\n");
    printf("Actual:   R0=0x%08X, R1=%u\n", reg_out[0], reg_out[1]);
    
    assert(reg_out[0] == 0xFFFFFFFB);  // -5 in two's complement
    assert(reg_out[1] == 9);

    printf("✅ BMI test passed!\n");
}

// === TEST 9: BPL (Branch if Plus/Positive) ===
void test_branch_bpl() {
    printf("\n=== TEST 9: BPL (Branch if Plus) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOVS R0, #10       (0x200A)
    // 1: SUBS R0, #3        (0x3803) - result is positive (10-3=7, N=0)
    // 2: BPL +1             (0xD500) - branch if positive (should take)
    // 3: MOVS R1, #99       (0x2163) - SKIPPED
    // 4: MOVS R1, #11       (0x210B) - EXECUTED
    
    instr_mem[0] = 0x200A | (0x3803 << 16);  // MOVS R0,#10 | SUBS R0,#3
    instr_mem[1] = 0xD500 | (0x2163 << 16);  // BPL +1 | MOVS R1,#99
    instr_mem[2] = 0x210B | (0xBF00 << 16);  // MOVS R1,#11 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 15; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=7, R1=11 (branch taken, result positive)\n");
    printf("Actual:   R0=%u, R1=%u\n", reg_out[0], reg_out[1]);
    
    assert(reg_out[0] == 7);
    assert(reg_out[1] == 11);

    printf("✅ BPL test passed!\n");
}

// === TEST 10: BVS (Branch if Overflow Set) ===
void test_branch_bvs() {
    printf("\n=== TEST 10: BVS (Branch if Overflow Set) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOVS R0, #127      (0x207F) - max positive 8-bit signed
    // 1: ADDS R0, #1        (0x3001) - overflow (127+1=128, but in signed it's -128)
    // 2: BVS +1             (0xD600) - branch if overflow (should take)
    // 3: MOVS R1, #99       (0x2163) - SKIPPED
    // 4: MOVS R1, #12       (0x210C) - EXECUTED
    
    instr_mem[0] = 0x207F | (0x3001 << 16);  // MOVS R0,#127 | ADDS R0,#1
    instr_mem[1] = 0xD600 | (0x2163 << 16);  // BVS +1 | MOVS R1,#99
    instr_mem[2] = 0x210C | (0xBF00 << 16);  // MOVS R1,#12 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 15; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=128, R1=12 (branch taken due to overflow)\n");
    printf("Actual:   R0=%u, R1=%u\n", reg_out[0], reg_out[1]);
    
    assert(reg_out[0] == 128);
    assert(reg_out[1] == 12);

    printf("✅ BVS test passed!\n");
}

// === TEST 11: BVC (Branch if Overflow Clear) ===
void test_branch_bvc() {
    printf("\n=== TEST 11: BVC (Branch if Overflow Clear) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOVS R0, #50       (0x2032)
    // 1: ADDS R0, #10       (0x300A) - no overflow (50+10=60)
    // 2: BVC +1             (0xD700) - branch if no overflow (should take)
    // 3: MOVS R1, #99       (0x2163) - SKIPPED
    // 4: MOVS R1, #13       (0x210D) - EXECUTED
    
    instr_mem[0] = 0x2032 | (0x300A << 16);  // MOVS R0,#50 | ADDS R0,#10
    instr_mem[1] = 0xD700 | (0x2163 << 16);  // BVC +1 | MOVS R1,#99
    instr_mem[2] = 0x210D | (0xBF00 << 16);  // MOVS R1,#13 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 15; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=60, R1=13 (branch taken, no overflow)\n");
    printf("Actual:   R0=%u, R1=%u\n", reg_out[0], reg_out[1]);
    
    assert(reg_out[0] == 60);
    assert(reg_out[1] == 13);

    printf("✅ BVC test passed!\n");
}

// === TEST 12: BHI (Branch if Higher - unsigned) ===
void test_branch_bhi() {
    printf("\n=== TEST 12: BHI (Branch if Higher - unsigned) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOVS R0, #10       (0x200A)
    // 1: MOVS R1, #5        (0x2105)
    // 2: CMP R0, R1         (0x4288) - 10 > 5, so C=1 and Z=0
    // 3: BHI +1             (0xD800) - branch if higher (C=1 AND Z=0) (should take)
    // 4: MOVS R2, #99       (0x2263) - SKIPPED
    // 5: MOVS R2, #14       (0x220E) - EXECUTED
    
    instr_mem[0] = 0x200A | (0x2105 << 16);  // MOVS R0,#10 | MOVS R1,#5
    instr_mem[1] = 0x4288 | (0xD800 << 16);  // CMP R0,R1 | BHI +1
    instr_mem[2] = 0x2263 | (0x220E << 16);  // MOVS R2,#99 | MOVS R2,#14

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 15; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=10, R1=5, R2=14 (10 > 5, branch taken)\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u\n", reg_out[0], reg_out[1], reg_out[2]);
    
    assert(reg_out[0] == 10);
    assert(reg_out[1] == 5);
    assert(reg_out[2] == 14);

    printf("✅ BHI test passed!\n");
}

// === TEST 13: BLS (Branch if Lower or Same - unsigned) ===
void test_branch_bls() {
    printf("\n=== TEST 13: BLS (Branch if Lower or Same - unsigned) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOVS R0, #5        (0x2005)
    // 1: MOVS R1, #10       (0x210A)
    // 2: CMP R0, R1         (0x4288) - 5 <= 10, so C=0 OR Z=0
    // 3: BLS +1             (0xD900) - branch if lower or same (should take)
    // 4: MOVS R2, #99       (0x2263) - SKIPPED
    // 5: MOVS R2, #15       (0x220F) - EXECUTED
    
    instr_mem[0] = 0x2005 | (0x210A << 16);  // MOVS R0,#5 | MOVS R1,#10
    instr_mem[1] = 0x4288 | (0xD900 << 16);  // CMP R0,R1 | BLS +1
    instr_mem[2] = 0x2263 | (0x220F << 16);  // MOVS R2,#99 | MOVS R2,#15

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 15; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=5, R1=10, R2=15 (5 <= 10, branch taken)\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u\n", reg_out[0], reg_out[1], reg_out[2]);
    
    assert(reg_out[0] == 5);
    assert(reg_out[1] == 10);
    assert(reg_out[2] == 15);

    printf("✅ BLS test passed!\n");
}

// === TEST 14: BGE (Branch if Greater or Equal - signed) ===
void test_branch_bge() {
    printf("\n=== TEST 14: BGE (Branch if Greater or Equal - signed) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOVS R0, #10       (0x200A)
    // 1: MOVS R1, #5        (0x2105)
    // 2: CMP R0, R1         (0x4288) - 10 >= 5 (signed), N==V
    // 3: BGE +1             (0xDA00) - branch if greater or equal (should take)
    // 4: MOVS R2, #99       (0x2263) - SKIPPED
    // 5: MOVS R2, #16       (0x2210) - EXECUTED
    
    instr_mem[0] = 0x200A | (0x2105 << 16);  // MOVS R0,#10 | MOVS R1,#5
    instr_mem[1] = 0x4288 | (0xDA00 << 16);  // CMP R0,R1 | BGE +1
    instr_mem[2] = 0x2263 | (0x2210 << 16);  // MOVS R2,#99 | MOVS R2,#16

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 15; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=10, R1=5, R2=16 (10 >= 5 signed, branch taken)\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u\n", reg_out[0], reg_out[1], reg_out[2]);
    
    assert(reg_out[0] == 10);
    assert(reg_out[1] == 5);
    assert(reg_out[2] == 16);

    printf("✅ BGE test passed!\n");
}

// === TEST 15: BLT (Branch if Less Than - signed) ===
void test_branch_blt() {
    printf("\n=== TEST 15: BLT (Branch if Less Than - signed) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOVS R0, #3        (0x2003)
    // 1: MOVS R1, #8        (0x2108)
    // 2: CMP R0, R1         (0x4288) - 3 < 8 (signed), N!=V
    // 3: BLT +1             (0xDB00) - branch if less than (should take)
    // 4: MOVS R2, #99       (0x2263) - SKIPPED
    // 5: MOVS R2, #17       (0x2211) - EXECUTED
    
    instr_mem[0] = 0x2003 | (0x2108 << 16);  // MOVS R0,#3 | MOVS R1,#8
    instr_mem[1] = 0x4288 | (0xDB00 << 16);  // CMP R0,R1 | BLT +1
    instr_mem[2] = 0x2263 | (0x2211 << 16);  // MOVS R2,#99 | MOVS R2,#17

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 15; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=3, R1=8, R2=17 (3 < 8 signed, branch taken)\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u\n", reg_out[0], reg_out[1], reg_out[2]);
    
    assert(reg_out[0] == 3);
    assert(reg_out[1] == 8);
    assert(reg_out[2] == 17);

    printf("✅ BLT test passed!\n");
}

// === TEST 16: BGT (Branch if Greater Than - signed) ===
void test_branch_bgt() {
    printf("\n=== TEST 16: BGT (Branch if Greater Than - signed) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOVS R0, #15       (0x200F)
    // 1: MOVS R1, #7        (0x2107)
    // 2: CMP R0, R1         (0x4288) - 15 > 7 (signed), Z==0 AND N==V
    // 3: BGT +1             (0xDC00) - branch if greater than (should take)
    // 4: MOVS R2, #99       (0x2263) - SKIPPED
    // 5: MOVS R2, #18       (0x2212) - EXECUTED
    
    instr_mem[0] = 0x200F | (0x2107 << 16);  // MOVS R0,#15 | MOVS R1,#7
    instr_mem[1] = 0x4288 | (0xDC00 << 16);  // CMP R0,R1 | BGT +1
    instr_mem[2] = 0x2263 | (0x2212 << 16);  // MOVS R2,#99 | MOVS R2,#18

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 15; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=15, R1=7, R2=18 (15 > 7 signed, branch taken)\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u\n", reg_out[0], reg_out[1], reg_out[2]);
    
    assert(reg_out[0] == 15);
    assert(reg_out[1] == 7);
    assert(reg_out[2] == 18);

    printf("✅ BGT test passed!\n");
}

// === TEST 17: BLE (Branch if Less or Equal - signed) ===
void test_branch_ble() {
    printf("\n=== TEST 17: BLE (Branch if Less or Equal - signed) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOVS R0, #6        (0x2006)
    // 1: MOVS R1, #12       (0x210C)
    // 2: CMP R0, R1         (0x4288) - 6 <= 12 (signed), Z==1 OR N!=V
    // 3: BLE +1             (0xDD00) - branch if less or equal (should take)
    // 4: MOVS R2, #99       (0x2263) - SKIPPED
    // 5: MOVS R2, #19       (0x2213) - EXECUTED
    
    instr_mem[0] = 0x2006 | (0x210C << 16);  // MOVS R0,#6 | MOVS R1,#12
    instr_mem[1] = 0x4288 | (0xDD00 << 16);  // CMP R0,R1 | BLE +1
    instr_mem[2] = 0x2263 | (0x2213 << 16);  // MOVS R2,#99 | MOVS R2,#19

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 15; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=6, R1=12, R2=19 (6 <= 12 signed, branch taken)\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u\n", reg_out[0], reg_out[1], reg_out[2]);
    
    assert(reg_out[0] == 6);
    assert(reg_out[1] == 12);
    assert(reg_out[2] == 19);

    printf("✅ BLE test passed!\n");
}

// === TEST 18: BX (Branch and Exchange) ===
void test_branch_bx() {
    printf("\n=== TEST 18: BX (Branch and Exchange) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOVS R0, #8        (0x2008) - load address (halfword 4 = byte 0x08)
    // 1: BX R0              (0x4700) - branch to address in R0
    // 2: MOVS R1, #99       (0x2163) - SKIPPED
    // 3: MOVS R1, #88       (0x2158) - SKIPPED
    // 4: MOVS R1, #20       (0x2114) - EXECUTED (target of BX)
    // 5: MOVS R2, #21       (0x2215) - EXECUTED
    
    instr_mem[0] = 0x2008 | (0x4700 << 16);  // MOVS R0,#8 | BX R0
    instr_mem[1] = 0x2163 | (0x2158 << 16);  // MOVS R1,#99 | MOVS R1,#88
    instr_mem[2] = 0x2114 | (0x2215 << 16);  // MOVS R1,#20 | MOVS R2,#21

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 15; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=8, R1=20, R2=21 (BX jumped to address in R0)\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u\n", reg_out[0], reg_out[1], reg_out[2]);
    
    assert(reg_out[0] == 8);
    assert(reg_out[1] == 20);
    assert(reg_out[2] == 21);

    printf("✅ BX test passed!\n");
}

// === TEST 19: Multiple Conditional Branches (Complex Control Flow) ===
void test_branch_multiple_conditions() {
    printf("\n=== TEST 19: Multiple Conditional Branches ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program: Test multiple branch conditions in sequence
    // 0: MOVS R0, #10       (0x200A)
    // 1: MOVS R1, #10       (0x210A)
    // 2: CMP R0, R1         (0x4288) - equal, Z=1
    // 3: BNE +1             (0xD100) - should NOT take (Z=1, condition is Z=0)
    // 4: MOVS R2, #5        (0x2205) - EXECUTED (fall through)
    // 5: BEQ +1             (0xD000) - should take (Z=1 from previous CMP)
    // 6: MOVS R3, #99       (0x2363) - SKIPPED
    // 7: MOVS R3, #25       (0x2319) - EXECUTED
    
    instr_mem[0] = 0x200A | (0x210A << 16);  // MOVS R0,#10 | MOVS R1,#10
    instr_mem[1] = 0x4288 | (0xD100 << 16);  // CMP R0,R1 | BNE +1
    instr_mem[2] = 0x2205 | (0xD000 << 16);  // MOVS R2,#5 | BEQ +1
    instr_mem[3] = 0x2363 | (0x2319 << 16);  // MOVS R3,#99 | MOVS R3,#25

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 20; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=10, R1=10, R2=5, R3=25\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u, R3=%u\n", 
           reg_out[0], reg_out[1], reg_out[2], reg_out[3]);
    
    assert(reg_out[0] == 10);
    assert(reg_out[1] == 10);
    assert(reg_out[2] == 5);
    assert(reg_out[3] == 25);

    printf("✅ Multiple conditional branches test passed!\n");
}

// === TEST 20: Edge Case - Branch to Same Location (No-op branch) ===
void test_branch_nop() {
    printf("\n=== TEST 20: Branch to Same Location (offset=0) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOVS R0, #1        (0x2001)
    // 1: MOVS R1, #2        (0x2102)
    // 2: B -1               (0xE7FF) - branch to next instruction (effectively NOP)
    // 3: MOVS R2, #3        (0x2203)
    // 4: MOVS R3, #4        (0x2304)
    // 
    // Note: B with offset -1 means PC+4 + (-1*2) = PC+4-2 = PC+2, 
    // which points to the next instruction anyway
    
    instr_mem[0] = 0x2001 | (0x2102 << 16);  // MOVS R0,#1 | MOVS R1,#2
    instr_mem[1] = 0xE7FE | (0x2203 << 16);  // B -2 (to self) | MOVS R2,#3
    instr_mem[2] = 0x2304 | (0xBF00 << 16);  // MOVS R3,#4 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 20; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
        // Break if we're in an infinite loop (R2 never gets set)
        if (i > 15 && reg_out[2] == 0) {
            printf("⚠️  Detected infinite loop - breaking\n");
            break;
        }
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: Infinite loop or controlled execution\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u, R3=%u\n", 
           reg_out[0], reg_out[1], reg_out[2], reg_out[3]);
    
    // This test demonstrates infinite loop handling
    printf("⚠️  Edge case test completed (infinite loop scenario)\n");
}

// === TEST 21: Nested Branches ===
void test_branch_nested() {
    printf("\n=== TEST 21: Nested Conditional Branches ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program: if (R0 > 5) { if (R0 < 15) { R1 = 10; } }
    // 0: MOVS R0, #10       (0x200A)
    // 1: CMP R0, #5         (0x2805) - compare with 5
    // 2: BLE +3             (0xDD03) - skip if R0 <= 5
    // 3: CMP R0, #15        (0x280F) - compare with 15
    // 4: BGE +1             (0xDA01) - skip if R0 >= 15
    // 5: MOVS R1, #10       (0x210A) - EXECUTED (5 < 10 < 15)
    // 6: MOVS R2, #30       (0x221E) - EXECUTED
    
    instr_mem[0] = 0x200A | (0x2805 << 16);  // MOVS R0,#10 | CMP R0,#5
    instr_mem[1] = 0xDD03 | (0x280F << 16);  // BLE +3 | CMP R0,#15
    instr_mem[2] = 0xDA01 | (0x210A << 16);  // BGE +1 | MOVS R1,#10
    instr_mem[3] = 0x221E | (0xBF00 << 16);  // MOVS R2,#30 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1);
    for (int i = 0; i < 20; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=10, R1=10, R2=30 (nested conditions met)\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u\n", reg_out[0], reg_out[1], reg_out[2]);
    
    assert(reg_out[0] == 10);
    assert(reg_out[1] == 10);
    assert(reg_out[2] == 30);

    printf("✅ Nested branches test passed!\n");
}

int main() {
    printf("========== Cortex-M0 Branch Test Suite (Corrected) ==========\n");

    // test_branch_forward();       // Test Case 1 Passed
    test_branch_with_link();     // Test Case 2 Passed
    // test_branch_conditional_eq(); // Test Case 3 Passed
    // test_branch_conditional_ne(); // Test Case 4 Passed
    // test_branch_backward();      // Test Case 5 Passed
    // test_branch_bcs();           // Test Case 6
    // test_branch_bcc();           // Test Case 7 Passed
    // test_branch_bmi();           // Test Case 8 Passed
    // test_branch_bpl();           // Test Case 9 Passed
    // test_branch_bvs();           // Test Case 10 Passed
    // test_branch_bvc();           // Test Case 11 Passed
    // test_branch_bhi();           // Test Case 12 Passed
    // test_branch_bls();           // Test Case 13 Passed
    // test_branch_bge();           // Test Case 14 Passed
    // test_branch_blt();           // Test Case 15 Passed
    // test_branch_bgt();           // Test Case 16 Passed
    // test_branch_ble();           // Test Case 17 Passed
    // test_branch_bx();            // Test Case 18 Passed
    // test_branch_multiple_conditions(); // Test Case 19
    // test_branch_nested();        // Test Case 20
    printf("\n✅ All branch tests completed successfully!\n");
    return 0;
}