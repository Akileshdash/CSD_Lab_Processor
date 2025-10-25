#include "decode.h"
#include <stdint.h>
#include <stdio.h>

// Helper function to extract bit fields
static inline uint32_t extract_bits(uint32_t value, int start, int end) {
    return (value >> start) & ((1u << (end - start + 1)) - 1);
}

// Helper function to sign-extend immediate values
static inline uint32_t sign_extend(uint32_t value, int bits) {
    uint32_t sign_bit = 1u << (bits - 1);
    return (value ^ sign_bit) - sign_bit;
}

decode_result_t decode_thumb16_instruction(uint16_t instruction) {
    decode_result_t result = {0};

    // Extract key opcode fields
    uint32_t bits_15_13 = extract_bits(instruction, 13, 15);
    uint32_t bits_15_12 = extract_bits(instruction, 12, 15);
    uint32_t bits_15_11 = extract_bits(instruction, 11, 15);
    uint32_t bits_15_10 = extract_bits(instruction, 10, 15);
    uint32_t bits_15_9  = extract_bits(instruction, 9, 15);
    uint32_t bits_15_8  = extract_bits(instruction, 8, 15);
    uint32_t bits_15_6  = extract_bits(instruction, 6, 15);

    printf("[DECODE DEBUG] instr=0x%04X | bits_15_13=0x%X | bits_15_12=0x%X | bits_15_11=0x%X | bits_15_10=0x%X | bits_15_9=0x%X | bits_15_8=0x%X | bits_15_6=0x%X\n",
        instruction, bits_15_13, bits_15_12, bits_15_11, bits_15_10, bits_15_9, bits_15_8, bits_15_6);

    result.instruction = instruction;
    result.valid = 1;

    // 1. MOV (register) [0001110000 Rn Rd]
    if (bits_15_6 == 0b0001110000) {
        uint32_t rn = extract_bits(instruction, 3, 5);
        uint32_t rd = extract_bits(instruction, 0, 2);

        result.rd = rd;
        result.rs1 = rn;
        result.immediate_flag = 0;
        result.operation = THUMB_MOV_REG;
    }


    // 2. ADD/SUB (register) [000110x]
    else if (bits_15_9 == 0b0001100 || bits_15_9 == 0b0001101) {
        uint32_t opc = extract_bits(instruction, 9, 9);
        uint32_t rm = extract_bits(instruction, 6, 8);
        uint32_t rn = extract_bits(instruction, 3, 5);
        uint32_t rd = extract_bits(instruction, 0, 2);

        result.rd = rd;
        result.rs1 = rn;
        result.rs2 = rm;
        result.immediate_flag = 0;
        result.operation = (opc == 0) ? THUMB_ADD_REG : THUMB_SUB_REG;
    }

    // 3. ADD/SUB (imm3) [000111x]
    else if (bits_15_9 == 0b0001110 || bits_15_9 == 0b0001111) {
        uint32_t opc = extract_bits(instruction, 9, 9);
        uint32_t imm3 = extract_bits(instruction, 6, 8);
        uint32_t rn = extract_bits(instruction, 3, 5);
        uint32_t rd = extract_bits(instruction, 0, 2);

        result.rd = rd;
        result.rs1 = rn;
        result.immediate_flag = 1;
        result.imm_value = imm3;
        result.operation = (opc == 0) ? THUMB_ADD_IMM3 : THUMB_SUB_IMM3;
    }

    // 4. MOV/CMP/ADD/SUB (imm8) [001xx]
    else if (bits_15_13 == 0b001) {
        uint32_t opcode = extract_bits(instruction, 11, 12);
        uint32_t rd = extract_bits(instruction, 8, 10);
        uint32_t imm8 = extract_bits(instruction, 0, 7);

        result.rd = rd;
        result.rs1 = rd;
        result.immediate_flag = 1;
        result.imm_value = imm8;

        switch (opcode) {
            case 0b00: result.operation = THUMB_MOV_IMM; break;
            case 0b01: result.operation = THUMB_CMP_IMM; break;
            case 0b10: result.operation = THUMB_ADD_IMM8; break;
            case 0b11: result.operation = THUMB_SUB_IMM8; break;
        }
    }

    // 5. Data processing [010000]
    else if (bits_15_10 == 0b010000) {
        uint32_t opcode = extract_bits(instruction, 6, 9);
        uint32_t rm = extract_bits(instruction, 3, 5);
        uint32_t rd = extract_bits(instruction, 0, 2);

        result.rd = rd;
        result.rs1 = rd;
        result.rs2 = rm;
        result.immediate_flag = 0;

        switch (opcode) {
            case 0b0000: result.operation = THUMB_AND; break;
            case 0b0001: result.operation = THUMB_EOR; break;
            case 0b0010: result.operation = THUMB_LSL_REG; break;
            case 0b0011: result.operation = THUMB_LSR_REG; break;
            case 0b0100: result.operation = THUMB_ASR_REG; break;
            case 0b0101: result.operation = THUMB_ADC; break;
            case 0b0110: result.operation = THUMB_SBC; break;
            case 0b0111: result.operation = THUMB_ROR; break;
            case 0b1000: result.operation = THUMB_TST; break;
            case 0b1001: result.operation = THUMB_RSB; break;
            case 0b1010: result.operation = THUMB_CMP_REG; break;
            case 0b1011: result.operation = THUMB_CMN; break;
            case 0b1100: result.operation = THUMB_ORR; break;
            case 0b1101: result.operation = THUMB_MUL; break;
            case 0b1110: result.operation = THUMB_BIC; break;
            case 0b1111: result.operation = THUMB_MVN; break;
        }
    }

    // 6. BX [01000111]
    else if (bits_15_8 == 0b01000111) {
        result.operation = THUMB_BX;
    }

    // 7. MOV/CMP (high register) [01000110 / 01000101]
    else if (bits_15_10 == 0b010001) {
        uint32_t opcode = extract_bits(instruction, 8, 9);
        uint32_t h1 = extract_bits(instruction, 7, 7);
        uint32_t h2 = extract_bits(instruction, 6, 6);
        uint32_t rm = extract_bits(instruction, 3, 5) + (h2 << 3);
        uint32_t rd = extract_bits(instruction, 0, 2) + (h1 << 3);

        result.rd = rd;
        result.rs1 = rd;
        result.rs2 = rm;
        result.immediate_flag = 0;

        switch (opcode) {
            case 0b01: result.operation = THUMB_CMP_HIGH; break;
            case 0b10: result.operation = THUMB_MOV_HIGH; break;
            default: result.valid = 0; break;
        }
    }

    // 8. LDR literal [01001]
    else if (bits_15_11 == 0b01001) {
        uint32_t rd = extract_bits(instruction, 8, 10);
        uint32_t imm8 = extract_bits(instruction, 0, 7);
        result.operation = THUMB_LDR_LIT;
        result.rd = rd;
        result.immediate_flag = 1;
        result.imm_value = imm8 << 2;
    }

    // 9. Load/store multiple [1100x]
    else if (bits_15_12 == 0b1100) {
        uint32_t l = extract_bits(instruction, 11, 11);
        uint32_t rn = extract_bits(instruction, 8, 10);
        uint32_t reglist = extract_bits(instruction, 0, 7);
        result.rs1 = rn;
        result.immediate_flag = 1;
        result.imm_value = reglist;
        result.operation = (l == 0) ? THUMB_STMIA : THUMB_LDMIA;
    }

    // 10. Conditional branch [1101]
    else if (bits_15_12 == 0b1101) {
        uint32_t cond = extract_bits(instruction, 8, 11);
        uint32_t imm8 = extract_bits(instruction, 0, 7);
        if (cond == 0b1111) {
            result.operation = THUMB_SVC;
            result.imm_value = imm8;
            result.immediate_flag = 1;
        } else {
            result.operation = THUMB_B_COND;
            result.imm_value = sign_extend(imm8 << 1, 9);
            result.immediate_flag = 1;
            result.condition = cond;
        }
    }

    // 11. Unconditional branch [11100]
    else if (bits_15_11 == 0b11100) {
        uint32_t imm11 = extract_bits(instruction, 0, 10);
        result.operation = THUMB_B;
        result.immediate_flag = 1;
        result.imm_value = sign_extend(imm11 << 1, 12);
    }

    // 12. Shift/move immediate [000xx]
    else if (bits_15_13 == 0b000) {
        uint32_t opcode = extract_bits(instruction, 11, 12);
        uint32_t imm5 = extract_bits(instruction, 6, 10);
        uint32_t rm = extract_bits(instruction, 3, 5);
        uint32_t rd = extract_bits(instruction, 0, 2);

        result.rd = rd;
        result.rs1 = rm;
        result.immediate_flag = 1;
        result.imm_value = imm5;

        switch (opcode) {
            case 0b00:
                if (imm5 == 1) result.operation = THUMB_LSL_IMM;
                break;
            case 0b01:
                result.operation = THUMB_LSR_IMM;
                if (imm5 == 0) result.imm_value = 32;
                break;
            case 0b10:
                result.operation = THUMB_ASR_IMM;
                if (imm5 == 0) result.imm_value = 32;
                break;
            default:
                result.valid = 0;
                break;
        }
    }

    else {
        result.valid = 0;
    }

    return result;
}

