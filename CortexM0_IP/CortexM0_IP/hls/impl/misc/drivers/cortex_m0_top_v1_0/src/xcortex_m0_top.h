// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XCORTEX_M0_TOP_H
#define XCORTEX_M0_TOP_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xcortex_m0_top_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Control_BaseAddress;
} XCortex_m0_top_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XCortex_m0_top;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XCortex_m0_top_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XCortex_m0_top_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XCortex_m0_top_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XCortex_m0_top_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XCortex_m0_top_Initialize(XCortex_m0_top *InstancePtr, UINTPTR BaseAddress);
XCortex_m0_top_Config* XCortex_m0_top_LookupConfig(UINTPTR BaseAddress);
#else
int XCortex_m0_top_Initialize(XCortex_m0_top *InstancePtr, u16 DeviceId);
XCortex_m0_top_Config* XCortex_m0_top_LookupConfig(u16 DeviceId);
#endif
int XCortex_m0_top_CfgInitialize(XCortex_m0_top *InstancePtr, XCortex_m0_top_Config *ConfigPtr);
#else
int XCortex_m0_top_Initialize(XCortex_m0_top *InstancePtr, const char* InstanceName);
int XCortex_m0_top_Release(XCortex_m0_top *InstancePtr);
#endif


void XCortex_m0_top_Set_instr_mem(XCortex_m0_top *InstancePtr, u64 Data);
u64 XCortex_m0_top_Get_instr_mem(XCortex_m0_top *InstancePtr);
void XCortex_m0_top_Set_data_mem(XCortex_m0_top *InstancePtr, u64 Data);
u64 XCortex_m0_top_Get_data_mem(XCortex_m0_top *InstancePtr);
void XCortex_m0_top_Set_reg_out(XCortex_m0_top *InstancePtr, u64 Data);
u64 XCortex_m0_top_Get_reg_out(XCortex_m0_top *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
