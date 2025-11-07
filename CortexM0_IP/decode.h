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
    THUMB_MOV_REG,                      // 1  MOV (register) — Copy value from one register to another              Correct
    THUMB_MOV_IMM,                      // 2  MOV (immediate) — Load an immediate value into a register             Correct
    THUMB_MOV_HIGH,                     // 3  MOV (high registers) — Move between high registers (R8–R15)           Correct
    THUMB_LSL_IMM,                      // 4  LSL (immediate) — Logical shift left by an immediate amount           Correct
    THUMB_LSL_REG,                      // 5  LSL (register) — Logical shift left by value in another register      Correct
    THUMB_LSR_IMM,                      // 6  LSR (immediate) — Logical shift right by an immediate amount          Correct
    THUMB_LSR_REG,                      // 7  LSR (register) — Logical shift right by value in another register     Correct
    THUMB_ASR_IMM,                      // 8  ASR (immediate) — Arithmetic shift right by an immediate amount (preserves sign)  Correct
    THUMB_ASR_REG,                      // 9  ASR (register) — Arithmetic shift right by value in another register              Correct

    // ───────────────────────────────────────────────
    // Add/Subtract (10–19)
    THUMB_ADD_REG,                      // 10 ADD (register) — Add two registers                                Correct ADD (3)
    THUMB_ADD_IMM3,                     // 11 ADD (imm3) — Add small immediate (3-bit)                          Correct ADD (1)
    THUMB_ADD_IMM8,                     // 12 ADD (imm8) — Add large immediate (8-bit)                          Correct ADD (2)
    THUMB_ADD_SP_IMM,                   // 13 ADD (SP + imm8) — Add immediate to stack pointer                  Correct ADD (6)
    THUMB_ADD_HIGH,                     // 14 ADD (high registers) — Add between high registers (R8–R15)        Correct ADD (4)
    THUMB_ADD_PC_IMM,                   // 15 ADD (PC + imm) — PC-relative add (ADR equivalent)                 Correct ADD (5)         
    THUMB_ADD_SP_IMM7,                  // 16 ADD (SP, #imm7*4) —                                               Correct ADD (7)
    THUMB_SUB_REG,                      // 17 SUB (register) — Subtract one register from another               Correct SUB (3)
    THUMB_SUB_IMM3,                     // 18 SUB (imm3) — Subtract small immediate                             Correct SUB (1)
    THUMB_SUB_IMM8,                     // 19 SUB (imm8) — Subtract large immediate                             Correct SUB (2)
    THUMB_SUB_SP_IMM7,                  // 20 SUB (SP - imm7) — Adjust SP downwards by immediate                Correct SUB (4)

    // ───────────────────────────────────────────────
    // Compare / Negate (20–25)
    THUMB_CMP_REG,                      // 21 CMP (register) — Compare two registers (sets flags)               Correct
    THUMB_CMP_IMM,                      // 22 CMP (immediate) — Compare register with immediate (sets flags)    Correct
    THUMB_CMP_HIGH,                     // 23 CMP (high registers) — Compare high registers (R8–R15)            Correct
    THUMB_CMN,                          // 24 CMN — Compare Negative (add and set flags)                        Correct
    THUMB_TST,                          // 25 TST — Bitwise AND, update flags (test bits)                       Correct
    THUMB_NEG,                          // 26 NEG — Two's complement negate (R = 0 - Rn)                        Correct

    // ───────────────────────────────────────────────
    // Data Processing (26–35)
    THUMB_AND,                          // 27 AND — Bitwise AND of two registers                                Correct 
    THUMB_EOR,                          // 28 EOR — Bitwise exclusive OR                                        Correct
    THUMB_ORR,                          // 39 ORR — Bitwise inclusive OR                                        Correct
    THUMB_BIC,                          // 30 BIC — Bit clear (R = Rn AND NOT Rm)                               Correct
    THUMB_MVN,                          // 31 MVN — Move NOT (bitwise invert source)                            Correct
    THUMB_ADC,                          // 32 ADC — Add with carry                                              Correct
    THUMB_SBC,                          // 33 SBC — Subtract with carry                                         Correct
    THUMB_RSB,                          // 34 RSB — Reverse subtract (R = 0 - Rn)
    THUMB_ROR,                          // 35 ROR — Rotate right                                                Correct
    THUMB_MUL,                          // 36 MUL — Multiply two registers                                      Correct

    // ───────────────────────────────────────────────
    // Branches (36–39)
    THUMB_B_COND,                       // 37 B<cond> — Conditional branch (based on flags)                     Correct
    THUMB_B,                            // 38 B — Unconditional branch (relative jump)                          Correct
    THUMB_BL,                           // 39 BL — Branch with link (call subroutine)                           Correct
    THUMB_BLX,                          // 40 BLX 
    THUMB_BX,                           // 41 BX — Branch and exchange to address in register                   Correct

    // ───────────────────────────────────────────────
    // Load / Store Single (40–56)
    THUMB_LDR_REG,                      // 42 LDR (register offset) — Load from address in register             Correct
    THUMB_LDR_IMM,                      // 43 LDR (immediate offset) — Load from address with offset            Correct
    THUMB_LDR_LIT,                      // 44 LDR (literal) — Load from PC-relative address                     Correct
    THUMB_LDR_SP,                       // 45 LDR (SP-relative) — Load from SP + offset                         Correct
    THUMB_STR_REG,                      // 46 STR (register offset) — Store to address in register              Correct
    THUMB_STR_IMM,                      // 47 STR (immediate offset) — Store to address with offset             Correct
    THUMB_STR_SP,                       // 48 STR (SP-relative) — Store to SP + offset                          Correct
    THUMB_LDRB_REG,                     // 49 LDRB (register offset) — Load byte from memory                    Correct
    THUMB_LDRB_IMM,                     // 50 LDRB (immediate offset) — Load byte with offset                   Correct
    THUMB_STRB_REG,                     // 51 STRB (register offset) — Store byte to memory                     Correct
    THUMB_STRB_IMM,                     // 52 STRB (immediate offset) — Store byte with offset                  Correct
    THUMB_LDRH_REG,                     // 53 LDRH (register offset) — Load halfword from memory                Correct
    THUMB_LDRH_IMM,                     // 54 LDRH (immediate offset) — Load halfword with offset               Correct
    THUMB_STRH_REG,                     // 55 STRH (register offset) — Store halfword to memory                 Correct
    THUMB_STRH_IMM,                     // 56 STRH (immediate offset) — Store halfword with offset              Correct
    THUMB_LDRSB_REG,                    // 57 LDRSB — Load signed byte                                          Correct
    THUMB_LDRSH_REG,                    // 58 LDRSH — Load signed halfword                                      Correct

    // ───────────────────────────────────────────────
    // Load / Store Multiple (57–60)
    THUMB_LDMIA,                        // 59 LDMIA — Load multiple registers incrementing after                Correct
    THUMB_STMIA,                        // 60 STMIA — Store multiple registers incrementing after               Correct
    THUMB_PUSH,                         // 61 PUSH — Push registers onto stack                                  Correct
    THUMB_POP,                          // 62 POP — Pop registers from stack                                    Correct

    // ───────────────────────────────────────────────
    // Miscellaneous (61–69)
    THUMB_SXTB,                         // 63 SXTB — Sign-extend byte to 32-bit                                 Correct
    THUMB_SXTH,                         // 64 SXTH — Sign-extend halfword to 32-bit                             Correct
    THUMB_UXTB,                         // 65 UXTB — Zero-extend byte to 32-bit                                 Correct
    THUMB_UXTH,                         // 66 UXTH — Zero-extend halfword to 32-bit                             Correct
    THUMB_REV,                          // 67 REV — Reverse byte order in a 32-bit word                         Correct
    THUMB_REV16,                        // 68 REV16 — Reverse byte order within each halfword                   Correct
    THUMB_REVSH,                        // 69 REVSH — Reverse bytes in a halfword and sign-extend               Correct
    THUMB_CBZ,                          // 70 CBZ — Compare register with zero, branch if zero                  Correct
    THUMB_CBNZ,                         // 71 CBNZ — Compare register with zero, branch if non-zero             Correct

    // ───────────────────────────────────────────────
    // Hints / Control (70–76)
    THUMB_NOP,                          // 72 NOP — No operation                                                Correct
    THUMB_YIELD,                        // 73 YIELD — Hint for thread yield
    THUMB_WFE,                          // 74 WFE — Wait for event
    THUMB_WFI,                          // 75 WFI — Wait for interrupt
    THUMB_SEV,                          // 76 SEV — Send event to all cores
    THUMB_BKPT,                         // 77 BKPT — Breakpoint instruction (debug)                             Correct
    THUMB_SVC                           // 78 SVC — Supervisor call (software interrupt)                        Correct
    // Total: 79 entries including INVALID and new ADD variants
} thumb_operation_t;

