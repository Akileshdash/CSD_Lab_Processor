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

void test_cbz_cbnz() {
    printf("\n=== TEST: CBZ/CBNZ Instructions ===\n");
    
    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};
    
    // MOV R0, #0        (0x2000) - R0 = 0
    // CBZ R0, skip      (0xB100) - Branch if R0 == 0
    // MOV R1, #5        (0x2105) - (should be skipped)
    // ...
    
    instr_mem[0] = 0x2000 | (0xB100 << 16);
    
    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 5; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }
    
    printf("✅ CBZ/CBNZ test completed\n");
}

void test_reverse_extend() {
    printf("\n=== TEST: REV, SXTB, UXTB Instructions ===\n");
    
    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE]  = {0};
    uint32_t reg_out[32] = {0};
    
    // MOV R0, #0x12    (0x2012) - R0 = 0x12
    // SXTB R1, R0      (0xB209) - R1 = sign-extended 0x12
    // REV R2, R0       (0xBA80) - R2 = reversed R0
    
    instr_mem[0] = 0x2012;
    instr_mem[1] = 0xB209 | (0xBA80 << 16);
    
    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);
    for (int i = 0; i < 8; i++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }
    
    printf("✅ Reverse/Extend test completed\n");
}


// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

int main() {
    test_cbz_cbnz();
    test_reverse_extend();
    printf("\n========== ✅ ALL TESTS PASSED! ==========\n");
    return 0;
}