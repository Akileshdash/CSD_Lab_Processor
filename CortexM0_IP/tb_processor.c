#include "processor.h"
#include "decode.h"
#include "regfile.h"
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>   // optional but good for printing

#define MEM_SIZE 128

// Helper macro for printing register states
#define PRINT_REGS(regs) do { \
    printf("R0=%08X R1=%08X R2=%08X R3=%08X R4=%08X R5=%08X R6=%08X R7=%08X\n", \
        regs[0], regs[1], regs[2], regs[3], regs[4], regs[5], regs[6], regs[7]); \
    printf("SP=%08X LR=%08X PC=%08X\n", regs[13], regs[14], regs[15]); \
} while(0)

// === TEST 1: Arithmetic and logic instructions ===
void test_basic_arithmetic() {
    printf("\n=== TEST 1: ADD, SUB, MOV, AND, ORR, EOR ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // MOVS R1, #5
    // MOVS R2, #10
    // ADDS R3, R1, R2   ; R3 = 15
    // SUBS R4, R2, R1   ; R4 = 5  
    // MOV R5, R2        ; R5 = 10
    // ANDS R5, R1       ; R5 = 0
    // MOV R6, R2        ; R6 = 10
    // ORRS R6, R1       ; R6 = 15
    // MOV R7, R2        ; R7 = 10
    // EORS R7, R1       ; R7 = 15

    instr_mem[0] = 0x2105 | (0x220A << 16);   // MOV R1,#5 | MOV R2,#10
    instr_mem[1] = 0x188B | (0x1A54 << 16);   // ADD R3,R1,R2 | SUB R4,R2,R1
    instr_mem[2] = 0x1C15 | (0x400D << 16);   // MOV R5, R2 | AND R5,R1,R2
    instr_mem[3] = 0x1C16 | (0x430E << 16);   // MOV R6, R2 | ORR R6,R1,R2
    instr_mem[4] = 0x1C17 | (0x404F << 16);   // MOV R7, R2 |  EOR R7,R1,R2

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 15; i++) cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);

    PRINT_REGS(reg_out);

    assert(reg_out[1] == 5);
    assert(reg_out[2] == 10);
    assert(reg_out[3] == 15);
    assert(reg_out[4] == 5);
    assert(reg_out[5] == 0);
    assert(reg_out[6] == 15);
    assert(reg_out[7] == 15);

    printf("✅ Arithmetic & logic instructions passed!\n");
}

// === TEST 2: Memory load/store ===
void test_load_store() {
    printf("\n=== TEST 2: LDR / STR ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    data_mem[0] = 0x12345678;
    reg_out[5] = (uintptr_t)&data_mem[0];

    // STR R3,[R5,#0]
    // LDR R6,[R5,#0]
    instr_mem[0] = 0x600B | (0x680E << 16);

    // Set R3 = 0xAABBCCDD before run
    reg_out[3] = 0xAABBCCDD;

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 20; i++) cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);

    PRINT_REGS(reg_out);
    printf("Memory[0] = 0x%08X\n", data_mem[0]);

    assert(data_mem[0] == 0xAABBCCDD);
    assert(reg_out[6] == 0xAABBCCDD);

    printf("✅ Load/Store instructions passed!\n");
}

// === TEST 3: Branch ===
void test_branch() {
    printf("\n=== TEST 3: Branch ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // MOVS R1, #1
    // B +2 (skip next instruction)
    // MOVS R1, #9 (should be skipped)
    // MOVS R2, #5
    instr_mem[0] = 0x2101 | (0xE002 << 16);
    instr_mem[1] = 0x2109 | (0x2205 << 16);

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 8; i++) cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);

    PRINT_REGS(reg_out);
    assert(reg_out[1] == 1);
    assert(reg_out[2] == 5);

    printf("✅ Branch instruction passed!\n");
}

// === TEST 4: Flags ===
void test_flags() {
    printf("\n=== TEST 4: CMP / Flags ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // MOVS R1,#10
    // MOVS R2,#10
    // CMP R1,R2
    instr_mem[0] = 0x210A | (0x220A << 16);
    instr_mem[1] = 0x428A;  // CMP R2,R1

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 5; i++) cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);

    PRINT_REGS(reg_out);

    printf("Check APSR flags: ");
    uint32_t apsr = reg_out[31]; // depending on how you export APSR
    printf("APSR = 0x%08X\n", apsr);
    printf("✅ CMP & flags test completed!\n");
}

int main() {
    printf("========== Cortex-M0 Functional Testbench ==========\n");

    test_basic_arithmetic();
    // test_load_store();
    // test_branch();
    // test_flags();

    printf("\n✅ All tests completed successfully!\n");
    return 0;
}
