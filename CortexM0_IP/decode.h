#ifndef DECODE_H
#define DECODE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Enumeration of all Thumb instruction operations
typedef enum {
    THUMB_INVALID = 0,

    // Shift and move operations
    THUMB_MOV_REG,
    THUMB_LSL_IMM,
    THUMB_LSR_IMM,
    THUMB_ASR_IMM,

    // Add/subtract register
    THUMB_ADD_REG,
    THUMB_SUB_REG,

    // Add/subtract immediate (3-bit)
    THUMB_ADD_IMM3,
    THUMB_SUB_IMM3,

    // Move/compare/add/subtract immediate (8-bit)
    THUMB_MOV_IMM,
    THUMB_CMP_IMM,
    THUMB_ADD_IMM8,
    THUMB_SUB_IMM8,

    // Data processing register operations
    THUMB_AND,
    THUMB_EOR,
    THUMB_LSL_REG,
    THUMB_LSR_REG,
    THUMB_ASR_REG,
    THUMB_ADC,
    THUMB_SBC,
    THUMB_ROR,
    THUMB_TST,
    THUMB_RSB,
    THUMB_CMP_REG,
    THUMB_CMN,
    THUMB_ORR,
    THUMB_MUL,
    THUMB_BIC,
    THUMB_MVN,

    // Special data processing
    THUMB_ADD_HIGH,
    THUMB_CMP_HIGH,
    THUMB_MOV_HIGH,

    // Branch and exchange
    THUMB_BX,
    THUMB_BLX_REG,

    // Load from literal pool
    THUMB_LDR_LIT,

    // Load/store register offset
    THUMB_STR_REG,
    THUMB_STRH_REG,
    THUMB_STRB_REG,
    THUMB_LDRSB_REG,
    THUMB_LDR_REG,
    THUMB_LDRH_REG,
    THUMB_LDRB_REG,
    THUMB_LDRSH_REG,

    // Load/store immediate offset (word/byte)
    THUMB_STR_IMM,
    THUMB_LDR_IMM,
    THUMB_STRB_IMM,
    THUMB_LDRB_IMM,

    // Load/store halfword immediate offset
    THUMB_STRH_IMM,
    THUMB_LDRH_IMM,

    // Stack load/store
    THUMB_STR_SP,
    THUMB_LDR_SP,

    // ADR / Add to PC/SP
    THUMB_ADR,
    THUMB_ADD_SP_IMM,
    THUMB_ADD_SP_IMM7,
    THUMB_SUB_SP_IMM7,

    // Sign/zero extend
    THUMB_SXTH,
    THUMB_SXTB,
    THUMB_UXTH,
    THUMB_UXTB,

    // Compare and branch on zero / non-zero
    THUMB_CBZ,
    THUMB_CBNZ,

    // Push/Pop
    THUMB_PUSH,
    THUMB_POP,

    // SETEND / CPS
    THUMB_SETEND,
    THUMB_CPS,

    // Byte-swapping / reverse
    THUMB_REV,
    THUMB_REV16,
    THUMB_REVSH,

    // BKPT / IT / hints
    THUMB_BKPT,
    THUMB_IT,
    THUMB_NOP,
    THUMB_YIELD,
    THUMB_WFE,
    THUMB_WFI,
    THUMB_SEV,

    // Load/store multiple
    THUMB_STMIA,
    THUMB_LDMIA,

    // Conditional branch / SVC / B
    THUMB_BCC,
    THUMB_SVC,
    THUMB_B

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

    // For conditional branches
    uint8_t condition;         // condition code for BCC (0-15)

} decode_result_t;

/* Decode a single 16-bit Thumb instruction.
 * Returns a populated decode_result_t. If the instruction is unknown or
 * a 32-bit instruction prefix, result.valid will be 0 (or is_32bit = 1).
 */
decode_result_t decode_thumb_instruction(uint16_t instruction);

/* Return human-readable name for an operation (used by decode.c debug helpers) */
const char* get_operation_name(thumb_operation_t op);

/* Debug helper to print a decode_result_t */
void print_decode_result(decode_result_t* result);

#ifdef __cplusplus
}
#endif

#endif // DECODE_H
