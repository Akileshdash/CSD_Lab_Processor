#include "processor.h"
#include <stdio.h>

int main() {
    const int MEM_SIZE = 256;
    uint32_t instr_mem[MEM_SIZE];
    uint32_t data_mem[MEM_SIZE];
    uint32_t reg_out[32];  // Expanded to include special registers

    // Initialize instruction & data memory
    for (int i = 0; i < MEM_SIZE; i++) {
        instr_mem[i] = 0;
        data_mem[i] = 0;
    }

    // ARM Cortex-M0 Reset Configuration
    data_mem[0] = 0x20001000;         // Initial MSP
    instr_mem[1] = 0x00000008 | 1;    // Reset vector (PC start, Thumb mode)

    // === Thumb test program (real 16-bit encodings) ===
    instr_mem[2] = 0x2105;   // MOVS R1, #5
    instr_mem[3] = 0x220A;   // MOVS R2, #10
    instr_mem[4] = 0x18CB;   // ADDS R3, R1, R2
    instr_mem[5] = 0x3B03;   // SUBS R3, #3
    instr_mem[6] = 0x2C07;   // CMP R4, #7
    instr_mem[7] = 0xD001;   // BEQ +2
    instr_mem[8] = 0x2563;   // MOVS R5, #99
    instr_mem[9] = 0x252A;   // MOVS R5, #42

    printf("=== Cortex-M0 Thumb Test ===\n");
    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);

    printf("Cycle | R0 R1 R2 R3 R4 R5 | SP       PC\n");
    printf("------|--------------------|------------\n");

    for (int cycle = 0; cycle < 20; cycle++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
        printf("%4d   |", cycle);
        for (int i = 0; i <= 5; i++) printf(" %3u", reg_out[i]);
        printf(" | %08X %08X\n", reg_out[13], reg_out[15]);
    }

    printf("\n=== Verification ===\n");
    printf("R1 should be 5   → %u\n", reg_out[1]);
    printf("R2 should be 10  → %u\n", reg_out[2]);
    printf("R3 = 12 - 3      → %u\n", reg_out[3]);
    printf("R4 compared with 7 (flags updated)\n");
    printf("R5 depends on branch → %u\n", reg_out[5]);

    return 0;
}
