set moduleName regfile_update_flags
set isTopModule 0
set isCombinational 1
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
set C_modelName {regfile_update_flags}
set C_modelType { void 0 }
set ap_memory_interface_dict [dict create]
set C_modelArgList {
	{ result int 32 regular  }
	{ carry int 1 regular  }
	{ overflow int 1 regular  }
	{ core_regs_apsr int 32 regular {pointer 2} {global 2}  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "result", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "carry", "interface" : "wire", "bitwidth" : 1, "direction" : "READONLY"} , 
 	{ "Name" : "overflow", "interface" : "wire", "bitwidth" : 1, "direction" : "READONLY"} , 
 	{ "Name" : "core_regs_apsr", "interface" : "wire", "bitwidth" : 32, "direction" : "READWRITE", "extern" : 0} ]}
# RTL Port declarations: 
set portNum 8
set portList { 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ result sc_in sc_lv 32 signal 0 } 
	{ carry sc_in sc_lv 1 signal 1 } 
	{ overflow sc_in sc_lv 1 signal 2 } 
	{ core_regs_apsr_i sc_in sc_lv 32 signal 3 } 
	{ core_regs_apsr_o sc_out sc_lv 32 signal 3 } 
	{ core_regs_apsr_o_ap_vld sc_out sc_logic 1 outvld 3 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
}
set NewPortList {[ 
	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "result", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "result", "role": "default" }} , 
 	{ "name": "carry", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "carry", "role": "default" }} , 
 	{ "name": "overflow", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "overflow", "role": "default" }} , 
 	{ "name": "core_regs_apsr_i", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "core_regs_apsr", "role": "i" }} , 
 	{ "name": "core_regs_apsr_o", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "core_regs_apsr", "role": "o" }} , 
 	{ "name": "core_regs_apsr_o_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "core_regs_apsr", "role": "o_ap_vld" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }}  ]}

set ArgLastReadFirstWriteLatency {
	regfile_update_flags {
		result {Type I LastRead 0 FirstWrite -1}
		carry {Type I LastRead 0 FirstWrite -1}
		overflow {Type I LastRead 0 FirstWrite -1}
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "0", "Max" : "0"}
	, {"Name" : "Interval", "Min" : "0", "Max" : "0"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	result { ap_none {  { result in_data 0 32 } } }
	carry { ap_none {  { carry in_data 0 1 } } }
	overflow { ap_none {  { overflow in_data 0 1 } } }
	core_regs_apsr { ap_ovld {  { core_regs_apsr_i in_data 0 32 }  { core_regs_apsr_o out_data 1 32 }  { core_regs_apsr_o_ap_vld out_vld 1 1 } } }
}
