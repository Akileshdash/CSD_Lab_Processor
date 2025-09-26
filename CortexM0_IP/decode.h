#ifndef DECODE_H
#define DECODE_H

#include <stdint.h>

// Thumb instruction format definitions
#define THUMB_INSTR_MASK    0x0000FFFF

// Format identification bits
#define THUMB_FORMAT_BITS   0xC000  // Bits [15:14]
#define THUMB_FORMAT_00     0x0000  // Format 1-5 instructions
#define THUMB_FORMAT_01     0x4000  // Format 6-9 instructions  
#define THUMB_FORMAT_10     0x8000  // Format 10-13 instructions
#define THUMB_FORMAT_11     0xC000  // Format 14-19 instructions

// Format 1-5 opcode bits [13:9] for when bits [15:14] = 00
#define THUMB_OPCODE_MASK   0x3E00
#define THUMB_OPCODE_SHIFT  9

// Thumb opcodes for Format 1-5 (bits [15:14] = 00)
typedef enum {
    THUMB_LSL_IMM = 0x00,   // 000xx - LSL (immediate)
    THUMB_LSR_IMM = 0x04,   // 001xx - LSR (immediate) 
    THUMB_ASR_IMM = 0x08,   // 010xx - ASR (immediate)
    THUMB_ADD_REG = 0x0C,   // 01100 - ADD (register)
    THUMB_SUB_REG = 0x0D,   // 01101 - SUB (register)
    THUMB_ADD_IMM3 = 0x0E,  // 01110 - ADD (3-bit immediate)
    THUMB_SUB_IMM3 = 0x0F,  // 01111 - SUB (3-bit immediate)
    THUMB_MOV_IMM = 0x10,   // 100xx - MOV (immediate)
    THUMB_CMP_IMM = 0x14,   // 101xx - CMP (immediate)
    THUMB_ADD_IMM8 = 0x18,  // 110xx - ADD (8-bit immediate)
    THUMB_SUB_IMM8 = 0x1C   // 111xx - SUB (8-bit immediate)
} thumb_opcode_t;

// Field extraction macros
#define THUMB_GET_RD_3BIT(instr)    ((instr) & 0x0007)          // Bits [2:0]
#define THUMB_GET_RN_3BIT(instr)    (((instr) >> 3) & 0x0007)   // Bits [5:3]
#define THUMB_GET_RM_3BIT(instr)    (((instr) >> 6) & 0x0007)   // Bits [8:6] 
#define THUMB_GET_IMM3(instr)       (((instr) >> 6) & 0x0007)   // Bits [8:6]
#define THUMB_GET_IMM5(instr)       (((instr) >> 6) & 0x001F)   // Bits [10:6]
#define THUMB_GET_RD_8BIT(instr)    (((instr) >> 8) & 0x0007)   // Bits [10:8]
#define THUMB_GET_IMM8(instr)       ((instr) & 0x00FF)          // Bits [7:0]

// Decoded instruction structure
typedef struct {
    uint32_t opcode;        // Internal processor opcode
    uint32_t rd;            // Destination register (0-15)
    uint32_t rn;            // First source register (0-15)
    uint32_t rm;            // Second source register (0-15)
    uint32_t immediate;     // Immediate value
    uint32_t imm_flag;      // 1 if instruction uses immediate
    uint32_t shift_type;    // Shift operation type
    uint32_t shift_imm;     // Shift immediate value
    uint32_t sets_flags;    // 1 if instruction sets condition flags
    uint32_t valid;         // 1 if instruction was decoded successfully
} decoded_instr_t;

// Internal processor opcodes (mapped from Thumb)
typedef enum {
    OP_MOV = 0,
    OP_ADD = 1, 
    OP_SUB = 2,
    OP_LSL = 3,
    OP_LSR = 4,
    OP_ASR = 5,
    OP_CMP = 6,
    OP_LOAD = 7,
    OP_STORE = 8,
    OP_NOP = 15
} internal_opcode_t;

// Function prototypes
decoded_instr_t decode_thumb_instruction(uint16_t instruction);
void print_decoded_instruction(decoded_instr_t decoded, uint16_t raw_instr);

#endif