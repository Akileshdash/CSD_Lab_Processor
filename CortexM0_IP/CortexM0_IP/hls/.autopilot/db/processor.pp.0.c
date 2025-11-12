# 1 "processor.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 339 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/tools/2025.1/Vitis/common/technology/autopilot/etc/autopilot_ssdm_op.h" 1
# 263 "/tools/2025.1/Vitis/common/technology/autopilot/etc/autopilot_ssdm_op.h"
    void _ssdm_op_IfRead() __attribute__ ((nothrow));
    void _ssdm_op_IfWrite() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_IfNbRead() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_IfNbWrite() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_IfCanRead() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_IfCanWrite() __attribute__ ((nothrow));


    void _ssdm_StreamRead() __attribute__ ((nothrow));
    void _ssdm_StreamWrite() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_StreamNbRead() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_StreamNbWrite() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_StreamCanRead() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_StreamCanWrite() __attribute__ ((nothrow));
    void _ssdm_op_ReadReq() __attribute__ ((nothrow));
    void _ssdm_op_Read() __attribute__ ((nothrow));
    void _ssdm_op_WriteReq() __attribute__ ((nothrow));
    void _ssdm_op_Write() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_NbReadReq() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_CanReadReq() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_NbWriteReq() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_CanWriteReq() __attribute__ ((nothrow));




    void _ssdm_op_MemShiftRead() __attribute__ ((nothrow));

    void _ssdm_op_PrintNone() __attribute__ ((nothrow));
    void _ssdm_op_PrintInt() __attribute__ ((nothrow));
    void _ssdm_op_PrintDouble() __attribute__ ((nothrow));

    void _ssdm_op_Wait(int) __attribute__ ((nothrow));
    void _ssdm_op_Poll() __attribute__ ((nothrow));

    void _ssdm_op_Return() __attribute__ ((nothrow));


    void _ssdm_op_SpecSynModule() __attribute__ ((nothrow));
    void _ssdm_op_SpecTopModule() __attribute__ ((nothrow));
    void _ssdm_op_SpecProcessDecl() __attribute__ ((nothrow));
    void _ssdm_op_SpecProcessDef() __attribute__ ((nothrow));
    void _ssdm_op_SpecPort() __attribute__ ((nothrow));
    void _ssdm_op_SpecConnection() __attribute__ ((nothrow));
    void _ssdm_op_SpecChannel() __attribute__ ((nothrow));
    void _ssdm_op_SpecSensitive() __attribute__ ((nothrow));
    void _ssdm_op_SpecModuleInst() __attribute__ ((nothrow));
    void _ssdm_op_SpecPortMap() __attribute__ ((nothrow));

    void _ssdm_op_SpecReset() __attribute__ ((nothrow));

    void _ssdm_op_SpecPlatform() __attribute__ ((nothrow));
    void _ssdm_op_SpecClockDomain() __attribute__ ((nothrow));
    void _ssdm_op_SpecPowerDomain() __attribute__ ((nothrow));

    int _ssdm_op_SpecRegionBegin() __attribute__ ((nothrow));
    int _ssdm_op_SpecRegionEnd() __attribute__ ((nothrow));

    void _ssdm_op_SpecLoopName() __attribute__ ((nothrow));

    void _ssdm_op_SpecLoopTripCount() __attribute__ ((nothrow));

    int _ssdm_op_SpecStateBegin() __attribute__ ((nothrow));
    int _ssdm_op_SpecStateEnd() __attribute__ ((nothrow));

    void _ssdm_op_SpecInterface() __attribute__ ((nothrow));

    void _ssdm_op_SpecPipeline() __attribute__ ((nothrow));
    void _ssdm_op_SpecDataflowPipeline() __attribute__ ((nothrow));


    void _ssdm_op_SpecLatency() __attribute__ ((nothrow));
    void _ssdm_op_SpecParallel() __attribute__ ((nothrow));
    void _ssdm_op_SpecProtocol() __attribute__ ((nothrow));
    void _ssdm_op_SpecOccurrence() __attribute__ ((nothrow));

    void _ssdm_op_SpecResource() __attribute__ ((nothrow));
    void _ssdm_op_SpecResourceLimit() __attribute__ ((nothrow));
    void _ssdm_op_SpecCHCore() __attribute__ ((nothrow));
    void _ssdm_op_SpecFUCore() __attribute__ ((nothrow));
    void _ssdm_op_SpecIFCore() __attribute__ ((nothrow));
    void _ssdm_op_SpecIPCore() __attribute__ ((nothrow));
    void _ssdm_op_SpecMemCore() __attribute__ ((nothrow));

    void _ssdm_op_SpecExt() __attribute__ ((nothrow));




    void _ssdm_SpecArrayDimSize() __attribute__ ((nothrow));

    void _ssdm_RegionBegin() __attribute__ ((nothrow));
    void _ssdm_RegionEnd() __attribute__ ((nothrow));

    void _ssdm_InlineAll() __attribute__ ((nothrow));
    void _ssdm_InlineLoop() __attribute__ ((nothrow));
    void _ssdm_Inline() __attribute__ ((nothrow));
    void _ssdm_InlineSelf() __attribute__ ((nothrow));
    void _ssdm_InlineRegion() __attribute__ ((nothrow));

    void _ssdm_SpecArrayMap() __attribute__ ((nothrow));
    void _ssdm_SpecArrayPartition() __attribute__ ((nothrow));
    void _ssdm_SpecArrayReshape() __attribute__ ((nothrow));

    void _ssdm_SpecStream() __attribute__ ((nothrow));

    void _ssdm_op_SpecStable() __attribute__ ((nothrow));
    void _ssdm_op_SpecStableContent() __attribute__ ((nothrow));

    void _ssdm_op_SpecBindPort() __attribute__ ((nothrow));

    void _ssdm_op_SpecPipoDepth() __attribute__ ((nothrow));

    void _ssdm_SpecExpr() __attribute__ ((nothrow));
    void _ssdm_SpecExprBalance() __attribute__ ((nothrow));

    void _ssdm_SpecDependence() __attribute__ ((nothrow));

    void _ssdm_SpecLoopMerge() __attribute__ ((nothrow));
    void _ssdm_SpecLoopFlatten() __attribute__ ((nothrow));
    void _ssdm_SpecLoopRewind() __attribute__ ((nothrow));

    void _ssdm_SpecFuncInstantiation() __attribute__ ((nothrow));
    void _ssdm_SpecFuncBuffer() __attribute__ ((nothrow));
    void _ssdm_SpecFuncExtract() __attribute__ ((nothrow));
    void _ssdm_SpecConstant() __attribute__ ((nothrow));

    void _ssdm_DataPack() __attribute__ ((nothrow));
    void _ssdm_SpecDataPack() __attribute__ ((nothrow));

    void _ssdm_op_SpecBitsMap() __attribute__ ((nothrow));
    void _ssdm_op_SpecLicense() __attribute__ ((nothrow));
# 2 "<built-in>" 2
# 1 "processor.c" 2
# 1 "./processor.h" 1



# 1 "/tools/2025.1/lnx64/tools/clang-3.9-csynth/lib/clang/7.0.0/include/stdint.h" 1 3
# 63 "/tools/2025.1/lnx64/tools/clang-3.9-csynth/lib/clang/7.0.0/include/stdint.h" 3
# 1 "/usr/include/stdint.h" 1 3 4
# 26 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 33 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 394 "/usr/include/features.h" 3 4
# 1 "/usr/include/features-time64.h" 1 3 4
# 20 "/usr/include/features-time64.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 21 "/usr/include/features-time64.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 1 3 4
# 19 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 20 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 2 3 4
# 22 "/usr/include/features-time64.h" 2 3 4
# 395 "/usr/include/features.h" 2 3 4
# 480 "/usr/include/features.h" 3 4
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 481 "/usr/include/features.h" 2 3 4
# 502 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 1 3 4
# 576 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 577 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/long-double.h" 1 3 4
# 578 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 503 "/usr/include/features.h" 2 3 4
# 526 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 1 3 4
# 10 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 2 3 4
# 527 "/usr/include/features.h" 2 3 4
# 34 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 2 3 4
# 27 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 28 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 1 3 4
# 19 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 20 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 2 3 4
# 29 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;






typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;



typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
# 141 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 1 3 4
# 142 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/time64.h" 1 3 4
# 143 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef long int __suseconds64_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;
# 28 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wchar.h" 1 3 4
# 29 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 30 "/usr/include/stdint.h" 2 3 4




# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h" 3 4
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 35 "/usr/include/stdint.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h" 3 4
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
# 38 "/usr/include/stdint.h" 2 3 4



# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-least.h" 1 3 4
# 25 "/usr/include/x86_64-linux-gnu/bits/stdint-least.h" 3 4
typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;


typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;
# 42 "/usr/include/stdint.h" 2 3 4





typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
# 60 "/usr/include/stdint.h" 3 4
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
# 76 "/usr/include/stdint.h" 3 4
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
# 90 "/usr/include/stdint.h" 3 4
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
# 64 "/tools/2025.1/lnx64/tools/clang-3.9-csynth/lib/clang/7.0.0/include/stdint.h" 2 3
# 5 "./processor.h" 2
# 1 "/tools/2025.1/lnx64/tools/clang-3.9-csynth/lib/clang/7.0.0/include/stdbool.h" 1 3
# 6 "./processor.h" 2

__attribute__((sdx_kernel("cortex_m0_top", 0))) void cortex_m0_top(
    volatile uint32_t* instr_mem,
    volatile uint32_t* data_mem,
    volatile uint32_t* reg_out,


    _Bool step,
    int * pc_out
);
# 2 "processor.c" 2
# 1 "./stages.h" 1




# 1 "./decode.h" 1
# 11 "./decode.h"
typedef enum {
    THUMB_INVALID = 0,



    THUMB_MOV_REG,
    THUMB_MOV_IMM,
    THUMB_MOV_HIGH,
    THUMB_LSL_IMM,
    THUMB_LSL_REG,
    THUMB_LSR_IMM,
    THUMB_LSR_REG,
    THUMB_ASR_IMM,
    THUMB_ASR_REG,



    THUMB_ADD_REG,
    THUMB_ADD_IMM3,
    THUMB_ADD_IMM8,
    THUMB_ADD_SP_IMM,
    THUMB_ADD_HIGH,
    THUMB_ADD_PC_IMM,
    THUMB_ADD_SP_IMM7,
    THUMB_SUB_REG,
    THUMB_SUB_IMM3,
    THUMB_SUB_IMM8,
    THUMB_SUB_SP_IMM7,



    THUMB_CMP_REG,
    THUMB_CMP_IMM,
    THUMB_CMP_HIGH,
    THUMB_CMN,
    THUMB_TST,
    THUMB_NEG,



    THUMB_AND,
    THUMB_EOR,
    THUMB_ORR,
    THUMB_BIC,
    THUMB_MVN,
    THUMB_ADC,
    THUMB_SBC,
    THUMB_RSB,
    THUMB_ROR,
    THUMB_MUL,



    THUMB_B_COND,
    THUMB_B,
    THUMB_BL,
    THUMB_BLX,
    THUMB_BX,



    THUMB_LDR_REG,
    THUMB_LDR_IMM,
    THUMB_LDR_LIT,
    THUMB_LDR_SP,
    THUMB_STR_REG,
    THUMB_STR_IMM,
    THUMB_STR_SP,
    THUMB_LDRB_REG,
    THUMB_LDRB_IMM,
    THUMB_STRB_REG,
    THUMB_STRB_IMM,
    THUMB_LDRH_REG,
    THUMB_LDRH_IMM,
    THUMB_STRH_REG,
    THUMB_STRH_IMM,
    THUMB_LDRSB_REG,
    THUMB_LDRSH_REG,



    THUMB_LDMIA,
    THUMB_STMIA,
    THUMB_PUSH,
    THUMB_POP,



    THUMB_SXTB,
    THUMB_SXTH,
    THUMB_UXTB,
    THUMB_UXTH,
    THUMB_REV,
    THUMB_REV16,
    THUMB_REVSH,
    THUMB_CBZ,
    THUMB_CBNZ,



    THUMB_NOP,
    THUMB_YIELD,
    THUMB_WFE,
    THUMB_WFI,
    THUMB_SEV,
    THUMB_BKPT,
    THUMB_SVC

} thumb_operation_t;


typedef struct {
    uint16_t instruction;
    uint8_t valid;
    uint8_t is_32bit;
    thumb_operation_t operation;

    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;

    uint8_t immediate_flag;
    uint32_t imm_value;
    int size;
    uint32_t condition;
    uint32_t r_bit;
} decode_result_t;







decode_result_t decode_thumb16_instruction(uint16_t instruction);






decode_result_t decode_thumb32_instruction(uint32_t instruction);






const char* get_operation_name(thumb_operation_t op);





void print_decode_result(decode_result_t* result);
# 6 "./stages.h" 2




typedef struct {
    uint32_t pc;
    uint32_t instr;
} IF_stage;




typedef struct {
    uint32_t pc;
    uint32_t instr;
    thumb_operation_t opcode;
    uint32_t rd;
    uint32_t rs1;
    uint32_t rs2;
    uint32_t immediate_flag;
    uint32_t imm_value;
    uint32_t reg_data1;
    uint32_t reg_data2;
    uint32_t condition;
    uint32_t cpsr;
    uint32_t r_bit;
} ID_stage;




typedef struct {
    thumb_operation_t opcode;
    uint32_t alu_result;
    uint32_t reg_data2;
    uint32_t rd;
    uint32_t link;
    uint32_t pc;
    uint32_t cpsr;


    int mem_size;
    int sign_extend;
    uint32_t r_bit;
} EX_stage;




typedef struct {
    thumb_operation_t opcode;
    uint32_t alu_result;
    uint32_t mem_data;
    uint32_t rd;
    uint32_t link;
    uint32_t cpsr;


    int mem_size;
    int sign_extend;
} MEM_stage;




typedef struct {
    thumb_operation_t opcode;
    uint32_t write_data;
    uint32_t rd;
    uint32_t link;
    uint32_t cpsr;
} WB_stage;
# 3 "processor.c" 2
# 1 "./execute.h" 1




# 1 "./regfile.h" 1
# 42 "./regfile.h"
typedef struct {

    uint32_t gpr[13];


    uint32_t msp;
    uint32_t psp;


    uint32_t lr;
    uint32_t pc;


    uint32_t apsr;
    uint32_t ipsr;
    uint32_t epsr;


    uint32_t control;
    uint32_t primask;


    uint32_t thread_mode;
} cortex_m0_registers_t;


void regfile_init(cortex_m0_registers_t* regs, uint32_t reset_vector, uint32_t msp_init);
void regfile_write(unsigned int rd, uint32_t value, cortex_m0_registers_t* regs);
uint32_t regfile_read(unsigned int rs, cortex_m0_registers_t* regs);


uint32_t regfile_get_sp(cortex_m0_registers_t* regs);
void regfile_set_sp(uint32_t value, cortex_m0_registers_t* regs);


uint32_t regfile_get_psr(cortex_m0_registers_t* regs);
void regfile_set_apsr(uint32_t value, cortex_m0_registers_t* regs);
void regfile_update_flags(cortex_m0_registers_t* regs, uint32_t result, uint32_t carry, uint32_t overflow);


void regfile_set_lr(uint32_t value, cortex_m0_registers_t* regs);
void regfile_set_pc(uint32_t value, cortex_m0_registers_t* regs);
uint32_t regfile_get_pc(cortex_m0_registers_t* regs);


void regfile_set_control(uint32_t value, cortex_m0_registers_t* regs);
uint32_t regfile_get_control(cortex_m0_registers_t* regs);


void regfile_enter_handler_mode(cortex_m0_registers_t* regs, uint32_t exception_num);
void regfile_exit_handler_mode(cortex_m0_registers_t* regs);
# 6 "./execute.h" 2
# 15 "./execute.h"
typedef struct {
    thumb_operation_t opcode;
    uint32_t pc;
    uint32_t reg_data1;
    uint32_t reg_data2;
    uint32_t rd;
    uint32_t condition;
    uint32_t cpsr;
    uint32_t r_bit;
} EX_input_t;


typedef struct {
    uint32_t alu_result;
    uint32_t carry;
    uint32_t overflow;
    uint32_t link;
    uint32_t cpsr;
    int flags_updated;
    uint32_t r_bit;


    int mem_size;
    int sign_extend;
} EX_output_t;


EX_output_t execute(EX_input_t input, cortex_m0_registers_t* regs);
static inline uint32_t popcount(uint32_t x) {
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x3F;
}
# 4 "processor.c" 2


# 1 "/usr/include/stdio.h" 1 3 4
# 28 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 29 "/usr/include/stdio.h" 2 3 4





