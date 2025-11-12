#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

void cortex_m0_top(
    volatile uint32_t* instr_mem,
    volatile uint32_t* data_mem,
    volatile uint32_t* reg_out,
    // int reset,
    // int clk
    bool step,
    int * pc_out
);
#endif