// Decoded result structure
typedef struct {
    uint16_t instruction;      // Raw 16-bit instruction
    uint8_t valid;             // 1 = valid decode, 0 = invalid/unrecognized
    uint8_t is_32bit;          // 1 = 32-bit instruction, 0 = 16-bit
    thumb_operation_t operation; // Decoded operation type

    uint8_t rd;                // Destination register (0-15)
    uint8_t rs1;               // Source register 1 / Base register (0-15)
    uint8_t rs2;               // Source register 2 / Offset register (0-15)

    uint8_t immediate_flag;    // 1 if instruction has immediate value
    uint32_t imm_value;        // Immediate value (already scaled if applicable)
    int size;                  // 1 = 16-bit, 2 = 32-bit
    uint32_t condition;        // For conditional branches: 0=EQ, 1=NE, 2=CS, 3=CC, 4=MI, 5=PL, 6=VS, 7=VC, 8=HI, 9=LS, 10=GE, 11=LT, 12=GT, 13=LE
    uint32_t r_bit;            // For PUSH/POP: 1 if LR/PC is included, 0 otherwise
} decode_result_t;

// Function prototypes
/**
 * Decode a 16-bit Thumb instruction
 * @param instruction 16-bit Thumb instruction word
 * @return Decoded result with operation type and operands
 */
decode_result_t decode_thumb16_instruction(uint16_t instruction);

/**
 * Decode a 32-bit Thumb instruction
 * @param instruction 32-bit Thumb instruction word
 * @return Decoded result with operation type and operands
 */
decode_result_t decode_thumb32_instruction(uint32_t instruction);

/**
 * Get human-readable operation name
 * @param op Operation enumeration value
 * @return String name of the operation
 */
const char* get_operation_name(thumb_operation_t op);

/**
 * Print decoded instruction result to stdout
 * @param result Pointer to decode_result_t structure
 */
void print_decode_result(decode_result_t* result);

#ifdef __cplusplus
}
#endif

#endif // DECODE_H