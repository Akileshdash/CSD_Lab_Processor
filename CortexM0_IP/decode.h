#ifndef DECODE_H
#define DECODE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Enumeration of Cortex-M0 Thumb operations (ARMv6-M)
typedef enum {
    THUMB_INVALID = 0,                   // 0  INVALID — Unknown or unsupported instruction

    // ───────────────────────────────────────────────
    // Shift and Move (1–9)
    THUMB_MOV_REG,                      // 1  MOV (register) — Copy value from one register to another           Correct
    THUMB_MOV_IMM,                      // 2  MOV (immediate) — Load an immediate value into a register           Correct
    THUMB_MOV_HIGH,                     // 3  MOV (high registers) — Move between high registers (R8–R15)           Correct
    THUMB_LSL_IMM,                      // 4  LSL (immediate) — Logical shift left by an immediate amount           Correct
    THUMB_LSL_REG,                      // 5  LSL (register) — Logical shift left by value in another register           Correct
    THUMB_LSR_IMM,                      // 6  LSR (immediate) — Logical shift right by an immediate amount           Correct
    THUMB_LSR_REG,                      // 7  LSR (register) — Logical shift right by value in another register           Correct
    THUMB_ASR_IMM,                      // 8  ASR (immediate) — Arithmetic shift right by an immediate amount (preserves sign)
    THUMB_ASR_REG,                      // 9  ASR (register) — Arithmetic shift right by value in another register

    // ───────────────────────────────────────────────
    // Add/Subtract (10–19)
    THUMB_ADD_REG,                      // 10 ADD (register) — Add two registers
    THUMB_ADD_IMM3,                     // 11 ADD (imm3) — Add small immediate (3-bit)
    THUMB_ADD_IMM8,                     // 12 ADD (imm8) — Add large immediate (8-bit)
    THUMB_ADD_SP_IMM,                   // 13 ADD (SP + imm8) — Add immediate to stack pointer
    THUMB_ADD_SP_IMM7,                  // 14 ADD (SP + imm7) — Adjust SP upwards by immediate
    THUMB_SUB_REG,                      // 15 SUB (register) — Subtract one register from another
    THUMB_SUB_IMM3,                     // 16 SUB (imm3) — Subtract small immediate
    THUMB_SUB_IMM8,                     // 17 SUB (imm8) — Subtract large immediate
    THUMB_SUB_SP_IMM7,                  // 18 SUB (SP - imm7) — Adjust SP downwards by immediate
    THUMB_ADR,                          // 19 ADR — Form address relative to PC

    // ───────────────────────────────────────────────
    // Compare / Negate (20–25)
    THUMB_CMP_REG,                      // 20 CMP (register) — Compare two registers (sets flags)
    THUMB_CMP_IMM,                      // 21 CMP (immediate) — Compare register with immediate (sets flags)
    THUMB_CMP_HIGH,                     // 22 CMP (high registers) — Compare high registers (R8–R15)
    THUMB_CMN,                          // 23 CMN — Compare Negative (add and set flags)
    THUMB_TST,                          // 24 TST — Bitwise AND, update flags (test bits)
    THUMB_NEG,                          // 25 NEG — Two’s complement negate (R = 0 - Rn)           Correct

    // ───────────────────────────────────────────────
    // Data Processing (26–35)
    THUMB_AND,                          // 26 AND — Bitwise AND of two registers
    THUMB_EOR,                          // 27 EOR — Bitwise exclusive OR
    THUMB_ORR,                          // 28 ORR — Bitwise inclusive OR           Correct
    THUMB_BIC,                          // 29 BIC — Bit clear (R = Rn AND NOT Rm)
    THUMB_MVN,                          // 30 MVN — Move NOT (bitwise invert source)           Correct
    THUMB_ADC,                          // 31 ADC — Add with carry
    THUMB_SBC,                          // 32 SBC — Subtract with carry                                        Correct
    THUMB_RSB,                          // 33 RSB — Reverse subtract (R = 0 - Rn)
    THUMB_ROR,                          // 34 ROR — Rotate right                   Correct
    THUMB_MUL,                          // 35 MUL — Multiply two registers           Correct

    // ───────────────────────────────────────────────
    // Branches (36–39)
    THUMB_B_COND,                       // 36 B<cond> — Conditional branch (based on flags)
    THUMB_B,                            // 37 B — Unconditional branch (relative jump)
    THUMB_BL,                           // 38 BL — Branch with link (call subroutine)
    THUMB_BX,                           // 39 BX — Branch and exchange to address in register

    // ───────────────────────────────────────────────
    // Load / Store Single (40–56)
    THUMB_LDR_REG,                      // 40 LDR (register offset) — Load from address in register                   Correct
    THUMB_LDR_IMM,                      // 41 LDR (immediate offset) — Load from address with offset           Correct
    THUMB_LDR_LIT,                      // 42 LDR (literal) — Load from PC-relative address           Correct
    THUMB_LDR_SP,                       // 43 LDR (SP-relative) — Load from SP + offset           Correct
    THUMB_STR_REG,                      // 44 STR (register offset) — Store to address in register                   Correct
    THUMB_STR_IMM,                      // 45 STR (immediate offset) — Store to address with offset                   Correct
    THUMB_STR_SP,                       // 46 STR (SP-relative) — Store to SP + offset                   Correct
    THUMB_LDRB_REG,                     // 47 LDRB (register offset) — Load byte from memory           Correct
    THUMB_LDRB_IMM,                     // 48 LDRB (immediate offset) — Load byte with offset           Correct
    THUMB_STRB_REG,                     // 49 STRB (register offset) — Store byte to memory                   Correct
    THUMB_STRB_IMM,                     // 50 STRB (immediate offset) — Store byte with offset                   Correct
    THUMB_LDRH_REG,                     // 51 LDRH (register offset) — Load halfword from memory           Correct
    THUMB_LDRH_IMM,                     // 52 LDRH (immediate offset) — Load halfword with offset           Correct
    THUMB_STRH_REG,                     // 53 STRH (register offset) — Store halfword to memory                   Correct
    THUMB_STRH_IMM,                     // 54 STRH (immediate offset) — Store halfword with offset                   Correct
    THUMB_LDRSB_REG,                    // 55 LDRSB — Load signed byte           Correct
    THUMB_LDRSH_REG,                    // 56 LDRSH — Load signed halfword           Correct

    // ───────────────────────────────────────────────
    // Load / Store Multiple (57–60)
    THUMB_LDMIA,                        // 57 LDMIA — Load multiple registers incrementing after           Correct
    THUMB_STMIA,                        // 58 STMIA — Store multiple registers incrementing after                   Correct
    THUMB_PUSH,                         // 59 PUSH — Push registers onto stack                                  Correct
    THUMB_POP,                          // 60 POP — Pop registers from stack                                Correct

    // ───────────────────────────────────────────────
    // Miscellaneous (61–69)
    THUMB_SXTB,                         // 61 SXTB — Sign-extend byte to 32-bit
    THUMB_SXTH,                         // 62 SXTH — Sign-extend halfword to 32-bit
    THUMB_UXTB,                         // 63 UXTB — Zero-extend byte to 32-bit
    THUMB_UXTH,                         // 64 UXTH — Zero-extend halfword to 32-bit
    THUMB_REV,                          // 65 REV — Reverse byte order in a 32-bit word
    THUMB_REV16,                        // 66 REV16 — Reverse byte order within each halfword
    THUMB_REVSH,                        // 67 REVSH — Reverse bytes in a halfword and sign-extend
    THUMB_CBZ,                          // 68 CBZ — Compare register with zero, branch if zero
    THUMB_CBNZ,                         // 69 CBNZ — Compare register with zero, branch if non-zero

    // ───────────────────────────────────────────────
    // Hints / Control (70–76)
    THUMB_NOP,                          // 70 NOP — No operation
    THUMB_YIELD,                        // 71 YIELD — Hint for thread yield
    THUMB_WFE,                          // 72 WFE — Wait for event
    THUMB_WFI,                          // 73 WFI — Wait for interrupt
    THUMB_SEV,                          // 74 SEV — Send event to all cores
    THUMB_BKPT,                         // 75 BKPT — Breakpoint instruction (debug)
    THUMB_SVC                           // 76 SVC — Supervisor call (software interrupt)
    // Total: 77 entries including INVALID
} thumb_operation_t;

// Decoded result structure
typedef struct {
    uint16_t instruction;      // Raw 16-bit instruction
    uint8_t valid;             // 1 = valid decode
    uint8_t is_32bit;          // 1 = 32-bit (only BL)
    thumb_operation_t operation;

    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;

    uint8_t immediate_flag;
    uint32_t imm_value;
    int size;                  // 1 = 16-bit, 2 = 32-bit
    uint32_t condition;        // For conditional branches: 0=EQ, 1=NE, 2=CS, 3=CC, etc.
    uint32_t r_bit;  // For PUSH/POP: indicates if LR/PC is included
} decode_result_t;

// Function prototypes
decode_result_t decode_thumb16_instruction(uint16_t instruction);
decode_result_t decode_thumb32_instruction(uint32_t instruction);

const char* get_operation_name(thumb_operation_t op);
void print_decode_result(decode_result_t* result);

#ifdef __cplusplus
}
#endif

#endif // DECODE_H