// Decode 32-bit BL
decode_result_t decode_thumb32_instruction(uint32_t instr32) {
    decode_result_t result = {0};
    result.valid = 1;
    result.is_32bit = 1;

    uint16_t hw1 = (instr32 >> 16) & 0xFFFF;
    uint16_t hw2 = instr32 & 0xFFFF;
    // BL
    if ((hw1 & 0xF800) == 0xF000 && (hw2 & 0xD000) == 0xD000) {
        uint32_t S = (hw1 >> 10) & 1;
        uint32_t J1 = (hw2 >> 13) & 1;
        uint32_t J2 = (hw2 >> 11) & 1;
        uint32_t imm10 = hw1 & 0x03FF;
        uint32_t imm11 = hw2 & 0x07FF;

        uint32_t I1 = ~(J1 ^ S) & 1;
        uint32_t I2 = ~(J2 ^ S) & 1;

        uint32_t imm32 = (S << 24) | (I1 << 23) | (I2 << 22) |
                         (imm10 << 12) | (imm11 << 1);

        result.operation = THUMB_BL;
        result.immediate_flag = 1;
        result.imm_value = sign_extend(imm32, 25);

        // Debug info
        printf("[DECODE32 BL] hw1=0x%04X hw2=0x%04X | S=%u J1=%u J2=%u | I1=%u I2=%u | imm10=0x%03X imm11=0x%03X | imm32=0x%08X | signext=0x%08X\n",
            hw1, hw2, S, J1, J2, I1, I2, imm10, imm11, imm32, result.imm_value);

        return result;
    }

    result.valid = 0;
    return result;
}

