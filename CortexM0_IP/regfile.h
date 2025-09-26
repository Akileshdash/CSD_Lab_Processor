#ifndef REGFILE_H
#define REGFILE_H

#include <stdint.h>

// ARM Cortex-M0 Core Registers
#define REG_COUNT 16

// Special register indices
#define REG_SP  13  // Stack Pointer (R13)
#define REG_LR  14  // Link Register (R14)
#define REG_PC  15  // Program Counter (R15)

// Stack pointer selection
#define MSP_SELECT 0
#define PSP_SELECT 1

// PSR bit field definitions
#define PSR_N_POS   31  // Negative flag
#define PSR_Z_POS   30  // Zero flag
#define PSR_C_POS   29  // Carry flag
#define PSR_V_POS   28  // Overflow flag
#define PSR_T_POS   24  // Thumb state bit (EPSR)
#define PSR_EXCEPTION_POS 0  // Exception number (IPSR)

#define PSR_N_MASK  (1U << PSR_N_POS)
#define PSR_Z_MASK  (1U << PSR_Z_POS)
#define PSR_C_MASK  (1U << PSR_C_POS)
#define PSR_V_MASK  (1U << PSR_V_POS)
#define PSR_T_MASK  (1U << PSR_T_POS)
#define PSR_EXCEPTION_MASK (0x1FF)  // 9 bits for exception number

// CONTROL register bits
#define CONTROL_SPSEL_POS 1
#define CONTROL_SPSEL_MASK (1U << CONTROL_SPSEL_POS)

// PRIMASK register bits
#define PRIMASK_PM_POS 0
#define PRIMASK_PM_MASK (1U << PRIMASK_PM_POS)

// Core register structure
typedef struct {
    // General-purpose registers R0-R12
    uint32_t gpr[13];
    
    // Stack pointers
    uint32_t msp;  // Main Stack Pointer
    uint32_t psp;  // Process Stack Pointer
    
    // Special registers
    uint32_t lr;   // Link Register (R14)
    uint32_t pc;   // Program Counter (R15)
    
    // Program Status Register components
    uint32_t apsr; // Application Program Status Register
    uint32_t ipsr; // Interrupt Program Status Register  
    uint32_t epsr; // Execution Program Status Register
    
    // Control registers
    uint32_t control;  // CONTROL register
    uint32_t primask;  // PRIMASK register
    
    // Current mode (for stack pointer selection)
    uint32_t thread_mode;  // 1 = Thread mode, 0 = Handler mode
} cortex_m0_registers_t;

// Function prototypes
void regfile_init(cortex_m0_registers_t* regs, uint32_t reset_vector, uint32_t msp_init);
void regfile_write(unsigned int rd, uint32_t value, cortex_m0_registers_t* regs);
uint32_t regfile_read(unsigned int rs, cortex_m0_registers_t* regs);

// Stack pointer operations
uint32_t regfile_get_sp(cortex_m0_registers_t* regs);
void regfile_set_sp(uint32_t value, cortex_m0_registers_t* regs);

// PSR operations
uint32_t regfile_get_psr(cortex_m0_registers_t* regs);
void regfile_set_apsr(uint32_t value, cortex_m0_registers_t* regs);
void regfile_update_flags(cortex_m0_registers_t* regs, uint32_t result, uint32_t carry, uint32_t overflow);

// Special register access
void regfile_set_lr(uint32_t value, cortex_m0_registers_t* regs);
void regfile_set_pc(uint32_t value, cortex_m0_registers_t* regs);
uint32_t regfile_get_pc(cortex_m0_registers_t* regs);

// Control register operations
void regfile_set_control(uint32_t value, cortex_m0_registers_t* regs);
uint32_t regfile_get_control(cortex_m0_registers_t* regs);

// Exception handling support
void regfile_enter_handler_mode(cortex_m0_registers_t* regs, uint32_t exception_num);
void regfile_exit_handler_mode(cortex_m0_registers_t* regs);

#endif