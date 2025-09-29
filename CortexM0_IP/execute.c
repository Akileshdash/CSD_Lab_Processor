#include "execute.h"
#include "alu.h"
#include "regfile.h"
#include "decode.h"
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
        case THUMB_BIC:
            out.alu_result = input.reg_data1 & ~input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        case THUMB_MVN:
            out.alu_result = ~input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;

        // ---------------- Move / Compare ----------------
        case THUMB_MOV_REG:
        case THUMB_MOV_IMM:
            out.alu_result = input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        case THUMB_CMP_REG:
        case THUMB_CMP_IMM:
        {
            uint32_t result = input.reg_data1 - input.reg_data2;
            uint32_t carry = (input.reg_data1 >= input.reg_data2);
            uint32_t overflow = (((input.reg_data1 ^ input.reg_data2) & (input.reg_data1 ^ result)) & 0x80000000) != 0;
            regfile_update_flags(regs, result, carry, overflow);
            out.alu_result = result; // CMP doesn’t write to Rd
            break;
        }

        // ---------------- Shift ----------------
        case THUMB_LSL_IMM:
            out.alu_result = input.reg_data1 << (input.reg_data2 & 0xFF);
            break;
        case THUMB_LSR_IMM:
            out.alu_result = input.reg_data1 >> (input.reg_data2 & 0xFF);
            break;
        case THUMB_ASR_IMM:
            out.alu_result = ((int32_t)input.reg_data1) >> (input.reg_data2 & 0xFF);
            break;
        case THUMB_LSL_REG:
            out.alu_result = input.reg_data1 << (input.reg_data2 & 0x1F);
            break;
        case THUMB_LSR_REG:
            out.alu_result = input.reg_data1 >> (input.reg_data2 & 0x1F);
            break;
        case THUMB_ASR_REG:
            out.alu_result = ((int32_t)input.reg_data1) >> (input.reg_data2 & 0x1F);
            break;

        // ---------------- Load/Store (address calc only) ----------------
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
            out.alu_result = input.reg_data1 + input.reg_data2; // effective address
            break;

        // ---------------- Branch ----------------
        case THUMB_B:
        case THUMB_BCC:
            out.alu_result = regfile_get_pc(regs) + (int32_t)input.reg_data2; // branch target
            break;
        case THUMB_BX:
        case THUMB_BLX_REG:
            out.alu_result = input.reg_data1 & ~1U; // align PC
            break;

        // 32-bit branch with link
        case THUMB_BL:
        {
            // In Thumb, BL stores return address in LR (Thumb mode: set LSB=1)
            uint32_t pc = regfile_get_pc(regs);
            out.alu_result = pc + (int32_t)input.reg_data2; // target address
            out.carry = 0;
            out.overflow = 0;
            out.link = regfile_get_pc(regs) + 4; // Thumb return address

            // Save link (return address) in carry temporarily
            // This can be passed along in EX_output_t, or you can add a separate field
            // Example: store LR in alu_result + 4
            break;
        }
        case THUMB_BLX_IMM:
        {
            uint32_t pc = regfile_get_pc(regs);
            out.alu_result = pc + (int32_t)input.reg_data2; // target address
            break;
        }

        // ---------------- Stack instructions (simplified, addr calc) ----------------
        case THUMB_PUSH:
        case THUMB_POP:
            out.alu_result = input.reg_data1; // SP base (handled in MEM)
            break;

        // ---------------- NOP / BKPT / hints ----------------
        case THUMB_NOP:
        case THUMB_YIELD:
        case THUMB_WFE:
        case THUMB_WFI:
        case THUMB_SEV:
        case THUMB_BKPT:
        case THUMB_IT:
            out.alu_result = 0;
            break;

        // ---------------- Default / unimplemented ----------------
        default:
            printf("[WARN] EXECUTE: Unhandled opcode %s\n", get_operation_name(input.opcode));
            out.alu_result = 0;
            break;
    }

    return out;
}
