# CSD LAB (CS401P) : ARM Pipeline Processor Implementation 

A 32-bit ARM-compatible 5-stage pipeline processor designed and implemented in Verilog for the Xilinx Zybo-Z7 FPGA development board.

## Project Overview

This project implements a fully functional 32-bit ARM-compatible processor with a 5-stage pipeline architecture. The processor is designed to execute a subset of ARM instructions and is optimized for FPGA implementation on the Zybo-Z7 development board.

### Key Features

- **32-bit ARM-compatible instruction set** (ARMv4-inspired subset)
- **5-stage pipeline:** Instruction Fetch (IF) → Instruction Decode (ID) → Execute (EX) → Memory Access (MEM) → Write Back (WB)
- **Hazard detection and forwarding** for data dependencies
- **16 general-purpose registers + status registers** (CPSR, SPSR)
- **Multiple addressing modes** (immediate, register, base+offset, PC-relative)
- **Load/Store operations** with byte, halfword, and word support
- **Memory-mapped I/O** interface for GPIO and UART
- **Direct memory interface** using BRAM for optimal FPGA resource utilization

## Team Members

| Name | Roll Number |
|------|------------|
| **Akilesh** | CS22B040 |
| **Tilak** | CS22B047 | 
| **Venkat** | CS22B052 |
| **Aiswarya** | CS22B023 |

## Architecture Overview

```
┌───────────────────────────────────────────────────────────────────────────┐
│                     5-Stage Pipeline Architecture                         │
├──────────┬───────────┬──────────┬──────────┬───────────┬──────────────────┤
│   IF     │    ID     │    EX    │   MEM    │    WB     │   Components     │
│ ┌──────┐ │ ┌───────┐ │ ┌──────┐ │ ┌──────┐ │ ┌───────┐ │                  │
│ │ PC   │ │ │Decode │ │ │ ALU  │ │ │D-Mem │ │ │RegFile│ │ • Register File  │
│ │ +4   │ │ │Unit   │ │ │Flags │ │ │I/O   │ │ │Write  │ │ • Hazard Unit    │
│ │I-Mem │ │ │RegFile│ │ │Branch│ │ │Ctrl  │ │ │Back   │ │ • Forwarding     │
│ └──────┘ │ └───────┘ │ └──────┘ │ └──────┘ │ └───────┘ │ • Control Unit   │
└──────────┴───────────┴──────────┴──────────┴───────────┴──────────────────┘
     │          │          │            │          │
     └──────────┼──────────┼────────────┼──────────┘
          Pipeline Registers (IF/ID, ID/EX, EX/MEM, MEM/WB)
```

## Planned Instruction Set

### Data Processing Instructions
```assembly
ADD  r1, r2, r3        ; Add registers
SUB  r1, r2, #100      ; Subtract with immediate
AND  r1, r2, r3, LSL #2 ; Logical AND with shifted operand
ORR  r1, r2, r3        ; Logical OR
EOR  r1, r2, r3        ; Exclusive OR
MOV  r1, r2            ; Move register
CMP  r1, r2            ; Compare (affects flags only)
TST  r1, r2            ; Test (logical AND, affects flags only)
```

### Load/Store Instructions
```assembly
LDR  r1, [r2]          ; Load word
LDR  r1, [r2, #4]      ; Load word with offset
STR  r1, [r2]          ; Store word  
STR  r1, [r2, #4]!     ; Store word with pre-increment
LDRB r1, [r2]          ; Load byte
STRB r1, [r2]          ; Store byte
```

### Branch Instructions
```assembly
B    label             ; Unconditional branch
BEQ  label             ; Branch if equal
BNE  label             ; Branch if not equal
BL   subroutine        ; Branch with link
BX   r1                ; Branch and exchange
```

### Conditional Execution
All instructions can be conditionally executed based on CPSR flags:
```assembly
ADDEQ r1, r2, r3       ; Add if equal (Z=1)
SUBNE r1, r2, r3       ; Subtract if not equal (Z=0)
MOVGT r1, r2           ; Move if greater than
```

## Implementation Status

| Module | Component | Status | Verification |
|--------|-----------|--------|--------------|
| **Module 1** | Register File & ISA | Complete |  Tested |
| **Module 2** | Instruction Decoder |  In Progress |  Pending |
| **Module 3** | Pipeline Control |  Planned |  Pending |
| **Module 4** | ALU & Execute |  Planned |  Pending |
| **Module 5** | Load/Store Unit |  Planned |  Pending |
| **Module 6** | Instruction Fetch |  Planned |  Pending |
| **Module 7** | Memory System |  Planned |  Pending |
| **Module 8** | Integration & Test |  Planned |  Pending |

## Documentation

- [**Module 1**](https://docs.google.com/document/d/1V2ExKlazTVMAgaIZj6pLaYQdCW4eW_aBg_MQCaqPaZ8/edit?usp=sharing) - Module 1 Specifications
