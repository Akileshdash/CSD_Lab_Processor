set moduleName execute
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
set C_modelName {execute}
set C_modelType { int 128 }
set ap_memory_interface_dict [dict create]
set C_modelArgList {
	{ empty_36 int 32 regular  }
	{ sub387 int 32 regular  }
	{ empty_37 int 32 regular  }
	{ ex_input_reg_data2_7 int 32 regular  }
	{ empty_38 int 32 regular  }
	{ empty_39 int 32 regular  }
	{ empty int 32 regular  }
	{ core_regs_apsr int 32 regular {pointer 2} {global 2}  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "empty_36", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sub387", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_37", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "ex_input_reg_data2_7", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_38", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_39", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "core_regs_apsr", "interface" : "wire", "bitwidth" : 32, "direction" : "READWRITE", "extern" : 0} , 
 	{ "Name" : "ap_return", "interface" : "wire", "bitwidth" : 128} ]}
# RTL Port declarations: 
set portNum 20
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ empty_36 sc_in sc_lv 32 signal 0 } 
	{ sub387 sc_in sc_lv 32 signal 1 } 
	{ empty_37 sc_in sc_lv 32 signal 2 } 
	{ ex_input_reg_data2_7 sc_in sc_lv 32 signal 3 } 
	{ empty_38 sc_in sc_lv 32 signal 4 } 
	{ empty_39 sc_in sc_lv 32 signal 5 } 
	{ empty sc_in sc_lv 32 signal 6 } 
	{ core_regs_apsr_i sc_in sc_lv 32 signal 7 } 
	{ core_regs_apsr_o sc_out sc_lv 32 signal 7 } 
	{ core_regs_apsr_o_ap_vld sc_out sc_logic 1 outvld 7 } 
	{ ap_return_0 sc_out sc_lv 32 signal -1 } 
	{ ap_return_1 sc_out sc_lv 32 signal -1 } 
	{ ap_return_2 sc_out sc_lv 32 signal -1 } 
	{ ap_return_3 sc_out sc_lv 32 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "empty_36", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_36", "role": "default" }} , 
 	{ "name": "sub387", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sub387", "role": "default" }} , 
 	{ "name": "empty_37", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_37", "role": "default" }} , 
 	{ "name": "ex_input_reg_data2_7", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ex_input_reg_data2_7", "role": "default" }} , 
 	{ "name": "empty_38", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_38", "role": "default" }} , 
 	{ "name": "empty_39", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty_39", "role": "default" }} , 
 	{ "name": "empty", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "empty", "role": "default" }} , 
 	{ "name": "core_regs_apsr_i", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "core_regs_apsr", "role": "i" }} , 
 	{ "name": "core_regs_apsr_o", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "core_regs_apsr", "role": "o" }} , 
 	{ "name": "core_regs_apsr_o_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "core_regs_apsr", "role": "o_ap_vld" }} , 
 	{ "name": "ap_return_0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_0", "role": "default" }} , 
 	{ "name": "ap_return_1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_1", "role": "default" }} , 
 	{ "name": "ap_return_2", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_2", "role": "default" }} , 
 	{ "name": "ap_return_3", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_3", "role": "default" }}  ]}

set ArgLastReadFirstWriteLatency {
	execute {
		empty_36 {Type I LastRead 0 FirstWrite -1}
		sub387 {Type I LastRead 0 FirstWrite -1}
		empty_37 {Type I LastRead 0 FirstWrite -1}
		ex_input_reg_data2_7 {Type I LastRead 0 FirstWrite -1}
		empty_38 {Type I LastRead 0 FirstWrite -1}
		empty_39 {Type I LastRead 0 FirstWrite -1}
		empty {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 6 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "1", "Max" : "6"}
	, {"Name" : "Interval", "Min" : "1", "Max" : "6"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	empty_36 { ap_none {  { empty_36 in_data 0 32 } } }
	sub387 { ap_none {  { sub387 in_data 0 32 } } }
	empty_37 { ap_none {  { empty_37 in_data 0 32 } } }
	ex_input_reg_data2_7 { ap_none {  { ex_input_reg_data2_7 in_data 0 32 } } }
	empty_38 { ap_none {  { empty_38 in_data 0 32 } } }
	empty_39 { ap_none {  { empty_39 in_data 0 32 } } }
	empty { ap_none {  { empty in_data 0 32 } } }
	core_regs_apsr { ap_ovld {  { core_regs_apsr_i in_data 0 32 }  { core_regs_apsr_o out_data 1 32 }  { core_regs_apsr_o_ap_vld out_vld 1 1 } } }
}