# 1 "/tools/2025.1/lnx64/tools/clang-3.9-csynth/lib/clang/7.0.0/include/stddef.h" 1 3 4
# 62 "/tools/2025.1/lnx64/tools/clang-3.9-csynth/lib/clang/7.0.0/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 35 "/usr/include/stdio.h" 2 3 4


# 1 "/tools/2025.1/lnx64/tools/clang-3.9-csynth/lib/clang/7.0.0/include/stdarg.h" 1 3 4
# 30 "/tools/2025.1/lnx64/tools/clang-3.9-csynth/lib/clang/7.0.0/include/stdarg.h" 3 4
typedef __builtin_va_list va_list;
# 48 "/tools/2025.1/lnx64/tools/clang-3.9-csynth/lib/clang/7.0.0/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 38 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h" 1 3 4




# 1 "/usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h" 1 3 4
# 13 "/usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h" 3 4
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
# 6 "/usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h" 2 3 4




typedef struct _G_fpos_t
{
  __off_t __pos;
  __mbstate_t __state;
} __fpos_t;
# 41 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h" 1 3 4
# 10 "/usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h" 3 4
typedef struct _G_fpos64_t
{
  __off64_t __pos;
  __mbstate_t __state;
} __fpos64_t;
# 42 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/__FILE.h" 1 3 4



struct _IO_FILE;
typedef struct _IO_FILE __FILE;
# 43 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/FILE.h" 1 3 4



struct _IO_FILE;


typedef struct _IO_FILE FILE;
# 44 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h" 1 3 4
# 35 "/usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h" 3 4
struct _IO_FILE;
struct _IO_marker;
struct _IO_codecvt;
struct _IO_wide_data;




typedef void _IO_lock_t;





struct _IO_FILE
{
  int _flags;


  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;


  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;
  int _flags2;
  __off_t _old_offset;


  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];

  _IO_lock_t *_lock;







  __off64_t _offset;

  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
  size_t __pad5;
  int _mode;

  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};
# 45 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/types/cookie_io_functions_t.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/types/cookie_io_functions_t.h" 3 4
typedef __ssize_t cookie_read_function_t (void *__cookie, char *__buf,
                                          size_t __nbytes);







typedef __ssize_t cookie_write_function_t (void *__cookie, const char *__buf,
                                           size_t __nbytes);







typedef int cookie_seek_function_t (void *__cookie, __off64_t *__pos, int __w);


typedef int cookie_close_function_t (void *__cookie);






typedef struct _IO_cookie_io_functions_t
{
  cookie_read_function_t *read;
  cookie_write_function_t *write;
  cookie_seek_function_t *seek;
  cookie_close_function_t *close;
} cookie_io_functions_t;
# 48 "/usr/include/stdio.h" 2 3 4





typedef __gnuc_va_list va_list;
# 64 "/usr/include/stdio.h" 3 4
typedef __off_t off_t;
# 78 "/usr/include/stdio.h" 3 4
typedef __ssize_t ssize_t;






typedef __fpos_t fpos_t;
# 129 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/stdio_lim.h" 1 3 4
# 130 "/usr/include/stdio.h" 2 3 4
# 149 "/usr/include/stdio.h" 3 4
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;






extern int remove (const char *__filename) __attribute__ ((__nothrow__ ));

extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ ));



extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ ));
# 184 "/usr/include/stdio.h" 3 4
extern int fclose (FILE *__stream) __attribute__ ((__nonnull__ (1)));
# 194 "/usr/include/stdio.h" 3 4
extern FILE *tmpfile (void)
  __attribute__ ((__malloc__)) ;
# 211 "/usr/include/stdio.h" 3 4
extern char *tmpnam (char[20]) __attribute__ ((__nothrow__ )) ;




extern char *tmpnam_r (char __s[20]) __attribute__ ((__nothrow__ )) ;
# 228 "/usr/include/stdio.h" 3 4
extern char *tempnam (const char *__dir, const char *__pfx)
   __attribute__ ((__nothrow__ )) __attribute__ ((__malloc__)) ;






extern int fflush (FILE *__stream);
# 245 "/usr/include/stdio.h" 3 4
extern int fflush_unlocked (FILE *__stream);
# 264 "/usr/include/stdio.h" 3 4
extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes)
  __attribute__ ((__malloc__)) ;




extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) __attribute__ ((__nonnull__ (3)));
# 299 "/usr/include/stdio.h" 3 4
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ ))
  __attribute__ ((__malloc__)) ;





extern FILE *fopencookie (void *__restrict __magic_cookie,
     const char *__restrict __modes,
     cookie_io_functions_t __io_funcs) __attribute__ ((__nothrow__ ))
  __attribute__ ((__malloc__)) ;




extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ )) __attribute__ ((__malloc__)) ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ ))
  __attribute__ ((__malloc__)) ;
# 334 "/usr/include/stdio.h" 3 4
extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ ))
  __attribute__ ((__nonnull__ (1)));



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ )) __attribute__ ((__nonnull__ (1)));




extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ )) __attribute__ ((__nonnull__ (1)));


extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ )) __attribute__ ((__nonnull__ (1)));







extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...) __attribute__ ((__nonnull__ (1)));




extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));





extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nonnull__ (1)));




extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));



extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));





extern int vasprintf (char **__restrict __ptr, const char *__restrict __f,
        __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 0))) ;
extern int __asprintf (char **__restrict __ptr,
         const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) ;
extern int asprintf (char **__restrict __ptr,
       const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) ;




extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));







extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) __attribute__ ((__nonnull__ (1)));




extern int scanf (const char *__restrict __format, ...) ;

extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ ));






# 1 "/usr/include/x86_64-linux-gnu/bits/floatn.h" 1 3 4
# 119 "/usr/include/x86_64-linux-gnu/bits/floatn.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/long-double.h" 1 3 4
# 25 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 2 3 4
# 214 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 3 4
typedef float _Float32;
# 251 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 3 4
typedef double _Float64;
# 268 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 3 4
typedef double _Float32x;
# 285 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 3 4
typedef long double _Float64x;
# 120 "/usr/include/x86_64-linux-gnu/bits/floatn.h" 2 3 4
# 438 "/usr/include/stdio.h" 2 3 4
# 463 "/usr/include/stdio.h" 3 4
extern int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf") __attribute__ ((__nonnull__ (1)));


extern int scanf (const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf") ;

extern int sscanf (const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__ ));
# 490 "/usr/include/stdio.h" 3 4
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) __attribute__ ((__nonnull__ (1)));





extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;


extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ )) __attribute__ ((__format__ (__scanf__, 2, 0)));
# 540 "/usr/include/stdio.h" 3 4
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")



     __attribute__ ((__format__ (__scanf__, 2, 0))) __attribute__ ((__nonnull__ (1)));
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")

     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__ ))



     __attribute__ ((__format__ (__scanf__, 2, 0)));
# 575 "/usr/include/stdio.h" 3 4
extern int fgetc (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int getc (FILE *__stream) __attribute__ ((__nonnull__ (1)));





extern int getchar (void);






extern int getc_unlocked (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int getchar_unlocked (void);
# 600 "/usr/include/stdio.h" 3 4
extern int fgetc_unlocked (FILE *__stream) __attribute__ ((__nonnull__ (1)));
# 611 "/usr/include/stdio.h" 3 4
extern int fputc (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));
extern int putc (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));





extern int putchar (int __c);
# 627 "/usr/include/stdio.h" 3 4
extern int fputc_unlocked (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));







extern int putc_unlocked (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream) __attribute__ ((__nonnull__ (1)));


extern int putw (int __w, FILE *__stream) __attribute__ ((__nonnull__ (2)));







extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
                                                          __attribute__ ((__nonnull__ (3)));
# 667 "/usr/include/stdio.h" 3 4
extern char *gets (char *__s) __attribute__ ((__deprecated__));
# 694 "/usr/include/stdio.h" 3 4
extern __ssize_t __getdelim (char **__restrict __lineptr,
                             size_t *__restrict __n, int __delimiter,
                             FILE *__restrict __stream) __attribute__ ((__nonnull__ (4)));
extern __ssize_t getdelim (char **__restrict __lineptr,
                           size_t *__restrict __n, int __delimiter,
                           FILE *__restrict __stream) __attribute__ ((__nonnull__ (4)));







extern __ssize_t getline (char **__restrict __lineptr,
                          size_t *__restrict __n,
                          FILE *__restrict __stream) __attribute__ ((__nonnull__ (3)));







