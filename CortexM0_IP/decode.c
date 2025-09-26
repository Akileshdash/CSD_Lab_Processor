#include "decode.h"
#include <stdint.h>
#include <stdio.h>

// Helper function to extract bit fields
static inline uint32_t extract_bits(uint32_t value, int start, int end) {
    return (value >> start) & ((1 << (end - start + 1)) - 1);
}

// Helper function to sign extend immediate values
static inline uint32_t sign_extend(uint32_t value, int bits) {
    uint32_t sign_bit = 1 << (bits - 1);
    return (value ^ sign_bit) - sign_bit;
}

decode_result_t decode_thumb_instruction(uint16_t instruction) {
    decode_result_t result = {0};
    
    // Extract main opcode fields
    uint32_t bits_15_11 = extract_bits(instruction, 11, 15);
    uint32_t bits_15_13 = extract_bits(instruction, 13, 15);
    uint32_t bits_15_12 = extract_bits(instruction, 12, 15);
    uint32_t bits_15_10 = extract_bits(instruction, 10, 15);
    uint32_t bits_15_9 = extract_bits(instruction, 9, 15);
    uint32_t bits_15_8 = extract_bits(instruction, 8, 15);
    uint32_t bits_15_6 = extract_bits(instruction, 6, 15);
    
    result.instruction = instruction;
    result.valid = 1;
    
    // Decode based on encoding hierarchy from PDF
    
    // 1. Shift (by immediate) and move (register) instructions [000xx]
    if (bits_15_13 == 0b000) {
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
                if (imm5 == 0) {
                    result.operation = THUMB_MOV_REG;
                    result.immediate_flag = 0; // MOV register form
                } else {
                    result.operation = THUMB_LSL_IMM;
                }
                break;
            case 0b01:
                result.operation = THUMB_LSR_IMM;
                if (imm5 == 0) result.imm_value = 32; // LSR #32
                break;
            case 0b10:
                result.operation = THUMB_ASR_IMM;
                if (imm5 == 0) result.imm_value = 32; // ASR #32
                break;
            default:
                result.valid = 0;
                break;
        }
    }
    
    // 2. Add and subtract (register) instructions [000110x]
    else if (bits_15_9 == 0b0001100 || bits_15_9 == 0b0001101) {
        uint32_t opc = extract_bits(instruction, 9, 9);
        uint32_t rm = extract_bits(instruction, 6, 8);
        uint32_t rn = extract_bits(instruction, 3, 5);
        uint32_t rd = extract_bits(instruction, 0, 2);
        
        result.rd = rd;
        result.rs1 = rn;
        result.rs2 = rm;
        result.immediate_flag = 0;
        
        if (opc == 0) {
            result.operation = THUMB_ADD_REG;
        } else {
            result.operation = THUMB_SUB_REG;
        }
    }
    
    // 3. Add and subtract (3-bit immediate) instructions [000111x]
    else if (bits_15_9 == 0b0001110 || bits_15_9 == 0b0001111) {
        uint32_t opc = extract_bits(instruction, 9, 9);
        uint32_t imm3 = extract_bits(instruction, 6, 8);
        uint32_t rn = extract_bits(instruction, 3, 5);
        uint32_t rd = extract_bits(instruction, 0, 2);
        
        result.rd = rd;
        result.rs1 = rn;
        result.immediate_flag = 1;
        result.imm_value = imm3;
        
        if (opc == 0) {
            result.operation = THUMB_ADD_IMM3;
        } else {
            result.operation = THUMB_SUB_IMM3;
        }
    }
    
    // 4. Move, compare, add, subtract (8-bit immediate) [001xx]
    else if (bits_15_13 == 0b001) {
        uint32_t opcode = extract_bits(instruction, 11, 12);
        uint32_t rd = extract_bits(instruction, 8, 10);
        uint32_t imm8 = extract_bits(instruction, 0, 7);
        
        result.rd = rd;
        result.rs1 = rd; // For CMP, ADD, SUB operations
        result.immediate_flag = 1;
        result.imm_value = imm8;
        
        switch (opcode) {
            case 0b00: result.operation = THUMB_MOV_IMM; break;
            case 0b01: result.operation = THUMB_CMP_IMM; break;
            case 0b10: result.operation = THUMB_ADD_IMM8; break;
            case 0b11: result.operation = THUMB_SUB_IMM8; break;
        }
    }
    
    // 5. Data processing (register) instructions [010000xx]
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
    
    // 6. Special data processing instructions [010001xx]
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
            case 0b00: result.operation = THUMB_ADD_HIGH; break;
            case 0b01: result.operation = THUMB_CMP_HIGH; break;
            case 0b10: result.operation = THUMB_MOV_HIGH; break;
            case 0b11: result.valid = 0; break; // Reserved
        }
    }
    
    // 7. Branch and Exchange [010001xx] with specific bit pattern
    else if (bits_15_8 == 0b01000111) {
        uint32_t l = extract_bits(instruction, 7, 7);
        uint32_t rm = extract_bits(instruction, 3, 6);
        
        result.rs1 = rm;
        result.immediate_flag = 0;
        
        if (l == 0) {
            result.operation = THUMB_BX;
        } else {
            result.operation = THUMB_BLX_REG;
        }
    }
    
    // 8. Load from literal pool [01001xxx]
    else if (bits_15_11 == 0b01001) {
        uint32_t rd = extract_bits(instruction, 8, 10);
        uint32_t imm8 = extract_bits(instruction, 0, 7);
        
        result.operation = THUMB_LDR_LIT;
        result.rd = rd;
        result.immediate_flag = 1;
        result.imm_value = imm8 << 2; // Word-aligned
    }
    
    // 9. Load/store register offset [0101xxx]
    else if (bits_15_12 == 0b0101) {
        uint32_t opcode = extract_bits(instruction, 9, 11);
        uint32_t rm = extract_bits(instruction, 6, 8);
        uint32_t rn = extract_bits(instruction, 3, 5);
        uint32_t rd = extract_bits(instruction, 0, 2);
        
        result.rd = rd;
        result.rs1 = rn;
        result.rs2 = rm;
        result.immediate_flag = 0;
        
        switch (opcode) {
            case 0b000: result.operation = THUMB_STR_REG; break;
            case 0b001: result.operation = THUMB_STRH_REG; break;
            case 0b010: result.operation = THUMB_STRB_REG; break;
            case 0b011: result.operation = THUMB_LDRSB_REG; break;
            case 0b100: result.operation = THUMB_LDR_REG; break;
            case 0b101: result.operation = THUMB_LDRH_REG; break;
            case 0b110: result.operation = THUMB_LDRB_REG; break;
            case 0b111: result.operation = THUMB_LDRSH_REG; break;
        }
    }
    
    // 10. Load/store word/byte immediate offset [011xx]
    else if (bits_15_13 == 0b011) {
        uint32_t b = extract_bits(instruction, 12, 12);
        uint32_t l = extract_bits(instruction, 11, 11);
        uint32_t imm5 = extract_bits(instruction, 6, 10);
        uint32_t rn = extract_bits(instruction, 3, 5);
        uint32_t rd = extract_bits(instruction, 0, 2);
        
        result.rd = rd;
        result.rs1 = rn;
        result.immediate_flag = 1;
        
        if (b == 0) {
            // Word operations
            result.imm_value = imm5 << 2; // Word-aligned
            if (l == 0) {
                result.operation = THUMB_STR_IMM;
            } else {
                result.operation = THUMB_LDR_IMM;
            }
        } else {
            // Byte operations
            result.imm_value = imm5;
            if (l == 0) {
                result.operation = THUMB_STRB_IMM;
            } else {
                result.operation = THUMB_LDRB_IMM;
            }
        }
    }
    
    // 11. Load/store halfword immediate offset [1000x]
    else if (bits_15_12 == 0b1000) {
        uint32_t l = extract_bits(instruction, 11, 11);
        uint32_t imm5 = extract_bits(instruction, 6, 10);
        uint32_t rn = extract_bits(instruction, 3, 5);
        uint32_t rd = extract_bits(instruction, 0, 2);
        
        result.rd = rd;
        result.rs1 = rn;
        result.immediate_flag = 1;
        result.imm_value = imm5 << 1; // Halfword-aligned
        
        if (l == 0) {
            result.operation = THUMB_STRH_IMM;
        } else {
            result.operation = THUMB_LDRH_IMM;
        }
    }
    
    // 12. Load/store to/from stack [1001x]
    else if (bits_15_12 == 0b1001) {
        uint32_t l = extract_bits(instruction, 11, 11);
        uint32_t rd = extract_bits(instruction, 8, 10);
        uint32_t imm8 = extract_bits(instruction, 0, 7);
        
        result.rd = rd;
        result.rs1 = 13; // SP
        result.immediate_flag = 1;
        result.imm_value = imm8 << 2; // Word-aligned
        
        if (l == 0) {
            result.operation = THUMB_STR_SP;
        } else {
            result.operation = THUMB_LDR_SP;
        }
    }
    
    // 13. Add to SP or PC [1010x]
    else if (bits_15_12 == 0b1010) {
        uint32_t sp = extract_bits(instruction, 11, 11);
        uint32_t rd = extract_bits(instruction, 8, 10);
        uint32_t imm8 = extract_bits(instruction, 0, 7);
        
        result.rd = rd;
        result.immediate_flag = 1;
        result.imm_value = imm8 << 2; // Word-aligned
        
        if (sp == 0) {
            result.operation = THUMB_ADR;
            result.rs1 = 15; // PC
        } else {
            result.operation = THUMB_ADD_SP_IMM;
            result.rs1 = 13; // SP
        }
    }
    
    // 14. Miscellaneous instructions [1011xxxx]
    else if (bits_15_12 == 0b1011) {
        uint32_t opcode = extract_bits(instruction, 8, 11);
        
        switch (opcode) {
            // Adjust stack pointer
            case 0b0000: {
                uint32_t opc = extract_bits(instruction, 7, 7);
                uint32_t imm7 = extract_bits(instruction, 0, 6);
                
                result.rd = 13; // SP
                result.rs1 = 13; // SP
                result.immediate_flag = 1;
                result.imm_value = imm7 << 2; // Word-aligned
                
                if (opc == 0) {
                    result.operation = THUMB_ADD_SP_IMM7;
                } else {
                    result.operation = THUMB_SUB_SP_IMM7;
                }
                break;
            }
            
            // Sign/zero extend
            case 0b0010: {
                uint32_t opc = extract_bits(instruction, 6, 7);
                uint32_t rm = extract_bits(instruction, 3, 5);
                uint32_t rd = extract_bits(instruction, 0, 2);
                
                result.rd = rd;
                result.rs1 = rm;
                result.immediate_flag = 0;
                
                switch (opc) {
                    case 0b00: result.operation = THUMB_SXTH; break;
                    case 0b01: result.operation = THUMB_SXTB; break;
                    case 0b10: result.operation = THUMB_UXTH; break;
                    case 0b11: result.operation = THUMB_UXTB; break;
                }
                break;
            }
            
            // Compare and branch on zero/non-zero
            case 0b0001:
            case 0b1001:
            case 0b0011:
            case 0b1011: {
                uint32_t n = extract_bits(instruction, 11, 11);
                uint32_t imm5 = extract_bits(instruction, 3, 7);
                uint32_t rn = extract_bits(instruction, 0, 2);
                
                result.rs1 = rn;
                result.immediate_flag = 1;
                result.imm_value = imm5 << 1; // Halfword offset
                
                if (n == 0) {
                    result.operation = THUMB_CBZ;
                } else {
                    result.operation = THUMB_CBNZ;
                }
                break;
            }
            
            // Push/Pop
            case 0b0100:
            case 0b0101:
            case 0b1100:
            case 0b1101: {
                uint32_t l = extract_bits(instruction, 11, 11);
                uint32_t r = extract_bits(instruction, 8, 8);
                uint32_t register_list = extract_bits(instruction, 0, 7);
                
                result.immediate_flag = 1;
                result.imm_value = register_list | (r << 8);
                
                if (l == 0) {
                    result.operation = THUMB_PUSH;
                } else {
                    result.operation = THUMB_POP;
                }
                break;
            }
            
            // // SETEND
            // case 0b0110: {
            //     if (extract_bits(instruction, 4, 7) == 0b0101) {
            //         result.operation = THUMB_SETEND;
            //         result.immediate_flag = 1;
            //         result.imm_value = extract_bits(instruction, 3, 3); // E bit
            //     } else {
            //         result.valid = 0;
            //     }
            //     break;
            // }
            
            // // CPS
            // case 0b0110: {
            //     if (extract_bits(instruction, 4, 7) == 0b0110) {
            //         result.operation = THUMB_CPS;
            //         result.immediate_flag = 1;
            //         result.imm_value = extract_bits(instruction, 0, 3);
            //     } else {
            //         result.valid = 0;
            //     }
            //     break;
            // }
            
            // Reverse bytes
            case 0b1010: {
                uint32_t opc = extract_bits(instruction, 6, 7);
                uint32_t rm = extract_bits(instruction, 3, 5);
                uint32_t rd = extract_bits(instruction, 0, 2);
                
                result.rd = rd;
                result.rs1 = rm;
                result.immediate_flag = 0;
                
                switch (opc) {
                    case 0b00: result.operation = THUMB_REV; break;
                    case 0b01: result.operation = THUMB_REV16; break;
                    case 0b10: result.valid = 0; break; // Undefined
                    case 0b11: result.operation = THUMB_REVSH; break;
                }
                break;
            }
            
            // BKPT
            case 0b1110: {
                result.operation = THUMB_BKPT;
                result.immediate_flag = 1;
                result.imm_value = extract_bits(instruction, 0, 7);
                break;
            }
            
            // IT and hints
            case 0b1111: {
                uint32_t opA = extract_bits(instruction, 4, 7);
                uint32_t opB = extract_bits(instruction, 0, 3);
                
                if (opA != 0) {
                    result.operation = THUMB_IT;
                    result.immediate_flag = 1;
                    result.imm_value = (opA << 4) | opB;
                } else {
                    // Hints
                    switch (opB) {
                        case 0b0000: result.operation = THUMB_NOP; break;
                        case 0b0001: result.operation = THUMB_YIELD; break;
                        case 0b0010: result.operation = THUMB_WFE; break;
                        case 0b0011: result.operation = THUMB_WFI; break;
                        case 0b0100: result.operation = THUMB_SEV; break;
                        default: result.valid = 0; break;
                    }
                }
                break;
            }
            
            default:
                result.valid = 0;
                break;
        }
    }
    
    // 15. Load/store multiple [1100x]
    else if (bits_15_12 == 0b1100) {
        uint32_t l = extract_bits(instruction, 11, 11);
        uint32_t rn = extract_bits(instruction, 8, 10);
        uint32_t register_list = extract_bits(instruction, 0, 7);
        
        result.rs1 = rn;
        result.immediate_flag = 1;
        result.imm_value = register_list;
        
        if (l == 0) {
            result.operation = THUMB_STMIA;
        } else {
            result.operation = THUMB_LDMIA;
        }
    }
    
    // 16. Conditional branch [1101xxxx]
    else if (bits_15_12 == 0b1101) {
        uint32_t cond = extract_bits(instruction, 8, 11);
        uint32_t imm8 = extract_bits(instruction, 0, 7);
        
        if (cond == 0b1110) {
            result.valid = 0; // Undefined
        } else if (cond == 0b1111) {
            result.operation = THUMB_SVC;
            result.immediate_flag = 1;
            result.imm_value = imm8;
        } else {
            result.operation = THUMB_BCC;
            result.immediate_flag = 1;
            result.imm_value = sign_extend(imm8 << 1, 9); // Sign-extend branch offset
            result.condition = cond;
        }
    }
    
    // 17. Unconditional branch [11100xxx]
    else if (bits_15_11 == 0b11100) {
        uint32_t imm11 = extract_bits(instruction, 0, 10);
        
        result.operation = THUMB_B;
        result.immediate_flag = 1;
        result.imm_value = sign_extend(imm11 << 1, 12); // Sign-extend branch offset
    }
    
    // 18. 32-bit instructions (should not happen in this decoder)
    else if (bits_15_11 == 0b11101 || bits_15_11 == 0b11110 || bits_15_11 == 0b11111) {
        result.valid = 0; // 32-bit instruction - not handled here
        result.is_32bit = 1;
    }
    
    else {
        // Unknown instruction
        result.valid = 0;
    }
    
    return result;
}

