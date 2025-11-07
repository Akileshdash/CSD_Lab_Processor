#include <stdio.h>
#include "processor.h"
#include <stdint.h>
#include <stdlib.h>

#define MEM_SIZE 1024*2*8*16          // Adjust according to your OS size / testbench

int main() {
    uint32_t instr_mem[MEM_SIZE] = {0};
    uint32_t data_mem[MEM_SIZE] = {0};
    uint32_t reg_out[32] = {0};

    FILE *fp = fopen("OS.bin", "rb");
    if (!fp) {
        perror("Cannot open vm.bin");
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
        if (word_index >= MEM_SIZE) break;  // prevent overflow
    }
    fclose(fp);

    printf("Loaded %zu halfwords (%zu instructions) into instr_mem\n", hw_count, hw_count);

    // === Dump loaded instructions to hex file ===
    FILE *hex_out = fopen("instr_mem_dump.txt", "w");
    if (!hex_out) {
        perror("Cannot open instr_mem_dump.txt");
        return 1;
    }

    size_t word_count = (hw_count + 1) / 2; // number of 32-bit words actually filled
    for (size_t i = 0; i < word_count; i++) {
        fprintf(hex_out, "0x%08X\n", instr_mem[i]);
    }
    fclose(hex_out);

    printf("Dumped %zu words to instr_mem_dump.txt\n", word_count);

    // Reset configuration
    data_mem[0] = 0x20001000;        // initial MSP
    // instr_mem[0] should already contain reset vector if present in vm.bin

    // === Call your cortex_m0_top function ===
    cortex_m0_top(instr_mem, data_mem, reg_out, 1, 1);  // reset

    // Run a few cycles
    for (int cycle = 0; cycle < 10; cycle++) {
        cortex_m0_top(instr_mem, data_mem, reg_out, 0, 1);
        // printf("Cycle %d | PC=0x%08X | R0=%u R1=%u\n",cycle, reg_out[15], reg_out[0], reg_out[1]);
    }

    return 0;
}
