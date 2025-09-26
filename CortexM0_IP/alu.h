#ifndef ALU_H
#define ALU_H

#include <stdint.h>

uint32_t alu_compute(unsigned int opcode, uint32_t op1, uint32_t op2, uint32_t carry_in) ;
#endif
