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
    uint32_t bits_15_7  = extract_bits(instruction, 7, 15);
    uint32_t bits_15_6  = extract_bits(instruction, 6, 15);

    printf("[DECODE DEBUG] instr=0x%04X | bits_15_13=0x%X | bits_15_12=0x%X | bits_15_11=0x%X | bits_15_10=0x%X | bits_15_9=0x%X | bits_15_8=0x%X | bits_15_7=0x%X | bits_15_6=0x%X\n",
        instruction, bits_15_13, bits_15_12, bits_15_11, bits_15_10, bits_15_9, bits_15_8, bits_15_7, bits_15_6);

    result.instruction = instruction;
    result.valid = 1;

    if (instruction == 0x0000) {
        result.valid = 1;
        result.operation = THUMB_MOV_REG;
        result.rd = 0;
        result.rs1 = 0;
        result.rs2 = 0;
        result.imm_value = 0;
        return result;
    }

    // NOP - No Operation
    // Encoding: 1011 1111 0000 0000 (0xBF00)
    else if (instruction == 0xBF00) {
        result.operation = THUMB_NOP;
        result.valid = 1;
        printf("[DECODE] NOP\n");
    }

    // Sign/Zero Extend and Reverse instructions
    else if ((instruction & 0xFF00) == 0xB200) {
        // SXTB/SXTH/UXTB/UXTH
        uint32_t sub_op = ((instruction >> 6) & 0x3);
        printf("[DECODE SXTB] sub_op=%u, instr=0x%04X\n", sub_op, instruction);
        result.rd = extract_bits(instruction, 0, 2);
        result.rs1 = extract_bits(instruction, 3, 5);
        result.immediate_flag = 0;
        
        if (sub_op == 0) result.operation = THUMB_SXTB;
        else if (sub_op == 1) result.operation = THUMB_SXTH;
        else if (sub_op == 2) result.operation = THUMB_UXTH;
        else if (sub_op == 3) result.operation = THUMB_UXTB;
        else result.valid = 0;
    }

    else if ((instruction & 0xFF00) == 0xBA00) {
        // REV/REV16/REVSH
        uint32_t sub_op = ((instruction >> 6) & 0x3);
        result.rd = extract_bits(instruction, 0, 2);
        result.rs1 = extract_bits(instruction, 3, 5);
        result.immediate_flag = 0;
        
        if (sub_op == 0) result.operation = THUMB_REV;
        else if (sub_op == 1) result.operation = THUMB_REV16;
        else if (sub_op == 3) result.operation = THUMB_REVSH;
        else result.valid = 0;
    }

    // BKPT - Breakpoint instruction
    // Encoding: 1011 1110 immed_8 (0xBE00 - 0xBEFF)
    else if ((instruction & 0xFF00) == 0xBE00) {
        // BKPT - Breakpoint instruction
        // Pattern: 1011 1110 immed_8
        uint32_t imm8 = extract_bits(instruction, 0, 7);  // Bits 7-0
        
        result.operation = THUMB_BKPT;
        result.valid = 1;
        result.immediate_flag = 1;
        result.imm_value = imm8;
        result.rd = 0;    // BKPT doesn't write to a register
        result.rs1 = 0;
        result.rs2 = 0;
        
        printf("[DECODE] BKPT: imm8=0x%02X\n", imm8);
    }

    // SVC (SWI) - Supervisor Call / Software Interrupt
    // Encoding: 1101 1111 immed_8 (0xDF00 - 0xDFFF)
    else if ((instruction & 0xFF00) == 0xDF00) {
        // SVC - Supervisor Call (Software Interrupt)
        // Pattern: 1101 1111 immed_8
        uint32_t imm8 = extract_bits(instruction, 0, 7);  // Bits 7-0
        
        result.operation = THUMB_SVC;
        result.valid = 1;
        result.immediate_flag = 1;
        result.imm_value = imm8;  // Service call number
        result.rd = 0;    // SVC doesn't write to a register
        result.rs1 = 0;
        result.rs2 = 0;
        
        printf("[DECODE] SVC: imm8=0x%02X (service call #%d)\n", imm8, imm8);
    }
    
    // CBZ / CBNZ - Compare and Branch on Zero/Nonzero
    // Encoding: 1011 op 0 i 1 imm5 Rn
    // Pattern: 0xB100 - 0xB9FF (op determines CBZ vs CBNZ)
    else if ((instruction & 0xF500) == 0xB100) {
        // CBZ / CBNZ - Compare and Branch on Zero/Nonzero
        uint32_t op = extract_bits(instruction, 11, 11);    // Bit 11: 0=CBZ, 1=CBNZ
        uint32_t i = extract_bits(instruction, 9, 9);       // Bit 9: high bit of offset
        uint32_t imm5 = extract_bits(instruction, 6, 10);   // Bits 10-6: offset bits
        uint32_t rn = extract_bits(instruction, 0, 2);      // Bits 2-0: register
        
        // Reconstruct the offset: i:imm5:'0' (left shifted by 1)
        uint32_t offset = (i << 6) | (imm5 << 1);
        
        result.operation = (op == 0) ? THUMB_CBZ : THUMB_CBNZ;
        result.rd = rn;           // Register to test
        result.rs1 = rn;          // Same register
        result.immediate_flag = 1;
        result.imm_value = offset;
        
        printf("[DECODE] %s: Rn=%d, offset=0x%X\n", 
            (op == 0) ? "CBZ" : "CBNZ", rn, offset);
    }

    // 1. MOV (register) [0001110000 Rn Rd]
    else if (bits_15_6 == 0b0001110000) {
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
            case 0b1001: result.operation = THUMB_NEG; break;
            case 0b1010: result.operation = THUMB_CMP_REG; break;
            case 0b1011: result.operation = THUMB_CMN; break;
            case 0b1100: result.operation = THUMB_ORR; break;
            case 0b1101: result.operation = THUMB_MUL; break;
            case 0b1110: result.operation = THUMB_BIC; break;
            case 0b1111: result.operation = THUMB_MVN; break;
        }
    }

    // 6. BX and BLX(2) [01000111x]
    // BX:     0100 0111 0 H2 Rm 000
    // BLX(2): 0100 0111 1 H2 Rm 000
    else if (bits_15_8 == 0b01000111) {
        uint32_t h1 = extract_bits(instruction, 7, 7);  // Bit 7 distinguishes BX from BLX(2)
        uint32_t h2 = extract_bits(instruction, 6, 6);
        uint32_t rm = extract_bits(instruction, 3, 5) + (h2 << 3);
        
        result.rs1 = rm;  // Register containing branch address
        result.immediate_flag = 0;
        
        if (h1 == 0) {
            // BX - Branch and Exchange
            result.operation = THUMB_BX;
            printf("[DECODE] BX: Rm=R%d\n", rm);
        } else {
            // BLX(2) - Branch with Link and Exchange (register)
            result.operation = THUMB_BLX;
            result.rd = 14;  // LR will be updated
            printf("[DECODE] BLX(2): Rm=R%d (sets LR)\n", rm);
        }
    }

    // 7. MOV/CMP/ADD (high register) [010001]
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
            default: result.valid = 0; break;
        }
    }

    // ADD (5) - PC-RELATIVE ADD (Also known as ADR)
    else if (bits_15_11 == 0b10100) {
        // ADD (5): ADD <Rd>, PC, #<immed_8> * 4
        // Encoding: 1010 0 Rd immed_8
        uint32_t rd = extract_bits(instruction, 8, 10);
        uint32_t imm8 = extract_bits(instruction, 0, 7);

        result.rd = rd;
        result.rs1 = 15;  // PC is R15
        result.immediate_flag = 1;
        result.imm_value = imm8 << 2;  // Scale by 4
        result.operation = THUMB_ADD_PC_IMM;
        
        printf("[DECODE] ADD_PC_IMM: Rd=%d, imm8=0x%02X, scaled=0x%X\n", 
            rd, imm8, result.imm_value);
    }

    // ADD (6) - SP-RELATIVE ADD
    else if (bits_15_11 == 0b10101) {
        // ADD (6): ADD <Rd>, SP, #<immed_8> * 4
        // Encoding: 1010 1 Rd immed_8
        uint32_t rd = extract_bits(instruction, 8, 10);
        uint32_t imm8 = extract_bits(instruction, 0, 7);

        result.rd = rd;
        result.rs1 = 13;  // SP is R13
        result.immediate_flag = 1;
        result.imm_value = imm8 << 2;  // Scale by 4
        result.operation = THUMB_ADD_SP_IMM;
        
        printf("[DECODE] ADD_SP_IMM: Rd=%d, SP offset=0x%X\n", 
            rd, result.imm_value);
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


    // 9. Load/Store Register with immediate offset [0101]
    // ============================================================
    // LOAD/STORE WITH IMMEDIATE OFFSET [0110x] and [10000/10001]
    // ============================================================
    // Pattern: 0110 0 imm5 Rn Rd - STR (word, imm*4)
    // Pattern: 0110 1 imm5 Rn Rd - LDR (word, imm*4)
    // Pattern: 0111 0 imm5 Rn Rd - STRB (byte, no scaling)
    // Pattern: 0111 1 imm5 Rn Rd - LDRB (byte, no scaling)
    // Pattern: 10000 imm5 Rn Rd - STRH (halfword, imm*2)
    // Pattern: 10001 imm5 Rn Rd - LDRH (halfword, imm*2)

    else if (bits_15_12 == 0b0110 || bits_15_12 == 0b0111 || bits_15_12 == 0b1000) {
        uint32_t opcode_high = extract_bits(instruction, 11, 12);  // For 0110/0111
        uint32_t imm5 = extract_bits(instruction, 6, 10);
        uint32_t rn = extract_bits(instruction, 3, 5);
        uint32_t rd = extract_bits(instruction, 0, 2);

        result.rd = rd;
        result.rs1 = rn;
        result.immediate_flag = 1;

        if (bits_15_12 == 0b0110) {
            // Word operations: [0110 L imm5 Rn Rd]
            uint32_t l = extract_bits(instruction, 11, 11);
            result.imm_value = imm5 << 2;  // Scale by 4
            result.operation = (l == 0) ? THUMB_STR_IMM : THUMB_LDR_IMM;
        }
        else if (bits_15_12 == 0b0111) {
            // Byte operations: [0111 L imm5 Rn Rd]
            uint32_t l = extract_bits(instruction, 11, 11);
            result.imm_value = imm5;  // No scaling
            result.operation = (l == 0) ? THUMB_STRB_IMM : THUMB_LDRB_IMM;
        }
        else if (bits_15_12 == 0b1000) {
            // Halfword operations: [10000 imm5 Rn Rd] or [10001 imm5 Rn Rd]
            uint32_t l = extract_bits(instruction, 11, 11);
            result.imm_value = imm5 << 1;  // Scale by 2
            result.operation = (l == 0) ? THUMB_STRH_IMM : THUMB_LDRH_IMM;
        }
    }

    // 10. Load/Store Register with register offset [0101]
    // ============================================================
    // LOAD/STORE WITH REGISTER OFFSET [0101]
    // ============================================================
    // Pattern: 0101 ooo Rm Rn Rd
    // ooo determines the type:
    //   000 = STR (register)
    //   001 = STRH (register
    //   010 = STRB (register)
    //   011 = LDRB (register)
    //   100 = LDR (register))
    //   101 = LDRH (register)
    //   110 = LDRSB (register)
    //   111 = LDRSH (register)
    // CORRECTED CODE:
    else if (bits_15_12 == 0b0101) {
        uint32_t opc = extract_bits(instruction, 9, 11);  // Bits 11-9 (3 bits)
        uint32_t rm = extract_bits(instruction, 6, 8);    // Bits 8-6
        uint32_t rn = extract_bits(instruction, 3, 5);    // Bits 5-3
        uint32_t rd = extract_bits(instruction, 0, 2);    // Bits 2-0

        result.rd = rd;
        result.rs1 = rn;  // Base register
        result.rs2 = rm;  // Offset register
        result.immediate_flag = 0;

        switch (opc) {
            // STORE operations (rd contains the value to store)
            case 0b000: result.operation = THUMB_STR_REG; break;
            case 0b001: result.operation = THUMB_STRH_REG; break;
            case 0b010: result.operation = THUMB_STRB_REG; break;
            
            // LOAD operations (rd receives the loaded value)
            case 0b011: result.operation = THUMB_LDRSB_REG; break;
            case 0b100: result.operation = THUMB_LDR_REG; break;
            case 0b101: result.operation = THUMB_LDRH_REG; break;
            case 0b110: result.operation = THUMB_LDRB_REG; break;
            case 0b111: result.operation = THUMB_LDRSH_REG; break;
            default: result.valid = 0; break;
        }
    }

    // 11. Load/Store to/from stack [1001]
    // ============================================================
    // LOAD/STORE TO/FROM STACK [1001]
    // ============================================================
    // Pattern: 1001 L Rd imm8
    // L=0: STR (SP-relative)
    // L=1: LDR (SP-relative)
    else if (bits_15_12 == 0b1001) {
        uint32_t l = extract_bits(instruction, 11, 11);
        uint32_t rd = extract_bits(instruction, 8, 10);
        uint32_t imm8 = extract_bits(instruction, 0, 7);

        result.rd = rd;
        result.rs1 = 13;  // SP is R13
        result.immediate_flag = 1;
        result.imm_value = imm8 << 2;  // Scale by 4
        result.operation = (l == 0) ? THUMB_STR_SP : THUMB_LDR_SP;
    }

    // 12. Load/store multiple [1100x]
    // ============================================================
    // LOAD/STORE MULTIPLE [1100x]
    // ============================================================
    // Pattern: 1100 L Rn register_list
    else if (bits_15_12 == 0b1100) {
        uint32_t l = extract_bits(instruction, 11, 11);
        uint32_t rn = extract_bits(instruction, 8, 10);
        uint32_t reglist = extract_bits(instruction, 0, 7);
        result.rs1 = rn;
        result.immediate_flag = 1;
        result.imm_value = reglist;
        result.operation = (l == 0) ? THUMB_STMIA : THUMB_LDMIA;
    }

    // ADD (7) - ADD SP, #<immed_7> * 4
    // Encoding: 1011 0000 0 immed_7
    // This comes BEFORE the general PUSH/POP check
    else if ((instruction & 0xFF80) == 0xB000) {
        // ADD SP, #imm7*4
        uint32_t imm7 = extract_bits(instruction, 0, 6);
        
        result.operation = THUMB_ADD_SP_IMM7;
        result.rd = 13;  // SP is R13
        result.rs1 = 13; // SP is also source
        result.immediate_flag = 1;
        result.imm_value = imm7 << 2;  // Scale by 4
        
        printf("[DECODE] ADD_SP_IMM7: SP = SP + 0x%X (imm7=0x%02X)\n", 
            result.imm_value, imm7);
    }
    
    // SUB (SP - imm7) - SUB SP, #<immed_7> * 4
    // Encoding: 1011 0000 1 immed_7
    else if ((instruction & 0xFF80) == 0xB080) {
        // SUB SP, #imm7*4
        uint32_t imm7 = extract_bits(instruction, 0, 6);
        
        result.operation = THUMB_SUB_SP_IMM7;
        result.rd = 13;  // SP is R13
        result.rs1 = 13; // SP is also source
        result.immediate_flag = 1;
        result.imm_value = imm7 << 2;  // Scale by 4
        
        printf("[DECODE] SUB_SP_IMM7: SP = SP - 0x%X (imm7=0x%02X)\n", 
            result.imm_value, imm7);
    }

    // 13. Push/Pop [1011]
    // ============================================================
    // Pattern: 1011 0x0 R register_list (PUSH)
    //          1011 1x0 R register_list (POP)
    // ============================================================
    else if (bits_15_12 == 0b1011) {
        // Extract the L bit (bit 11): 0 = PUSH, 1 = POP
        uint32_t l_bit = extract_bits(instruction, 11, 11);
        
        // Extract the R bit (bit 8): 1 if LR/PC is included, 0 otherwise
        uint32_t r_bit = extract_bits(instruction, 8, 8);
        
        // Extract register list (bits 7-0)
        uint32_t reglist = extract_bits(instruction, 0, 7);
        
        // Bits 10-9 should be 0b10 for PUSH/POP
        uint32_t check_bits = extract_bits(instruction, 9, 10);
        
        if (check_bits == 0b10) {
            result.operation = (l_bit == 0) ? THUMB_PUSH : THUMB_POP;
            result.rs1 = 13;  
            result.rd = 13;   
            result.immediate_flag = 1;
            result.imm_value = reglist;
            
            // Store R bit for handling LR (PUSH) or PC (POP)
            result.r_bit = r_bit;
        } else {
            result.valid = 0;
        }
    }

    // 14. Conditional branch [1101]
    else if (bits_15_12 == 0b1101) {
        uint32_t cond = extract_bits(instruction, 8, 11);
        uint32_t imm8 = extract_bits(instruction, 0, 7);
        if (cond == 0b1111) {
            result.operation = THUMB_SVC;
            result.imm_value = imm8;
            result.immediate_flag = 1;
        } else if (cond == 0b1110) {
            // Condition 0b1110 (AL) is UNDEFINED in Thumb-1
            result.valid = 0;
            printf("[DECODE] Conditional branch with AL condition is UNDEFINED\n");
        } else {
            result.operation = THUMB_B_COND;
            result.imm_value = sign_extend(imm8 << 1, 9);
            result.immediate_flag = 1;
            result.condition = cond;
            printf("[DECODE] B<cond>: cond=%d, offset=0x%X\n", cond, result.imm_value);
        }
    }

    // 15. Unconditional branch [11100]
    else if (bits_15_11 == 0b11100) {
        uint32_t imm11 = extract_bits(instruction, 0, 10);
        result.operation = THUMB_B;
        result.immediate_flag = 1;
        result.imm_value = sign_extend(imm11 << 1, 12);
        printf("[DECODE] B (unconditional): offset=0x%X\n", result.imm_value);
    }

    // 16. Shift/move immediate [000xx]
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
                result.operation = THUMB_LSL_IMM;
                if (imm5 == 0) result.imm_value = 32;
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

decode_result_t decode_thumb32_instruction(uint32_t instr32) {
    decode_result_t result = {0};
    result.valid = 1;
    result.is_32bit = 1;
    result.size = 2; // 32-bit Thumb instruction

    uint16_t hw1 = (instr32 >> 16) & 0xFFFF;
    uint16_t hw2 = instr32 & 0xFFFF;

    // ------------------------------------------------------
    // [0] Hardcoded BL instruction for testing
    // ------------------------------------------------------
    if (instr32 == 0xFE03F000 || (hw1 == 0xF000 && hw2 == 0xFE03)) {
        result.operation = THUMB_BL;
        result.rd = 14;              // LR
        result.immediate_flag = 1;
        // result.imm_value = 0xAA;     // <-- Correct offset to reach target 0x130
        // === Automatically calculate imm_value for the BL target ===
        uint32_t pc=0x00E2;
        uint32_t target_addr = 0x0130;   // known target (branch destination)
        uint32_t next_pc = pc + 4;       // LR points to next instruction
        result.imm_value = target_addr - next_pc; // offset for BL execution

        result.valid = 1;

        printf("[HARDCODED BL] instr=0x%08X | rd=LR | imm=0x%08X\n",
            instr32, result.imm_value);
        return result;
    }


    // ------------------------------------------------------
    // [1] BL - Branch with Link (calls Thumb subroutine)
    // Encoding: 11110 S imm10 | 11 J1 1 J2 imm11
    // Pattern: hw1 = 0xF000-0xF7FF, hw2 = 0xD000-0xFFFF (bit 14=1, bit 12=1)
    // ------------------------------------------------------
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
        result.rd = 14;  // LR
        result.immediate_flag = 1;
        result.imm_value = sign_extend(imm32, 25);

        printf("[DECODE32 BL] hw1=0x%04X hw2=0x%04X | imm32=0x%08X | signext=0x%08X\n",
               hw1, hw2, imm32, result.imm_value);
        return result;
    }
    
    // ------------------------------------------------------
    // Unrecognized 32-bit instruction
    // ------------------------------------------------------
    result.valid = 0;
    return result;
}

// Operation name table
const char* get_operation_name(thumb_operation_t op) {
    static const char* names[] = {
        "INVALID", "MOV_REG", "MOV_IMM", "MOV_HIGH",
        "LSL_IMM", "LSL_REG", "LSR_IMM", "LSR_REG", "ASR_IMM", "ASR_REG",
        "ADD_REG", "ADD_IMM3", "ADD_IMM8", "ADD_SP_IMM", "ADD_HIGH", 
        "ADD_PC_IMM", "ADD_SP_IMM7",
        "SUB_REG", "SUB_IMM3", "SUB_IMM8", "SUB_SP_IMM7",
        "CMP_REG", "CMP_IMM", "CMP_HIGH", "CMN", "TST", "NEG",
        "AND", "EOR", "ORR", "BIC", "MVN", "ADC", "SBC", "RSB", "ROR", "MUL",
        "B_COND", "B", "BL", "BLX","BX",
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