// Operation name table
const char* get_operation_name(thumb_operation_t op) {
    static const char* names[] = {
        "INVALID", "MOV_REG", "MOV_IMM", "MOV_HIGH",
        "LSL_IMM", "LSL_REG", "LSR_IMM", "LSR_REG", "ASR_IMM", "ASR_REG",
        "ADD_REG", "ADD_IMM3", "ADD_IMM8", "ADD_SP_IMM", "ADD_SP_IMM7",
        "SUB_REG", "SUB_IMM3", "SUB_IMM8", "SUB_SP_IMM7", "ADR",
        "CMP_REG", "CMP_IMM", "CMP_HIGH", "CMN", "TST", "NEG",
        "AND", "EOR", "ORR", "BIC", "MVN", "ADC", "SBC", "RSB", "ROR", "MUL",
        "B_COND", "B", "BL", "BX",
        "LDR_REG", "LDR_IMM", "LDR_LIT", "LDR_SP",
        "STR_REG", "STR_IMM", "STR_SP",
        "LDRB_REG", "LDRB_IMM", "STRB_REG", "STRB_IMM",
        "LDRH_REG", "LDRH_IMM", "STRH_REG", "STRH_IMM",
        "LDRSB_REG", "LDRSH_REG", "LDMIA", "STMIA", "PUSH", "POP",
        "SXTB", "SXTH", "UXTB", "UXTH",
        "REV", "REV16", "REVSH", "CBZ", "CBNZ",
        "NOP", "YIELD", "WFE", "WFI", "SEV", "BKPT", "SVC"
    };

    if (op < sizeof(names)/sizeof(names[0]))
        return names[op];
    return "UNKNOWN";
}

// Debug print
void print_decode_result(decode_result_t* result) {
    printf("Instruction: 0x%04X\n", result->instruction);
    printf("Valid: %s\n", result->valid ? "YES" : "NO");
    printf("Operation: %s\n", get_operation_name(result->operation));
    printf("Rd: %u, Rs1: %u, Rs2: %u\n", result->rd, result->rs1, result->rs2);
    if (result->immediate_flag)
        printf("Immediate: 0x%X\n", result->imm_value);
    if (result->operation == THUMB_B_COND)
        printf("Condition: %u\n", result->condition);
    printf("\n");
}
