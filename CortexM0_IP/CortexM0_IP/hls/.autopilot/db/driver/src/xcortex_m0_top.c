// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xcortex_m0_top.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XCortex_m0_top_CfgInitialize(XCortex_m0_top *InstancePtr, XCortex_m0_top_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XCortex_m0_top_Set_instr_mem(XCortex_m0_top *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCortex_m0_top_WriteReg(InstancePtr->Control_BaseAddress, XCORTEX_M0_TOP_CONTROL_ADDR_INSTR_MEM_DATA, (u32)(Data));
    XCortex_m0_top_WriteReg(InstancePtr->Control_BaseAddress, XCORTEX_M0_TOP_CONTROL_ADDR_INSTR_MEM_DATA + 4, (u32)(Data >> 32));
}

u64 XCortex_m0_top_Get_instr_mem(XCortex_m0_top *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCortex_m0_top_ReadReg(InstancePtr->Control_BaseAddress, XCORTEX_M0_TOP_CONTROL_ADDR_INSTR_MEM_DATA);
    Data += (u64)XCortex_m0_top_ReadReg(InstancePtr->Control_BaseAddress, XCORTEX_M0_TOP_CONTROL_ADDR_INSTR_MEM_DATA + 4) << 32;
    return Data;
}

void XCortex_m0_top_Set_data_mem(XCortex_m0_top *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCortex_m0_top_WriteReg(InstancePtr->Control_BaseAddress, XCORTEX_M0_TOP_CONTROL_ADDR_DATA_MEM_DATA, (u32)(Data));
    XCortex_m0_top_WriteReg(InstancePtr->Control_BaseAddress, XCORTEX_M0_TOP_CONTROL_ADDR_DATA_MEM_DATA + 4, (u32)(Data >> 32));
}

u64 XCortex_m0_top_Get_data_mem(XCortex_m0_top *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCortex_m0_top_ReadReg(InstancePtr->Control_BaseAddress, XCORTEX_M0_TOP_CONTROL_ADDR_DATA_MEM_DATA);
    Data += (u64)XCortex_m0_top_ReadReg(InstancePtr->Control_BaseAddress, XCORTEX_M0_TOP_CONTROL_ADDR_DATA_MEM_DATA + 4) << 32;
    return Data;
}

void XCortex_m0_top_Set_reg_out(XCortex_m0_top *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCortex_m0_top_WriteReg(InstancePtr->Control_BaseAddress, XCORTEX_M0_TOP_CONTROL_ADDR_REG_OUT_DATA, (u32)(Data));
    XCortex_m0_top_WriteReg(InstancePtr->Control_BaseAddress, XCORTEX_M0_TOP_CONTROL_ADDR_REG_OUT_DATA + 4, (u32)(Data >> 32));
}

u64 XCortex_m0_top_Get_reg_out(XCortex_m0_top *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCortex_m0_top_ReadReg(InstancePtr->Control_BaseAddress, XCORTEX_M0_TOP_CONTROL_ADDR_REG_OUT_DATA);
    Data += (u64)XCortex_m0_top_ReadReg(InstancePtr->Control_BaseAddress, XCORTEX_M0_TOP_CONTROL_ADDR_REG_OUT_DATA + 4) << 32;
    return Data;
}

