#include "execute.h"
#include "regfile.h"
#include "decode.h"
#include <stdint.h>
#include <stdio.h>

EX_output_t execute(EX_input_t input, cortex_m0_registers_t* regs) {
    EX_output_t out = {0};

    uint32_t carry_in = (regs->apsr & 0x20000000) ? 1 : 0; // C flag

    printf("[EX DEBUG] EXECUTE: Opcode=%s, Rd=%u, Operand1=0x%08X, Operand2=0x%08X, CarryIn=%u\n",
           get_operation_name(input.opcode), input.rd, input.reg_data1, input.reg_data2, carry_in);

    switch (input.opcode) {
        // ────────────────────────────────
        // Arithmetic
        // ────────────────────────────────
        case THUMB_ADD_REG:
        case THUMB_ADD_IMM3:
        case THUMB_ADD_IMM8:
        case THUMB_ADD_SP_IMM:
        case THUMB_ADD_SP_IMM7:
        {
            uint64_t temp = (uint64_t)input.reg_data1 + input.reg_data2;
            out.alu_result = (uint32_t)temp;
            uint32_t carry = (temp > 0xFFFFFFFF);
            uint32_t overflow = (((input.reg_data1 ^ out.alu_result) & (input.reg_data2 ^ out.alu_result)) & 0x80000000) != 0;
            regfile_update_flags(regs, out.alu_result, carry, overflow);
            out.carry = carry;
            out.overflow = overflow;
            break;
        }

        case THUMB_ADC:
        {
            uint64_t temp = (uint64_t)input.reg_data1 + input.reg_data2 + carry_in;
            out.alu_result = (uint32_t)temp;
            uint32_t carry = (temp > 0xFFFFFFFF);
            uint32_t overflow = (((input.reg_data1 ^ out.alu_result) & (input.reg_data2 ^ out.alu_result)) & 0x80000000) != 0;
            regfile_update_flags(regs, out.alu_result, carry, overflow);
            break;
        }

        case THUMB_SUB_REG:
        case THUMB_SUB_IMM3:
        case THUMB_SUB_IMM8:
        case THUMB_SUB_SP_IMM7:
        {
            int64_t temp = (int64_t)input.reg_data1 - (int64_t)input.reg_data2;
            out.alu_result = (uint32_t)temp;
            uint32_t carry = (input.reg_data1 >= input.reg_data2);
            uint32_t overflow = (((input.reg_data1 ^ input.reg_data2) & (input.reg_data1 ^ out.alu_result)) & 0x80000000) != 0;
            regfile_update_flags(regs, out.alu_result, carry, overflow);
            out.carry = carry;
            out.overflow = overflow;
            break;
        }

        case THUMB_SBC:
        {
            uint64_t temp = (uint64_t)input.reg_data1 - input.reg_data2 - (1 - carry_in);
            out.alu_result = (uint32_t)temp;
            uint32_t carry = !(temp >> 32);
            uint32_t overflow = (((input.reg_data1 ^ input.reg_data2) & (input.reg_data1 ^ out.alu_result)) & 0x80000000) != 0;
            regfile_update_flags(regs, out.alu_result, carry, overflow);
            break;
        }

        case THUMB_NEG:
        case THUMB_RSB:
            out.alu_result = (uint32_t)(0 - input.reg_data2);
            regfile_update_flags(regs, out.alu_result, (input.reg_data2 != 0), 0);
            break;

        // ────────────────────────────────
        // Logical / Bitwise
        // ────────────────────────────────
        case THUMB_AND:
            out.alu_result = input.reg_data1 & input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        case THUMB_ORR:
            out.alu_result = input.reg_data1 | input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        case THUMB_EOR:
            out.alu_result = input.reg_data1 ^ input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        case THUMB_BIC:
            out.alu_result = input.reg_data1 & ~input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        case THUMB_MVN:
            out.alu_result = ~input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        case THUMB_MUL:
            out.alu_result = input.reg_data1 * input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;

        // ────────────────────────────────
        // Move / Compare
        // ────────────────────────────────
        case THUMB_MOV_REG:
        case THUMB_MOV_IMM:
        case THUMB_MOV_HIGH:
            out.alu_result = input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        case THUMB_CMP_REG:
        {
            // Compare: R1 - R2, set flags
            int32_t val1 = (int32_t)input.reg_data1;
            int32_t val2 = (int32_t)input.reg_data2;
            int32_t result = val1 - val2;
            
            out.alu_result = result;
            
            // Calculate flags
            uint32_t flags = 0;
            
            // Z flag: Set if result is zero
            if (result == 0) flags |= FLAG_Z;
            
            // N flag: Set if result is negative (bit 31)
            if (result < 0) flags |= FLAG_N;
            
            // C flag: Set if there was NO borrow (unsigned comparison: R1 >= R2)
            if ((uint32_t)val1 >= (uint32_t)val2) flags |= FLAG_C;
            
            // V flag: Set if signed overflow occurred
            // Overflow when: (R1 and R2 have opposite signs) and (result has different sign from R1)
            int sign1 = (val1 >> 31) & 1;
            int sign2 = (val2 >> 31) & 1;
            int sign_result = (result >> 31) & 1;
            if ((sign1 != sign2) && (sign_result != sign1)) flags |= FLAG_V;
            
            out.cpsr = flags;  // Store flags to be propagated
            
            printf("[EX DEBUG CMP] CMP: 0x%08X - 0x%08X = 0x%08X, flags=0x%08X (N=%d Z=%d C=%d V=%d)\n",
                val1, val2, result, flags,
                (flags & FLAG_N) ? 1 : 0,
                (flags & FLAG_Z) ? 1 : 0,
                (flags & FLAG_C) ? 1 : 0,
                (flags & FLAG_V) ? 1 : 0);
            break;
        }
        case THUMB_CMP_IMM:
        {
            // Compare immediate
            int32_t val1 = (int32_t)input.reg_data1;
            int32_t val2 = (int32_t)input.reg_data2;  // Immediate value
            int32_t result = val1 - val2;
            
            out.alu_result = result;
            
            uint32_t flags = 0;
            if (result == 0) flags |= FLAG_Z;
            if (result < 0) flags |= FLAG_N;
            if ((uint32_t)val1 >= (uint32_t)val2) flags |= FLAG_C;
            
            int sign1 = (val1 >> 31) & 1;
            int sign2 = (val2 >> 31) & 1;
            int sign_result = (result >> 31) & 1;
            if ((sign1 != sign2) && (sign_result != sign1)) flags |= FLAG_V;
            
            out.cpsr = flags;
            break;
        }
        case THUMB_CMP_HIGH:
        {
            uint32_t result = input.reg_data1 - input.reg_data2;
            uint32_t carry = (input.reg_data1 >= input.reg_data2);
            uint32_t overflow = (((input.reg_data1 ^ input.reg_data2) & (input.reg_data1 ^ result)) & 0x80000000) != 0;
            regfile_update_flags(regs, result, carry, overflow);
            out.alu_result = result; // Not written back
            break;
        }
        case THUMB_TST:
            out.alu_result = input.reg_data1 & input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        case THUMB_CMN:
            out.alu_result = input.reg_data1 + input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;

        // ────────────────────────────────
        // Shifts
        // ────────────────────────────────
        case THUMB_LSL_IMM:
        case THUMB_LSL_REG:
            out.alu_result = input.reg_data1 << (input.reg_data2 & 0x1F);
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        case THUMB_LSR_IMM:
        case THUMB_LSR_REG:
            out.alu_result = input.reg_data1 >> (input.reg_data2 & 0x1F);
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        case THUMB_ASR_IMM:
        case THUMB_ASR_REG:
            out.alu_result = ((int32_t)input.reg_data1) >> (input.reg_data2 & 0x1F);
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        case THUMB_ROR:
            out.alu_result = (input.reg_data1 >> (input.reg_data2 & 31)) | (input.reg_data1 << (32 - (input.reg_data2 & 31)));
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;

        // ────────────────────────────────
        // Load/Store (address calculation)
        // ────────────────────────────────
        case THUMB_LDR_IMM:
        case THUMB_LDR_REG:
        case THUMB_LDRB_IMM:
        case THUMB_LDRB_REG:
        case THUMB_LDRH_IMM:
        case THUMB_LDRH_REG:
        case THUMB_LDRSB_REG:
        case THUMB_LDRSH_REG:
        case THUMB_STR_IMM:
        case THUMB_STR_REG:
        case THUMB_STRB_IMM:
        case THUMB_STRB_REG:
        case THUMB_STRH_IMM:
        case THUMB_STRH_REG:
        case THUMB_LDR_LIT:
            out.alu_result = input.reg_data1 + input.reg_data2; // Effective address
            break;

        // ────────────────────────────────
        // Branches
        // ────────────────────────────────
        case THUMB_B_COND:
        {
            // Conditional branch - check flags
            // The condition code comes from the instruction
            // We'll need to pass it through decode -> pipeline
            
            // For now, assume it's available in input.condition
            uint32_t cond = input.condition;  // From decode
            uint32_t apsr = input.cpsr;       // Current flags from previous instruction
            
            int condition_met = 0;
            
            switch (cond) {
                case 0x0: condition_met = (apsr & FLAG_Z) != 0; break;              // EQ: Z==1
                case 0x1: condition_met = (apsr & FLAG_Z) == 0; break;              // NE: Z==0
                case 0x2: condition_met = (apsr & FLAG_C) != 0; break;              // CS/HS: C==1
                case 0x3: condition_met = (apsr & FLAG_C) == 0; break;              // CC/LO: C==0
                case 0x4: condition_met = (apsr & FLAG_N) != 0; break;              // MI: N==1
                case 0x5: condition_met = (apsr & FLAG_N) == 0; break;              // PL: N==0
                case 0x6: condition_met = (apsr & FLAG_V) != 0; break;              // VS: V==1
                case 0x7: condition_met = (apsr & FLAG_V) == 0; break;              // VC: V==0
                case 0x8: // HI: C==1 AND Z==0
                    condition_met = ((apsr & FLAG_C) != 0) && ((apsr & FLAG_Z) == 0);
                    break;
                case 0x9: // LS: C==0 OR Z==1
                    condition_met = ((apsr & FLAG_C) == 0) || ((apsr & FLAG_Z) != 0);
                    break;
                case 0xA: // GE: N==V
                    condition_met = (((apsr & FLAG_N) != 0) == ((apsr & FLAG_V) != 0));
                    break;
                case 0xB: // LT: N!=V
                    condition_met = (((apsr & FLAG_N) != 0) != ((apsr & FLAG_V) != 0));
                    break;
                case 0xC: // GT: Z==0 AND N==V
                    condition_met = ((apsr & FLAG_Z) == 0) && 
                                (((apsr & FLAG_N) != 0) == ((apsr & FLAG_V) != 0));
                    break;
                case 0xD: // LE: Z==1 OR N!=V
                    condition_met = ((apsr & FLAG_Z) != 0) || 
                                (((apsr & FLAG_N) != 0) != ((apsr & FLAG_V) != 0));
                    break;
                case 0xE: // AL: Always
                    condition_met = 1;
                    break;
                default:
                    condition_met = 0;
                    break;
            }
            
            if (condition_met) {
                out.alu_result = input.pc + 4 + (int32_t)input.reg_data2;
                printf("[EX DEBUG B_COND] Branch TAKEN - Condition 0x%X met, target=0x%08X\n",
                    cond, out.alu_result);
            } else {
                out.alu_result = input.pc + 4;  // Fall through to next instruction
                printf("[EX DEBUG B_COND] Branch NOT TAKEN - Condition 0x%X not met, fall through to 0x%08X\n",
                    cond, out.alu_result);
            }
            
            out.cpsr = apsr;  // Preserve flags
            break;
        }
        case THUMB_B:
            // Branch offset is already scaled by 2 in decode (sign-extended)
            // For ARM: PC = instruction address + 4 (pointing to instruction after next)
            // Target = (PC of branch + 4) + offset
            out.alu_result = input.pc + 4 + (int32_t)input.reg_data2;
            printf("[EX DEBUG BRANCH] Branch at PC=0x%08X, offset=%d, target=0x%08X\n",
                input.pc, (int32_t)input.reg_data2, out.alu_result);
            break;

        case THUMB_BX:
            out.alu_result = input.reg_data1 & ~1U; // Target (aligned)
            break;

        case THUMB_BL:
        {
            // PC points to the instruction address
            out.alu_result = (input.pc) + 4 + (int32_t)input.reg_data2;
            out.link = input.pc + 4; // Return address (next instruction after BL)
            printf("[EX DEBUG BL] BL at PC=0x%08X, target=0x%08X, LR=0x%08X\n",
                input.pc, out.alu_result, out.link);
            break;
        }        
        // ────────────────────────────────
        // Stack instructions (address setup)
        // ────────────────────────────────
        case THUMB_PUSH:
        case THUMB_POP:
        case THUMB_LDMIA:
        case THUMB_STMIA:
            out.alu_result = input.reg_data1; // Base address (SP or Rn)
            break;

        // ────────────────────────────────
        // Hints / NOP / Control
        // ────────────────────────────────
        case THUMB_NOP:
        case THUMB_YIELD:
        case THUMB_WFE:
        case THUMB_WFI:
        case THUMB_SEV:
        case THUMB_BKPT:
        case THUMB_SVC:
            out.alu_result = 0;
            break;

        // ────────────────────────────────
        // Default
        // ────────────────────────────────
        default:
            printf("[WARN] EXECUTE: Unhandled opcode %s\n", get_operation_name(input.opcode));
            out.alu_result = 0;
            break;
    }

    return out;
}
