#include "processor.h"
#include <stdio.h>

int main() {
    const int MEM_SIZE = 256;
    uint32_t instr_mem[MEM_SIZE];
    uint32_t data_mem[MEM_SIZE];
    uint32_t reg_out[32];  // Expanded to include special registers

    // Initialize instruction memory and data memory
    for(int i = 0; i < MEM_SIZE; i++) {
        instr_mem[i] = 0;
        data_mem[i] = i + 1;
    }

    // ARM Cortex-M0 Reset Configuration
    data_mem[0] = 0x20001000;         // MSP
    instr_mem[1] = 0x00000008 | 1;    // Reset vector (PC start), Thumb mode

    // Test Instructions
    // Format: [opcode 28:31][Rd 24:27][Rn 20:23][Rs2/imm 0:19]
    
    // MOV R1, R0
    instr_mem[2] = (7<<28)|(1<<24)|(0<<20)|(0);
    
    // MOV R2, R0
    instr_mem[3] = (7<<28)|(2<<24)|(0<<20)|(0);

    // ADD R3, R1, R2 (register)
    instr_mem[4] = (1<<28)|(3<<24)|(1<<20)|(2);

    // ADD R4, R3, #10 (immediate value)
    // Use lower 20 bits for immediate
    instr_mem[5] = (1<<28)|(4<<24)|(3<<20)|(10);

    // SUB R5, R4, #5 (immediate subtraction)
    instr_mem[6] = (4<<28)|(5<<24)|(4<<20)|(5);

    // ADCS R6, R1, R2
    instr_mem[7] = (2<<28)|(6<<24)|(1<<20)|(2);

    // RSBS R7, R6, #0
    instr_mem[8] = (3<<28)|(7<<24)|(6<<20)|(0);

    // SBCS R8, R7, R1
    instr_mem[9] = (5<<28)|(8<<24)|(7<<20)|(1);

    // Initialize R0
    reg_out[0] = 5;

    printf("=== ARM Cortex-M0 Processor Test with Immediate ===\n");
    printf("Resetting processor...\n");
    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);

    printf("Cycle | R0 R1 R2 R3 R4 R5 R6 R7 R8 | SP       PC\n");
    printf("------|-----------------------------|------------\n");

    for(int cycle=0; cycle<12; cycle++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
        printf("%4d   |", cycle);
        for(int i=0; i<=8; i++) printf(" %3u", reg_out[i]);
        printf(" | %08X %08X\n", reg_out[13], reg_out[15]);
    }

    printf("\n=== Verification ===\n");
    printf("R3 (R1+R2): %u\n", reg_out[3]);
    printf("R4 (R3+10): %u\n", reg_out[4]);
    printf("R5 (R4-5) : %u\n", reg_out[5]);
    printf("R6 (ADCS)  : %u\n", reg_out[6]);
    printf("R7 (RSBS)  : %u\n", reg_out[7]);
    printf("R8 (SBCS)  : %u\n", reg_out[8]);

    return 0;
}