extern int fputs (const char *__restrict __s, FILE *__restrict __stream)
  __attribute__ ((__nonnull__ (2)));





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream)
  __attribute__ ((__nonnull__ (4)));




extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s) __attribute__ ((__nonnull__ (4)));
# 766 "/usr/include/stdio.h" 3 4
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream)
  __attribute__ ((__nonnull__ (4)));
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream)
  __attribute__ ((__nonnull__ (4)));







extern int fseek (FILE *__stream, long int __off, int __whence)
  __attribute__ ((__nonnull__ (1)));




extern long int ftell (FILE *__stream) __attribute__ ((__nonnull__ (1)));




extern void rewind (FILE *__stream) __attribute__ ((__nonnull__ (1)));
# 803 "/usr/include/stdio.h" 3 4
extern int fseeko (FILE *__stream, __off_t __off, int __whence)
  __attribute__ ((__nonnull__ (1)));




extern __off_t ftello (FILE *__stream) __attribute__ ((__nonnull__ (1)));
# 829 "/usr/include/stdio.h" 3 4
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos)
  __attribute__ ((__nonnull__ (1)));




extern int fsetpos (FILE *__stream, const fpos_t *__pos) __attribute__ ((__nonnull__ (1)));
# 860 "/usr/include/stdio.h" 3 4
extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ )) __attribute__ ((__nonnull__ (1)));

extern int feof (FILE *__stream) __attribute__ ((__nothrow__ )) __attribute__ ((__nonnull__ (1)));

extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ )) __attribute__ ((__nonnull__ (1)));



extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ )) __attribute__ ((__nonnull__ (1)));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ )) __attribute__ ((__nonnull__ (1)));
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ )) __attribute__ ((__nonnull__ (1)));







extern void perror (const char *__s) __attribute__ ((__cold__));




extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ )) __attribute__ ((__nonnull__ (1)));




extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ )) __attribute__ ((__nonnull__ (1)));
# 897 "/usr/include/stdio.h" 3 4
extern int pclose (FILE *__stream) __attribute__ ((__nonnull__ (1)));





extern FILE *popen (const char *__command, const char *__modes)
  __attribute__ ((__malloc__)) ;






extern char *ctermid (char *__s) __attribute__ ((__nothrow__ ))
                                     ;
# 941 "/usr/include/stdio.h" 3 4
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ )) __attribute__ ((__nonnull__ (1)));



extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ )) __attribute__ ((__nonnull__ (1)));


extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ )) __attribute__ ((__nonnull__ (1)));
# 959 "/usr/include/stdio.h" 3 4
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);
# 7 "processor.c" 2
# 16 "processor.c"
static inline int thumb_writes_register(thumb_operation_t op) {
    switch (op) {

        case THUMB_MOV_REG:
        case THUMB_MOV_IMM:
        case THUMB_MOV_HIGH:
        case THUMB_LSL_IMM:
        case THUMB_LSL_REG:
        case THUMB_LSR_IMM:
        case THUMB_LSR_REG:
        case THUMB_ASR_IMM:
        case THUMB_ASR_REG:
        case THUMB_ADD_REG:
        case THUMB_ADD_IMM3:
        case THUMB_ADD_IMM8:
        case THUMB_ADD_SP_IMM:
        case THUMB_ADD_SP_IMM7:
        case THUMB_ADD_HIGH:
        case THUMB_ADD_PC_IMM:
        case THUMB_SUB_REG:
        case THUMB_SUB_IMM3:
        case THUMB_SUB_IMM8:
        case THUMB_SUB_SP_IMM7:
        case THUMB_NEG:
        case THUMB_AND:
        case THUMB_EOR:
        case THUMB_ORR:
        case THUMB_BIC:
        case THUMB_MVN:
        case THUMB_ADC:
        case THUMB_SBC:
        case THUMB_RSB:
        case THUMB_ROR:
        case THUMB_MUL:
        case THUMB_SXTB:
        case THUMB_SXTH:
        case THUMB_UXTB:
        case THUMB_UXTH:
        case THUMB_REV:
        case THUMB_REV16:
        case THUMB_REVSH:
            return 1;


        case THUMB_LDR_REG:
        case THUMB_LDR_IMM:
        case THUMB_LDR_LIT:
        case THUMB_LDR_SP:
        case THUMB_LDRB_REG:
        case THUMB_LDRB_IMM:
        case THUMB_LDRH_REG:
        case THUMB_LDRH_IMM:
        case THUMB_LDRSB_REG:
        case THUMB_LDRSH_REG:
        case THUMB_LDMIA:
        case THUMB_POP:
            return 1;


        case THUMB_BL:
        case THUMB_BLX:
            return 1;

        default:
            return 0;
    }
}

static inline int is_load_instruction(thumb_operation_t op) {
    switch (op) {
        case THUMB_LDR_REG:
        case THUMB_LDR_IMM:
        case THUMB_LDR_LIT:
        case THUMB_LDR_SP:
        case THUMB_LDRB_REG:
        case THUMB_LDRB_IMM:
        case THUMB_LDRH_REG:
        case THUMB_LDRH_IMM:
        case THUMB_LDRSB_REG:
        case THUMB_LDRSH_REG:
        case THUMB_LDMIA:
        case THUMB_POP:
            return 1;
        default:
            return 0;
    }
}

static inline int is_store_instruction(thumb_operation_t op) {
    switch (op) {
        case THUMB_STR_REG:
        case THUMB_STR_IMM:
        case THUMB_STR_SP:
        case THUMB_STRB_REG:
        case THUMB_STRB_IMM:
        case THUMB_STRH_REG:
        case THUMB_STRH_IMM:
        case THUMB_STMIA:
        case THUMB_PUSH:
            return 1;
        default:
            return 0;
    }
}

static int cycle = 0;

int is_32bit_thumb(uint16_t hw) {
    return ((hw & 0xF800) == 0xE800) ||
           ((hw & 0xF800) == 0xF000) ||
           ((hw & 0xF800) == 0xF800);
}


typedef struct {
    int stall;
    int flush_ID;
    int flush_EX;
    int flush_MEM;
} hazard_control_t;


hazard_control_t detect_hazards(ID_stage ID, EX_stage EX, MEM_stage MEM, WB_stage WB) {
    hazard_control_t ctrl;
    ctrl.stall = 0;
    ctrl.flush_ID = 0;
    ctrl.flush_EX = 0;
    ctrl.flush_MEM = 0;







    int is_unconditional_branch_WB = (WB.opcode == THUMB_B || WB.opcode == THUMB_BX || WB.opcode == THUMB_BL || WB.opcode == THUMB_BLX || (WB.opcode == THUMB_POP && WB.write_data != 0));
    int is_unconditional_branch_MEM = (MEM.opcode == THUMB_B || MEM.opcode == THUMB_BX || MEM.opcode == THUMB_BL || MEM.opcode == THUMB_BLX || (MEM.opcode == THUMB_POP && MEM.mem_data != 0));
    int is_unconditional_branch_EX = (EX.opcode == THUMB_B || EX.opcode == THUMB_BX || EX.opcode == THUMB_BL || EX.opcode == THUMB_BLX);

    if (is_unconditional_branch_WB) {

        ctrl.flush_ID = 1;
        ctrl.flush_EX = 1;
        ctrl.flush_MEM = 1;
        printf("[HAZARD] Unconditional branch in WB - flushing pipeline.\n");
    }
    else if (is_unconditional_branch_MEM) {

        ctrl.flush_ID = 1;
        ctrl.flush_EX = 1;
        printf("[HAZARD] Unconditional branch in MEM - flushing ID, EX.\n");
    }
    else if (is_unconditional_branch_EX) {

        ctrl.flush_ID = 1;
        printf("[HAZARD] Unconditional branch in EX - flushing ID.\n");
    }






    if (!ctrl.flush_ID && is_load_instruction(EX.opcode) && thumb_writes_register(EX.opcode)) {
        if ((EX.rd == ID.rs1 || EX.rd == ID.rs2)) {
            ctrl.stall = 1;
            printf("[HAZARD] Load-Use hazard - stalling.\n");
        }
    }

    return ctrl;
}


typedef struct {
    uint32_t forward_data1;
    uint32_t forward_data2;
    uint32_t forward_cpsr;
    int forward_src1;
    int forward_src2;
    int forward_cpsr_src;
} forward_control_t;

