#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "xparameters.h"
#include "xcortex_m0_top.h"
#include "sleep.h"
#include "xgpiops.h"
#include "xil_cache.h"
#include "ff.h"
#include "axi_ps2.h"
#include "xaxivdma.h"
#include "xscugic.h"
#include "xsdps.h"
#include "xgpio.h"

/************************** Constant Definitions *****************************/
// AXI-mapped memory regions from your address map
#define INSTR_DATA_MEM_BASE  0x08000000  // HP0/HP1 - 64M region for instructions and data

// Control interface base addresses
#define CORTEX_M0_CONTROL_BASE    XPAR_XCORTEX_M0_TOP_0_S_AXI_CONTROL_BASEADDR
#define CORTEX_M0_DEVICE_ID       XPAR_XCORTEX_M0_TOP_0_DEVICE_ID
#define GPIO_RESET_PIN            54

// AXI GPIO (connected to PC output)
#define AXI_GPIO_PC_DEVICE_ID     XPAR_AXI_GPIO_0_DEVICE_ID
#define AXI_GPIO_PC_BASEADDR      XPAR_AXI_GPIO_0_BASEADDR
#define AXI_GPIO_CHANNEL          1

// Display Macros
#define HSize 1920
#define VSize 1080
#define FrameSize HSize * VSize * 3
#define imgHSize 512
#define imgVSize 512

// Debug base address (where processor writes register state)
#define DEBUG_BASE_ADDR 0x10000000

/************************** Variable Definitions *****************************/
XCortex_m0_top CortexM0Instance;
XCortex_m0_top_Config CortexM0Config = {
    CORTEX_M0_DEVICE_ID,
    CORTEX_M0_CONTROL_BASE,
};

XGpioPs Gpio;
XGpio AxiGpio;
static FATFS fatfs;
static XScuGic Intc;
XAxiVdma myVDMA;
FRESULT res;
static axi_ps2 Ps2Inst;
XAxiVdma_Config *config;
volatile unsigned char Buffer[FrameSize] __attribute__((section(".frame_buffer")));

/************************** Function Prototypes ******************************/
int CortexM0_Initialize(XCortex_m0_top *InstancePtr);
void LoadTestProgramToMemory(void);
void MonitorPC(int cycles);
void PrintProcessorState(void);
void MonitorProcessorExecution(int snapshots);
void AnalyzePC(int samples);
void TraceMemoryAccesses(u32 base_addr, u32 size);
int LoadProgramFromSD(const char *filename, u32 base_addr);
static int SetupIntrSystem(XAxiVdma *AxiVdmaPtr, u16 VdmaIntrId, axi_ps2 *Ps2Ptr, u16 Ps2IntrId);
static void ReadCallBack(void *CallbackRef, u32 Mask);
static void ReadErrorCallBack(void *CallbackRef, u32 Mask);
void PS2_InterruptHandler(void *CallBackRef);
int InitGPIO(void);
int InitSDCard(void);
int InitVDMA(XAxiVdma *myVDMA);
int InitPS2(axi_ps2 *Ps2Ptr);
void PrintDebugSnapshot(u32 *buf);
void PrintMemory(u32 base_addr, int num_words);

/********************************************************************/

void PrintMemory(u32 base_addr, int num_words)
{
    Xil_DCacheFlush();
    xil_printf("\r\nMemory dump at 0x%08X:\r\n", base_addr);
    xil_printf("----------------------------------------\r\n");
    for (int i = 0; i < num_words; i++) {
        u32 addr = base_addr + (i * 4);
        u32 val  = Xil_In32(addr);
        xil_printf("  [0x%08X] = 0x%08X\r\n", addr, val);
    }
    xil_printf("----------------------------------------\r\n\r\n");
}

/******************************************************************************/
/**
* Print processor state from debug memory region
******************************************************************************/
void PrintProcessorState(void)
{
    // Invalidate cache before reading to ensure fresh data
    Xil_DCacheInvalidateRange(DEBUG_BASE_ADDR, 64);

    xil_printf("\r\n========== PROCESSOR STATE ==========\r\n");

    // Read registers R0-R12
    for (int i = 0; i < 13; i++) {
        u32 reg_val = Xil_In32(DEBUG_BASE_ADDR + (i * 4));
        xil_printf("R%-2d: 0x%08X  ", i, reg_val);
        if ((i+1) % 4 == 0) xil_printf("\r\n");
    }

    // Read SP, LR, PC
    u32 sp = Xil_In32(DEBUG_BASE_ADDR + (13 * 4));
    u32 lr = Xil_In32(DEBUG_BASE_ADDR + (14 * 4));
    u32 pc = Xil_In32(DEBUG_BASE_ADDR + (15 * 4));

    xil_printf("SP : 0x%08X\r\n", sp);
    xil_printf("LR : 0x%08X\r\n", lr);
    xil_printf("PC : 0x%08X (halfword: %d, byte: 0x%08X)\r\n", pc, pc >> 1, pc);
    xil_printf("=====================================\r\n");
}

