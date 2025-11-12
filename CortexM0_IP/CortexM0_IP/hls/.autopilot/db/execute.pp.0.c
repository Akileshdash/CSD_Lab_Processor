# 1 "execute.c"
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
# 1 "execute.c" 2
# 1 "./execute.h" 1



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
# 5 "./execute.h" 2
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
# 7 "./execute.h" 2








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
# 2 "execute.c" 2



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
# 6 "execute.c" 2

EX_output_t execute(EX_input_t input, cortex_m0_registers_t* regs) {
    EX_output_t out = {0};

    uint32_t carry_in = (regs->apsr & 0x20000000) ? 1 : 0;

    printf("[EX DEBUG] EXECUTE: Opcode=%s, Rd=%u, Operand1=0x%08X, Operand2=0x%08X, CarryIn=%u\n",
           get_operation_name(input.opcode), input.rd, input.reg_data1, input.reg_data2, carry_in);

    switch (input.opcode) {



        case THUMB_ADD_REG:
        case THUMB_ADD_IMM3:
        case THUMB_ADD_IMM8:
        {
            uint64_t temp = (uint64_t)input.reg_data1 + input.reg_data2;
            out.alu_result = (uint32_t)temp;
            uint32_t carry = (temp > 0xFFFFFFFF);
            uint32_t overflow = (((input.reg_data1 ^ out.alu_result) & (input.reg_data2 ^ out.alu_result)) & 0x80000000) != 0;
            regfile_update_flags(regs, out.alu_result, carry, overflow);


            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            out.carry = carry;
            out.overflow = overflow;
            break;
        }
        case THUMB_ADD_HIGH:
        {

            uint64_t temp = (uint64_t)input.reg_data1 + input.reg_data2;
            out.alu_result = (uint32_t)temp;

            printf("[EX DEBUG ADD_HIGH] ADD: 0x%08X + 0x%08X = 0x%08X (Rd=%u, Rm=%u)\n",
                input.reg_data1, input.reg_data2, out.alu_result, input.rd,
                (input.reg_data2 == 0) ? 0 : 1);


            out.flags_updated = 0;
            out.cpsr = regs->apsr;


            break;
        }
        case THUMB_ADD_PC_IMM:
        {





            uint32_t aligned_pc = input.reg_data1 & 0xFFFFFFFC;
            out.alu_result = aligned_pc + input.reg_data2;

            printf("[EX DEBUG ADD_PC_IMM] ADD_PC: PC=0x%08X (aligned from 0x%08X), immed=0x%08X, result=0x%08X (Rd=%u)\n",
                aligned_pc, input.reg_data1, input.reg_data2, out.alu_result, input.rd);


            out.flags_updated = 0;
            out.cpsr = regs->apsr;

            break;
        }

        case THUMB_ADD_SP_IMM:
        {




            out.alu_result = input.reg_data1 + input.reg_data2;

            printf("[EX DEBUG ADD_SP_IMM] ADD SP: SP=0x%08X + offset=0x%08X = result=0x%08X (Rd=%u)\n",
                input.reg_data1, input.reg_data2, out.alu_result, input.rd);


            out.flags_updated = 0;
            out.cpsr = regs->apsr;

            break;
        }
        case THUMB_ADD_SP_IMM7:
        {






            out.alu_result = input.reg_data1 + input.reg_data2;

            printf("[EX DEBUG ADD_SP_IMM7] ADD SP: SP=0x%08X + offset=0x%08X = result=0x%08X\n",
                input.reg_data1, input.reg_data2, out.alu_result);


            out.flags_updated = 0;
            out.cpsr = regs->apsr;

            break;
        }


        case THUMB_ADC:
        {

            uint32_t actual_carry = carry_in;

            uint64_t temp = (uint64_t)input.reg_data1 + input.reg_data2 + actual_carry;
            out.alu_result = (uint32_t)temp;
            uint32_t carry = (temp > 0xFFFFFFFF);
            uint32_t overflow = (((input.reg_data1 ^ out.alu_result) & (input.reg_data2 ^ out.alu_result)) & 0x80000000) != 0;
            regfile_update_flags(regs, out.alu_result, carry, overflow);


            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;
        }

        case THUMB_SUB_REG:
        case THUMB_SUB_IMM3:
        case THUMB_SUB_IMM8:
        case THUMB_SUB_SP_IMM7:
        {
            int64_t temp = (int64_t)input.reg_data1 - (int64_t)input.reg_data2;
            out.alu_result = (uint32_t)temp;
            uint32_t carry = (input.reg_data1 >= input.reg_data2);
            uint32_t overflow = (((input.reg_data1 ^ input.reg_data2) & (input.reg_data1 ^ out.alu_result)) & 0x80000000) != 0;
            regfile_update_flags(regs, out.alu_result, carry, overflow);


            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            out.carry = carry;
            out.overflow = overflow;
            break;
        }

        case THUMB_SBC:
        {
            uint64_t temp = (uint64_t)input.reg_data1 - input.reg_data2 - (1 - carry_in);
            out.alu_result = (uint32_t)temp;
            uint32_t carry = !(temp >> 32);
            uint32_t overflow = (((input.reg_data1 ^ input.reg_data2) & (input.reg_data1 ^ out.alu_result)) & 0x80000000) != 0;
            regfile_update_flags(regs, out.alu_result, carry, overflow);

            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;
        }

        case THUMB_NEG:
        case THUMB_RSB:
            out.alu_result = (uint32_t)(0 - input.reg_data2);
            regfile_update_flags(regs, out.alu_result, (input.reg_data2 != 0), 0);

            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;




        case THUMB_AND:
            out.alu_result = input.reg_data1 & input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);

            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;
        case THUMB_ORR:
            out.alu_result = input.reg_data1 | input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);

            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;
        case THUMB_EOR:
            out.alu_result = input.reg_data1 ^ input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);

            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;
        case THUMB_BIC:
            out.alu_result = input.reg_data1 & ~input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);

            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;
        case THUMB_MVN:
            out.alu_result = ~input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;
        case THUMB_MUL:
            out.alu_result = input.reg_data1 * input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;




        case THUMB_MOV_REG:
        case THUMB_MOV_IMM:
        case THUMB_MOV_HIGH:
            out.alu_result = input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;
        case THUMB_CMP_REG:
        {

            int32_t val1 = (int32_t)input.reg_data1;
            int32_t val2 = (int32_t)input.reg_data2;
            int32_t result = val1 - val2;

            out.alu_result = result;


            uint32_t flags = 0;


            if (result == 0) flags |= (1U << 30);


            if (result < 0) flags |= (1U << 31);


            if ((uint32_t)val1 >= (uint32_t)val2) flags |= (1U << 29);



            int sign1 = (val1 >> 31) & 1;
            int sign2 = (val2 >> 31) & 1;
            int sign_result = (result >> 31) & 1;
            if ((sign1 != sign2) && (sign_result != sign1)) flags |= (1U << 28);

            out.cpsr = flags;

            printf("[EX DEBUG CMP] CMP: 0x%08X - 0x%08X = 0x%08X, flags=0x%08X (N=%d Z=%d C=%d V=%d)\n",
                val1, val2, result, flags,
                (flags & (1U << 31)) ? 1 : 0,
                (flags & (1U << 30)) ? 1 : 0,
                (flags & (1U << 29)) ? 1 : 0,
                (flags & (1U << 28)) ? 1 : 0);
            out.flags_updated = 1;
            out.cpsr = flags;
            break;
        }
        case THUMB_CMP_IMM:
        {

            int32_t val1 = (int32_t)input.reg_data1;
            int32_t val2 = (int32_t)input.reg_data2;
            int32_t result = val1 - val2;

            out.alu_result = result;

            uint32_t flags = 0;
            if (result == 0) flags |= (1U << 30);
            if (result < 0) flags |= (1U << 31);
            if ((uint32_t)val1 >= (uint32_t)val2) flags |= (1U << 29);

            int sign1 = (val1 >> 31) & 1;
            int sign2 = (val2 >> 31) & 1;
            int sign_result = (result >> 31) & 1;
            if ((sign1 != sign2) && (sign_result != sign1)) flags |= (1U << 28);

            out.cpsr = flags;
            out.flags_updated = 1;
            break;
        }
        case THUMB_CMP_HIGH:
        {
            uint32_t result = input.reg_data1 - input.reg_data2;
            uint32_t carry = (input.reg_data1 >= input.reg_data2);
            uint32_t overflow = (((input.reg_data1 ^ input.reg_data2) & (input.reg_data1 ^ result)) & 0x80000000) != 0;
            uint32_t flags = 0;
            if (result == 0) flags |= (1U << 30);
            if (result < 0) flags |= (1U << 31);

            regfile_update_flags(regs, result, carry, overflow);
            out.alu_result = result;
            out.flags_updated = 1;
            out.cpsr = flags;
            break;
        }
        case THUMB_TST:
            out.alu_result = input.reg_data1 & input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);

            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;
        case THUMB_CMN:
            out.alu_result = input.reg_data1 + input.reg_data2;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;




        case THUMB_LSL_IMM:
        case THUMB_LSL_REG:
            out.alu_result = input.reg_data1 << (input.reg_data2 & 0x1F);
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        case THUMB_LSR_IMM:
        case THUMB_LSR_REG:
            out.alu_result = input.reg_data1 >> (input.reg_data2 & 0x1F);
            regfile_update_flags(regs, out.alu_result, 0, 0);
            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;
        case THUMB_ASR_IMM:
        case THUMB_ASR_REG:
            out.alu_result = ((int32_t)input.reg_data1) >> (input.reg_data2 & 0x1F);
            regfile_update_flags(regs, out.alu_result, 0, 0);

            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;
        case THUMB_ROR:
            out.alu_result = (input.reg_data1 >> (input.reg_data2 & 31)) | (input.reg_data1 << (32 - (input.reg_data2 & 31)));
            regfile_update_flags(regs, out.alu_result, 0, 0);

            out.flags_updated = 1;
            out.cpsr = regs->apsr;
            break;




        case THUMB_LDR_IMM:
        case THUMB_LDR_REG:
            out.alu_result = input.reg_data1 + input.reg_data2;
            out.mem_size = 4;
            printf("[EX] LDR: base=0x%08X + offset=0x%08X = addr=0x%08X\n",
                input.reg_data1, input.reg_data2, out.alu_result);
            break;

        case THUMB_LDR_LIT:
            out.alu_result = input.reg_data1 + input.reg_data2;
            out.mem_size = 4;
            printf("[EX] LDR_LIT: PC=0x%08X + offset=0x%08X = addr=0x%08X\n",
                input.reg_data1, input.reg_data2, out.alu_result);
            break;

        case THUMB_LDR_SP:
            out.alu_result = input.reg_data1 + input.reg_data2;
            out.mem_size = 4;
            printf("[EX] LDR_SP: SP=0x%08X + offset=0x%08X = addr=0x%08X\n",
                input.reg_data1, input.reg_data2, out.alu_result);
            break;


        case THUMB_STR_IMM:
        case THUMB_STR_REG:
            out.alu_result = input.reg_data1 + input.reg_data2;
            out.mem_size = 4;
            printf("[EX] STR: base=0x%08X + offset=0x%08X = addr=0x%08X\n",
                input.reg_data1, input.reg_data2, out.alu_result);
            break;

        case THUMB_STR_SP:
            out.alu_result = input.reg_data1 + input.reg_data2;
            out.mem_size = 4;
            printf("[EX] STR_SP: SP=0x%08X + offset=0x%08X = addr=0x%08X\n",
                input.reg_data1, input.reg_data2, out.alu_result);
            break;


        case THUMB_LDRB_IMM:
        case THUMB_LDRB_REG:
            out.alu_result = input.reg_data1 + input.reg_data2;
            out.mem_size = 1;
            printf("[EX] LDRB: base=0x%08X + offset=0x%08X = addr=0x%08X\n",
                input.reg_data1, input.reg_data2, out.alu_result);
            break;

        case THUMB_LDRSB_REG:
            out.alu_result = input.reg_data1 + input.reg_data2;
            out.mem_size = 1;
            out.sign_extend = 1;
            printf("[EX] LDRSB: base=0x%08X + offset=0x%08X = addr=0x%08X\n",
                input.reg_data1, input.reg_data2, out.alu_result);
            break;


        case THUMB_STRB_IMM:
        case THUMB_STRB_REG:
            out.alu_result = input.reg_data1 + input.reg_data2;
            out.mem_size = 1;
            printf("[EX] STRB: base=0x%08X + offset=0x%08X = addr=0x%08X\n",
                input.reg_data1, input.reg_data2, out.alu_result);
            break;


        case THUMB_LDRH_IMM:
        case THUMB_LDRH_REG:
            out.alu_result = input.reg_data1 + input.reg_data2;
            out.mem_size = 2;
            printf("[EX] LDRH: base=0x%08X + offset=0x%08X = addr=0x%08X\n",
                input.reg_data1, input.reg_data2, out.alu_result);
            break;

            case THUMB_LDRSH_REG:
            out.alu_result = input.reg_data1 + input.reg_data2;
            out.mem_size = 2;
            out.sign_extend = 1;
            printf("[EX] LDRSH: base=0x%08X + offset=0x%08X = addr=0x%08X\n",
                input.reg_data1, input.reg_data2, out.alu_result);
            break;


        case THUMB_STRH_IMM:
        case THUMB_STRH_REG:
            out.alu_result = input.reg_data1 + input.reg_data2;
            out.mem_size = 2;
            printf("[EX] STRH: base=0x%08X + offset=0x%08X = addr=0x%08X\n",
                input.reg_data1, input.reg_data2, out.alu_result);
            break;




        case THUMB_B_COND:
        {





            uint32_t cond = input.condition;
            uint32_t apsr = input.cpsr;

            int condition_met = 0;

            switch (cond) {
                case 0x0: condition_met = (apsr & (1U << 30)) != 0; break;
                case 0x1: condition_met = (apsr & (1U << 30)) == 0; break;
                case 0x2: condition_met = (apsr & (1U << 29)) != 0; break;
                case 0x3: condition_met = (apsr & (1U << 29)) == 0; break;
                case 0x4: condition_met = (apsr & (1U << 31)) != 0; break;
                case 0x5: condition_met = (apsr & (1U << 31)) == 0; break;
                case 0x6: condition_met = (apsr & (1U << 28)) != 0; break;
                case 0x7: condition_met = (apsr & (1U << 28)) == 0; break;
                case 0x8:
                    condition_met = ((apsr & (1U << 29)) != 0) && ((apsr & (1U << 30)) == 0);
                    break;
                case 0x9:
                    condition_met = ((apsr & (1U << 29)) == 0) || ((apsr & (1U << 30)) != 0);
                    break;
                case 0xA:
                    condition_met = (((apsr & (1U << 31)) != 0) == ((apsr & (1U << 28)) != 0));
                    break;
                case 0xB:
                    condition_met = (((apsr & (1U << 31)) != 0) != ((apsr & (1U << 28)) != 0));
                    break;
                case 0xC:
                    condition_met = ((apsr & (1U << 30)) == 0) &&
                                (((apsr & (1U << 31)) != 0) == ((apsr & (1U << 28)) != 0));
                    break;
                case 0xD:
                    condition_met = ((apsr & (1U << 30)) != 0) ||
                                (((apsr & (1U << 31)) != 0) != ((apsr & (1U << 28)) != 0));
                    break;
                case 0xE:
                    condition_met = 1;
                    break;
                default:
                    condition_met = 0;
                    break;
            }

            if (condition_met) {
                out.alu_result = input.pc + 4 + (int32_t)input.reg_data2;
                printf("[EX DEBUG B_COND] Branch TAKEN - Condition 0x%X met, target=0x%08X\n",
                    cond, out.alu_result);
            } else {
                out.alu_result = input.pc + 4;
                printf("[EX DEBUG B_COND] Branch NOT TAKEN - Condition 0x%X not met, fall through to 0x%08X\n",
                    cond, out.alu_result);
            }

            out.cpsr = apsr;
            break;
        }
        case THUMB_B:



            out.alu_result = input.pc + 4 + (int32_t)input.reg_data2;
            printf("[EX DEBUG BRANCH] Branch at PC=0x%08X, offset=%d, target=0x%08X\n",
                input.pc, (int32_t)input.reg_data2, out.alu_result);
            break;

        case THUMB_BX:
            out.alu_result = input.reg_data1 & ~1U;
            break;

        case THUMB_BL:
        {

            out.alu_result = (input.pc) + 4 + (int32_t)input.reg_data2;
            out.link = input.pc + 4;
            printf("[EX DEBUG BL] BL at PC=0x%04X, target=0x%04X, LR=0x%04X\n",
                input.pc, out.alu_result, out.link);
            break;
        }
        case THUMB_BLX:
        {


            uint32_t target = (input.pc) + 4 + (int32_t)input.reg_data2;


            out.alu_result = target & 0xFFFFFFFC;


            out.link = (input.pc + 4) | 1;

            printf("[EX DEBUG BLX] BLX at PC=0x%08X, offset=0x%08X, target=0x%08X (ARM), LR=0x%08X\n",
                input.pc, (int32_t)input.reg_data2, out.alu_result, out.link);
            break;
        }



        case THUMB_PUSH:
        {

            uint32_t reglist = input.reg_data2;
            uint32_t num_regs = popcount(reglist);
            if (input.r_bit) num_regs++;


            out.alu_result = input.reg_data1 - (num_regs * 4);
            out.mem_size = reglist;
            out.r_bit = input.r_bit;

            printf("[EX] PUSH: Current SP=0x%08X, reglist=0x%02X, regs=%d, new SP=0x%08X\n",
                input.reg_data1, reglist, num_regs, out.alu_result);
            break;
        }

        case THUMB_POP:
        {

            uint32_t reglist = input.reg_data2;
            uint32_t num_regs = popcount(reglist);
            if (input.r_bit) num_regs++;


            out.alu_result = input.reg_data1 + (num_regs * 4);
            out.mem_size = reglist;
            out.r_bit = input.r_bit;

            printf("[EX] POP: Current SP=0x%08X, reglist=0x%02X, regs=%d, new SP=0x%08X\n",
                input.reg_data1, reglist, num_regs, out.alu_result);
            break;
        }
        case THUMB_LDMIA:
        case THUMB_STMIA:
            out.alu_result = input.reg_data1;
            break;




        case THUMB_NOP:
            out.alu_result = 0;
            printf("[EX DEBUG NOP] No operation\n");
            break;
        case THUMB_YIELD:
            out.alu_result = 0;
            printf("[EX DEBUG YIELD] Yield Hint (NOP in simulation)\n");
            break;
        case THUMB_WFE:
            out.alu_result = 0;
            printf("[EX DEBUG WFE] Wait For Event (NOP in simulation)\n");
        case THUMB_WFI:
            out.alu_result = 0;
            printf("[EX DEBUG WFI] Wait For Interrupt (NOP in simulation)\n");
            break;
        case THUMB_SEV:
            out.alu_result = 0;
            printf("[EX DEBUG SEV] Send Event (NOP in simulation)\n");
            break;

        case THUMB_BKPT:
        {




            uint32_t imm8 = input.reg_data2;

            printf("[EX DEBUG BKPT] Breakpoint hit!\n");
            printf("[EX DEBUG BKPT]   PC: 0x%08X\n", input.pc);
            printf("[EX DEBUG BKPT]   Immediate value: 0x%02X\n", imm8);
            printf("[EX DEBUG BKPT]   CPSR: 0x%08X\n", input.cpsr);






            out.alu_result = input.pc + 4;
            out.cpsr = input.cpsr;

            printf("[EX DEBUG BKPT] Exception would be taken, R14_abt would be set to 0x%08X\n",
                input.pc + 4);

            break;
        }
        case THUMB_SVC:
        {
# 647 "execute.c"
            uint32_t service_num = input.reg_data2;

            printf("[EX DEBUG SVC] Supervisor Call (SVC #%d)\n", service_num);
            printf("[EX DEBUG SVC] PC at SVC: 0x%08X\n", input.pc);
            printf("[EX DEBUG SVC] Next instruction would be at: 0x%08X\n", input.pc + 2);






            out.alu_result = input.pc + 2;


            out.flags_updated = 0;
            out.cpsr = regs->apsr;

            printf("[EX DEBUG SVC] SVC exception would be taken\n");
            printf("[EX DEBUG SVC] R14_svc would be set to: 0x%08X\n", out.alu_result);

            break;
        }



        case THUMB_SXTB:
        {
            int8_t byte_val = (int8_t)(input.reg_data1 & 0xFF);
            out.alu_result = (int32_t)byte_val;
            printf("[EX DEBUG SXTB] Input=0x%08X, Byte=0x%02X (%d), Result=0x%08X\n",
                input.reg_data1, (unsigned char)(input.reg_data1 & 0xFF), byte_val, out.alu_result);
            regfile_update_flags(regs, out.alu_result, 0, 0);
            break;
        }
        case THUMB_SXTH:
        {

            int16_t hw_val = (int16_t)(input.reg_data1 & 0xFFFF);
            out.alu_result = (int32_t)hw_val;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            printf("[EX DEBUG SXTH] Input=0x%08X, Halfword=0x%04X, Output=0x%08X\n",
                input.reg_data1, (uint16_t)(input.reg_data1 & 0xFFFF), out.alu_result);
            break;
        }
        case THUMB_UXTB:
        {

            out.alu_result = input.reg_data1 & 0xFF;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            printf("[EX DEBUG UXTB] Input=0x%08X, Output=0x%08X\n",
                input.reg_data1, out.alu_result);
            break;
        }
        case THUMB_UXTH:
        {

            out.alu_result = input.reg_data1 & 0xFFFF;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            printf("[EX DEBUG UXTH] Input=0x%08X, Output=0x%08X\n",
                input.reg_data1, out.alu_result);
            break;
        }




        case THUMB_REV:
        {

            uint32_t val = input.reg_data1;
            out.alu_result = ((val & 0xFF000000) >> 24) |
                            ((val & 0x00FF0000) >> 8) |
                            ((val & 0x0000FF00) << 8) |
                            ((val & 0x000000FF) << 24);
            regfile_update_flags(regs, out.alu_result, 0, 0);
            printf("[EX DEBUG REV] Input=0x%08X, Output=0x%08X\n", val, out.alu_result);
            break;
        }
        case THUMB_REV16:
        {

            uint32_t val = input.reg_data1;
            uint16_t lo = val & 0xFFFF;
            uint16_t hi = (val >> 16) & 0xFFFF;

            uint16_t lo_reversed = ((lo & 0xFF) << 8) | ((lo >> 8) & 0xFF);
            uint16_t hi_reversed = ((hi & 0xFF) << 8) | ((hi >> 8) & 0xFF);

            out.alu_result = (hi_reversed << 16) | lo_reversed;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            printf("[EX DEBUG REV16] Input=0x%08X, Output=0x%08X\n", val, out.alu_result);
            break;
        }
        case THUMB_REVSH:
        {

            uint16_t hw = input.reg_data1 & 0xFFFF;
            uint16_t reversed = ((hw & 0xFF) << 8) | ((hw >> 8) & 0xFF);
            int16_t signed_val = (int16_t)reversed;
            out.alu_result = (int32_t)signed_val;
            regfile_update_flags(regs, out.alu_result, 0, 0);
            printf("[EX DEBUG REVSH] Input=0x%04X, Reversed=0x%04X, Output=0x%08X\n",
                hw, reversed, out.alu_result);
            break;
        }


        case THUMB_CBZ:
        case THUMB_CBNZ:
        {

            uint32_t reg_value = input.reg_data1;
            uint32_t offset = input.reg_data2;

            int is_cbnz = (input.opcode == THUMB_CBNZ);
            int condition_met = is_cbnz ? (reg_value != 0) : (reg_value == 0);

            if (condition_met) {

                out.alu_result = input.pc + 4 + offset;
                printf("[EX DEBUG %s] Branch TAKEN - Rn=0x%08X, target=0x%08X\n",
                    is_cbnz ? "CBNZ" : "CBZ", reg_value, out.alu_result);
            } else {

                out.alu_result = input.pc + 4;
                printf("[EX DEBUG %s] Branch NOT TAKEN - Rn=0x%08X, fall through to 0x%08X\n",
                    is_cbnz ? "CBNZ" : "CBZ", reg_value, out.alu_result);
            }

            out.cpsr = regs->apsr;
            break;
        }




        default:
            printf("[WARN] EXECUTE: Unhandled opcode %s\n", get_operation_name(input.opcode));
            out.alu_result = 0;
            break;
    }

    return out;
}
