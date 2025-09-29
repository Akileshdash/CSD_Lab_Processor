#ifndef DECODE_H
#define DECODE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Enumeration of all Thumb instruction operations
typedef enum {
    THUMB_INVALID = 0,      // 0

    // Shift and move operations
    THUMB_MOV_REG,           // 1
    THUMB_LSL_IMM,           // 2
    THUMB_LSR_IMM,           // 3
    THUMB_ASR_IMM,           // 4

    // Add/subtract register
    THUMB_ADD_REG,           // 5
    THUMB_SUB_REG,           // 6

    // Add/subtract immediate (3-bit)
    THUMB_ADD_IMM3,          // 7
    THUMB_SUB_IMM3,          // 8

    // Move/compare/add/subtract immediate (8-bit)
    THUMB_MOV_IMM,           // 9
    THUMB_CMP_IMM,           // 10
    THUMB_ADD_IMM8,          // 11
    THUMB_SUB_IMM8,          // 12

    // Data processing register operations
    THUMB_AND,               // 13
    THUMB_EOR,               // 14
    THUMB_LSL_REG,           // 15
    THUMB_LSR_REG,           // 16
    THUMB_ASR_REG,           // 17
    THUMB_ADC,               // 18
    THUMB_SBC,               // 19
    THUMB_ROR,               // 20
    THUMB_TST,               // 21
    THUMB_RSB,               // 22
    THUMB_CMP_REG,           // 23
    THUMB_CMN,               // 24
    THUMB_ORR,               // 25
    THUMB_MUL,               // 26
    THUMB_BIC,               // 27
    THUMB_MVN,               // 28

    // Special data processing
    THUMB_ADD_HIGH,          // 29
    THUMB_CMP_HIGH,          // 30
    THUMB_MOV_HIGH,          // 31

    // Branch and exchange
    THUMB_BX,                // 32
    THUMB_BLX_REG,           // 33

    // Load from literal pool
    THUMB_LDR_LIT,           // 34

    // Load/store register offset
    THUMB_STR_REG,           // 35
    THUMB_STRH_REG,          // 36
    THUMB_STRB_REG,          // 37
    THUMB_LDRSB_REG,         // 38
    THUMB_LDR_REG,           // 39
    THUMB_LDRH_REG,          // 40
    THUMB_LDRB_REG,          // 41
    THUMB_LDRSH_REG,         // 42

    // Load/store immediate offset (word/byte)
    THUMB_STR_IMM,           // 43
    THUMB_LDR_IMM,           // 44
    THUMB_STRB_IMM,          // 45
    THUMB_LDRB_IMM,          // 46

    // Load/store halfword immediate offset
    THUMB_STRH_IMM,          // 47
    THUMB_LDRH_IMM,          // 48

    // Stack load/store
    THUMB_STR_SP,            // 49
    THUMB_LDR_SP,            // 50

    // ADR / Add to PC/SP
    THUMB_ADR,               // 51
    THUMB_ADD_SP_IMM,        // 52
    THUMB_ADD_SP_IMM7,       // 53
    THUMB_SUB_SP_IMM7,       // 54

    // Sign/zero extend
    THUMB_SXTH,              // 55
    THUMB_SXTB,              // 56
    THUMB_UXTH,              // 57
    THUMB_UXTB,              // 58

    // Compare and branch on zero / non-zero
    THUMB_CBZ,               // 59
    THUMB_CBNZ,              // 60

    // Push/Pop
    THUMB_PUSH,              // 61
    THUMB_POP,               // 62

    // SETEND / CPS
    THUMB_SETEND,            // 63
    THUMB_CPS,               // 64

    // Byte-swapping / reverse
    THUMB_REV,               // 65
    THUMB_REV16,             // 66
    THUMB_REVSH,             // 67

    // BKPT / IT / hints
    THUMB_BKPT,              // 68
    THUMB_IT,                // 69
    THUMB_NOP,               // 70
    THUMB_YIELD,             // 71
    THUMB_WFE,               // 72
    THUMB_WFI,               // 73
    THUMB_SEV,               // 74

    // Load/store multiple
    THUMB_STMIA,             // 75
    THUMB_LDMIA,             // 76

    // Conditional branch / SVC / B
    THUMB_BCC,               // 77
    THUMB_SVC,               // 78
    THUMB_B,                  // 79

    // 32-bit branch instructions
    THUMB_BL,                // 80
    THUMB_BLX_IMM            // 81
} thumb_operation_t;

// Result of decoding a single 16-bit Thumb instruction
typedef struct {
    uint16_t instruction;      // raw 16-bit instruction word
    uint8_t valid;             // non-zero if the decode is valid
    uint8_t is_32bit;          // non-zero if this belongs to a 32-bit instruction prefix (not handled)
    thumb_operation_t operation;

    // Register operands (small ints are sufficient)
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;

    // Immediate handling
    uint8_t immediate_flag;    // 1 if instruction uses immediate
    uint32_t imm_value;        // immediate value (already shifted/aligned as decode.c does)
    int size;   // 1 = 16-bit Thumb, 2 = 32-bit Thumb

    // For conditional branches
    uint8_t condition;         // condition code for BCC (0-15)

} decode_result_t;

/* Decode a single 16-bit Thumb instruction.
 * Returns a populated decode_result_t. If the instruction is unknown or
 * a 32-bit instruction prefix, result.valid will be 0 (or is_32bit = 1).
 */
decode_result_t decode_thumb16_instruction(uint16_t instruction);
decode_result_t decode_thumb32_instruction(uint32_t instruction);

/* Return human-readable name for an operation (used by decode.c debug helpers) */
const char* get_operation_name(thumb_operation_t op);

/* Debug helper to print a decode_result_t */
void print_decode_result(decode_result_t* result);

#ifdef __cplusplus
}
#endif

#endif // DECODE_H