/******************************************************************************/
/**
* Monitor processor execution with detailed snapshots
******************************************************************************/
void MonitorProcessorExecution(int snapshots)
{
    xil_printf("\r\n========================================\r\n");
    xil_printf("Monitoring Processor Execution\r\n");
    xil_printf("========================================\r\n");

    for (int i = 0; i < snapshots; i++) {
        xil_printf("\r\n--- Snapshot %d ---\r\n", i);

        // Read PC from AXI GPIO
        u32 pc_gpio = XGpio_DiscreteRead(&AxiGpio, AXI_GPIO_CHANNEL);
        xil_printf("PC (from AXI GPIO): 0x%08X\r\n", pc_gpio);

        // Read full processor state from debug memory
        PrintProcessorState();

        // Delay between snapshots
        usleep(100000);  // 100ms
    }

    xil_printf("\r\n========================================\r\n");
    xil_printf("End of Monitoring\r\n");
    xil_printf("========================================\r\n\r\n");
}

/******************************************************************************/
/**
* Analyze PC patterns and frequency
******************************************************************************/
void AnalyzePC(int samples)
{
    u32 pc_history[100];
    u32 pc_counts[256] = {0};  // Count frequency of each PC

    xil_printf("\r\n========================================\r\n");
    xil_printf("PC Analysis - Collecting %d samples\r\n", samples);
    xil_printf("========================================\r\n");

    // Collect samples
    for (int i = 0; i < samples && i < 100; i++) {
        pc_history[i] = XGpio_DiscreteRead(&AxiGpio, AXI_GPIO_CHANNEL);
        usleep(1000);  // 1ms between samples
    }

    // Print sequence
    xil_printf("\r\nPC Sequence:\r\n");
    xil_printf("Sample |   PC Value\r\n");
    xil_printf("-------|------------\r\n");
    for (int i = 0; i < samples && i < 100; i++) {
        xil_printf("%04d   | 0x%08X\r\n", i, pc_history[i]);

        // Count frequency (use lower 8 bits as index)
        u32 pc_idx = (pc_history[i] >> 1) & 0xFF;
        if (pc_idx < 256) pc_counts[pc_idx]++;
    }

    // Print frequency analysis
    xil_printf("\r\nMost Frequent PC Values:\r\n");
    xil_printf("PC Value   | Count\r\n");
    xil_printf("-----------|------\r\n");
    for (int i = 0; i < 256; i++) {
        if (pc_counts[i] > 2) {
            xil_printf("0x%08X | %d\r\n", i << 1, pc_counts[i]);
        }
    }
    xil_printf("========================================\r\n\r\n");
}

/******************************************************************************/
/**
* Trace memory changes
******************************************************************************/
void TraceMemoryAccesses(u32 base_addr, u32 size)
{
    static u32 prev_snapshot[256] = {0};
    static int first_call = 1;

    xil_printf("\r\n--- Memory Change Trace (base: 0x%08X) ---\r\n", base_addr);
    Xil_DCacheInvalidateRange(base_addr, size * 4);

    int changes = 0;
    for (u32 i = 0; i < size && i < 256; i++) {
        u32 addr = base_addr + (i * 4);
        u32 current = Xil_In32(addr);

        if (first_call) {
            // First call - just record initial state
            prev_snapshot[i] = current;
        } else if (current != prev_snapshot[i]) {
            xil_printf("  [0x%08X] changed: 0x%08X -> 0x%08X\r\n",
                       addr, prev_snapshot[i], current);
            prev_snapshot[i] = current;
            changes++;
        }
    }

    if (!first_call && changes == 0) {
        xil_printf("  (No changes detected)\r\n");
    }

    if (first_call) {
        xil_printf("  (Initial snapshot captured)\r\n");
        first_call = 0;
    }

    xil_printf("-------------------------------------------\r\n");
}

