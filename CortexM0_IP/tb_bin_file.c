#include <stdio.h>
#include "processor.h"
#include <stdint.h>
#include <stdlib.h>

#define INSTR_MEM_SIZE (1024*2*8*16*1024)  // Large for instructions
#define DATA_MEM_SIZE  (128*1024)           // 128K words = 512KB RAM (reasonable)

int main() {
    uint32_t *instr_mem = calloc(INSTR_MEM_SIZE, sizeof(uint32_t));
    uint32_t *data_mem = calloc(DATA_MEM_SIZE, sizeof(uint32_t));
    uint32_t reg_out[32] = {0};
    
    if (!instr_mem || !data_mem) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    FILE *fp = fopen("OS.bin", "rb");
    if (!fp) {
        perror("Cannot open OS.bin");
        free(instr_mem);
        free(data_mem);
        return 1;
    }

    // Read the binary file 2 bytes at a time (Thumb halfword)
    uint16_t halfword;
    size_t hw_count = 0;
    while (fread(&halfword, sizeof(uint16_t), 1, fp) == 1) {
        size_t word_index = hw_count / 2;
        if (hw_count % 2 == 0) {
            // lower half of 32-bit word
            instr_mem[word_index] = halfword;
        } else {
            // upper half of 32-bit word
            instr_mem[word_index] |= ((uint32_t)halfword << 16);
        }
        hw_count++;
        if (word_index >= INSTR_MEM_SIZE) break;
    }
    fclose(fp);

    printf("Loaded %zu halfwords (%zu instructions) into instr_mem\n", hw_count, hw_count);

    // === Dump loaded instructions to hex file ===
    FILE *hex_out = fopen("instr_mem_dump.txt", "w");
    if (hex_out) {
        size_t word_count = (hw_count + 1) / 2;
        for (size_t i = 0; i < word_count; i++) {
            fprintf(hex_out, "0x%08X\n", instr_mem[i]);
        }
        fclose(hex_out);
        printf("Dumped %zu words to instr_mem_dump.txt\n", word_count);
    }

    // *** FIX: Override the initial stack pointer in instruction memory ***
    // The Cortex-M vector table at address 0x00000000 contains:
    //   [0x00000000] = Initial MSP (Main Stack Pointer)
    //   [0x00000004] = Reset vector (initial PC)
    
    // Save original values for debug
    uint32_t original_msp = instr_mem[0];
    uint32_t original_reset = instr_mem[1];  // Note: word index 1 = byte address 0x00000004
    
    printf("\n=== VECTOR TABLE DEBUG ===\n");
    printf("Original MSP from binary: 0x%08X\n", original_msp);
    printf("Original Reset Vector: 0x%08X\n", original_reset);
    
    // Override with a reasonable stack pointer
    // Stack grows downward, so set SP to the END of RAM
    // If we have 512KB (128K words) of data RAM, set SP to end of it
    uint32_t ram_size_bytes = DATA_MEM_SIZE * 4;  // Convert words to bytes
    uint32_t new_msp = ram_size_bytes;  // Stack pointer at end of RAM
    
    instr_mem[0] = new_msp;  // *** THIS IS THE KEY FIX ***
    
    printf("Overriding MSP to: 0x%08X (end of %d KB RAM)\n", 
           new_msp, ram_size_bytes / 1024);
    printf("==========================\n\n");

    // === Call your cortex_m0_top function ===
    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);  // reset

    // Run a few cycles
    for (int cycle = 0; cycle < 20; cycle++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
    }

    printf("\n=== Final Register State ===\n");
    printf("R0=0x%08X  R1=0x%08X  R2=0x%08X  R3=0x%08X\n", 
           reg_out[0], reg_out[1], reg_out[2], reg_out[3]);
    printf("PC=0x%08X  SP=0x%08X  LR=0x%08X\n", 
           reg_out[15], reg_out[13], reg_out[14]);

    free(instr_mem);
    free(data_mem);
    return 0;
}