forward_control_t detect_forwarding(ID_stage ID, EX_stage EX, MEM_stage MEM, WB_stage WB, cortex_m0_registers_t* core_regs) {
    forward_control_t fwd;

    fwd.forward_data1 = regfile_read(ID.rs1, core_regs);
    fwd.forward_data2 = regfile_read(ID.rs2, core_regs);
    fwd.forward_cpsr = core_regs->apsr;
    fwd.forward_src1 = 0;
    fwd.forward_src2 = 0;
    fwd.forward_cpsr_src = 0;



    if (MEM.opcode == THUMB_CMP_REG || MEM.opcode == THUMB_CMP_IMM ||
        MEM.opcode == THUMB_CMP_HIGH || MEM.opcode == THUMB_TST ||
        MEM.opcode == THUMB_CMN) {
        fwd.forward_cpsr = MEM.cpsr;
        fwd.forward_cpsr_src = 2;
        printf("[FORWARD] MEM->ID forwarding CPSR=0x%08X\n", MEM.cpsr);
    }

    else if (EX.opcode == THUMB_CMP_REG || EX.opcode == THUMB_CMP_IMM ||
             EX.opcode == THUMB_CMP_HIGH || EX.opcode == THUMB_TST ||
             EX.opcode == THUMB_CMN) {
        fwd.forward_cpsr = EX.cpsr;
        fwd.forward_cpsr_src = 1;
        printf("[FORWARD] EX->ID forwarding CPSR=0x%08X\n", EX.cpsr);
    }

    else if (WB.opcode == THUMB_CMP_REG || WB.opcode == THUMB_CMP_IMM ||
             WB.opcode == THUMB_CMP_HIGH || WB.opcode == THUMB_TST ||
             WB.opcode == THUMB_CMN) {
        fwd.forward_cpsr = WB.cpsr;
        fwd.forward_cpsr_src = 3;
        printf("[FORWARD] WB->ID forwarding CPSR=0x%08X\n", WB.cpsr);
    }




    if (ID.rs1 >= 0 && ID.rs1 <= 15) {




        if (thumb_writes_register(EX.opcode) && EX.rd == ID.rs1) {
            if (!is_load_instruction(EX.opcode)) {
                fwd.forward_data1 = EX.alu_result;
                fwd.forward_src1 = 1;
                printf("[FORWARD] EX->ID forwarding for rs1=%d, data=0x%08X\n", ID.rs1, EX.alu_result);
            }
        }
        else if (thumb_writes_register(MEM.opcode) && MEM.rd == ID.rs1 ) {
            fwd.forward_data1 = MEM.mem_data;
            fwd.forward_src1 = 2;
            printf("[FORWARD DEBUG] MEM->ID for rs1: MEM.rd=%d, ID.rs1=%d, MEM.opcode=%d, match=%d\n",
                MEM.rd, ID.rs1, MEM.opcode, (MEM.rd == ID.rs1));
            printf("[FORWARD] MEM->ID forwarding for rs1=%d, data=0x%08X\n", ID.rs1, MEM.mem_data);
        }
        else if (thumb_writes_register(WB.opcode) && WB.rd == ID.rs1 ) {
            fwd.forward_data1 = WB.write_data;
            fwd.forward_src1 = 3;
            printf("[FORWARD] WB->ID forwarding for rs1=%d, data=0x%08X\n", ID.rs1, WB.write_data);
        }
        else {
            printf("[FORWARD DEBUG] NO FORWARDING for rs1=%d\n", ID.rs1);
        }
    }



    if (ID.rs2 >= 0 && ID.rs2 <= 15) {
        if (thumb_writes_register(EX.opcode) && EX.rd == ID.rs2) {
            if (!is_load_instruction(EX.opcode)) {
                fwd.forward_data2 = EX.alu_result;
                fwd.forward_src2 = 1;
                printf("[FORWARD] EX->ID forwarding for rs2=%d, data=0x%08X\n", ID.rs2, EX.alu_result);
            }
        }
        else if (thumb_writes_register(MEM.opcode) && MEM.rd == ID.rs2 ) {
            fwd.forward_data2 = MEM.mem_data;
            fwd.forward_src2 = 2;
            printf("[FORWARD] MEM->ID forwarding for rs2=%d, data=0x%08X\n", ID.rs2, MEM.mem_data);
        }
        else if (thumb_writes_register(WB.opcode) && WB.rd == ID.rs2 ) {
            fwd.forward_data2 = WB.write_data;
            fwd.forward_src2 = 3;
            printf("[FORWARD] WB->ID forwarding for rs2=%d, data=0x%08X\n", ID.rs2, WB.write_data);
        }
    }

    return fwd;
}


static uint32_t process_mem_data(uint32_t raw_data, uint32_t address, int mem_size, int sign_extend) {
    uint32_t result = 0;

    switch (mem_size) {
        case 1:
        {
            uint8_t byte_val = (raw_data >> ((address & 3) * 8)) & 0xFF;
            if (sign_extend) {
                result = (int32_t)(int8_t)byte_val;
            } else {
                result = byte_val;
            }
            break;
        }
        case 2:
        {
            uint16_t hw_val = (raw_data >> ((address & 2) * 8)) & 0xFFFF;
            if (sign_extend) {
                result = (int32_t)(int16_t)hw_val;
            } else {
                result = hw_val;
            }
            break;
        }
        case 4:
        default:
            result = raw_data;
            break;
    }

    return result;
}

