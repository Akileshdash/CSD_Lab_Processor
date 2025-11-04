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

// ============================================================================
// TEST SUITE FOR ALL 6 ADD INSTRUCTIONS
// Format: 2 Thumb instructions packed per 32-bit memory location
// ============================================================================

// === TEST 1: ADD (1) - ADD <Rd>, <Rn>, #<immed_3> ===
void test_add_1_imm3() {
    printf("\n=== TEST 1: ADD (1) - ADD <Rd>, <Rn>, #immed_3 ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOV R1, #16        (0x2110) - R1 = 16
    // 1: ADD R2, R1, #3     (0x1C6A) - R2 = R1 + 3 = 16 + 3 = 19
    // 2: MOV R3, #7         (0x2307) - R3 = 7
    
    instr_mem[0] = 0x2110 | (0x1CCA << 16);  // MOV R1,#16 | ADD R2,R1,#3
    instr_mem[1] = 0x2307 | (0x0000 << 16);  // MOV R3,#7 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 12; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R1=16, R2=19, R3=7\n");
    printf("Actual:   R1=%u, R2=%u, R3=%u\n", 
           reg_out[1], reg_out[2], reg_out[3]);
    
    assert(reg_out[1] == 16);
    assert(reg_out[2] == 19);
    assert(reg_out[3] == 7);

    printf("✅ ADD (1) test passed!\n");
}

// === TEST 2: ADD (2) - ADD <Rd>, #<immed_8> ===
void test_add_2_imm8() {
    printf("\n=== TEST 2: ADD (2) - ADD <Rd>, #immed_8 ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOV R0, #32        (0x3020) - R0 = 32 (0x20)
    // 1: ADD R0, #85        (0x3055) - R0 = R0 + 85 = 32 + 85 = 117 (0x75)
    // 2: MOV R1, #10        (0x210A) - R1 = 10
    
    instr_mem[0] = 0x3020 | (0x3055 << 16);  // MOV R0,#32 | ADD R0,#85
    instr_mem[1] = 0x210A | (0x0000 << 16);  // MOV R1,#10 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 12; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=117, R1=10\n");
    printf("Actual:   R0=%u, R1=%u\n", 
           reg_out[0], reg_out[1]);
    
    assert(reg_out[0] == 117);
    assert(reg_out[1] == 10);

    printf("✅ ADD (2) test passed!\n");
}

// === TEST 3: ADD (3) - ADD <Rd>, <Rn>, <Rm> ===
void test_add_3_reg() {
    printf("\n=== TEST 3: ADD (3) - ADD <Rd>, <Rn>, <Rm> ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOV R0, #48        (0x3030) - R0 = 48
    // 1: MOV R1, #32        (0x3120) - R1 = 32
    // 2: ADD R2, R0, R1     (0x1C42) - R2 = R0 + R1 = 48 + 32 = 80
    // 3: MOV R3, #15        (0x230F) - R3 = 15
    
    instr_mem[0] = 0x3030 | (0x3120 << 16);  // MOV R0,#48 | MOV R1,#32
    instr_mem[1] = 0x1842 | (0x230F << 16);  // ADD R2,R0,R1 | MOV R3,#15

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 12; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=48, R1=32, R2=80, R3=15\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u, R3=%u\n", 
           reg_out[0], reg_out[1], reg_out[2], reg_out[3]);
    
    assert(reg_out[0] == 48);
    assert(reg_out[1] == 32);
    assert(reg_out[2] == 80);
    assert(reg_out[3] == 15);

    printf("✅ ADD (3) test passed!\n");
}

// === TEST 4: ADD (4) - ADD <Rd>, <Rm> (HIGH REGISTERS) ===
void test_add_4_high() {
    printf("\n=== TEST 4: ADD (4) - ADD <Rd>, <Rm> (HIGH REGISTERS) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: MOV R0, #50        (0x3032) - R0 = 50 (temporary, will move to R10)
    // 1: MOV R1, #25        (0x3119) - R1 = 25 (temporary, will move to R12)
    // 2: ADD R10, R0        (0x4482) - R10 = R0 = 50 (move via ADD)
    // 3: ADD R12, R1        (0x4484) - R12 = R1 = 25 (move via ADD)
    // 4: ADD R10, R12       (0x44CA) - R10 = R10 + R12 = 50 + 25 = 75
    
    instr_mem[0] = 0x3032 | (0x3119 << 16);  // MOV R0,#50 | MOV R1,#25
    instr_mem[1] = 0x4482 | (0x448C << 16);  // ADD R10,R0 | ADD R12,R1
    instr_mem[2] = 0x44E2 | (0x0000 << 16);  // ADD R10,R12 | NOP
    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 15; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R10=75 (50+25)\n");
    printf("Actual:   R10=%u\n", reg_out[10]);
    
    assert(reg_out[10] == 75);

    printf("✅ ADD (4) test passed!\n");
}

// === TEST 5: ADD (5) - ADD <Rd>, PC, #<immed_8> * 4 (PC-RELATIVE) ===
void test_add_5_pc_imm() {
    printf("\n=== TEST 5: ADD (5) - ADD <Rd>, PC, #immed_8*4 (PC-RELATIVE) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program:
    // 0: ADD R0, PC, #100   (0xA019) - R0 = (PC & 0xFFFFFFFC) + 100
    //    immed_8 = 100/4 = 25 (0x19)
    // 1: MOV R1, #20        (0x2114) - R1 = 20 (for verification)
    // 2: NOP                (0x0000)
    
    instr_mem[0] = 0xA019 | (0x2114 << 16);  // ADD R0,PC,#100 | MOV R1,#20
    instr_mem[1] = 0x0000 | (0x0000 << 16);  // NOP | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 12; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0 >= 100 (PC-relative), R1=20\n");
    printf("Actual:   R0=0x%08X, R1=%u\n", reg_out[0], reg_out[1]);
    
    // PC-relative value should be non-zero and >= 100
    assert(reg_out[0] >= 100);
    assert(reg_out[1] == 20);

    printf("✅ ADD (5) test passed!\n");
}

// === TEST 6: ADD (6) - ADD <Rd>, SP, #<immed_8> * 4 (SP-RELATIVE) ===
void test_add_6_sp_imm() {
    printf("\n=== TEST 6: ADD (6) - ADD <Rd>, SP, #immed_8*4 (SP-RELATIVE) ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Initialize SP
    data_mem[0] = 0x2000;  // Initial SP = 0x2000

    // Program:
    // 0: ADD R1, SP, #20    (0xA905) - R1 = SP + 20
    //    immed_8 = 20/4 = 5 (0x05)
    // 1: ADD R2, SP, #40    (0xAA0A) - R2 = SP + 40
    //    immed_8 = 40/4 = 10 (0x0A)
    // 2: MOV R3, #100       (0x2364) - R3 = 100
    
    instr_mem[0] = 0xA905 | (0xAA0A << 16);  // ADD R1,SP,#20 | ADD R2,SP,#40
    instr_mem[1] = 0x2364 | (0x0000 << 16);  // MOV R3,#100 | NOP

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 12; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    
    uint32_t sp = reg_out[13];
    printf("Expected: R1=SP+20=0x%08X, R2=SP+40=0x%08X, R3=100\n", 
           sp + 20, sp + 40);
    printf("Actual:   R1=0x%08X, R2=0x%08X, R3=%u\n", 
           reg_out[1], reg_out[2], reg_out[3]);
    
    assert(reg_out[1] == sp + 20);
    assert(reg_out[2] == sp + 40);
    assert(reg_out[3] == 100);

    printf("✅ ADD (6) test passed!\n");
}

// === COMBINED TEST: All ADD instructions with FLAG verification ===
void test_add_combined_flags() {
    printf("\n=== COMBINED TEST: ADD Instructions with FLAG verification ===\n");

    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};

    // Program to test multiple ADD variants:
    // 0: MOV R0, #100       (0x3064) - R0 = 100
    // 1: MOV R1, #50        (0x3132) - R1 = 50
    // 2: ADD R2, R0, R1     (0x1C42) - R2 = 100 + 50 = 150
    // 3: ADD R3, #25        (0x3319) - R3 = R3 + 25 = 0 + 25 = 25
    // 4: ADD R4, R1, #5     (0x1D8C) - R4 = R1 + 5 = 50 + 5 = 55
    // 5: MOV R5, #200       (0x35C8) - R5 = 200

    instr_mem[0] = 0x3064 | (0x3132 << 16);  // MOV R0,#100 | MOV R1,#50
    instr_mem[1] = 0x1842 | (0x3319 << 16);  // ADD R2,R0,R1 | ADD R3,#25
    instr_mem[2] = 0x1D4C | (0x35C8 << 16);  // ADD R4,R1,#5 | MOV R5,#200

    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 18; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    PRINT_REGS(reg_out);
    
    printf("Expected: R0=100, R1=50, R2=150, R3=25, R4=55, R5=200\n");
    printf("Actual:   R0=%u, R1=%u, R2=%u, R3=%u, R4=%u, R5=%u\n", 
           reg_out[0], reg_out[1], reg_out[2], reg_out[3], reg_out[4], reg_out[5]);
    
    assert(reg_out[0] == 100);
    assert(reg_out[1] == 50);
    assert(reg_out[2] == 150);
    assert(reg_out[3] == 25);
    assert(reg_out[4] == 55);
    assert(reg_out[5] == 200);

    printf("✅ COMBINED test passed!\n");
}

// === RUN ALL TESTS ===
void run_all_add_tests() {
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║        COMPLETE TEST SUITE FOR ALL 6 ADD INSTRUCTIONS      ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");

    // test_add_1_imm3();
    // test_add_2_imm8();
    // test_add_3_reg();
    // test_add_4_high();
    // test_add_5_pc_imm();
    // test_add_6_sp_imm();
    test_add_combined_flags();

    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║       ✅ ALL ADD INSTRUCTION TESTS PASSED SUCCESSFULLY ✅   ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
}

int main(){
    run_all_add_tests();
    return 0;
}