/******************************************************************************/
/**
* Main function
******************************************************************************/
int main(void)
{
    int Status;
    int status;

    Xil_DCacheDisable();  // Disable data cache
    Xil_ICacheDisable();  // Disable instruction cache

    init_platform();

    xil_printf("\r\n\r\n");
    xil_printf("========================================\r\n");
    xil_printf("  Cortex-M0 Processor Debug System\r\n");
    xil_printf("========================================\r\n\r\n");

    // Step 1: Initialize Cortex-M0 driver
    xil_printf("Step 1: Initializing Cortex-M0 driver...\r\n");
    Status = CortexM0_Initialize(&CortexM0Instance);
    if (Status != XST_SUCCESS) {
        xil_printf("  [ERROR] Initialization failed!\r\n");
        cleanup_platform();
        return XST_FAILURE;
    }
    xil_printf("  [OK] Driver initialized\r\n\r\n");

    // Step 2: Initialize GPIO for reset control
    xil_printf("Step 2: Initializing GPIO for reset control...\r\n");
    XGpioPs_Config *GpioConfig = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
    if (GpioConfig == NULL) {
        xil_printf("  [ERROR] GPIO config lookup failed\r\n");
        return XST_FAILURE;
    }
    Status = XGpioPs_CfgInitialize(&Gpio, GpioConfig, GpioConfig->BaseAddr);
    if (Status != XST_SUCCESS) {
        xil_printf("  [ERROR] GPIO initialization failed\r\n");
        return XST_FAILURE;
    }
    XGpioPs_SetDirectionPin(&Gpio, GPIO_RESET_PIN, 1);
    XGpioPs_SetOutputEnablePin(&Gpio, GPIO_RESET_PIN, 1);
    XGpioPs_WritePin(&Gpio, GPIO_RESET_PIN, 0);
    xil_printf("  [OK] Soft Core reset asserted\r\n\r\n");

    // Initialize SD Card
    status = InitSDCard();
    if (status != XST_SUCCESS) {
        xil_printf("  [ERROR] SD Card initialization failed\r\n");
        return XST_FAILURE;
    }

    // Initialize VDMA
    status = InitVDMA(&myVDMA);
    if (status != XST_SUCCESS) {
        xil_printf("  [ERROR] VDMA initialization failed\r\n");
        return XST_FAILURE;
    }
    xil_printf("  [OK] VDMA Initialized\r\n\r\n");

    // Initialize PS/2 Keyboard Interface
    status = InitPS2(&Ps2Inst);
    if (status != XST_SUCCESS) {
        xil_printf("  [ERROR] PS2 initialization failed\r\n");
        return status;
    }

    // Setup Interrupts for both PS2 + VDMA
    status = SetupIntrSystem(&myVDMA,
                             XPAR_FABRIC_AXI_VDMA_0_MM2S_INTROUT_INTR,
                             &Ps2Inst,
                             XPAR_FABRIC_AXI_PS2_0_PS2_INTERRUPT_INTR);
    if (status != XST_SUCCESS) {
        xil_printf("  [ERROR] Interrupt setup failed\r\n");
        return status;
    }

    // Start DMA
    Xil_DCacheFlush();
    status = XAxiVdma_DmaStart(&myVDMA, XAXIVDMA_READ);
    if (status != XST_SUCCESS) {
        if (status == XST_VDMA_MISMATCH_ERROR)
            xil_printf("  [ERROR] DMA Mismatch Error\r\n");
        return status;
    }

    // Enable PS2 interrupts
    axi_ps2_SetHandler(&Ps2Inst, PS2_InterruptHandler, &Ps2Inst);
    axi_ps2_IntrEnable(&Ps2Inst, axi_ps2_IPIXR_RX_ALL);
    axi_ps2_IntrGlobalEnable(&Ps2Inst);

    xil_printf("  [OK] System Initialization Complete\r\n\r\n");

    // Step 3: Initialize AXI GPIO (for reading PC)
    xil_printf("Step 3: Initializing AXI GPIO for PC monitoring...\r\n");
    Status = XGpio_Initialize(&AxiGpio, AXI_GPIO_PC_DEVICE_ID);
    if (Status != XST_SUCCESS) {
        xil_printf("  [ERROR] AXI GPIO init failed!\r\n");
        return XST_FAILURE;
    }
    XGpio_SetDataDirection(&AxiGpio, AXI_GPIO_CHANNEL, 0xFFFFFFFF); // All inputs
    xil_printf("  [OK] AXI GPIO ready\r\n\r\n");

    // Step 4: Load OS into memory
    xil_printf("Step 4: Loading OS into memory...\r\n");
    Status = LoadProgramFromSD("os.bin", INSTR_DATA_MEM_BASE);
    if (Status != XST_SUCCESS) {
        xil_printf("  [ERROR] Failed to load OS\r\n");
        return XST_FAILURE;
    }

    // Print memory contents after loading
    PrintMemory(INSTR_DATA_MEM_BASE, 16);
    xil_printf("  [OK] OS loaded\r\n\r\n");

    // Step 5: Verify reset vector
    xil_printf("Step 5: Verifying reset vector...\r\n");
    u32 msp_init = Xil_In32(INSTR_DATA_MEM_BASE);
    u32 reset_vector = Xil_In32(INSTR_DATA_MEM_BASE + 4);
    xil_printf("  MSP (Initial Stack Pointer): 0x%08X\r\n", msp_init);
    xil_printf("  Reset Vector: 0x%08X\r\n", reset_vector);
    xil_printf("  Expected First PC: 0x%08X\r\n", reset_vector & 0xFFFFFFFE);
    xil_printf("  [OK] Reset vector verified\r\n\r\n");

    // Step 6: Release processor from reset
    xil_printf("Step 6: Releasing processor from reset...\r\n");
    XGpioPs_WritePin(&Gpio, GPIO_RESET_PIN, 1);
    xil_printf("  [OK] Reset released, processor running\r\n\r\n");

    // Wait a moment for processor to start
    usleep(10000);  // 10ms

    // Step 7: Immediate state check
    xil_printf("Step 7: Immediate processor state check...\r\n");
    u32 first_pc_gpio = XGpio_DiscreteRead(&AxiGpio, AXI_GPIO_CHANNEL);
    xil_printf("  First PC read from GPIO: 0x%08X\r\n", first_pc_gpio);
    PrintProcessorState();

    // Step 8: Quick PC monitoring (original function)
    xil_printf("\r\nStep 8: Quick PC monitoring (50 samples, 1ms apart)...\r\n");
    MonitorPC(50);

    // Step 9: Detailed execution monitoring
    xil_printf("\r\nStep 9: Detailed execution monitoring...\r\n");
    MonitorProcessorExecution(5);  // 5 detailed snapshots

    // Step 10: PC frequency analysis
    xil_printf("\r\nStep 10: PC frequency analysis...\r\n");
    AnalyzePC(50);

    // Step 11: Memory trace
    xil_printf("\r\nStep 11: Initial memory snapshot...\r\n");
    TraceMemoryAccesses(INSTR_DATA_MEM_BASE, 64);

    xil_printf("\r\n========================================\r\n");
    xil_printf("  Entering Continuous Monitoring Mode\r\n");
    xil_printf("========================================\r\n\r\n");

    // Continuous monitoring loop
    int iteration = 0;
    while(1) {
        xil_printf("\r\n===== Monitoring Iteration %d =====\r\n", iteration++);

        // Print processor state
        PrintProcessorState();

        // Check for memory changes
        TraceMemoryAccesses(INSTR_DATA_MEM_BASE + 0x100, 32);  // Check stack area

        // Wait 1 second before next iteration
        usleep(1000000);
    }

    cleanup_platform();
    return XST_SUCCESS;
}