__attribute__((sdx_kernel("cortex_m0_top", 0))) void cortex_m0_top(
    volatile uint32_t* instr_mem,
    volatile uint32_t* data_mem,
    volatile uint32_t* reg_out,


    _Bool step,
    int * pc_out
) {
#line 1 "directive"
#pragma HLSDIRECTIVE TOP name=cortex_m0_top
# 334 "processor.c"

#pragma HLS INTERFACE m_axi port=instr_mem offset=slave bundle=INSTR_BUS
#pragma HLS INTERFACE m_axi port=data_mem offset=slave bundle=DATA_BUS
#pragma HLS INTERFACE m_axi port=reg_out offset=slave bundle=REG_BUS


#pragma HLS INTERFACE ap_ctrl_none port=return
 static IF_stage IF;
    static ID_stage ID;
    static EX_stage EX;
    static MEM_stage MEM;
    static WB_stage WB;
    static cortex_m0_registers_t core_regs;
    static _Bool init_done = 0;
    static _Bool prev_step = 0;


#pragma HLS RESET variable=IF.pc
#pragma HLS RESET variable=IF.instr
#pragma HLS RESET variable=ID.pc
#pragma HLS RESET variable=ID.instr
#pragma HLS RESET variable=ID.reg_data1
#pragma HLS RESET variable=ID.reg_data2
#pragma HLS RESET variable=ID.opcode
#pragma HLS RESET variable=ID.rd
#pragma HLS RESET variable=ID.rs1
#pragma HLS RESET variable=ID.rs2
#pragma HLS RESET variable=ID.immediate_flag
#pragma HLS RESET variable=ID.imm_value
#pragma HLS RESET variable=ID.condition
#pragma HLS RESET variable=ID.cpsr
#pragma HLS RESET variable=EX.opcode
#pragma HLS RESET variable=EX.alu_result
#pragma HLS RESET variable=EX.reg_data2
#pragma HLS RESET variable=EX.rd
#pragma HLS RESET variable=EX.link
#pragma HLS RESET variable=EX.cpsr
#pragma HLS RESET variable=EX.pc
#pragma HLS RESET variable=MEM.opcode
#pragma HLS RESET variable=MEM.alu_result
#pragma HLS RESET variable=MEM.mem_data
#pragma HLS RESET variable=MEM.rd
#pragma HLS RESET variable=MEM.link
#pragma HLS RESET variable=MEM.cpsr
#pragma HLS RESET variable=WB.opcode
#pragma HLS RESET variable=WB.write_data
#pragma HLS RESET variable=WB.rd
#pragma HLS RESET variable=WB.link
#pragma HLS RESET variable=WB.cpsr
#pragma HLS RESET variable=init_done

 if(!init_done) {

        uint32_t msp_init = data_mem[(((0) + 0x08000000) >> 2)];;
        uint32_t reset_vector = data_mem[(((4) + 0x08000000) >> 2)];

        uint32_t pc_value = reset_vector & 0xFFFFFFFE;
        regfile_init(&core_regs, pc_value, msp_init);




        IF.pc = regfile_get_pc(&core_regs);
        cycle = 0;
        prev_step = 0;






        init_done = 1;


    }

    if (prev_step == step){
        return;
    }
    prev_step = step;

    printf("\n================ Cycle %d ==================\n", cycle);
    cycle++;


    hazard_control_t hazard = detect_hazards(ID, EX, MEM, WB);


    forward_control_t forward = detect_forwarding(ID, EX, MEM, WB, &core_regs);


    IF_stage next_IF = IF;
    ID_stage next_ID = ID;
    EX_stage next_EX = EX;
    MEM_stage next_MEM = MEM;
    WB_stage next_WB = WB;


    int branch_taken = 0;
    uint32_t branch_target = 0;




    if (WB.opcode == THUMB_CMP_REG || WB.opcode == THUMB_CMP_IMM ||
        WB.opcode == THUMB_CMP_HIGH || WB.opcode == THUMB_TST ||
        WB.opcode == THUMB_CMN) {
        core_regs.apsr = WB.cpsr;
        printf("[WB] Updated APSR=0x%08X from CMP instruction\n", WB.cpsr);
    }

    switch (WB.opcode) {
        case THUMB_BL:

            branch_taken = 1;
            branch_target = WB.write_data;
            regfile_set_pc(branch_target, &core_regs);
            next_IF.pc = branch_target;


            if (WB.link != 0) {
                core_regs.lr = WB.link;
                printf("[WB] BL: Setting LR=0x%08X\n", WB.link);
            }

            printf("[WB] BL TAKEN! Target PC=0x%08X, LR=0x%08X\n", branch_target, WB.link);
            break;
            case THUMB_BLX:

                branch_taken = 1;
                branch_target = WB.write_data;
                regfile_set_pc(branch_target, &core_regs);
                next_IF.pc = branch_target;


                if (WB.link != 0) {
                    core_regs.lr = WB.link;
                    printf("[WB] BLX: Setting LR=0x%08X\n", WB.link);
                }

                printf("[WB] BLX TAKEN! Target PC=0x%08X (ARM mode), LR=0x%08X\n", branch_target, WB.link);
                break;
        case THUMB_B:
        case THUMB_BX:

            branch_taken = 1;
            branch_target = WB.write_data;
            regfile_set_pc(branch_target, &core_regs);
            next_IF.pc = branch_target ;
            printf("[WB] BRANCH TAKEN! Target PC=0x%08X (halfword=%d)\n", branch_target, next_IF.pc);
            break;
        case THUMB_B_COND:
        {

            uint32_t sequential_pc = regfile_get_pc(&core_regs);


            if (WB.write_data != sequential_pc) {
                branch_taken = 1;
                branch_target = WB.write_data;
                regfile_set_pc(branch_target, &core_regs);
                next_IF.pc = branch_target ;
                printf("[WB] CONDITIONAL BRANCH TAKEN! Target PC=0x%08X (halfword=%d)\n",
                    branch_target, next_IF.pc);
            } else {
                printf("[WB] CONDITIONAL BRANCH NOT TAKEN - continuing at PC=0x%08X\n", sequential_pc);
            }
        }
            break;
        case THUMB_CBZ:
        case THUMB_CBNZ:
        {

            uint32_t sequential_pc = regfile_get_pc(&core_regs);

            if (WB.write_data != sequential_pc) {
                branch_taken = 1;
                branch_target = WB.write_data;
                regfile_set_pc(branch_target, &core_regs);
                next_IF.pc = branch_target ;
                printf("[WB] CBZ/CBNZ BRANCH TAKEN! Target PC=0x%08X\n", branch_target);
            } else {
                printf("[WB] CBZ/CBNZ BRANCH NOT TAKEN - continuing at PC=0x%08X\n", sequential_pc);
            }
        }
            break;
        case THUMB_POP:

            if (WB.write_data != 0) {

                branch_taken = 1;
                branch_target = WB.write_data;
                regfile_set_pc(branch_target, &core_regs);
                next_IF.pc = branch_target;
                printf("[WB] POP {pc} RETURN! Target PC=0x%08X\n", branch_target);
            }
            break;


        default:

            if (thumb_writes_register(WB.opcode)) {
                if (WB.rd == 15) {

                    regfile_set_pc(WB.write_data, &core_regs);
                    next_IF.pc = WB.write_data ;
                } else if (WB.opcode != THUMB_INVALID) {


                    regfile_write(WB.rd, WB.write_data, &core_regs);
                }
            }
            break;
    }

    printf("[WB]  opcode=%d | rd=%d | write_data=0x%08X\n", WB.opcode, WB.rd, WB.write_data);


    if (hazard.flush_MEM) {
        next_MEM.opcode = THUMB_INVALID;
        next_MEM.rd = 0;
        next_MEM.alu_result = 0;
        next_MEM.mem_data = 0;
        next_MEM.link = 0;
        next_MEM.cpsr = 0;
        next_MEM.mem_size = 0;
        next_MEM.sign_extend = 0;
        printf("[MEM] **FLUSHED DUE TO BRANCH**\n");
    } else {
        next_MEM.opcode = EX.opcode;
        next_MEM.rd = EX.rd;
        next_MEM.alu_result = EX.alu_result;
        next_MEM.link = EX.link;
        next_MEM.mem_size = EX.mem_size;
        next_MEM.sign_extend = EX.sign_extend;
        next_MEM.cpsr = EX.cpsr;


        if (EX.opcode == THUMB_PUSH) {

            uint32_t reglist = EX.mem_size;
            uint32_t num_regs = popcount(reglist);


            uint32_t r_bit = EX.r_bit;
            if (r_bit) num_regs++;


            uint32_t sp_value = regfile_get_sp(&core_regs);
            uint32_t start_addr = sp_value - (num_regs * 4);
            uint32_t address = start_addr;

            printf("[MEM] PUSH START: SP=0x%08X, reglist=0x%02X, r_bit=%d, num_regs=%d, start_addr=0x%08X\n",
                sp_value, reglist, r_bit, num_regs, start_addr);


            VITIS_LOOP_590_1: for (int i = 0; i < 8; i++) {
                if (reglist & (1 << i)) {
                    uint32_t reg_val = regfile_read(i, &core_regs);
                    uint32_t addr_word = (((address) + 0x08000000) >> 2);
                    instr_mem[addr_word] = reg_val;
                    printf("[MEM] PUSH: R%d (0x%08X) -> addr 0x%08X\n", i, reg_val, address);
                    address += 4;
                }
            }


            if (r_bit) {
                uint32_t lr_val = core_regs.lr;
                uint32_t addr_word = (((address) + 0x08000000) >> 2);
                instr_mem[addr_word] = lr_val;
                printf("[MEM] PUSH: LR (0x%08X) -> addr 0x%08X\n", lr_val, address);
                address += 4;
            }


            regfile_set_sp(start_addr, &core_regs);
            printf("[MEM] PUSH END: New SP=0x%08X\n", start_addr);

            next_MEM.mem_data = 0;
        }
        else if (EX.opcode == THUMB_POP) {

            uint32_t reglist = EX.mem_size;
            uint32_t num_regs = popcount(reglist);


            uint32_t r_bit = EX.r_bit;
            if (r_bit) num_regs++;


            uint32_t sp_value = regfile_get_sp(&core_regs);
            uint32_t address = sp_value;

            printf("[MEM] POP START: SP=0x%08X, reglist=0x%02X, r_bit=%d, num_regs=%d\n",
                sp_value, reglist, r_bit, num_regs);

            uint32_t pc_return_value = 0;


            VITIS_LOOP_634_2: for (int i = 0; i < 8; i++) {
                if (reglist & (1 << i)) {
                    uint32_t addr_word = (((address) + 0x08000000) >> 2);
                    uint32_t reg_val = data_mem[addr_word];
                    regfile_write(i, reg_val, &core_regs);
                    printf("[MEM] POP: addr 0x%08X -> R%d (0x%08X)\n", address, i, reg_val);
                    address += 4;
                }
            }


            if (r_bit) {







                uint32_t addr_word = (((address) + 0x08000000) >> 2);
                pc_return_value = data_mem[addr_word];
                printf("[MEM] POP: addr 0x%08X -> PC value (0x%08X) - will update in WB\n", address, pc_return_value);
                address += 4;
            }


            uint32_t new_sp = sp_value + (num_regs * 4);
            regfile_set_sp(new_sp, &core_regs);
            printf("[MEM] POP END: New SP=0x%08X\n", new_sp);


            next_MEM.mem_data = r_bit ? pc_return_value : 0;
        }


        else if(EX.opcode == THUMB_LDR_IMM || EX.opcode == THUMB_LDR_REG ||
           EX.opcode == THUMB_LDR_LIT || EX.opcode == THUMB_LDR_SP)
        {
            uint32_t raw_data = data_mem[(((EX.alu_result) + 0x08000000) >> 2)];
            next_MEM.mem_data = process_mem_data(raw_data, EX.alu_result, 4, 0);
            printf("[MEM] LOAD WORD: addr=0x%08X, data=0x%08X\n", EX.alu_result, next_MEM.mem_data);
        }
        else if(EX.opcode == THUMB_LDRB_IMM || EX.opcode == THUMB_LDRB_REG)
        {
            uint32_t raw_data = data_mem[(((EX.alu_result) + 0x08000000) >> 2)];
            next_MEM.mem_data = process_mem_data(raw_data, EX.alu_result, 1, 0);
            printf("[MEM] LOAD BYTE: addr=0x%08X, data=0x%08X\n", EX.alu_result, next_MEM.mem_data);
        }
        else if(EX.opcode == THUMB_LDRSB_REG)
        {
            uint32_t raw_data = data_mem[(((EX.alu_result) + 0x08000000) >> 2)];
            next_MEM.mem_data = process_mem_data(raw_data, EX.alu_result, 1, 1);
            printf("[MEM] LOAD SIGNED BYTE: addr=0x%08X, data=0x%08X\n", EX.alu_result, next_MEM.mem_data);
        }
        else if(EX.opcode == THUMB_LDRH_IMM || EX.opcode == THUMB_LDRH_REG)
        {
            uint32_t raw_data = data_mem[(((EX.alu_result) + 0x08000000) >> 2)];
            next_MEM.mem_data = process_mem_data(raw_data, EX.alu_result, 2, 0);
            printf("[MEM] LOAD HALFWORD: addr=0x%08X, data=0x%08X\n", EX.alu_result, next_MEM.mem_data);
        }
        else if(EX.opcode == THUMB_LDRSH_REG)
        {
            uint32_t raw_data = data_mem[(((EX.alu_result) + 0x08000000) >> 2)];
            next_MEM.mem_data = process_mem_data(raw_data, EX.alu_result, 2, 1);
            printf("[MEM] LOAD SIGNED HALFWORD: addr=0x%08X, data=0x%08X\n", EX.alu_result, next_MEM.mem_data);
        }

        else if(EX.opcode == THUMB_STR_IMM || EX.opcode == THUMB_STR_REG ||
                EX.opcode == THUMB_STR_SP)
        {

            uint32_t value_to_store;
            if (WB.opcode != THUMB_INVALID && thumb_writes_register(WB.opcode) && WB.rd == EX.rd) {

                value_to_store = WB.write_data;
                printf("[MEM] STORE: Using WB-forwarded value (R%d = 0x%08X)\n", EX.rd, value_to_store);
            }
            else {

                value_to_store = regfile_read(EX.rd, &core_regs);
            }

            data_mem[(((EX.alu_result) + 0x08000000) >> 2)] = value_to_store;
            next_MEM.mem_data = value_to_store;
            printf("[MEM] STORE WORD: addr=0x%08X, value=0x%08X (from R%d)\n",
                EX.alu_result, value_to_store, EX.rd);
        }

        else if(EX.opcode == THUMB_STRB_IMM || EX.opcode == THUMB_STRB_REG)
        {
            uint32_t value_to_store = regfile_read(EX.rd, &core_regs);
            uint32_t byte_pos = (EX.alu_result & 3) * 8;
            uint32_t mask = ~(0xFF << byte_pos);
            uint32_t mem_idx = (((EX.alu_result) + 0x08000000) >> 2);
            data_mem[mem_idx] = (data_mem[mem_idx] & mask) | ((value_to_store & 0xFF) << byte_pos);
            next_MEM.mem_data = value_to_store & 0xFF;
            printf("[MEM] STORE BYTE: addr=0x%08X, byte_pos=%d, data=0x%02X (from R%d=0x%08X)\n",
                EX.alu_result, byte_pos, value_to_store & 0xFF, EX.rd, value_to_store);
        }

        else if(EX.opcode == THUMB_STRH_IMM || EX.opcode == THUMB_STRH_REG)
        {
            uint32_t value_to_store = regfile_read(EX.rd, &core_regs);
            uint32_t hw_pos = ((EX.alu_result >> 1) & 1) * 16;
            uint32_t mask = ~(0xFFFF << hw_pos);
            uint32_t mem_idx = (((EX.alu_result) + 0x08000000) >> 2);
            data_mem[mem_idx] = (data_mem[mem_idx] & mask) | ((value_to_store & 0xFFFF) << hw_pos);
            next_MEM.mem_data = value_to_store & 0xFFFF;
            printf("[MEM] STORE HALFWORD: addr=0x%08X, data=0x%04X (from R%d)\n",
                EX.alu_result, value_to_store & 0xFFFF, EX.rd);
        }
        else if (EX.opcode == THUMB_BL || EX.opcode == THUMB_BLX)
        {
            next_MEM.mem_data = EX.alu_result;
            next_MEM.link = EX.link;
        }
        else
        {
            next_MEM.mem_data = EX.alu_result;
        }
        printf("[MEM] opcode=%d | rd=%d | alu_result=0x%08X | mem_data=0x%08X\n",
            next_MEM.opcode, next_MEM.rd, next_MEM.alu_result, next_MEM.mem_data);
    }


    next_WB.opcode = next_MEM.opcode;
    next_WB.rd = next_MEM.rd;
    next_WB.write_data = next_MEM.mem_data;
    next_WB.link = next_MEM.link;
    next_WB.cpsr = next_MEM.cpsr;


    if (hazard.stall || hazard.flush_EX) {
        next_EX.opcode = THUMB_INVALID;
        next_EX.rd = 0;
        next_EX.alu_result = 0;
        next_EX.reg_data2 = 0;
        next_EX.link = 0;
        next_EX.pc = 0;
        next_EX.cpsr = 0;
        next_EX.mem_size = 0;
        next_EX.sign_extend = 0;
        if (hazard.stall) {
            printf("[EX]  **BUBBLE INSERTED DUE TO STALL**\n");
        } else {
            printf("[EX]  **FLUSHED DUE TO BRANCH**\n");
        }
    } else {
        EX_input_t ex_input;
        ex_input.opcode = ID.opcode;
        ex_input.rd = ID.rd;
        ex_input.pc = ID.pc -1;
        ex_input.r_bit = ID.r_bit;


        ex_input.reg_data1 = forward.forward_data1;
        ex_input.condition = ID.condition;
        ex_input.cpsr = forward.forward_cpsr;

        if (is_store_instruction(ID.opcode)) {

            if (ID.immediate_flag) {

                ex_input.reg_data2 = ID.imm_value;
            } else if (ID.rs2 >= 0 && ID.rs2 <= 15) {


                if (thumb_writes_register(MEM.opcode) && MEM.rd == ID.rs2) {
                    ex_input.reg_data2 = MEM.mem_data;
                } else if (thumb_writes_register(EX.opcode) && EX.rd == ID.rs2) {
                    if (!is_load_instruction(EX.opcode)) {
                        ex_input.reg_data2 = EX.alu_result;
                    }
                } else {
                    ex_input.reg_data2 = ID.reg_data2;
                }
            }
        }
        else if(ID.opcode == THUMB_MOV_REG) {
            ex_input.reg_data2 = forward.forward_data1;
        }
        else if(ID.immediate_flag) {
            ex_input.reg_data2 = ID.imm_value;
        } else {
            ex_input.reg_data2 = forward.forward_data2;
        }

        printf("[EX PROCESSOR DEBUG] | reg_data1=0x%08X | reg_data2=0x%08X | imm_flag=%d | pc=0x%08X\n",
            ex_input.reg_data1, ex_input.reg_data2, ID.immediate_flag, ex_input.pc);

        EX_output_t ex_output = execute(ex_input, &core_regs);

        next_EX.opcode = ID.opcode;
        next_EX.rd = ID.rd;
        next_EX.cpsr = ex_output.cpsr;
        next_EX.reg_data2 = ex_input.reg_data2;
        next_EX.alu_result = ex_output.alu_result;
        next_EX.link = ex_output.link;
        next_EX.mem_size = ex_output.mem_size;
        next_EX.sign_extend = ex_output.sign_extend;
        next_EX.r_bit = ID.r_bit;

        printf("[EX]  opcode=%d | rd=%d | alu_result=0x%08X | reg_data2=0x%08X | next_EX.link=0x%08X\n",
            next_EX.opcode, next_EX.rd, next_EX.alu_result, next_EX.reg_data2,next_EX.link);
    }


    if (hazard.stall) {
        next_ID = ID;
        printf("[ID]  **STALLED - REPEATING CURRENT INSTRUCTION**\n");
    } else if (hazard.flush_ID) {
        next_ID.pc = IF.pc;
        next_ID.instr = 0;
        next_ID.opcode = THUMB_INVALID;
        next_ID.rd = 0;
        next_ID.rs1 = 0;
        next_ID.rs2 = 0;
        next_ID.immediate_flag = 0;
        next_ID.imm_value = 0;
        next_ID.reg_data1 = 0;
        next_ID.reg_data2 = 0;
        next_ID.condition = 0;
        next_ID.cpsr = 0;
        next_ID.r_bit = 0;
        printf("[ID]  **FLUSHED DUE TO BRANCH**\n");
    } else {
        next_ID.pc = IF.pc;

        uint16_t instr16_ID = IF.instr;
        printf("[ID] Current ID pc=0x%04X\n",ID.pc);
        printf("[ID Current Instr] =0x%04X\n",instr16_ID);
        printf("[ID] next ID pc=0x%04X\n",next_ID.pc);

        int is32bit = is_32bit_thumb(instr16_ID);
        decode_result_t dres;

        if (is32bit) {
            printf("[ID] Yes 32 Bit Instr\n");
            uint32_t byte_addr = ID.pc ;
            uint32_t word = instr_mem[(((byte_addr) + 0x08000000) >> 2)];

            printf("[ID] byte_addr =0x%04X\n",byte_addr);
            printf("[ID Word] Current word=0x%04X\n",word);
            uint16_t instr16_next;

            if (((ID.pc) & 1) == 0) {
                printf("Even\n");
                instr16_next = (word >> 16) & 0xFFFF;

            } else {
                printf("Odd\n");

                uint32_t next_word = instr_mem[(((byte_addr + 4) + 0x08000000) >> 2)];
                printf("[ID Word] Next word=0x%04X\n",next_word);
                instr16_next = next_word & 0xFFFF;
            }
            printf("[ID instr16_ID] instr16_ID=0x%04X\n",instr16_ID);
            printf("[ID instr16_next] instr16_next=0x%04X\n",instr16_next);


            uint32_t full_instr = instr16_next | (instr16_ID<<16);
            next_ID.instr = full_instr;

            printf("[ID 32 bit] full instr=0x%04X\n",full_instr);
            dres = decode_thumb32_instruction(full_instr);
        } else {
            next_ID.instr = instr16_ID;
            dres = decode_thumb16_instruction(instr16_ID);
        }

        if (!dres.valid) {
            next_ID.opcode = THUMB_INVALID;
            next_ID.rd = 0;
            next_ID.rs1 = 0;
            next_ID.rs2 = 0;
            next_ID.immediate_flag = 0;
            next_ID.imm_value = 0;
            next_ID.reg_data1 = 0;
            next_ID.reg_data2 = 0;
            next_ID.condition = 0;
            next_ID.cpsr = EX.cpsr;
            next_ID.r_bit = 0;
        } else {
            next_ID.opcode = dres.operation;
            next_ID.rd = dres.rd;
            next_ID.rs1 = dres.rs1;
            next_ID.rs2 = dres.rs2;
            next_ID.immediate_flag = dres.immediate_flag;
            next_ID.imm_value = dres.imm_value;
            next_ID.condition = dres.condition;


            if (dres.operation == THUMB_PUSH || dres.operation == THUMB_POP) {
                next_ID.r_bit = dres.r_bit;
            } else {
                next_ID.r_bit = 0;
            }

            next_ID.cpsr = forward.forward_cpsr;
# 941 "processor.c"
            uint32_t rs1_regfile = regfile_read(dres.rs1, &core_regs);


            if (forward.forward_src1 > 0) {
                next_ID.reg_data1 = forward.forward_data1;
                printf("[ID] Forwarding rs1=%d from stage %d: 0x%08X (bypassing regfile 0x%08X)\n",
                       dres.rs1, forward.forward_src1, forward.forward_data1, rs1_regfile);
            } else {
                next_ID.reg_data1 = rs1_regfile;
                printf("[ID] Reading rs1=%d from regfile: 0x%08X\n", dres.rs1, rs1_regfile);
            }


            if (dres.immediate_flag) {
                next_ID.reg_data2 = dres.imm_value;
                printf("[ID] Using immediate for rs2: 0x%08X\n", dres.imm_value);
            } else {
                uint32_t rs2_regfile = regfile_read(dres.rs2, &core_regs);


                if (forward.forward_src2 > 0) {
                    next_ID.reg_data2 = forward.forward_data2;
                    printf("[ID] Forwarding rs2=%d from stage %d: 0x%08X (bypassing regfile 0x%08X)\n",
                           dres.rs2, forward.forward_src2, forward.forward_data2, rs2_regfile);
                } else {
                    next_ID.reg_data2 = rs2_regfile;
                    printf("[ID] Reading rs2=%d from regfile: 0x%08X\n", dres.rs2, rs2_regfile);
                }
            }
        }

        printf("[ID]  instr16=0x%04X | is32bit=%d | opcode=%u | rd=%d | rs1=%d | rs2=%d\n",
               instr16_ID, is32bit, next_ID.opcode, next_ID.rd, next_ID.rs1, next_ID.rs2);
    }


    if (hazard.stall) {
        next_IF = IF;
        printf("[IF]  **STALLED - NOT FETCHING NEW INSTRUCTION**\n");
    } else if (branch_taken) {

        uint32_t byte_addr = next_IF.pc ;
        uint32_t word = instr_mem[(((byte_addr) + 0x08000000) >> 2)];
        uint16_t instr16;

        if ((next_IF.pc & 1) == 0) {
            instr16 = word & 0xFFFF;
        } else {
            instr16 = (word >> 16) & 0xFFFF;
        }

        next_IF.instr = instr16;
        next_IF.pc = next_IF.pc + 1;
        regfile_set_pc(0x00000000 + next_IF.pc , &core_regs);

        printf("[IF]  BRANCH TARGET FETCH | pc=0x%04X | instr16=0x%04X | next_pc=0x%04X\n",
               next_IF.pc - 1, instr16, next_IF.pc);
    } else {
        uint32_t byte_addr = IF.pc;
        uint32_t hw_addr = byte_addr + 0x08000000;
        uint32_t word = instr_mem[(((byte_addr) + 0x08000000) >> 2)];

        uint16_t instr16;

        if ((IF.pc & 1) == 0) {
            instr16 = word & 0xFFFF;
        } else {
            instr16 = (word >> 16) & 0xFFFF;
        }

        next_IF.instr = instr16;

        int is32bit = is_32bit_thumb(instr16);
        if (is32bit) {
            next_IF.pc = IF.pc + 2;
        } else {
            next_IF.pc = IF.pc + 1;
        }




        regfile_set_pc(0x00000000 + next_IF.pc, &core_regs);

        printf("[IF]  pc=0x%04X | byte_addr=0x%08X | hw_addr=0x%08X | hw_idx=%d | instr16=0x%04X | next_pc=0x%04X\n",
            IF.pc, byte_addr, hw_addr, (((byte_addr) + 0x08000000) >> 2), instr16, next_IF.pc);
    }


    IF = next_IF;
    ID = next_ID;
    EX = next_EX;
    MEM = next_MEM;
    WB = next_WB;
    *pc_out = regfile_get_pc(&core_regs);


    VITIS_LOOP_1038_3: for(int i = 0; i < 13; i++) {
        reg_out[(((i<<2) + 0x10000000) >> 2)] = core_regs.gpr[i];
    }

    reg_out[(((13<<2) + 0x10000000) >> 2)] = regfile_get_sp(&core_regs);
    reg_out[(((14<<2) + 0x10000000) >> 2)] = core_regs.lr;
    reg_out[(((15<<2) + 0x10000000) >> 2)] = regfile_get_pc(&core_regs);

    printf("[REGFILE] R0-R12:\n");
    VITIS_LOOP_1047_4: for(int i = 0; i < 13; i++) {
        printf(" R%-2d=0x%08X", i, reg_out[i]);
        if ((i+1) % 4 == 0) printf("\n");
    }
    printf(" SP=0x%08X | LR=0x%08X | PC=0x%08X\n",
           reg_out[13], reg_out[14], reg_out[15]);
}
