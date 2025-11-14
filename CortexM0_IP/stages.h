#ifndef STAGES_H
#define STAGES_H

#include <stdint.h>
#include "decode.h"  // for thumb_operation_t

// ──────────────────────────────────────
// Instruction Fetch Stage
// ──────────────────────────────────────
typedef struct {
    uint32_t pc;        // Program counter (in halfword units)
    uint32_t instr_pc;        // PC of the instruction being passed to ID
    uint16_t curr_instr16;     // 16-bit current instruction
    uint32_t instr32;     // 32-bit instruction fetched
} IF_stage;

// ──────────────────────────────────────
// Instruction Decode Stage
// ──────────────────────────────────────
typedef struct {
    uint32_t pc;              // Program counter
    uint32_t instr;           // Full instruction (16 or 32-bit)
    uint32_t instr32;     // 32-bit instruction fetched
    thumb_operation_t opcode; // Decoded operation
    uint32_t rd;              // Destination register
    uint32_t rs1;             // Source register 1 (base address for loads/stores)
    uint32_t rs2;             // Source register 2 (store data or offset)
    uint32_t immediate_flag;  // 1 if immediate is used
    uint32_t imm_value;       // Immediate value (offset or constant)
    uint32_t reg_data1;       // Data from rs1
    uint32_t reg_data2;       // Data from rs2 or immediate
    uint32_t condition;       // For B<cond> instructions (0x0-0xE)
    uint32_t cpsr;            // Current condition flags (for conditional branches)
    uint32_t r_bit;         // For PUSH/POP: LR/PC included flag
} ID_stage;

// ──────────────────────────────────────
// Execute Stage
// ──────────────────────────────────────
typedef struct {
    thumb_operation_t opcode; // Operation
    uint32_t alu_result;      // ALU result or effective address
    uint32_t reg_data2;       // Original data to be stored (for STR instructions)
    uint32_t rd;              // Destination register
    uint32_t link;            // LR value for BL
    uint32_t pc;              // Program counter of this instruction
    uint32_t cpsr;            // Updated condition flags
    
    // ──── Memory Operation Fields ────
    int mem_size;             // 1=byte, 2=halfword, 4=word (0=no memory access)
    int sign_extend;          // 1 for signed loads (LDRSB, LDRSH)
    uint32_t r_bit;         // For PUSH/POP: LR/PC included flag
    int branch_taken;  
} EX_stage;

// ──────────────────────────────────────
// Memory Access Stage
// ──────────────────────────────────────
typedef struct {
    thumb_operation_t opcode; // Operation
    uint32_t alu_result;      // Effective address (for debug)
    uint32_t mem_data;        // Data from load or data to store
    uint32_t rd;              // Destination register
    uint32_t link;            // LR value for BL
    uint32_t cpsr;            // Condition flags
    
    // ──── Memory Operation Fields ────
    int mem_size;             // 1=byte, 2=halfword, 4=word (0=no memory access)
    int sign_extend;          // 1 for signed loads (LDRSB, LDRSH)
    int branch_taken;  
} MEM_stage;

// ──────────────────────────────────────
// Write Back Stage
// ──────────────────────────────────────
typedef struct {
    uint32_t pc;              // Program counter
    thumb_operation_t opcode; // Operation
    uint32_t write_data;      // Data to write back to register (from MEM.mem_data)
    uint32_t rd;              // Destination register
    uint32_t link;            // LR value for BL
    uint32_t cpsr;            // Condition flags
    int branch_taken;  
} WB_stage;

#endif