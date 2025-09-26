#include "execute.h"
#include "alu.h"
#include "regfile.h"
#include <stdint.h>
#include <stdio.h>

EX_output_t execute(EX_input_t input, cortex_m0_registers_t* regs) {
    EX_output_t out = {0};

    uint32_t carry_in = (regs->apsr & 0x20000000) ? 1 : 0; // C flag

    printf("[DEBUG] EXECUTE: Opcode=%s, Rd=%u, Operand1=0x%08X, Operand2=0x%08X, CarryIn=%u\n",
           get_operation_name(input.opcode), input.rd, input.reg_data1, input.reg_data2, carry_in);

    switch (input.opcode) {
        // ---------------- Arithmetic ----------------
        case THUMB_ADD_REG:
        case THUMB_ADD_IMM3:
        case THUMB_ADD_IMM8:
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
        case THUMB_SUB_REG:
        case THUMB_SUB_IMM3:
        case THUMB_SUB_IMM8:
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

        // ---------------- Logical ----------------
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
        case THUMB_MVN:
            out.alu_result = ~input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;

        // ---------------- Move/compare ----------------
        case THUMB_MOV_REG:
        case THUMB_MOV_IMM:
            out.alu_result = input.reg_data2; // MOV just copies operand2
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        case THUMB_CMP_REG:
        case THUMB_CMP_IMM:
        {
            uint32_t result = input.reg_data1 - input.reg_data2;
            uint32_t carry = (input.reg_data1 >= input.reg_data2);
            uint32_t overflow = (((input.reg_data1 ^ input.reg_data2) & (input.reg_data1 ^ result)) & 0x80000000) != 0;
            regfile_update_flags(regs, result, carry, overflow);
            out.alu_result = result; // but not written back
            break;
        }

        // ---------------- Load/Store (address calculation only here) ----------------
        case THUMB_LDR_IMM:
        case THUMB_LDR_REG:
        case THUMB_STR_IMM:
        case THUMB_STR_REG:
            out.alu_result = input.reg_data1 + input.reg_data2; // effective address
            break;

        // ---------------- Branches (PC will be updated in processor.c) ----------------
        case THUMB_B:
        case THUMB_BCC:   // conditional, condition check should be done earlier
        {
            // NOTE: input.reg_data1 could carry PC if we decide that in ID stage
            // Here, assume regs->pc contains current PC (byte address)
            uint32_t pc = regfile_get_pc(regs);
            out.alu_result = pc + (int32_t)input.reg_data2;  // reg_data2 holds imm offset
            break;
        }

        case THUMB_BX:
        case THUMB_BLX_REG:
            out.alu_result = input.reg_data1 & ~1U; // align to halfword
            break;

        // ---------------- Default ----------------
        default:
            printf("[WARN] EXECUTE: Unhandled opcode %s\n", get_operation_name(input.opcode));
            out.alu_result = 0;
            break;
    }

    return out;
}
