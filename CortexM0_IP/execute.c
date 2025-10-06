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
        case THUMB_CMP_IMM:
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
        case THUMB_B:
            out.alu_result = regfile_get_pc(regs) + (int32_t)input.reg_data2; // Branch target
            break;
        case THUMB_BX:
            out.alu_result = input.reg_data1 & ~1U; // Target (aligned)
            break;
        case THUMB_BL:
        {
            uint32_t pc = regfile_get_pc(regs);
            out.alu_result = pc + (int32_t)input.reg_data2;
            out.link = pc + 4; // Return address (Thumb mode)
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
