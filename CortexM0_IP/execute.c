#include "execute.h"
#include "alu.h"
#include "regfile.h"
#include <stdint.h>
#include "stdio.h"

EX_output_t execute(EX_input_t input, cortex_m0_registers_t* regs) {
    EX_output_t out = {0};

    // Get carry flag for ADCS/SBCS
    uint32_t carry_in = (regs->apsr & 0x20000000) ? 1 : 0; // Example: C flag in APSR bit 29

    // Debug: Print input operands
    printf("[DEBUG] EXECUTE: Opcode=%u, Rd=%u, Operand1=0x%08X, Operand2=0x%08X, CarryIn=%u\n",
           input.opcode, input.rd, input.reg_data1, input.reg_data2, carry_in);
    // Compute ALU result
    out.alu_result = alu_compute(input.opcode, input.reg_data1, input.reg_data2, carry_in);

    // Update flags only for arithmetic instructions that end with S
    switch(input.opcode) {
        case 1: // ADDS
        case 2: // ADCS
        case 3: // RSBS
        case 4: // SUBS
        case 5: // SBCS
        {
            uint32_t carry = 0;
            uint32_t overflow = 0;

            if(input.opcode == 1 || input.opcode == 2) { // ADD / ADCS
                uint64_t temp = (uint64_t)input.reg_data1 + (uint64_t)input.reg_data2 + (input.opcode==2 ? carry_in : 0);
                carry = (temp > 0xFFFFFFFF) ? 1 : 0;

                // Overflow: same sign operands, different sign result
                if(((input.reg_data1 ^ out.alu_result) & (input.reg_data2 ^ out.alu_result)) & 0x80000000)
                    overflow = 1;

            } else if(input.opcode == 3) { // RSBS
                carry = (out.alu_result <= 0xFFFFFFFF) ? 1 : 0;
                overflow = ((0 ^ input.reg_data2) & (0 ^ out.alu_result)) & 0x80000000 ? 1 : 0;

            } else { // SUB / SBC
                uint64_t temp = (uint64_t)input.reg_data1 - (uint64_t)input.reg_data2 - (input.opcode==5 ? (1 - carry_in) : 0);
                carry = (temp <= 0xFFFFFFFF) ? 1 : 0;
                if(((input.reg_data1 ^ input.reg_data2) & (input.reg_data1 ^ out.alu_result)) & 0x80000000)
                    overflow = 1;
            }

            // Update APSR flags
            regfile_update_flags(regs, out.alu_result, carry, overflow);
            out.carry = carry;
            out.overflow = overflow;
            break;
        }
        default:
            break;
    }

    return out;
}
