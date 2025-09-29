#include "processor.h"
#include <stdio.h>
#include <stdint.h>
#include <stdint.h>

#define MEM_SIZE 4   // enough to hold 8 halfwords (4 words)
int main() {
    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE] = {0};
    uint32_t reg_out[32] = {0};

    // Initialize memory
    data_mem[0] = 0x20001000; // Initial MSP

    // -------------------------------
    // Pack Thumb instructions (16-bit each)
    // Word 0: halfword0 = MOVS R1,#5, halfword1 = MOVS R2,#10
    instr_mem[0] = 0x2105 | (0x220A << 16);

    // Word 1: halfword0 = ADDS R3,R1,R2, halfword1 = SUBS R4,R2,R1
    instr_mem[1] = 0x1892 | (0x1A14 << 16);

    // Word 2: halfword0 = STR R3,[R5,#0], halfword1 = LDR R6,[R5,#0]
    instr_mem[2] = 0x6B03 | (0x6C05 << 16);

    // Word 3: NOP ; B +2 (skip next instruction, just for demo)
    instr_mem[3] = (0x4600) | (0xE002 << 16);

    // Initialize R4 for STR/LDR
    reg_out[4] = 0; // index 0 in data_mem

    // printf("=== Cortex-M0 Thumb Pipeline Test ===\n");

    // Reset processor
    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);

    // printf("Cycle | R0  R1  R2  R3  R5 | MEM[0] | SP       PC\n");
    // printf("------|--------------------|--------|------------\n");

    for(int cycle = 0; cycle < 10; cycle++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
        // printf("%4d   | %3u %3u %3u %3u %3u | %6u | %08X %08X\n", 
        //     cycle, reg_out[0], reg_out[1], reg_out[2], reg_out[3], reg_out[5], 
        //     data_mem[0], reg_out[13], reg_out[15]);
    }

    return 0;
}