// Helper function to get operation name for debugging
const char* get_operation_name(thumb_operation_t op) {
    static const char* names[] = {
        "INVALID", "MOV_REG", "LSL_IMM", "LSR_IMM", "ASR_IMM",
        "ADD_REG", "SUB_REG", "ADD_IMM3", "SUB_IMM3",
        "MOV_IMM", "CMP_IMM", "ADD_IMM8", "SUB_IMM8",
        "AND", "EOR", "LSL_REG", "LSR_REG", "ASR_REG",
        "ADC", "SBC", "ROR", "TST", "RSB", "CMP_REG", "CMN",
        "ORR", "MUL", "BIC", "MVN",
        "ADD_HIGH", "CMP_HIGH", "MOV_HIGH",
        "BX", "BLX_REG", "LDR_LIT",
        "STR_REG", "STRH_REG", "STRB_REG", "LDRSB_REG",
        "LDR_REG", "LDRH_REG", "LDRB_REG", "LDRSH_REG",
        "STR_IMM", "LDR_IMM", "STRB_IMM", "LDRB_IMM",
        "STRH_IMM", "LDRH_IMM", "STR_SP", "LDR_SP",
        "ADR", "ADD_SP_IMM", "ADD_SP_IMM7", "SUB_SP_IMM7",
        "SXTH", "SXTB", "UXTH", "UXTB",
        "CBZ", "CBNZ", "PUSH", "POP",
        "SETEND", "CPS", "REV", "REV16", "REVSH",
        "BKPT", "IT", "NOP", "YIELD", "WFE", "WFI", "SEV",
        "STMIA", "LDMIA", "BCC", "SVC", "B"
    };
    
    if (op < sizeof(names)/sizeof(names[0])) {
        return names[op];
    }
    return "UNKNOWN";
}

// Debug function to print decoded instruction
void print_decode_result(decode_result_t* result) {
    printf("Instruction: 0x%04X\n", result->instruction);
    printf("Valid: %s\n", result->valid ? "YES" : "NO");
    printf("Operation: %s\n", get_operation_name(result->operation));
    printf("Rd: %u, Rs1: %u, Rs2: %u\n", result->rd, result->rs1, result->rs2);
    printf("Immediate: %s", result->immediate_flag ? "YES" : "NO");
    if (result->immediate_flag) {
        printf(" (0x%08X)", result->imm_value);
    }
    printf("\n");
    if (result->operation == THUMB_BCC) {
        printf("Condition: %u\n", result->condition);
    }
    printf("\n");
}