/******************************************************************************/
/**
* Initialize Cortex-M0 driver
******************************************************************************/
int CortexM0_Initialize(XCortex_m0_top *InstancePtr)
{
    int Status = XCortex_m0_top_CfgInitialize(InstancePtr, &CortexM0Config);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }
    return XST_SUCCESS;
}

/******************************************************************************/
/**
* Monitor PC continuously from AXI GPIO (original function)
******************************************************************************/
void MonitorPC(int cycles)
{
    xil_printf("Sample |     PC Value\r\n");
    xil_printf("-------|-------------\r\n");

    for (int i = 0; i < cycles; i++) {
        u32 pc_val = XGpio_DiscreteRead(&AxiGpio, AXI_GPIO_CHANNEL);
        xil_printf("%04d   |  0x%08X\r\n", i, pc_val);
        usleep(1000);  // 1ms delay between samples
    }
}

/******************************************************************************/
/**
* Initialize SD Card
******************************************************************************/
int InitSDCard(void)
{
    FRESULT fr;

    xil_printf("Initializing SD card...\r\n");

    fr = f_mount(&fatfs, "0:", 1);
    if (fr != FR_OK) {
        xil_printf("  [ERROR] f_mount failed: %d\r\n", fr);
        return XST_FAILURE;
    }

    xil_printf("  [OK] SD card mounted successfully\r\n");
    return XST_SUCCESS;
}

