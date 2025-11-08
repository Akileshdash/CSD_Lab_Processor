#include "regfile.h"

void regfile_init(cortex_m0_registers_t* regs, uint32_t reset_vector, uint32_t msp_init) {
    // Initialize all registers to zero
    for(int i = 0; i < 13; i++) {
        regs->gpr[i] = 0;
    }
    
    // Initialize stack pointers
    regs->msp = msp_init;  // Load MSP from address 0x00000000
    regs->psp = 0;
    
    // Initialize special registers
    regs->lr = 0xFFFFFFFF;  // Unknown value as per ARM spec
    regs->pc = reset_vector;  // Load PC from reset vector, clear bit[0]
    
    // Initialize PSR components
    regs->apsr = 0;
    regs->ipsr = 0;  // No exception active
    regs->epsr = (reset_vector & 1) << PSR_T_POS;  // Set T-bit from bit[0] of reset vector
    
    // Initialize control registers
    regs->control = 0;  // Use MSP by default
    regs->primask = 0;  // Exceptions enabled
    
    // Start in Thread mode
    regs->thread_mode = 1;
}

void regfile_write(unsigned int rd, uint32_t value, cortex_m0_registers_t* regs) {
    if(rd < 13) {
        // General-purpose registers R0-R12 (all are writable in Cortex-M0)
        regs->gpr[rd] = value;
    } else if(rd == REG_SP) {
        // Stack Pointer (R13) - write to current stack pointer
        regfile_set_sp(value, regs);
    } else if(rd == REG_LR) {
        // Link Register (R14)
        regs->lr = value;
    } else if(rd == REG_PC) {
        // Program Counter (R15)
        regfile_set_pc(value, regs);
    }
}

uint32_t regfile_read(unsigned int rs, cortex_m0_registers_t* regs) {
    if(rs < 13) {
        // General-purpose registers R0-R12
        return regs->gpr[rs];
    } else if(rs == REG_SP) {
        // Stack Pointer (R13) - read current stack pointer
        return regfile_get_sp(regs);
    } else if(rs == REG_LR) {
        // Link Register (R14)
        return regs->lr;
    } else if(rs == REG_PC) {
        // Program Counter (R15) - returns PC + 4 due to pipeline
        return regs->pc + 4;
    }
    return 0;
}

uint32_t regfile_get_sp(cortex_m0_registers_t* regs) {
    // In Handler mode, always use MSP
    if(!regs->thread_mode) {
        return regs->msp;
    }
    
    // In Thread mode, check CONTROL register SPSEL bit
    if(regs->control & CONTROL_SPSEL_MASK) {
        return regs->psp;  // Use Process Stack Pointer
    } else {
        return regs->msp;  // Use Main Stack Pointer
    }
}

void regfile_set_sp(uint32_t value, cortex_m0_registers_t* regs) {
    // In Handler mode, always write to MSP
    if(!regs->thread_mode) {
        regs->msp = value;
        return;
    }
    
    // In Thread mode, check CONTROL register SPSEL bit
    if(regs->control & CONTROL_SPSEL_MASK) {
        regs->psp = value;  // Write to Process Stack Pointer
    } else {
        regs->msp = value;  // Write to Main Stack Pointer
    }
}

uint32_t regfile_get_psr(cortex_m0_registers_t* regs) {
    // Combine APSR, IPSR, and EPSR into single PSR
    return regs->apsr | regs->ipsr | regs->epsr;
}

void regfile_set_apsr(uint32_t value, cortex_m0_registers_t* regs) {
    // Only update the APSR flags (bits 31:28)
    regs->apsr = value & (PSR_N_MASK | PSR_Z_MASK | PSR_C_MASK | PSR_V_MASK);
}

void regfile_update_flags(cortex_m0_registers_t* regs, uint32_t result, uint32_t carry, uint32_t overflow) {
    // Preserve non-NZCV bits (if any extensions exist in future)
    uint32_t apsr = regs->apsr & ~(PSR_N_MASK | PSR_Z_MASK | PSR_C_MASK | PSR_V_MASK);

    // N flag (bit 31) — set if result bit[31] == 1
    if (result & 0x80000000U) {
        apsr |= PSR_N_MASK;
    }

    // Z flag — set if result == 0
    if (result == 0) {
        apsr |= PSR_Z_MASK;
    }

    // C flag — set if carry out of bit 31 occurred
    if (carry) {
        apsr |= PSR_C_MASK;
    }

    // V flag — set if signed overflow occurred
    if (overflow) {
        apsr |= PSR_V_MASK;
    }

    regs->apsr = apsr;
}

void regfile_set_lr(uint32_t value, cortex_m0_registers_t* regs) {
    regs->lr = value;
}

void regfile_set_pc(uint32_t value, cortex_m0_registers_t* regs) {
    // PC must be aligned to 2-byte boundary
    regs->pc = value & 0xFFFFFFFE;

    // Force T-bit for Cortex-M0 (Thumb-only)
    regs->epsr |= PSR_T_MASK;
}

uint32_t regfile_get_pc(cortex_m0_registers_t* regs) {
    return regs->pc;
}

void regfile_set_control(uint32_t value, cortex_m0_registers_t* regs) {
    // Only update SPSEL bit (bit 1) in Thread mode
    if(regs->thread_mode) {
        regs->control = value & CONTROL_SPSEL_MASK;
    }
    // Handler mode ignores writes to CONTROL register
}

uint32_t regfile_get_control(cortex_m0_registers_t* regs) {
    return regs->control;
}

void regfile_enter_handler_mode(cortex_m0_registers_t* regs, uint32_t exception_num) {
    // Switch to Handler mode
    regs->thread_mode = 0;
    
    // Set exception number in IPSR
    regs->ipsr = exception_num & PSR_EXCEPTION_MASK;
    
    // Handler mode always uses MSP
    // Stack operations would be handled by exception entry mechanism
}

void regfile_exit_handler_mode(cortex_m0_registers_t* regs) {
    // Return to Thread mode
    regs->thread_mode = 1;
    
    // Clear exception number in IPSR
    regs->ipsr = 0;
    
    // Stack pointer selection is restored from stacked CONTROL register
}