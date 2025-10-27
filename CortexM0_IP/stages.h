#ifndef STAGES_H
#define STAGES_H

#include <stdint.h>
#include "decode.h"   // for thumb_operation_t

typedef uint32_t addr_t;

typedef struct { 
    addr_t pc; 
    uint32_t instr; 
} IF_stage;

// ID Stage
typedef struct {
    addr_t pc; 
    uint32_t instr; 
    uint32_t reg_data1; 
    uint32_t reg_data2;
    thumb_operation_t opcode;   // Use Thumb ISA enum
    unsigned int rd; 
    unsigned int rs1; 
    unsigned int rs2;
    uint8_t immediate_flag;     // 1 if instruction uses immediate
    uint32_t imm_value;         // immediate value
    uint32_t condition;  // For conditional branches
    uint32_t cpsr;
} ID_stage;

// EX Stage
typedef struct {
    uint32_t pc;          // Program counter of this instruction
    thumb_operation_t opcode;
    uint8_t rd;
    uint32_t alu_result;
    uint32_t reg_data2;   // For stores
    uint32_t link;        // For BL instruction
    uint32_t condition;  // For conditional branches
    uint32_t cpsr;       // Condition flags from previous ALU operations
    int flags_updated;      // NEW
} EX_stage;

// MEM Stage
typedef struct {
    thumb_operation_t opcode;
    uint8_t rd;
    uint32_t alu_result;  // Address for load/store
    uint32_t mem_data;    // Data from memory (loads) or ALU result
    uint32_t link;        // For BL instruction
    uint32_t cpsr;
    int flags_updated;      // NEW
} MEM_stage;

// WB Stage
typedef struct {
    thumb_operation_t opcode;
    uint8_t rd;
    uint32_t write_data;  // Data to write to register file
    uint32_t link;
    uint32_t cpsr;
    int flags_updated;      // NEW
} WB_stage;

#endif // STAGES_H