/******************************************************************************/
/**
* Load ARM Thumb test program (big-endian)
******************************************************************************/
void LoadTestProgramToMemory(void)
{
    u16 instructions[] = {
        0xBEEA, 0x08BD, 0x0004, 0x0000,
        0x2100, 0x2000,
        0x2318, 0x5842,
        0x511A, 0x2400,
        0x0000, 0x0000,
        0x0000, 0x0000,
        0x0000, 0x0000
    };

    int num_instr = sizeof(instructions) / sizeof(u16);
    xil_printf("  Writing %d instructions (big-endian)...\r\n", num_instr);

    u32 instr_addr = INSTR_DATA_MEM_BASE;
    for (int i = 0; i < num_instr; i++) {
        Xil_Out16(instr_addr, instructions[i]);
        instr_addr += 2;
    }
    Xil_DCacheFlush();
}

/******************************************************************************/
/**
* Load program from SD card
******************************************************************************/
int LoadProgramFromSD(const char *filename, u32 base_addr)
{
    FIL file;
    FRESULT fr;
    UINT br;
    u32 addr = base_addr;
    u8 buffer[4096];
    UINT total_bytes = 0;

    xil_printf("  Opening file: %s\r\n", filename);
    fr = f_open(&file, filename, FA_READ);
    if (fr != FR_OK) {
        xil_printf("  [ERROR] Cannot open %s (code %d)\r\n", filename, fr);
        return XST_FAILURE;
    }

    xil_printf("  Reading file into memory at 0x%08X...\r\n", base_addr);

    do {
        fr = f_read(&file, buffer, sizeof(buffer), &br);
        if (fr != FR_OK) {
            xil_printf("  [ERROR] f_read failed: %d\r\n", fr);
            f_close(&file);
            return XST_FAILURE;
        }

        for (UINT i = 0; i < br; i++) {
            Xil_Out8(addr++, buffer[i]);
        }

        total_bytes += br;
    } while (br == sizeof(buffer));

    f_close(&file);

    Xil_DCacheFlushRange(base_addr, total_bytes);

    xil_printf("  [OK] Loaded %u bytes from %s into 0x%08X\r\n", total_bytes, filename, base_addr);
    return XST_SUCCESS;
}

/******************************************************************************/
/**
* Initialize VDMA
******************************************************************************/
int InitVDMA(XAxiVdma *myVDMA)
{
    XAxiVdma_DmaSetup ReadCfg;
    int status;
    u32 Addr;
    int Index;

    config = XAxiVdma_LookupConfig(XPAR_AXI_VDMA_0_DEVICE_ID);
    status = XAxiVdma_CfgInitialize(myVDMA, config, config->BaseAddress);
    if (status != XST_SUCCESS) {
        xil_printf("  [ERROR] VDMA initialization failed\r\n");
        return status;
    }

    ReadCfg.VertSizeInput = VSize;
    ReadCfg.HoriSizeInput = HSize * 3;
    ReadCfg.Stride = HSize * 3;
    ReadCfg.FrameDelay = 0;
    ReadCfg.EnableCircularBuf = 1;
    ReadCfg.EnableSync = 1;
    ReadCfg.PointNum = 0;
    ReadCfg.EnableFrameCounter = 0;
    ReadCfg.FixedFrameStoreAddr = 0;

    status = XAxiVdma_DmaConfig(myVDMA, XAXIVDMA_READ, &ReadCfg);
    if (status != XST_SUCCESS) {
        xil_printf("  [ERROR] VDMA channel config failed %d\r\n", status);
        return status;
    }

    Addr = (u32)&Buffer[0];
    xil_printf("  Frame Buffer Address: 0x%08X\r\n", Addr);

    for (Index = 0; Index < myVDMA->MaxNumFrames; Index++) {
        ReadCfg.FrameStoreStartAddr[Index] = Addr;
        Addr += FrameSize;
    }

    status = XAxiVdma_DmaSetBufferAddr(myVDMA, XAXIVDMA_READ, ReadCfg.FrameStoreStartAddr);
    if (status != XST_SUCCESS) {
        xil_printf("  [ERROR] VDMA set buffer address failed %d\r\n", status);
        return XST_FAILURE;
    }

    XAxiVdma_IntrEnable(myVDMA, XAXIVDMA_IXR_COMPLETION_MASK, XAXIVDMA_READ);
    return XST_SUCCESS;
}

