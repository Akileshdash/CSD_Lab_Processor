// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
// control
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of instr_mem
//        bit 31~0 - instr_mem[31:0] (Read/Write)
// 0x14 : Data signal of instr_mem
//        bit 31~0 - instr_mem[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of data_mem
//        bit 31~0 - data_mem[31:0] (Read/Write)
// 0x20 : Data signal of data_mem
//        bit 31~0 - data_mem[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of reg_out
//        bit 31~0 - reg_out[31:0] (Read/Write)
// 0x2c : Data signal of reg_out
//        bit 31~0 - reg_out[63:32] (Read/Write)
// 0x30 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XCORTEX_M0_TOP_CONTROL_ADDR_INSTR_MEM_DATA 0x10
#define XCORTEX_M0_TOP_CONTROL_BITS_INSTR_MEM_DATA 64
#define XCORTEX_M0_TOP_CONTROL_ADDR_DATA_MEM_DATA  0x1c
#define XCORTEX_M0_TOP_CONTROL_BITS_DATA_MEM_DATA  64
#define XCORTEX_M0_TOP_CONTROL_ADDR_REG_OUT_DATA   0x28
#define XCORTEX_M0_TOP_CONTROL_BITS_REG_OUT_DATA   64

