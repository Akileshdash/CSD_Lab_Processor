#include "processor.h"
#include "decode.h"
#include "regfile.h"
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>

#define MEM_SIZE 256
#define NUM_CYCLES 25

// Helper macro for printing register states
#define PRINT_REGS(regs) do { \
    printf("R0=%08X R1=%08X R2=%08X R3=%08X R4=%08X R5=%08X R6=%08X R7=%08X\n", \
        regs[0], regs[1], regs[2], regs[3], regs[4], regs[5], regs[6], regs[7]); \
    printf("SP=%08X LR=%08X PC=%08X\n", regs[13], regs[14], regs[15]); \
} while(0)

// Helper macro for printing memory
#define PRINT_MEM(data_mem, start, count) do { \
    printf("Memory dump from 0x%04X:\n", start*4); \
    for (int i = start; i < start + count; i++) { \
        printf("  [0x%04X]: 0x%08X\n", i*4, data_mem[i]); \
    } \
} while(0)

/*
 * THUMB INSTRUCTION ENCODING REFERENCE:
 * 
 * MOV immediate (001 00 Rd imm8):
 *   0x2000 + (Rd << 8) + imm8
 *   e.g., MOV R0, #16 = 0x2010
 * 
 * LDR with immediate offset (01101 imm5 Rn Rd):
 *   Bits: [15:11]=01101, [10:6]=imm5, [5:3]=Rn, [2:0]=Rd
 *   0x6800 + (imm5 << 6) + (Rn << 3) + Rd
 *   e.g., LDR R1, [R0, #0] = 0x6800 + (0 << 6) + (0 << 3) + 1 = 0x6801
 * 
 * LDR with register offset (0101 100 Rm Rn Rd):
 *   Bits: [15:9]=0101100, [8:6]=Rm, [5:3]=Rn, [2:0]=Rd
 *   0x5800 + (Rm << 6) + (Rn << 3) + Rd
 *   e.g., LDR R2, [R0, R1] = 0x5800 + (1 << 6) + (0 << 3) + 2 = 0x5842
 * 
 * STR with immediate offset (01100 imm5 Rn Rd):
 *   0x6000 + (imm5 << 6) + (Rn << 3) + Rd
 *   e.g., STR R1, [R0, #0] = 0x6000 + (0 << 6) + (0 << 3) + 1 = 0x6001
 * 
 * LDRB with immediate offset (01111 imm5 Rn Rd):
 *   0x7800 + (imm5 << 6) + (Rn << 3) + Rd
 *   e.g., LDRB R1, [R0, #0] = 0x7800 + (0 << 6) + (0 << 3) + 1 = 0x7801
 * 
 * STRB with immediate offset (01110 imm5 Rn Rd):
 *   0x7000 + (imm5 << 6) + (Rn << 3) + Rd
 *   e.g., STRB R1, [R0, #0] = 0x7000 + (0 << 6) + (0 << 3) + 1 = 0x7001
 * 
 * LDRH with immediate offset (10001 imm5 Rn Rd):
 *   0x8800 + (imm5 << 6) + (Rn << 3) + Rd
 *   e.g., LDRH R1, [R0, #0] = 0x8800 + (0 << 6) + (0 << 3) + 1 = 0x8801
 * 
 * STRH with immediate offset (10000 imm5 Rn Rd):
 *   0x8000 + (imm5 << 6) + (Rn << 3) + Rd
 *   e.g., STRH R1, [R0, #0] = 0x8000 + (0 << 6) + (0 << 3) + 1 = 0x8001
 * 
 * LDRB with register offset (0101 110 Rm Rn Rd):
 *   0x5C00 + (Rm << 6) + (Rn << 3) + Rd
 *   e.g., LDRB R2, [R0, R1] = 0x5C00 + (1 << 6) + (0 << 3) + 2 = 0x5C42
 * 
 * LDRSB with register offset (0101 011 Rm Rn Rd):
 *   0x5600 + (Rm << 6) + (Rn << 3) + Rd
 *   e.g., LDRSB R2, [R0, R1] = 0x5600 + (1 << 6) + (0 << 3) + 2 = 0x5642
 * 
 * LDRSH with register offset (0101 111 Rm Rn Rd):
 *   0x5E00 + (Rm << 6) + (Rn << 3) + Rd
 *   e.g., LDRSH R2, [R0, R1] = 0x5E00 + (1 << 6) + (0 << 3) + 2 = 0x5E42
 */

