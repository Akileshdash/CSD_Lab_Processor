#ifndef STAGES_H
#define STAGES_H

#include <stdint.h>
#include "decode.h"   // for thumb_operation_t

typedef uint32_t addr_t;

typedef struct { 
    addr_t pc; 
    uint32_t instr; 
} IF_stage;

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
} ID_stage;

typedef struct { 
    thumb_operation_t opcode;   // Use Thumb ISA enum
    uint32_t alu_result; 
    uint32_t reg_data2; 
    uint32_t link;
    unsigned int rd; 
} EX_stage;

typedef struct { 
    thumb_operation_t opcode;   // Use Thumb ISA enum
    uint32_t alu_result; 
    uint32_t mem_data; 
    uint32_t link;
    unsigned int rd; 
} MEM_stage;

typedef struct { 
    thumb_operation_t opcode;   // Use Thumb ISA enum
    uint32_t write_data; 
    unsigned int rd; 
} WB_stage;

#endif