/******************************************************************************/
/**
* Initialize PS2
******************************************************************************/
int InitPS2(axi_ps2 *Ps2Ptr)
{
    axi_ps2_Config *ConfigPtr = axi_ps2_LookupConfig(XPAR_AXI_PS2_0_DEVICE_ID);
    if (ConfigPtr == NULL) {
        xil_printf("  [ERROR] PS2 config lookup failed\r\n");
        return XST_FAILURE;
    }

    int status = axi_ps2_CfgInitialize(Ps2Ptr, ConfigPtr, ConfigPtr->BaseAddress);
    if (status != XST_SUCCESS) {
        xil_printf("  [ERROR] PS2 init failed\r\n");
        return XST_FAILURE;
    }

    xil_printf("  [OK] PS2 Initialized successfully\r\n");
    return XST_SUCCESS;
}

/******************************************************************************/
/**
* Setup interrupt system
******************************************************************************/
static int SetupIntrSystem(XAxiVdma *AxiVdmaPtr, u16 VdmaIntrId, axi_ps2 *Ps2Ptr, u16 Ps2IntrId)
{
    int Status;
    XScuGic_Config *IntcConfig = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);
    Status = XScuGic_CfgInitialize(&Intc, IntcConfig, IntcConfig->CpuBaseAddress);
    if (Status != XST_SUCCESS) {
        xil_printf("  [ERROR] Interrupt controller initialization failed\r\n");
        return XST_FAILURE;
    }

    // Connect VDMA interrupt
    Status = XScuGic_Connect(&Intc, VdmaIntrId, (Xil_InterruptHandler)XAxiVdma_ReadIntrHandler, (void *)AxiVdmaPtr);
    if (Status != XST_SUCCESS) {
        xil_printf("  [ERROR] Failed to connect VDMA interrupt\r\n");
        return XST_FAILURE;
    }
    XScuGic_Enable(&Intc, VdmaIntrId);

    // Connect PS2 interrupt
    Status = XScuGic_Connect(&Intc, Ps2IntrId, (Xil_InterruptHandler)axi_ps2_IntrHandler, (void *)Ps2Ptr);
    if (Status != XST_SUCCESS) {
        xil_printf("  [ERROR] Failed to connect PS2 interrupt\r\n");
        return XST_FAILURE;
    }
    XScuGic_Enable(&Intc, Ps2IntrId);

    // Register callbacks
    XAxiVdma_SetCallBack(AxiVdmaPtr, XAXIVDMA_HANDLER_GENERAL, ReadCallBack, (void *)AxiVdmaPtr, XAXIVDMA_READ);
    XAxiVdma_SetCallBack(AxiVdmaPtr, XAXIVDMA_HANDLER_ERROR, ReadErrorCallBack, (void *)AxiVdmaPtr, XAXIVDMA_READ);

    // Enable exceptions globally
    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, &Intc);
    Xil_ExceptionEnable();

    return XST_SUCCESS;
}

/******************************************************************************/
/**
* VDMA callbacks
******************************************************************************/
static void ReadCallBack(void *CallbackRef, u32 Mask)
{
    Xil_DCacheFlushRange((INTPTR)Buffer, FrameSize);
}

static void ReadErrorCallBack(void *CallbackRef, u32 Mask)
{
    xil_printf("  [ERROR] VDMA Read Error Callback Triggered\r\n");
}

/******************************************************************************/
/**
* PS2 interrupt handler
******************************************************************************/
void PS2_InterruptHandler(void *CallBackRef)
{
    axi_ps2 *InstancePtr = (axi_ps2 *)CallBackRef;
    u32 Data;
    axi_ps2_Recv(InstancePtr, &Data, 1);
}

/******************************************************************************/
/**
* Print debug snapshot (legacy function)
******************************************************************************/
void PrintDebugSnapshot(u32 *buf)
{
    int NUM_GPR = 13;
    xil_printf("\r\n================ DEBUG SNAPSHOT ================\r\\n");
    for (int i = 0; i < NUM_GPR; i++) {
        xil_printf("R%-2d: 0x%08X  ", i, buf[i]);
        if ((i+1) % 4 == 0) xil_printf("\r\n");
    }

    xil_printf("SP : 0x%08X\r\n", buf[NUM_GPR]);
    xil_printf("LR : 0x%08X\r\n", buf[NUM_GPR + 1]);
    xil_printf("PC : 0x%08X\r\n", buf[NUM_GPR + 2]);
    xil_printf("\r\n================================================\r\n");
}
