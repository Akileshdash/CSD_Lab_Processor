set moduleName detect_forwarding
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set isPipelined_legacy 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set DLRegFirstOffset 0
set DLRegItemOffset 0
set svuvm_can_support 1
set cdfgNum 13
set C_modelName {detect_forwarding}
set C_modelType { int 160 }
set ap_memory_interface_dict [dict create]
dict set ap_memory_interface_dict core_regs_gpr { MEM_WIDTH 32 MEM_SIZE 52 MASTER_TYPE BRAM_CTRL MEM_ADDRESS_MODE WORD_ADDRESS PACKAGE_IO port READ_LATENCY 1 }
set C_modelArgList {
	{ empty_40 int 32 regular  }
	{ empty_41 int 32 regular  }
	{ empty_42 int 32 regular  }
	{ empty_43 int 32 regular  }
	{ empty_44 int 32 regular  }
	{ empty_45 int 32 regular  }
	{ empty_46 int 32 regular  }
	{ empty_47 int 32 regular  }
	{ empty_48 int 32 regular  }
	{ empty_49 int 32 regular  }
	{ empty_50 int 32 regular  }
	{ empty_51 int 32 regular  }
	{ empty_52 int 32 regular  }
	{ empty int 32 regular  }
	{ core_regs_msp int 32 regular {pointer 0} {global 0}  }
	{ core_regs_lr int 32 regular {pointer 0} {global 0}  }
	{ core_regs_pc int 32 regular {pointer 0} {global 0}  }
	{ core_regs_gpr int 32 regular {array 13 { 1 3 } 1 1 } {global 0}  }
	{ core_regs_apsr int 32 regular {pointer 0} {global 0}  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "empty_40", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_41", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_42", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_43", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_44", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_45", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_46", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_47", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_48", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_49", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_50", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_51", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_52", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "core_regs_msp", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "extern" : 0} , 
 	{ "Name" : "core_regs_lr", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "extern" : 0} , 
 	{ "Name" : "core_regs_pc", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "extern" : 0} , 
 	{ "Name" : "core_regs_gpr", "interface" : "memory", "bitwidth" : 32, "direction" : "READONLY", "extern" : 0} , 
 	{ "Name" : "core_regs_apsr", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "extern" : 0} , 
 	{ "Name" : "ap_return", "interface" : "wire", "bitwidth" : 160} ]}
