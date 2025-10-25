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
    uint32_t reg_data1;
    uint32_t reg_data2;
    uint32_t rd;
    uint32_t condition;  // For conditional branches
    uint32_t cpsr;   // Condition flags from previous ALU operations
} EX_input_t;

// EX stage output structure
typedef struct {
    uint32_t alu_result;
    uint32_t carry;
    uint32_t overflow;
    uint32_t link;       // for BL (LR value)
    uint32_t cpsr; 
} EX_output_t;

// Execute function prototype
EX_output_t execute(EX_input_t input, cortex_m0_registers_t* regs);

#endif
