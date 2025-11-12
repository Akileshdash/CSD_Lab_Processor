#ifndef EXECUTE_H
#define EXECUTE_H

#include <stdint.h>
#include "regfile.h"
#include "decode.h"   // for thumb_operation_t


#define FLAG_N  PSR_N_MASK
#define FLAG_Z  PSR_Z_MASK
#define FLAG_C  PSR_C_MASK
#define FLAG_V  PSR_V_MASK

// EX stage input structure
typedef struct {
    thumb_operation_t opcode;  // Thumb enum opcode
    uint32_t pc;          // Program counter of this instruction
    uint32_t reg_data1;   // First operand / base address for loads/stores
    uint32_t reg_data2;   // Second operand / store data
    uint32_t rd;          // Destination register
    uint32_t condition;   // For conditional branches (0x0-0xE)
    uint32_t cpsr;        // Condition flags from previous ALU operations
    uint32_t r_bit;  
} EX_input_t;

// EX stage output structure
typedef struct {
    uint32_t alu_result;          // ALU result or effective memory address
    uint32_t carry;               // Carry flag output
    uint32_t overflow;            // Overflow flag output
    uint32_t link;                // For BL (Link Register value = PC + 4)
    uint32_t cpsr;                // Updated condition flags
    int flags_updated;            // 1 if this instruction updated flags
    uint32_t r_bit;  
    
    // ──── Memory Operation Fields ────
    int mem_size;                 // 1=byte, 2=halfword, 4=word (0=no memory access)
    int sign_extend;              // 1 for signed loads (LDRSB, LDRSH), 0 for unsigned
} EX_output_t;

// Execute function prototype
EX_output_t execute(EX_input_t input, cortex_m0_registers_t* regs);
static inline uint32_t popcount(uint32_t x) {
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x3F;
}


#endif