# RTL Port declarations: 
set portNum 32
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ empty_40 sc_in sc_lv 32 signal 0 } 
	{ empty_41 sc_in sc_lv 32 signal 1 } 
	{ empty_42 sc_in sc_lv 32 signal 2 } 
	{ empty_43 sc_in sc_lv 32 signal 3 } 
	{ empty_44 sc_in sc_lv 32 signal 4 } 
	{ empty_45 sc_in sc_lv 32 signal 5 } 
	{ empty_46 sc_in sc_lv 32 signal 6 } 
	{ empty_47 sc_in sc_lv 32 signal 7 } 
	{ empty_48 sc_in sc_lv 32 signal 8 } 
	{ empty_49 sc_in sc_lv 32 signal 9 } 
	{ empty_50 sc_in sc_lv 32 signal 10 } 
	{ empty_51 sc_in sc_lv 32 signal 11 } 
	{ empty_52 sc_in sc_lv 32 signal 12 } 
	{ empty sc_in sc_lv 32 signal 13 } 
	{ core_regs_msp sc_in sc_lv 32 signal 14 } 
	{ core_regs_lr sc_in sc_lv 32 signal 15 } 
	{ core_regs_pc sc_in sc_lv 32 signal 16 } 
	{ core_regs_gpr_address0 sc_out sc_lv 4 signal 17 } 
	{ core_regs_gpr_ce0 sc_out sc_logic 1 signal 17 } 
	{ core_regs_gpr_q0 sc_in sc_lv 32 signal 17 } 
	{ core_regs_apsr sc_in sc_lv 32 signal 18 } 
	{ ap_return_0 sc_out sc_lv 32 signal -1 } 
	{ ap_return_1 sc_out sc_lv 32 signal -1 } 
	{ ap_return_2 sc_out sc_lv 32 signal -1 } 
	{ ap_return_3 sc_out sc_lv 32 signal -1 } 
	{ ap_return_4 sc_out sc_lv 32 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "empty_40", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_40", "role": "default" }} , 
 	{ "name": "empty_41", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_41", "role": "default" }} , 
 	{ "name": "empty_42", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_42", "role": "default" }} , 
 	{ "name": "empty_43", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_43", "role": "default" }} , 
 	{ "name": "empty_44", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_44", "role": "default" }} , 
 	{ "name": "empty_45", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_45", "role": "default" }} , 
 	{ "name": "empty_46", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_46", "role": "default" }} , 
 	{ "name": "empty_47", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_47", "role": "default" }} , 
 	{ "name": "empty_48", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_48", "role": "default" }} , 
 	{ "name": "empty_49", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_49", "role": "default" }} , 
 	{ "name": "empty_50", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_50", "role": "default" }} , 
 	{ "name": "empty_51", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_51", "role": "default" }} , 
 	{ "name": "empty_52", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_52", "role": "default" }} , 
 	{ "name": "empty", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty", "role": "default" }} , 
 	{ "name": "core_regs_msp", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "core_regs_msp", "role": "default" }} , 
 	{ "name": "core_regs_lr", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "core_regs_lr", "role": "default" }} , 
 	{ "name": "core_regs_pc", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "core_regs_pc", "role": "default" }} , 
 	{ "name": "core_regs_gpr_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "core_regs_gpr", "role": "address0" }} , 
 	{ "name": "core_regs_gpr_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "core_regs_gpr", "role": "ce0" }} , 
 	{ "name": "core_regs_gpr_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "core_regs_gpr", "role": "q0" }} , 
 	{ "name": "core_regs_apsr", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "core_regs_apsr", "role": "default" }} , 
 	{ "name": "ap_return_0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_0", "role": "default" }} , 
 	{ "name": "ap_return_1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_1", "role": "default" }} , 
 	{ "name": "ap_return_2", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_2", "role": "default" }} , 
 	{ "name": "ap_return_3", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_3", "role": "default" }} , 
 	{ "name": "ap_return_4", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_4", "role": "default" }}  ]}

set ArgLastReadFirstWriteLatency {
	detect_forwarding {
		empty_40 {Type I LastRead 0 FirstWrite -1}
		empty_41 {Type I LastRead 1 FirstWrite -1}
		empty_42 {Type I LastRead 0 FirstWrite -1}
		empty_43 {Type I LastRead 2 FirstWrite -1}
		empty_44 {Type I LastRead 2 FirstWrite -1}
		empty_45 {Type I LastRead 2 FirstWrite -1}
		empty_46 {Type I LastRead 0 FirstWrite -1}
		empty_47 {Type I LastRead 2 FirstWrite -1}
		empty_48 {Type I LastRead 2 FirstWrite -1}
		empty_49 {Type I LastRead 2 FirstWrite -1}
		empty_50 {Type I LastRead 1 FirstWrite -1}
		empty_51 {Type I LastRead 2 FirstWrite -1}
		empty_52 {Type I LastRead 2 FirstWrite -1}
		empty {Type I LastRead 2 FirstWrite -1}
		core_regs_msp {Type I LastRead 2 FirstWrite -1}
		core_regs_lr {Type I LastRead 2 FirstWrite -1}
		core_regs_pc {Type I LastRead 1 FirstWrite -1}
		core_regs_gpr {Type I LastRead 1 FirstWrite -1}
		core_regs_apsr {Type I LastRead 2 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "4", "Max" : "8"}
	, {"Name" : "Interval", "Min" : "4", "Max" : "8"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	empty_40 { ap_none {  { empty_40 in_data 0 32 } } }
	empty_41 { ap_none {  { empty_41 in_data 0 32 } } }
	empty_42 { ap_none {  { empty_42 in_data 0 32 } } }
	empty_43 { ap_none {  { empty_43 in_data 0 32 } } }
	empty_44 { ap_none {  { empty_44 in_data 0 32 } } }
	empty_45 { ap_none {  { empty_45 in_data 0 32 } } }
	empty_46 { ap_none {  { empty_46 in_data 0 32 } } }
	empty_47 { ap_none {  { empty_47 in_data 0 32 } } }
	empty_48 { ap_none {  { empty_48 in_data 0 32 } } }
	empty_49 { ap_none {  { empty_49 in_data 0 32 } } }
	empty_50 { ap_none {  { empty_50 in_data 0 32 } } }
	empty_51 { ap_none {  { empty_51 in_data 0 32 } } }
	empty_52 { ap_none {  { empty_52 in_data 0 32 } } }
	empty { ap_none {  { empty in_data 0 32 } } }
	core_regs_msp { ap_none {  { core_regs_msp in_data 0 32 } } }
	core_regs_lr { ap_none {  { core_regs_lr in_data 0 32 } } }
	core_regs_pc { ap_none {  { core_regs_pc in_data 0 32 } } }
	core_regs_gpr { ap_memory {  { core_regs_gpr_address0 mem_address 1 4 }  { core_regs_gpr_ce0 mem_ce 1 1 }  { core_regs_gpr_q0 mem_dout 0 32 } } }
	core_regs_apsr { ap_none {  { core_regs_apsr in_data 0 32 } } }
}
