#include "processor.h"
#include <stdio.h>
#include <stdint.h>

#define OS_START_ADDR 0x00100000  // base address of OS in DDR

int main() {
    const int MEM_SIZE = 8;       // small memory for one instruction
    uint32_t instr_mem[MEM_SIZE];
    uint32_t data_mem[MEM_SIZE];
    uint32_t reg_out[32];         // include special registers

    // Initialize memory
    for(int i = 0; i < MEM_SIZE; i++) {
        instr_mem[i] = 0;
        data_mem[i] = 0;
    }

    // Reset configuration
    data_mem[0] = 0x20001000;        // Initial MSP
    instr_mem[0] = 0x00000009;       // Reset vector (PC=0x04, Thumb bit set)

    // Pack **one real Thumb instruction** into a 32-bit word
    // Word 1: instr[2] = MOVS R1, #5
    instr_mem[1] = 0x00000005 | (0x2105 << 0); // lower half = MOVS R1,#5

    printf("=== Cortex-M0 Thumb Single Instruction Test ===\n");

    // Reset processor
    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);

    printf("Cycle | R0 R1 | SP       PC\n");
    printf("------|--------|------------\n");

    for(int cycle = 0; cycle < 7; cycle++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
        printf("%4d   | %3u %3u | %08X %08X\n", 
            cycle, reg_out[0], reg_out[1], reg_out[13], reg_out[15]);
    }

    return 0;
}
