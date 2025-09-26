#include "alu.h"
#include <stdint.h>

uint32_t alu_compute(unsigned int opcode, uint32_t op1, uint32_t op2, uint32_t carry_in) {
    switch(opcode) {
        case 0: return 0;                      // NOP
        case 1: return op1 + op2;              // ADD
        case 2: return op1 + op2 + carry_in;   // ADCS
        case 3: return 0 - op2;                // RSBS
        case 4: return op1 - op2;              // SUB
        case 5: return op1 - op2 - (1 - carry_in); // SBCS
        case 6: return op1 & op2;              // AND
        case 7: return op1 | op2;              // OR
        case 8: return op2;                    // MOV
        default: return 0;
    }
}