// ============================================================================
// TEST 1: LDR with Immediate Offset (Load Word)
// ============================================================================
void test_ldr_imm() {
    printf("\n=== TEST 1: LDR with Immediate Offset ===\n");
    printf("Purpose: Load 32-bit word from memory with immediate offset\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Setup: Initialize data in memory at word offset 4 (byte address 0x10)
    data_mem[4] = 0x12345678;

    // Program:
    // 0x0000: MOV R0, #16      (0x2010) - R0 = 16 (address for later)
    // 0x0002: LDR R1, [R0, #0] (0x6801) - R1 = [R0+0] = [16] = data_mem[4] = 0x12345678
    // Encoding: LDR immediate is 01101 imm5 Rn Rd
    // For [R0, #0]: imm5=0, Rn=0, Rd=1 => 0x6800 + (0<<6) + (0<<3) + 1 = 0x6801
    
    instr_mem[0] = 0x2010 | (0x6801 << 16);

    // Reset and run
    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    PRINT_MEM(data_mem, 4, 2);

    printf("Expected: R0=16, R1=0x12345678\n");
    printf("Actual:   R0=%08X, R1=%08X\n", reg_out[0], reg_out[1]);

    assert(reg_out[0] == 16);
    assert(reg_out[1] == 0x12345678);

    printf("✅ LDR_IMM test passed!\n");
}

// ============================================================================
// TEST 2: LDR with Register Offset
// ============================================================================
void test_ldr_reg() {
    printf("\n=== TEST 2: LDR with Register Offset ===\n");
    printf("Purpose: Load 32-bit word from memory with register offset\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Setup: Initialize data in memory
    data_mem[5] = 0xDEADBEEF;

    // Program:
    // 0x0000: MOV R0, #20      (0x2014) - R0 = 20
    // 0x0002: MOV R1, #0       (0x2100) - R1 = 0
    // 0x0004: LDR R2, [R0, R1] (0x5842) - R2 = [R0+R1] = [20] = data_mem[5]
    // Encoding: LDR register offset is 0101100 Rm Rn Rd
    // For [R0, R1]: Rm=1, Rn=0, Rd=2 => 0x5800 + (1<<6) + (0<<3) + 2 = 0x5842
    
    instr_mem[0] = 0x2014 | (0x2100 << 16);
    instr_mem[1] = 0x5842 | (0xBF00 << 16);  // 0xBF00 = NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);

    printf("Expected: R0=20, R1=0, R2=0xDEADBEEF\n");
    printf("Actual:   R0=%08X, R1=%08X, R2=%08X\n", reg_out[0], reg_out[1], reg_out[2]);

    assert(reg_out[0] == 20);
    assert(reg_out[1] == 0);
    assert(reg_out[2] == 0xDEADBEEF);

    printf("✅ LDR_REG test passed!\n");
}

// ============================================================================
// TEST 3: STR with Immediate Offset (Store Word)
// ============================================================================
void test_str_imm() {
    printf("\n=== TEST 3: STR with Immediate Offset ===\n");
    printf("Purpose: Store 32-bit word to memory with immediate offset\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0x0000: MOV R0, #24      (0x2018) - R0 = 24 (address)
    // 0x0002: MOV R1, #0x34    (0x2134) - R1 = 0x34 (value to store)
    // 0x0004: STR R1, [R0, #0] (0x6001) - [R0+0] = R1
    // Encoding: STR immediate is 01100 imm5 Rn Rd
    // For [R0, #0]: imm5=0, Rn=0, Rd=1 => 0x6000 + (0<<6) + (0<<3) + 1 = 0x6001
    
    instr_mem[0] = 0x2018 | (0x2134 << 16);
    instr_mem[1] = 0x6001 | (0xBF00 << 16);

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    PRINT_MEM(data_mem, 6, 2);

    printf("Expected: R0=24, R1=0x34, data_mem[6]=0x34\n");
    printf("Actual:   R0=%08X, R1=%08X, data_mem[6]=%08X\n", 
           reg_out[0], reg_out[1], data_mem[6]);

    assert(reg_out[0] == 24);
    assert(reg_out[1] == 52);
    assert(data_mem[6] == 52);

    printf("✅ STR_IMM test passed!\n");
}

// ============================================================================
// TEST 4: STR with Register Offset
// ============================================================================
void test_str_reg() {
    printf("\n=== TEST 4: STR with Register Offset ===\n");
    printf("Purpose: Store 32-bit word to memory with register offset\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};


    // Instruction sequence:
    // 0x0000: MOV R0, #28      - R0 = 28 (byte address for data_mem[7])
    // 0x0002: MOV R1, #0       - R1 = 0 (no offset)
    // 0x0004: LDR R2, [R0, R1] - R2 = data_mem[28>>2] = data_mem[7] = 0xDEADBEEF
    // 0x0006: MOV R3, #44      - R3 = 44 (byte address for data_mem[11])
    // 0x0008: MOV R4, #0       - R4 = 0 (no offset)
    // 0x000A: STR R2, [R3, R4] - data_mem[44>>2] = R2 → data_mem[11] = 0xDEADBEEF

    // Setup: Initialize data in memory
    data_mem[7] = 0xDEADBEEF;
    
    instr_mem[0] = 0x201C | (0x2100 << 16);
    instr_mem[1] = 0x5842 | (0x232C << 16);
    instr_mem[2] = 0x2400 | (0x511A << 16);

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    PRINT_MEM(data_mem, 7, 2);

    printf("\nExpected:\n");
    printf("  R0=28, R1=0, R2=0xDEADBEEF, R3=44, R4=0\n");
    printf("  data_mem[7]=0xDEADBEEF (unchanged - source)\n");
    printf("  data_mem[11]=0xDEADBEEF (destination after store)\n");
    
    printf("\nActual:\n");
    printf("  R0=%d, R1=%d, R2=0x%08X, R3=%d, R4=%d\n", 
           reg_out[0], reg_out[1], reg_out[2], reg_out[3], reg_out[4]);
    printf("  data_mem[7]=0x%08X\n", data_mem[7]);
    printf("  data_mem[11]=0x%08X\n", data_mem[11]);

    assert(reg_out[0] == 28);
    assert(reg_out[1] == 0);
    assert(reg_out[2] == 0xDEADBEEF);
    assert(reg_out[3] == 44);
    assert(reg_out[4] == 0);
    assert(data_mem[7] == 0xDEADBEEF);      // Source unchanged
    assert(data_mem[11] == 0xDEADBEEF);     // Successfully stored


    printf("✅ STR_REG test passed!\n");
}

// ============================================================================
// TEST 5: LDRB with Immediate Offset (Load Byte - Unsigned)
// ============================================================================
void test_ldrb_imm() {
    printf("\n=== TEST 5: LDRB with Immediate Offset ===\n");
    printf("Purpose: Load unsigned byte from memory with immediate offset\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Setup: Initialize byte in memory
    data_mem[8] = 0x000000FF;

    // Program:
    // 0x0000: MOV R0, #32      (0x2020) - R0 = 32
    // 0x0002: LDRB R1, [R0, #0] (0x7801) - R1 = [R0+0] & 0xFF
    // Encoding: LDRB immediate is 01111 imm5 Rn Rd
    // For [R0, #0]: imm5=0, Rn=0, Rd=1 => 0x7800 + (0<<6) + (0<<3) + 1 = 0x7801
    
    instr_mem[0] = 0x2020 | (0x7801 << 16);

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);

    printf("Expected: R0=32, R1=0xFF\n");
    printf("Actual:   R0=%08X, R1=%08X\n", reg_out[0], reg_out[1]);

    assert(reg_out[0] == 32);
    assert(reg_out[1] == 0xFF);

    printf("✅ LDRB_IMM test passed!\n");
}

// ============================================================================
// TEST 6: STRB with Immediate Offset (Store Byte)
// ============================================================================
void test_strb_imm() {
    printf("\n=== TEST 6: STRB with Immediate Offset ===\n");
    printf("Purpose: Store byte to memory with immediate offset\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0x0000: MOV R0, #36      (0x2024) - R0 = 36
    // 0x0002: MOV R1, #0x77    (0x2177) - R1 = 0x77
    // 0x0004: STRB R1, [R0, #0] (0x7001) - [R0+0] = R1 & 0xFF
    // Encoding: STRB immediate is 01110 imm5 Rn Rd
    // For [R0, #0]: imm5=0, Rn=0, Rd=1 => 0x7000 + (0<<6) + (0<<3) + 1 = 0x7001
    
    instr_mem[0] = 0x2024 | (0x2177 << 16);
    instr_mem[1] = 0x7001 | (0xBF00 << 16);

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    PRINT_MEM(data_mem, 9, 2);

    printf("Expected: R0=36, R1=0x77, data_mem[9] byte=0x77\n");
    printf("Actual:   R0=%08X, R1=%08X, data_mem[9]=%08X\n", 
           reg_out[0], reg_out[1], data_mem[9]);

    assert(reg_out[0] == 36);
    assert(reg_out[1] == 0x77);
    assert((data_mem[9] & 0xFF) == 0x77);

    printf("✅ STRB_IMM test passed!\n");
}

// ============================================================================
// TEST 7: LDRH with Immediate Offset (Load Halfword - Unsigned)
// ============================================================================
void test_ldrh_imm() {
    printf("\n=== TEST 7: LDRH with Immediate Offset ===\n");
    printf("Purpose: Load unsigned halfword from memory with immediate offset\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Setup: Initialize halfword in memory
    data_mem[10] = 0x0000ABCD;

    // Program:
    // 0x0000: MOV R0, #40      (0x2028) - R0 = 40
    // 0x0002: LDRH R1, [R0, #0] (0x8801) - R1 = [R0+0] & 0xFFFF
    // Encoding: LDRH immediate is 10001 imm5 Rn Rd
    // For [R0, #0]: imm5=0, Rn=0, Rd=1 => 0x8800 + (0<<6) + (0<<3) + 1 = 0x8801
    
    instr_mem[0] = 0x2028 | (0x8801 << 16);

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);

    printf("Expected: R0=40, R1=0xABCD\n");
    printf("Actual:   R0=%08X, R1=%08X\n", reg_out[0], reg_out[1]);

    assert(reg_out[0] == 40);
    assert(reg_out[1] == 0xABCD);

    printf("✅ LDRH_IMM test passed!\n");
}

// ============================================================================
// TEST 8: STRH with Immediate Offset (Store Halfword)
// ============================================================================
void test_strh_imm() {
    printf("\n=== TEST 8: STRH with Immediate Offset ===\n");
    printf("Purpose: Store halfword to memory with immediate offset\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0x0000: MOV R0, #44      (0x202C) - R0 = 44
    // 0x0002: MOV R1, #0xCD    (0x21CD) - R1 = 0xCD
    // 0x0004: STRH R1, [R0, #0] (0x8001) - [R0+0] = R1 & 0xFFFF
    // Encoding: STRH immediate is 10000 imm5 Rn Rd
    // For [R0, #0]: imm5=0, Rn=0, Rd=1 => 0x8000 + (0<<6) + (0<<3) + 1 = 0x8001
    
    instr_mem[0] = 0x202C | (0x21CD << 16);
    instr_mem[1] = 0x8001 | (0xBF00 << 16);

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    PRINT_MEM(data_mem, 11, 2);

    printf("Expected: R0=44, R1=0xCD, data_mem[11] halfword=0xCD\n");
    printf("Actual:   R0=%08X, R1=%08X, data_mem[11]=%08X\n", 
           reg_out[0], reg_out[1], data_mem[11]);

    assert(reg_out[0] == 44);
    assert(reg_out[1] == 0xCD);
    assert((data_mem[11] & 0xFFFF) == 0xCD);

    printf("✅ STRH_IMM test passed!\n");
}

// ============================================================================
// TEST 9: LDRSB with Register Offset (Load Signed Byte)
// ============================================================================
void test_ldrsb_reg() {
    printf("\n=== TEST 9: LDRSB with Register Offset ===\n");
    printf("Purpose: Load signed byte from memory with register offset\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Setup: Initialize signed byte (0xFF = -1)
    data_mem[12] = 0x000000FF;

    // Program:
    // 0x0000: MOV R0, #48      (0x2030) - R0 = 48
    // 0x0002: MOV R1, #0       (0x2100) - R1 = 0
    // 0x0004: LDRSB R2, [R0, R1] (0x5642) - R2 = sign_extend([R0+R1])
    // Encoding: LDRSB is 0101011 Rm Rn Rd
    // For [R0, R1]: Rm=1, Rn=0, Rd=2 => 0x5600 + (1<<6) + (0<<3) + 2 = 0x5642
    
    instr_mem[0] = 0x2030 | (0x2100 << 16);
    instr_mem[1] = 0x5642 | (0xBF00 << 16);

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);

    printf("Expected: R0=48, R1=0, R2=0xFFFFFFFF (-1)\n");
    printf("Actual:   R0=%08X, R1=%08X, R2=%08X\n", reg_out[0], reg_out[1], reg_out[2]);

    assert(reg_out[0] == 48);
    assert(reg_out[1] == 0);
    assert((int32_t)reg_out[2] == -1);

    printf("✅ LDRSB_REG test passed!\n");
}

// ============================================================================
// TEST 10: LDRSH with Register Offset (Load Signed Halfword)
// ============================================================================
void test_ldrsh_reg() {
    printf("\n=== TEST 10: LDRSH with Register Offset ===\n");
    printf("Purpose: Load signed halfword from memory with register offset\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Setup: Initialize signed halfword (0xFFFF = -1)
    data_mem[13] = 0x0000FFFF;

    // Program:
    // 0x0000: MOV R0, #52      (0x2034) - R0 = 52
    // 0x0002: MOV R1, #0       (0x2100) - R1 = 0
    // 0x0004: LDRSH R2, [R0, R1] (0x5E42) - R2 = sign_extend([R0+R1])
    // Encoding: LDRSH is 0101111 Rm Rn Rd
    // For [R0, R1]: Rm=1, Rn=0, Rd=2 => 0x5E00 + (1<<6) + (0<<3) + 2 = 0x5E42
    
    instr_mem[0] = 0x2034 | (0x2100 << 16);
    instr_mem[1] = 0x5E42 | (0xBF00 << 16);

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);

    printf("Expected: R0=52, R1=0, R2=0xFFFFFFFF (-1)\n");
    printf("Actual:   R0=%08X, R1=%08X, R2=%08X\n", reg_out[0], reg_out[1], reg_out[2]);

    assert(reg_out[0] == 52);
    assert(reg_out[1] == 0);
    assert((int32_t)reg_out[2] == -1);

    printf("✅ LDRSH_REG test passed!\n");
}

// ============================================================================
// TEST 11: LDRB with Register Offset
// ============================================================================
void test_ldrb_reg() {
    printf("\n=== TEST 11: LDRB with Register Offset ===\n");
    printf("Purpose: Load unsigned byte from memory with register offset\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Setup
    data_mem[14] = 0x000000AA;

    // Program:
    // 0x0000: MOV R0, #56      (0x2038) - R0 = 56
    // 0x0002: MOV R1, #0       (0x2100) - R1 = 0
    // 0x0004: LDRB R2, [R0, R1] (0x5C42) - R2 = [R0+R1] & 0xFF
    // Encoding: LDRB register is 0101110 Rm Rn Rd
    // For [R0, R1]: Rm=1, Rn=0, Rd=2 => 0x5C00 + (1<<6) + (0<<3) + 2 = 0x5C42
    
    instr_mem[0] = 0x2038 | (0x2100 << 16);
    instr_mem[1] = 0x5C42 | (0xBF00 << 16);

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);

    printf("Expected: R0=56, R1=0, R2=0xAA\n");
    printf("Actual:   R0=%08X, R1=%08X, R2=%08X\n", reg_out[0], reg_out[1], reg_out[2]);

    assert(reg_out[0] == 56);
    assert(reg_out[1] == 0);
    assert(reg_out[2] == 0xAA);

    printf("✅ LDRB_REG test passed!\n");
}

// ============================================================================
// TEST 12: STRB with Register Offset
// ============================================================================
void test_strb_reg() {
    printf("\n=== TEST 12: STRB with Register Offset ===\n");
    printf("Purpose: Store byte to memory with register offset\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0x0000: MOV R0, #60      (0x203C) - R0 = 60
    // 0x0002: MOV R1, #0       (0x2100) - R1 = 0
    // 0x0004: MOV R2, #0x33    (0x2233) - R2 = 0x33
    // 0x0006: STRB R2, [R0, R1] (0x5402) - [R0+R1] = R2 & 0xFF
    // Encoding: STRB register is 0101010 Rm Rn Rd
    // For [R0, R1]: Rm=1, Rn=0, Rd=2 => 0x5400 + (1<<6) + (0<<3) + 2 = 0x5442
    
    instr_mem[0] = 0x203C | (0x2100 << 16);
    instr_mem[1] = 0x2233 | (0x5442 << 16);

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    PRINT_MEM(data_mem, 15, 2);

    printf("Expected: R0=60, R1=0, R2=0x33, data_mem[15] byte=0x33\n");
    printf("Actual:   R0=%08X, R1=%08X, R2=%08X, data_mem[15]=%08X\n", 
           reg_out[0], reg_out[1], reg_out[2], data_mem[15]);

    assert(reg_out[0] == 60);
    assert(reg_out[1] == 0);
    assert(reg_out[2] == 0x33);
    assert((data_mem[15] & 0xFF) == 0x33);

    printf("✅ STRB_REG test passed!\n");
}

// ============================================================================
// TEST 13: LDRH with Register Offset
// ============================================================================
void test_ldrh_reg() {
    printf("\n=== TEST 13: LDRH with Register Offset ===\n");
    printf("Purpose: Load unsigned halfword from memory with register offset\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Setup
    data_mem[16] = 0x0000FACE;

    // Program:
    // 0x0000: MOV R0, #64      (0x2040) - R0 = 64
    // 0x0002: MOV R1, #0       (0x2100) - R1 = 0
    // 0x0004: LDRH R2, [R0, R1] (0x5A42) - R2 = [R0+R1] & 0xFFFF
    // Encoding: LDRH register is 0101101 Rm Rn Rd
    // For [R0, R1]: Rm=1, Rn=0, Rd=2 => 0x5A00 + (1<<6) + (0<<3) + 2 = 0x5A42
    
    instr_mem[0] = 0x2040 | (0x2100 << 16);
    instr_mem[1] = 0x5A42 | (0xBF00 << 16);

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);

    printf("Expected: R0=64, R1=0, R2=0xFACE\n");
    printf("Actual:   R0=%08X, R1=%08X, R2=%08X\n", reg_out[0], reg_out[1], reg_out[2]);

    assert(reg_out[0] == 64);
    assert(reg_out[1] == 0);
    assert(reg_out[2] == 0xFACE);

    printf("✅ LDRH_REG test passed!\n");
}

// ============================================================================
// TEST 14: STRH with Register Offset
// ============================================================================
void test_strh_reg() {
    printf("\n=== TEST 14: STRH with Register Offset ===\n");
    printf("Purpose: Store halfword to memory with register offset\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0x0000: MOV R0, #68      (0x2044) - R0 = 68
    // 0x0002: MOV R1, #0       (0x2100) - R1 = 0
    // 0x0004: MOV R2, #0xEF    (0x22EF) - R2 = 0xEF
    // 0x0006: STRH R2, [R0, R1] (0x5242) - [R0+R1] = R2 & 0xFFFF
    // Encoding: STRH register is 0101001 Rm Rn Rd
    // For [R0, R1]: Rm=1, Rn=0, Rd=2 => 0x5200 + (1<<6) + (0<<3) + 2 = 0x5242
    
    instr_mem[0] = 0x2044 | (0x2100 << 16);
    instr_mem[1] = 0x22EF | (0x5242 << 16);

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    PRINT_MEM(data_mem, 17, 2);

    printf("Expected: R0=68, R1=0, R2=0xEF, data_mem[17] halfword=0xEF\n");
    printf("Actual:   R0=%08X, R1=%08X, R2=%08X, data_mem[17]=%08X\n", 
           reg_out[0], reg_out[1], reg_out[2], data_mem[17]);

    assert(reg_out[0] == 68);
    assert(reg_out[1] == 0);
    assert(reg_out[2] == 0xEF);
    assert((data_mem[17] & 0xFFFF) == 0xEF);

    printf("✅ STRH_REG test passed!\n");
}

// ============================================================================
// TEST 15: Combined Load and Store (Read-Modify-Write)
// ============================================================================
void test_load_store_chain() {
    printf("\n=== TEST 15: Combined Load and Store (Read-Modify-Write) ===\n");
    printf("Purpose: Load value, modify it, and store back\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Setup
    data_mem[18] = 0x00000010;  // Initial value = 16

    // Program:
    // 0x0000: MOV R0, #72      (0x2048) - R0 = 72 (address)
    // 0x0002: LDR R1, [R0, #0] (0x6801) - R1 = [R0+0] = 16
    // 0x0004: MOV R2, #5       (0x2205) - R2 = 5
    // 0x0006: ADDS R1, R1, R2  (0x1889) - R1 = R1 + R2 = 21
    // 0x0008: STR R1, [R0, #0] (0x6001) - [R0+0] = R1 = 21
    
    instr_mem[0] = 0x2048 | (0x6801 << 16);
    instr_mem[1] = 0x2205 | (0x1889 << 16);
    instr_mem[2] = 0x6001;

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < NUM_CYCLES; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    PRINT_MEM(data_mem, 18, 2);

    printf("Expected: R0=72, R1=21, R2=5, data_mem[18]=21\n");
    printf("Actual:   R0=%08X, R1=%08X, R2=%08X, data_mem[18]=%08X\n", 
           reg_out[0], reg_out[1], reg_out[2], data_mem[18]);

    assert(reg_out[0] == 72);
    assert(reg_out[1] == 21);
    assert(reg_out[2] == 5);
    assert(data_mem[18] == 21);

    printf("✅ Load-Store-Chain test passed!\n");
}


// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

int main() {
    printf("========== Cortex-M0 Load/Store Instruction Test Suite ==========\n");
    printf("Testing all 16-bit load and store instructions (FIXED ENCODINGS)\n\n");

    // Word Operations
    printf("\n========== WORD LOAD/STORE TESTS ==========\n");
    test_ldr_imm();             // TEST 1 Passed
    test_ldr_reg();             // TEST 2 Passed
    test_str_imm();             // TEST 3 Passed
    test_str_reg();             // TEST 4 Passed

    // Byte Operations
    printf("\n========== BYTE LOAD/STORE TESTS ==========\n");
    test_ldrb_imm();            // TEST 5  Passed
    test_ldrb_reg();            // TEST 11 Passed
    test_strb_imm();            // TEST 6 Passed
    test_strb_reg();            // TEST 12 Passed

    // Halfword Operations
    printf("\n========== HALFWORD LOAD/STORE TESTS ==========\n");
    test_ldrh_imm();            // TEST 7 Passed
    test_ldrh_reg();            // TEST 13 Passed
    test_strh_imm();            // TEST 8 Passed
    test_strh_reg();            // TEST 14 Passed

    // Signed Load Operations
    printf("\n========== SIGNED LOAD TESTS ==========\n");
    test_ldrsb_reg();           // TEST 9 Passed
    test_ldrsh_reg();           // TEST 10 Passed

    // Complex Operations
    printf("\n========== COMPLEX OPERATION TESTS ==========\n");
    test_load_store_chain();    // TEST 15 Passed

    printf("\n========== ✅ ALL TESTS PASSED! ==========\n");
    return 0;
}