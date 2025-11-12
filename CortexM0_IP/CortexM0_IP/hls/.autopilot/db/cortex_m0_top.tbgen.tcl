set moduleName cortex_m0_top
set isTopModule 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set isPipelined_legacy 0
set pipeline_type none
set FunctionProtocol ap_ctrl_none
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set DLRegFirstOffset 0
set DLRegItemOffset 0
set svuvm_can_support 1
set cdfgNum 13
set C_modelName {cortex_m0_top}
set C_modelType { void 0 }
set ap_memory_interface_dict [dict create]
set C_modelArgList {
	{ INSTR_BUS int 32 regular {axi_master 2}  }
	{ DATA_BUS int 32 regular {axi_master 2}  }
	{ REG_BUS int 32 regular {axi_master 2}  }
	{ instr_mem int 64 regular {axi_slave 0}  }
	{ data_mem int 64 regular {axi_slave 0}  }
	{ reg_out int 64 regular {axi_slave 0}  }
	{ step uint 1 regular  }
	{ pc_out int 32 regular {pointer 1}  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "INSTR_BUS", "interface" : "axi_master", "bitwidth" : 32, "direction" : "READWRITE", "bitSlice":[ {"cElement": [{"cName": "instr_mem","offset": { "type": "dynamic","port_name": "instr_mem","bundle": "control"},"direction": "READWRITE"}]}]} , 
 	{ "Name" : "DATA_BUS", "interface" : "axi_master", "bitwidth" : 32, "direction" : "READWRITE", "bitSlice":[ {"cElement": [{"cName": "data_mem","offset": { "type": "dynamic","port_name": "data_mem","bundle": "control"},"direction": "READWRITE"}]}]} , 
 	{ "Name" : "REG_BUS", "interface" : "axi_master", "bitwidth" : 32, "direction" : "READWRITE", "bitSlice":[ {"cElement": [{"cName": "reg_out","offset": { "type": "dynamic","port_name": "reg_out","bundle": "control"},"direction": "READWRITE"}]}]} , 
 	{ "Name" : "instr_mem", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":16}, "offset_end" : {"in":27}} , 
 	{ "Name" : "data_mem", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":28}, "offset_end" : {"in":39}} , 
 	{ "Name" : "reg_out", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":40}, "offset_end" : {"in":51}} , 
 	{ "Name" : "step", "interface" : "wire", "bitwidth" : 1, "direction" : "READONLY"} , 
 	{ "Name" : "pc_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 157
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst_n sc_in sc_logic 1 reset -1 active_low_sync } 
	{ m_axi_INSTR_BUS_AWVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_INSTR_BUS_AWREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_INSTR_BUS_AWADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_INSTR_BUS_AWID sc_out sc_lv 1 signal 0 } 
	{ m_axi_INSTR_BUS_AWLEN sc_out sc_lv 8 signal 0 } 
	{ m_axi_INSTR_BUS_AWSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_INSTR_BUS_AWBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_INSTR_BUS_AWLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_INSTR_BUS_AWCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_INSTR_BUS_AWPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_INSTR_BUS_AWQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_INSTR_BUS_AWREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_INSTR_BUS_AWUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_INSTR_BUS_WVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_INSTR_BUS_WREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_INSTR_BUS_WDATA sc_out sc_lv 32 signal 0 } 
	{ m_axi_INSTR_BUS_WSTRB sc_out sc_lv 4 signal 0 } 
	{ m_axi_INSTR_BUS_WLAST sc_out sc_logic 1 signal 0 } 
	{ m_axi_INSTR_BUS_WID sc_out sc_lv 1 signal 0 } 
	{ m_axi_INSTR_BUS_WUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_INSTR_BUS_ARVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_INSTR_BUS_ARREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_INSTR_BUS_ARADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_INSTR_BUS_ARID sc_out sc_lv 1 signal 0 } 
	{ m_axi_INSTR_BUS_ARLEN sc_out sc_lv 8 signal 0 } 
	{ m_axi_INSTR_BUS_ARSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_INSTR_BUS_ARBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_INSTR_BUS_ARLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_INSTR_BUS_ARCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_INSTR_BUS_ARPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_INSTR_BUS_ARQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_INSTR_BUS_ARREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_INSTR_BUS_ARUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_INSTR_BUS_RVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_INSTR_BUS_RREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_INSTR_BUS_RDATA sc_in sc_lv 32 signal 0 } 
	{ m_axi_INSTR_BUS_RLAST sc_in sc_logic 1 signal 0 } 
	{ m_axi_INSTR_BUS_RID sc_in sc_lv 1 signal 0 } 
	{ m_axi_INSTR_BUS_RUSER sc_in sc_lv 1 signal 0 } 
	{ m_axi_INSTR_BUS_RRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_INSTR_BUS_BVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_INSTR_BUS_BREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_INSTR_BUS_BRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_INSTR_BUS_BID sc_in sc_lv 1 signal 0 } 
	{ m_axi_INSTR_BUS_BUSER sc_in sc_lv 1 signal 0 } 
	{ m_axi_DATA_BUS_AWVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_DATA_BUS_AWREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_DATA_BUS_AWADDR sc_out sc_lv 64 signal 1 } 
	{ m_axi_DATA_BUS_AWID sc_out sc_lv 1 signal 1 } 
	{ m_axi_DATA_BUS_AWLEN sc_out sc_lv 8 signal 1 } 
	{ m_axi_DATA_BUS_AWSIZE sc_out sc_lv 3 signal 1 } 
	{ m_axi_DATA_BUS_AWBURST sc_out sc_lv 2 signal 1 } 
	{ m_axi_DATA_BUS_AWLOCK sc_out sc_lv 2 signal 1 } 
	{ m_axi_DATA_BUS_AWCACHE sc_out sc_lv 4 signal 1 } 
	{ m_axi_DATA_BUS_AWPROT sc_out sc_lv 3 signal 1 } 
	{ m_axi_DATA_BUS_AWQOS sc_out sc_lv 4 signal 1 } 
	{ m_axi_DATA_BUS_AWREGION sc_out sc_lv 4 signal 1 } 
	{ m_axi_DATA_BUS_AWUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_DATA_BUS_WVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_DATA_BUS_WREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_DATA_BUS_WDATA sc_out sc_lv 32 signal 1 } 
	{ m_axi_DATA_BUS_WSTRB sc_out sc_lv 4 signal 1 } 
	{ m_axi_DATA_BUS_WLAST sc_out sc_logic 1 signal 1 } 
	{ m_axi_DATA_BUS_WID sc_out sc_lv 1 signal 1 } 
	{ m_axi_DATA_BUS_WUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_DATA_BUS_ARVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_DATA_BUS_ARREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_DATA_BUS_ARADDR sc_out sc_lv 64 signal 1 } 
	{ m_axi_DATA_BUS_ARID sc_out sc_lv 1 signal 1 } 
	{ m_axi_DATA_BUS_ARLEN sc_out sc_lv 8 signal 1 } 
	{ m_axi_DATA_BUS_ARSIZE sc_out sc_lv 3 signal 1 } 
	{ m_axi_DATA_BUS_ARBURST sc_out sc_lv 2 signal 1 } 
	{ m_axi_DATA_BUS_ARLOCK sc_out sc_lv 2 signal 1 } 
	{ m_axi_DATA_BUS_ARCACHE sc_out sc_lv 4 signal 1 } 
	{ m_axi_DATA_BUS_ARPROT sc_out sc_lv 3 signal 1 } 
	{ m_axi_DATA_BUS_ARQOS sc_out sc_lv 4 signal 1 } 
	{ m_axi_DATA_BUS_ARREGION sc_out sc_lv 4 signal 1 } 
	{ m_axi_DATA_BUS_ARUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_DATA_BUS_RVALID sc_in sc_logic 1 signal 1 } 
	{ m_axi_DATA_BUS_RREADY sc_out sc_logic 1 signal 1 } 
	{ m_axi_DATA_BUS_RDATA sc_in sc_lv 32 signal 1 } 
	{ m_axi_DATA_BUS_RLAST sc_in sc_logic 1 signal 1 } 
	{ m_axi_DATA_BUS_RID sc_in sc_lv 1 signal 1 } 
	{ m_axi_DATA_BUS_RUSER sc_in sc_lv 1 signal 1 } 
	{ m_axi_DATA_BUS_RRESP sc_in sc_lv 2 signal 1 } 
	{ m_axi_DATA_BUS_BVALID sc_in sc_logic 1 signal 1 } 
	{ m_axi_DATA_BUS_BREADY sc_out sc_logic 1 signal 1 } 
	{ m_axi_DATA_BUS_BRESP sc_in sc_lv 2 signal 1 } 
	{ m_axi_DATA_BUS_BID sc_in sc_lv 1 signal 1 } 
	{ m_axi_DATA_BUS_BUSER sc_in sc_lv 1 signal 1 } 
	{ m_axi_REG_BUS_AWVALID sc_out sc_logic 1 signal 2 } 
	{ m_axi_REG_BUS_AWREADY sc_in sc_logic 1 signal 2 } 
	{ m_axi_REG_BUS_AWADDR sc_out sc_lv 64 signal 2 } 
	{ m_axi_REG_BUS_AWID sc_out sc_lv 1 signal 2 } 
	{ m_axi_REG_BUS_AWLEN sc_out sc_lv 8 signal 2 } 
	{ m_axi_REG_BUS_AWSIZE sc_out sc_lv 3 signal 2 } 
	{ m_axi_REG_BUS_AWBURST sc_out sc_lv 2 signal 2 } 
	{ m_axi_REG_BUS_AWLOCK sc_out sc_lv 2 signal 2 } 
	{ m_axi_REG_BUS_AWCACHE sc_out sc_lv 4 signal 2 } 
	{ m_axi_REG_BUS_AWPROT sc_out sc_lv 3 signal 2 } 
	{ m_axi_REG_BUS_AWQOS sc_out sc_lv 4 signal 2 } 
	{ m_axi_REG_BUS_AWREGION sc_out sc_lv 4 signal 2 } 
	{ m_axi_REG_BUS_AWUSER sc_out sc_lv 1 signal 2 } 
	{ m_axi_REG_BUS_WVALID sc_out sc_logic 1 signal 2 } 
	{ m_axi_REG_BUS_WREADY sc_in sc_logic 1 signal 2 } 
	{ m_axi_REG_BUS_WDATA sc_out sc_lv 32 signal 2 } 
	{ m_axi_REG_BUS_WSTRB sc_out sc_lv 4 signal 2 } 
	{ m_axi_REG_BUS_WLAST sc_out sc_logic 1 signal 2 } 
	{ m_axi_REG_BUS_WID sc_out sc_lv 1 signal 2 } 
	{ m_axi_REG_BUS_WUSER sc_out sc_lv 1 signal 2 } 
	{ m_axi_REG_BUS_ARVALID sc_out sc_logic 1 signal 2 } 
	{ m_axi_REG_BUS_ARREADY sc_in sc_logic 1 signal 2 } 
	{ m_axi_REG_BUS_ARADDR sc_out sc_lv 64 signal 2 } 
	{ m_axi_REG_BUS_ARID sc_out sc_lv 1 signal 2 } 
	{ m_axi_REG_BUS_ARLEN sc_out sc_lv 8 signal 2 } 
	{ m_axi_REG_BUS_ARSIZE sc_out sc_lv 3 signal 2 } 
	{ m_axi_REG_BUS_ARBURST sc_out sc_lv 2 signal 2 } 
	{ m_axi_REG_BUS_ARLOCK sc_out sc_lv 2 signal 2 } 
	{ m_axi_REG_BUS_ARCACHE sc_out sc_lv 4 signal 2 } 
	{ m_axi_REG_BUS_ARPROT sc_out sc_lv 3 signal 2 } 
	{ m_axi_REG_BUS_ARQOS sc_out sc_lv 4 signal 2 } 
	{ m_axi_REG_BUS_ARREGION sc_out sc_lv 4 signal 2 } 
	{ m_axi_REG_BUS_ARUSER sc_out sc_lv 1 signal 2 } 
	{ m_axi_REG_BUS_RVALID sc_in sc_logic 1 signal 2 } 
	{ m_axi_REG_BUS_RREADY sc_out sc_logic 1 signal 2 } 
	{ m_axi_REG_BUS_RDATA sc_in sc_lv 32 signal 2 } 
	{ m_axi_REG_BUS_RLAST sc_in sc_logic 1 signal 2 } 
	{ m_axi_REG_BUS_RID sc_in sc_lv 1 signal 2 } 
	{ m_axi_REG_BUS_RUSER sc_in sc_lv 1 signal 2 } 
	{ m_axi_REG_BUS_RRESP sc_in sc_lv 2 signal 2 } 
	{ m_axi_REG_BUS_BVALID sc_in sc_logic 1 signal 2 } 
	{ m_axi_REG_BUS_BREADY sc_out sc_logic 1 signal 2 } 
	{ m_axi_REG_BUS_BRESP sc_in sc_lv 2 signal 2 } 
	{ m_axi_REG_BUS_BID sc_in sc_lv 1 signal 2 } 
	{ m_axi_REG_BUS_BUSER sc_in sc_lv 1 signal 2 } 
	{ step sc_in sc_lv 1 signal 6 } 
	{ pc_out sc_out sc_lv 32 signal 7 } 
	{ pc_out_ap_vld sc_out sc_logic 1 outvld 7 } 
	{ s_axi_control_AWVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_AWREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_AWADDR sc_in sc_lv 6 signal -1 } 
	{ s_axi_control_WVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_WREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_WDATA sc_in sc_lv 32 signal -1 } 
	{ s_axi_control_WSTRB sc_in sc_lv 4 signal -1 } 
	{ s_axi_control_ARVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_ARREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_ARADDR sc_in sc_lv 6 signal -1 } 
	{ s_axi_control_RVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_RREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_RDATA sc_out sc_lv 32 signal -1 } 
	{ s_axi_control_RRESP sc_out sc_lv 2 signal -1 } 
	{ s_axi_control_BVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_BREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_BRESP sc_out sc_lv 2 signal -1 } 
}
set NewPortList {[ 
	{ "name": "s_axi_control_AWADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "control", "role": "AWADDR" },"address":[{"name":"instr_mem","role":"data","value":"16"},{"name":"data_mem","role":"data","value":"28"},{"name":"reg_out","role":"data","value":"40"}] },
	{ "name": "s_axi_control_AWVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWVALID" } },
	{ "name": "s_axi_control_AWREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWREADY" } },
	{ "name": "s_axi_control_WVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WVALID" } },
	{ "name": "s_axi_control_WREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WREADY" } },
	{ "name": "s_axi_control_WDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "WDATA" } },
	{ "name": "s_axi_control_WSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "control", "role": "WSTRB" } },
	{ "name": "s_axi_control_ARADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "control", "role": "ARADDR" },"address":[] },
	{ "name": "s_axi_control_ARVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "ARVALID" } },
	{ "name": "s_axi_control_ARREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "ARREADY" } },
	{ "name": "s_axi_control_RVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "RVALID" } },
	{ "name": "s_axi_control_RREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "RREADY" } },
	{ "name": "s_axi_control_RDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "RDATA" } },
	{ "name": "s_axi_control_RRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control", "role": "RRESP" } },
	{ "name": "s_axi_control_BVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "BVALID" } },
	{ "name": "s_axi_control_BREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "BREADY" } },
	{ "name": "s_axi_control_BRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control", "role": "BRESP" } }, 
 	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst_n", "role": "default" }} , 
 	{ "name": "m_axi_INSTR_BUS_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "AWVALID" }} , 
 	{ "name": "m_axi_INSTR_BUS_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "AWREADY" }} , 
 	{ "name": "m_axi_INSTR_BUS_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "AWADDR" }} , 
 	{ "name": "m_axi_INSTR_BUS_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "AWID" }} , 
 	{ "name": "m_axi_INSTR_BUS_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "AWLEN" }} , 
 	{ "name": "m_axi_INSTR_BUS_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_INSTR_BUS_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "AWBURST" }} , 
 	{ "name": "m_axi_INSTR_BUS_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_INSTR_BUS_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_INSTR_BUS_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "AWPROT" }} , 
 	{ "name": "m_axi_INSTR_BUS_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "AWQOS" }} , 
 	{ "name": "m_axi_INSTR_BUS_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "AWREGION" }} , 
 	{ "name": "m_axi_INSTR_BUS_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "AWUSER" }} , 
 	{ "name": "m_axi_INSTR_BUS_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "WVALID" }} , 
 	{ "name": "m_axi_INSTR_BUS_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "WREADY" }} , 
 	{ "name": "m_axi_INSTR_BUS_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "WDATA" }} , 
 	{ "name": "m_axi_INSTR_BUS_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "WSTRB" }} , 
 	{ "name": "m_axi_INSTR_BUS_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "WLAST" }} , 
 	{ "name": "m_axi_INSTR_BUS_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "WID" }} , 
 	{ "name": "m_axi_INSTR_BUS_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "WUSER" }} , 
 	{ "name": "m_axi_INSTR_BUS_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "ARVALID" }} , 
 	{ "name": "m_axi_INSTR_BUS_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "ARREADY" }} , 
 	{ "name": "m_axi_INSTR_BUS_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "ARADDR" }} , 
 	{ "name": "m_axi_INSTR_BUS_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "ARID" }} , 
 	{ "name": "m_axi_INSTR_BUS_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "ARLEN" }} , 
 	{ "name": "m_axi_INSTR_BUS_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_INSTR_BUS_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "ARBURST" }} , 
 	{ "name": "m_axi_INSTR_BUS_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_INSTR_BUS_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_INSTR_BUS_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "ARPROT" }} , 
 	{ "name": "m_axi_INSTR_BUS_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "ARQOS" }} , 
 	{ "name": "m_axi_INSTR_BUS_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "ARREGION" }} , 
 	{ "name": "m_axi_INSTR_BUS_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "ARUSER" }} , 
 	{ "name": "m_axi_INSTR_BUS_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "RVALID" }} , 
 	{ "name": "m_axi_INSTR_BUS_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "RREADY" }} , 
 	{ "name": "m_axi_INSTR_BUS_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "RDATA" }} , 
 	{ "name": "m_axi_INSTR_BUS_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "RLAST" }} , 
 	{ "name": "m_axi_INSTR_BUS_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "RID" }} , 
 	{ "name": "m_axi_INSTR_BUS_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "RUSER" }} , 
 	{ "name": "m_axi_INSTR_BUS_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "RRESP" }} , 
 	{ "name": "m_axi_INSTR_BUS_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "BVALID" }} , 
 	{ "name": "m_axi_INSTR_BUS_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "BREADY" }} , 
 	{ "name": "m_axi_INSTR_BUS_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "BRESP" }} , 
 	{ "name": "m_axi_INSTR_BUS_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "BID" }} , 
 	{ "name": "m_axi_INSTR_BUS_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "INSTR_BUS", "role": "BUSER" }} , 
 	{ "name": "m_axi_DATA_BUS_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "AWVALID" }} , 
 	{ "name": "m_axi_DATA_BUS_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "AWREADY" }} , 
 	{ "name": "m_axi_DATA_BUS_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "AWADDR" }} , 
 	{ "name": "m_axi_DATA_BUS_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "AWID" }} , 
 	{ "name": "m_axi_DATA_BUS_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "AWLEN" }} , 
 	{ "name": "m_axi_DATA_BUS_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_DATA_BUS_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "AWBURST" }} , 
 	{ "name": "m_axi_DATA_BUS_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_DATA_BUS_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_DATA_BUS_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "AWPROT" }} , 
 	{ "name": "m_axi_DATA_BUS_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "AWQOS" }} , 
 	{ "name": "m_axi_DATA_BUS_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "AWREGION" }} , 
 	{ "name": "m_axi_DATA_BUS_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "AWUSER" }} , 
 	{ "name": "m_axi_DATA_BUS_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "WVALID" }} , 
 	{ "name": "m_axi_DATA_BUS_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "WREADY" }} , 
 	{ "name": "m_axi_DATA_BUS_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "WDATA" }} , 
 	{ "name": "m_axi_DATA_BUS_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "WSTRB" }} , 
 	{ "name": "m_axi_DATA_BUS_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "WLAST" }} , 
 	{ "name": "m_axi_DATA_BUS_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "WID" }} , 
 	{ "name": "m_axi_DATA_BUS_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "WUSER" }} , 
 	{ "name": "m_axi_DATA_BUS_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "ARVALID" }} , 
 	{ "name": "m_axi_DATA_BUS_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "ARREADY" }} , 
 	{ "name": "m_axi_DATA_BUS_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "ARADDR" }} , 
 	{ "name": "m_axi_DATA_BUS_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "ARID" }} , 
 	{ "name": "m_axi_DATA_BUS_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "ARLEN" }} , 
 	{ "name": "m_axi_DATA_BUS_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_DATA_BUS_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "ARBURST" }} , 
 	{ "name": "m_axi_DATA_BUS_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_DATA_BUS_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_DATA_BUS_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "ARPROT" }} , 
 	{ "name": "m_axi_DATA_BUS_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "ARQOS" }} , 
 	{ "name": "m_axi_DATA_BUS_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "ARREGION" }} , 
 	{ "name": "m_axi_DATA_BUS_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "ARUSER" }} , 
 	{ "name": "m_axi_DATA_BUS_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "RVALID" }} , 
 	{ "name": "m_axi_DATA_BUS_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "RREADY" }} , 
 	{ "name": "m_axi_DATA_BUS_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "RDATA" }} , 
 	{ "name": "m_axi_DATA_BUS_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "RLAST" }} , 
 	{ "name": "m_axi_DATA_BUS_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "RID" }} , 
 	{ "name": "m_axi_DATA_BUS_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "RUSER" }} , 
 	{ "name": "m_axi_DATA_BUS_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "RRESP" }} , 
 	{ "name": "m_axi_DATA_BUS_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "BVALID" }} , 
 	{ "name": "m_axi_DATA_BUS_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "BREADY" }} , 
 	{ "name": "m_axi_DATA_BUS_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "BRESP" }} , 
 	{ "name": "m_axi_DATA_BUS_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "BID" }} , 
 	{ "name": "m_axi_DATA_BUS_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "DATA_BUS", "role": "BUSER" }} , 
 	{ "name": "m_axi_REG_BUS_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "AWVALID" }} , 
 	{ "name": "m_axi_REG_BUS_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "AWREADY" }} , 
 	{ "name": "m_axi_REG_BUS_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "REG_BUS", "role": "AWADDR" }} , 
 	{ "name": "m_axi_REG_BUS_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "AWID" }} , 
 	{ "name": "m_axi_REG_BUS_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "REG_BUS", "role": "AWLEN" }} , 
 	{ "name": "m_axi_REG_BUS_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "REG_BUS", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_REG_BUS_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "REG_BUS", "role": "AWBURST" }} , 
 	{ "name": "m_axi_REG_BUS_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "REG_BUS", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_REG_BUS_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "REG_BUS", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_REG_BUS_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "REG_BUS", "role": "AWPROT" }} , 
 	{ "name": "m_axi_REG_BUS_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "REG_BUS", "role": "AWQOS" }} , 
 	{ "name": "m_axi_REG_BUS_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "REG_BUS", "role": "AWREGION" }} , 
 	{ "name": "m_axi_REG_BUS_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "AWUSER" }} , 
 	{ "name": "m_axi_REG_BUS_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "WVALID" }} , 
 	{ "name": "m_axi_REG_BUS_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "WREADY" }} , 
 	{ "name": "m_axi_REG_BUS_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "REG_BUS", "role": "WDATA" }} , 
 	{ "name": "m_axi_REG_BUS_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "REG_BUS", "role": "WSTRB" }} , 
 	{ "name": "m_axi_REG_BUS_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "WLAST" }} , 
 	{ "name": "m_axi_REG_BUS_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "WID" }} , 
 	{ "name": "m_axi_REG_BUS_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "WUSER" }} , 
 	{ "name": "m_axi_REG_BUS_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "ARVALID" }} , 
 	{ "name": "m_axi_REG_BUS_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "ARREADY" }} , 
 	{ "name": "m_axi_REG_BUS_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "REG_BUS", "role": "ARADDR" }} , 
 	{ "name": "m_axi_REG_BUS_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "ARID" }} , 
 	{ "name": "m_axi_REG_BUS_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "REG_BUS", "role": "ARLEN" }} , 
 	{ "name": "m_axi_REG_BUS_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "REG_BUS", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_REG_BUS_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "REG_BUS", "role": "ARBURST" }} , 
 	{ "name": "m_axi_REG_BUS_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "REG_BUS", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_REG_BUS_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "REG_BUS", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_REG_BUS_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "REG_BUS", "role": "ARPROT" }} , 
 	{ "name": "m_axi_REG_BUS_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "REG_BUS", "role": "ARQOS" }} , 
 	{ "name": "m_axi_REG_BUS_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "REG_BUS", "role": "ARREGION" }} , 
 	{ "name": "m_axi_REG_BUS_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "ARUSER" }} , 
 	{ "name": "m_axi_REG_BUS_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "RVALID" }} , 
 	{ "name": "m_axi_REG_BUS_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "RREADY" }} , 
 	{ "name": "m_axi_REG_BUS_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "REG_BUS", "role": "RDATA" }} , 
 	{ "name": "m_axi_REG_BUS_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "RLAST" }} , 
 	{ "name": "m_axi_REG_BUS_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "RID" }} , 
 	{ "name": "m_axi_REG_BUS_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "RUSER" }} , 
 	{ "name": "m_axi_REG_BUS_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "REG_BUS", "role": "RRESP" }} , 
 	{ "name": "m_axi_REG_BUS_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "BVALID" }} , 
 	{ "name": "m_axi_REG_BUS_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "BREADY" }} , 
 	{ "name": "m_axi_REG_BUS_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "REG_BUS", "role": "BRESP" }} , 
 	{ "name": "m_axi_REG_BUS_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "BID" }} , 
 	{ "name": "m_axi_REG_BUS_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "REG_BUS", "role": "BUSER" }} , 
 	{ "name": "step", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "step", "role": "default" }} , 
 	{ "name": "pc_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "pc_out", "role": "default" }} , 
 	{ "name": "pc_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "pc_out", "role": "ap_vld" }}  ]}

set ArgLastReadFirstWriteLatency {
	cortex_m0_top {
		INSTR_BUS {Type IO LastRead 77 FirstWrite 4}
		DATA_BUS {Type IO LastRead 37 FirstWrite -1}
		REG_BUS {Type IO LastRead 102 FirstWrite -1}
		instr_mem {Type I LastRead 0 FirstWrite -1}
		data_mem {Type I LastRead 0 FirstWrite -1}
		reg_out {Type I LastRead 0 FirstWrite -1}
		step {Type I LastRead 0 FirstWrite -1}
		pc_out {Type O LastRead -1 FirstWrite 84}
		init_done {Type IO LastRead -1 FirstWrite -1}
		core_regs_epsr {Type IO LastRead -1 FirstWrite -1}
		IF_pc {Type IO LastRead -1 FirstWrite -1}
		cycle {Type IO LastRead -1 FirstWrite -1}
		prev_step {Type IO LastRead -1 FirstWrite -1}
		core_regs_gpr {Type IO LastRead -1 FirstWrite -1}
		core_regs_msp {Type IO LastRead -1 FirstWrite -1}
		core_regs_lr {Type IO LastRead -1 FirstWrite -1}
		core_regs_pc {Type IO LastRead -1 FirstWrite -1}
		core_regs_apsr {Type IO LastRead -1 FirstWrite -1}
		ID_rs1 {Type IO LastRead -1 FirstWrite -1}
		ID_rs2 {Type IO LastRead -1 FirstWrite -1}
		EX_opcode {Type IO LastRead -1 FirstWrite -1}
		EX_alu_result {Type IO LastRead -1 FirstWrite -1}
		EX_rd {Type IO LastRead -1 FirstWrite -1}
		EX_cpsr {Type IO LastRead -1 FirstWrite -1}
		MEM_opcode {Type IO LastRead -1 FirstWrite -1}
		MEM_mem_data {Type IO LastRead -1 FirstWrite -1}
		MEM_rd {Type IO LastRead -1 FirstWrite -1}
		MEM_cpsr {Type IO LastRead -1 FirstWrite -1}
		WB_opcode {Type IO LastRead -1 FirstWrite -1}
		WB_write_data {Type IO LastRead -1 FirstWrite -1}
		WB_rd {Type IO LastRead -1 FirstWrite -1}
		WB_cpsr {Type IO LastRead -1 FirstWrite -1}
		EX_pc {Type IO LastRead -1 FirstWrite -1}
		EX_r_bit {Type IO LastRead -1 FirstWrite -1}
		WB_link {Type IO LastRead -1 FirstWrite -1}
		EX_link {Type IO LastRead -1 FirstWrite -1}
		EX_mem_size {Type IO LastRead -1 FirstWrite -1}
		ID_opcode {Type IO LastRead -1 FirstWrite -1}
		ID_pc {Type IO LastRead -1 FirstWrite -1}
		ID_r_bit {Type IO LastRead -1 FirstWrite -1}
		ID_condition {Type IO LastRead -1 FirstWrite -1}
		ID_immediate_flag {Type IO LastRead -1 FirstWrite -1}
		ID_imm_value {Type IO LastRead -1 FirstWrite -1}
		ID_reg_data2 {Type IO LastRead -1 FirstWrite -1}
		ID_rd {Type IO LastRead -1 FirstWrite -1}
		IF_instr {Type IO LastRead -1 FirstWrite -1}
		ID_instr {Type IO LastRead -1 FirstWrite -1}
		ID_reg_data1 {Type IO LastRead -1 FirstWrite -1}
		ID_cpsr {Type IO LastRead -1 FirstWrite -1}}
	cortex_m0_top_Pipeline_VITIS_LOOP_5_1 {
		core_regs_gpr {Type O LastRead -1 FirstWrite 1}}
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
		core_regs_apsr {Type I LastRead 2 FirstWrite -1}}
	cortex_m0_top_Pipeline_VITIS_LOOP_634_2 {
		sp_value_2 {Type I LastRead 0 FirstWrite -1}
		DATA_BUS {Type I LastRead 11 FirstWrite -1}
		empty {Type I LastRead 0 FirstWrite -1}
		data_mem {Type I LastRead 0 FirstWrite -1}
		address_4_out {Type O LastRead -1 FirstWrite 11}
		core_regs_gpr {Type O LastRead -1 FirstWrite 12}}
	cortex_m0_top_Pipeline_VITIS_LOOP_590_1 {
		start_addr {Type I LastRead 0 FirstWrite -1}
		INSTR_BUS {Type O LastRead 5 FirstWrite 4}
		empty {Type I LastRead 0 FirstWrite -1}
		instr_mem {Type I LastRead 0 FirstWrite -1}
		address_3_out {Type O LastRead -1 FirstWrite 8}
		core_regs_gpr {Type I LastRead 2 FirstWrite -1}}
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
		core_regs_apsr {Type IO LastRead 0 FirstWrite 0}}
	decode_thumb16_instruction {
		conv487 {Type I LastRead 0 FirstWrite -1}}
	extract_bits {
		value_r {Type I LastRead 1 FirstWrite -1}
		start_r {Type I LastRead 0 FirstWrite -1}
		end_r {Type I LastRead 1 FirstWrite -1}}
	extract_bits {
		value_r {Type I LastRead 1 FirstWrite -1}
		start_r {Type I LastRead 0 FirstWrite -1}
		end_r {Type I LastRead 1 FirstWrite -1}}
	extract_bits {
		value_r {Type I LastRead 1 FirstWrite -1}
		start_r {Type I LastRead 0 FirstWrite -1}
		end_r {Type I LastRead 1 FirstWrite -1}}
	extract_bits {
		value_r {Type I LastRead 1 FirstWrite -1}
		start_r {Type I LastRead 0 FirstWrite -1}
		end_r {Type I LastRead 1 FirstWrite -1}}
	extract_bits {
		value_r {Type I LastRead 1 FirstWrite -1}
		start_r {Type I LastRead 0 FirstWrite -1}
		end_r {Type I LastRead 1 FirstWrite -1}}
	extract_bits {
		value_r {Type I LastRead 1 FirstWrite -1}
		start_r {Type I LastRead 0 FirstWrite -1}
		end_r {Type I LastRead 1 FirstWrite -1}}
	extract_bits {
		value_r {Type I LastRead 1 FirstWrite -1}
		start_r {Type I LastRead 0 FirstWrite -1}
		end_r {Type I LastRead 1 FirstWrite -1}}
	cortex_m0_top_Pipeline_VITIS_LOOP_1038_3 {
		REG_BUS {Type O LastRead 4 FirstWrite 3}
		reg_out {Type I LastRead 0 FirstWrite -1}
		core_regs_gpr {Type I LastRead 1 FirstWrite -1}}
	cortex_m0_top_Pipeline_VITIS_LOOP_1047_4 {
		REG_BUS {Type I LastRead 10 FirstWrite -1}
		reg_out {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "2", "Max" : "198"}
	, {"Name" : "Interval", "Min" : "3", "Max" : "199"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	INSTR_BUS { m_axi {  { m_axi_INSTR_BUS_AWVALID VALID 1 1 }  { m_axi_INSTR_BUS_AWREADY READY 0 1 }  { m_axi_INSTR_BUS_AWADDR ADDR 1 64 }  { m_axi_INSTR_BUS_AWID ID 1 1 }  { m_axi_INSTR_BUS_AWLEN SIZE 1 8 }  { m_axi_INSTR_BUS_AWSIZE BURST 1 3 }  { m_axi_INSTR_BUS_AWBURST LOCK 1 2 }  { m_axi_INSTR_BUS_AWLOCK CACHE 1 2 }  { m_axi_INSTR_BUS_AWCACHE PROT 1 4 }  { m_axi_INSTR_BUS_AWPROT QOS 1 3 }  { m_axi_INSTR_BUS_AWQOS REGION 1 4 }  { m_axi_INSTR_BUS_AWREGION USER 1 4 }  { m_axi_INSTR_BUS_AWUSER DATA 1 1 }  { m_axi_INSTR_BUS_WVALID VALID 1 1 }  { m_axi_INSTR_BUS_WREADY READY 0 1 }  { m_axi_INSTR_BUS_WDATA FIFONUM 1 32 }  { m_axi_INSTR_BUS_WSTRB STRB 1 4 }  { m_axi_INSTR_BUS_WLAST LAST 1 1 }  { m_axi_INSTR_BUS_WID ID 1 1 }  { m_axi_INSTR_BUS_WUSER DATA 1 1 }  { m_axi_INSTR_BUS_ARVALID VALID 1 1 }  { m_axi_INSTR_BUS_ARREADY READY 0 1 }  { m_axi_INSTR_BUS_ARADDR ADDR 1 64 }  { m_axi_INSTR_BUS_ARID ID 1 1 }  { m_axi_INSTR_BUS_ARLEN SIZE 1 8 }  { m_axi_INSTR_BUS_ARSIZE BURST 1 3 }  { m_axi_INSTR_BUS_ARBURST LOCK 1 2 }  { m_axi_INSTR_BUS_ARLOCK CACHE 1 2 }  { m_axi_INSTR_BUS_ARCACHE PROT 1 4 }  { m_axi_INSTR_BUS_ARPROT QOS 1 3 }  { m_axi_INSTR_BUS_ARQOS REGION 1 4 }  { m_axi_INSTR_BUS_ARREGION USER 1 4 }  { m_axi_INSTR_BUS_ARUSER DATA 1 1 }  { m_axi_INSTR_BUS_RVALID VALID 0 1 }  { m_axi_INSTR_BUS_RREADY READY 1 1 }  { m_axi_INSTR_BUS_RDATA FIFONUM 0 32 }  { m_axi_INSTR_BUS_RLAST LAST 0 1 }  { m_axi_INSTR_BUS_RID ID 0 1 }  { m_axi_INSTR_BUS_RUSER DATA 0 1 }  { m_axi_INSTR_BUS_RRESP RESP 0 2 }  { m_axi_INSTR_BUS_BVALID VALID 0 1 }  { m_axi_INSTR_BUS_BREADY READY 1 1 }  { m_axi_INSTR_BUS_BRESP RESP 0 2 }  { m_axi_INSTR_BUS_BID ID 0 1 }  { m_axi_INSTR_BUS_BUSER DATA 0 1 } } }
	DATA_BUS { m_axi {  { m_axi_DATA_BUS_AWVALID VALID 1 1 }  { m_axi_DATA_BUS_AWREADY READY 0 1 }  { m_axi_DATA_BUS_AWADDR ADDR 1 64 }  { m_axi_DATA_BUS_AWID ID 1 1 }  { m_axi_DATA_BUS_AWLEN SIZE 1 8 }  { m_axi_DATA_BUS_AWSIZE BURST 1 3 }  { m_axi_DATA_BUS_AWBURST LOCK 1 2 }  { m_axi_DATA_BUS_AWLOCK CACHE 1 2 }  { m_axi_DATA_BUS_AWCACHE PROT 1 4 }  { m_axi_DATA_BUS_AWPROT QOS 1 3 }  { m_axi_DATA_BUS_AWQOS REGION 1 4 }  { m_axi_DATA_BUS_AWREGION USER 1 4 }  { m_axi_DATA_BUS_AWUSER DATA 1 1 }  { m_axi_DATA_BUS_WVALID VALID 1 1 }  { m_axi_DATA_BUS_WREADY READY 0 1 }  { m_axi_DATA_BUS_WDATA FIFONUM 1 32 }  { m_axi_DATA_BUS_WSTRB STRB 1 4 }  { m_axi_DATA_BUS_WLAST LAST 1 1 }  { m_axi_DATA_BUS_WID ID 1 1 }  { m_axi_DATA_BUS_WUSER DATA 1 1 }  { m_axi_DATA_BUS_ARVALID VALID 1 1 }  { m_axi_DATA_BUS_ARREADY READY 0 1 }  { m_axi_DATA_BUS_ARADDR ADDR 1 64 }  { m_axi_DATA_BUS_ARID ID 1 1 }  { m_axi_DATA_BUS_ARLEN SIZE 1 8 }  { m_axi_DATA_BUS_ARSIZE BURST 1 3 }  { m_axi_DATA_BUS_ARBURST LOCK 1 2 }  { m_axi_DATA_BUS_ARLOCK CACHE 1 2 }  { m_axi_DATA_BUS_ARCACHE PROT 1 4 }  { m_axi_DATA_BUS_ARPROT QOS 1 3 }  { m_axi_DATA_BUS_ARQOS REGION 1 4 }  { m_axi_DATA_BUS_ARREGION USER 1 4 }  { m_axi_DATA_BUS_ARUSER DATA 1 1 }  { m_axi_DATA_BUS_RVALID VALID 0 1 }  { m_axi_DATA_BUS_RREADY READY 1 1 }  { m_axi_DATA_BUS_RDATA FIFONUM 0 32 }  { m_axi_DATA_BUS_RLAST LAST 0 1 }  { m_axi_DATA_BUS_RID ID 0 1 }  { m_axi_DATA_BUS_RUSER DATA 0 1 }  { m_axi_DATA_BUS_RRESP RESP 0 2 }  { m_axi_DATA_BUS_BVALID VALID 0 1 }  { m_axi_DATA_BUS_BREADY READY 1 1 }  { m_axi_DATA_BUS_BRESP RESP 0 2 }  { m_axi_DATA_BUS_BID ID 0 1 }  { m_axi_DATA_BUS_BUSER DATA 0 1 } } }
	REG_BUS { m_axi {  { m_axi_REG_BUS_AWVALID VALID 1 1 }  { m_axi_REG_BUS_AWREADY READY 0 1 }  { m_axi_REG_BUS_AWADDR ADDR 1 64 }  { m_axi_REG_BUS_AWID ID 1 1 }  { m_axi_REG_BUS_AWLEN SIZE 1 8 }  { m_axi_REG_BUS_AWSIZE BURST 1 3 }  { m_axi_REG_BUS_AWBURST LOCK 1 2 }  { m_axi_REG_BUS_AWLOCK CACHE 1 2 }  { m_axi_REG_BUS_AWCACHE PROT 1 4 }  { m_axi_REG_BUS_AWPROT QOS 1 3 }  { m_axi_REG_BUS_AWQOS REGION 1 4 }  { m_axi_REG_BUS_AWREGION USER 1 4 }  { m_axi_REG_BUS_AWUSER DATA 1 1 }  { m_axi_REG_BUS_WVALID VALID 1 1 }  { m_axi_REG_BUS_WREADY READY 0 1 }  { m_axi_REG_BUS_WDATA FIFONUM 1 32 }  { m_axi_REG_BUS_WSTRB STRB 1 4 }  { m_axi_REG_BUS_WLAST LAST 1 1 }  { m_axi_REG_BUS_WID ID 1 1 }  { m_axi_REG_BUS_WUSER DATA 1 1 }  { m_axi_REG_BUS_ARVALID VALID 1 1 }  { m_axi_REG_BUS_ARREADY READY 0 1 }  { m_axi_REG_BUS_ARADDR ADDR 1 64 }  { m_axi_REG_BUS_ARID ID 1 1 }  { m_axi_REG_BUS_ARLEN SIZE 1 8 }  { m_axi_REG_BUS_ARSIZE BURST 1 3 }  { m_axi_REG_BUS_ARBURST LOCK 1 2 }  { m_axi_REG_BUS_ARLOCK CACHE 1 2 }  { m_axi_REG_BUS_ARCACHE PROT 1 4 }  { m_axi_REG_BUS_ARPROT QOS 1 3 }  { m_axi_REG_BUS_ARQOS REGION 1 4 }  { m_axi_REG_BUS_ARREGION USER 1 4 }  { m_axi_REG_BUS_ARUSER DATA 1 1 }  { m_axi_REG_BUS_RVALID VALID 0 1 }  { m_axi_REG_BUS_RREADY READY 1 1 }  { m_axi_REG_BUS_RDATA FIFONUM 0 32 }  { m_axi_REG_BUS_RLAST LAST 0 1 }  { m_axi_REG_BUS_RID ID 0 1 }  { m_axi_REG_BUS_RUSER DATA 0 1 }  { m_axi_REG_BUS_RRESP RESP 0 2 }  { m_axi_REG_BUS_BVALID VALID 0 1 }  { m_axi_REG_BUS_BREADY READY 1 1 }  { m_axi_REG_BUS_BRESP RESP 0 2 }  { m_axi_REG_BUS_BID ID 0 1 }  { m_axi_REG_BUS_BUSER DATA 0 1 } } }
	step { ap_none {  { step in_data 0 1 } } }
	pc_out { ap_vld {  { pc_out out_data 1 32 }  { pc_out_ap_vld out_vld 1 1 } } }
}

set maxi_interface_dict [dict create]
dict set maxi_interface_dict DATA_BUS { CHANNEL_NUM 0 BUNDLE DATA_BUS NUM_READ_OUTSTANDING 16 NUM_WRITE_OUTSTANDING 16 MAX_READ_BURST_LENGTH 16 MAX_WRITE_BURST_LENGTH 16 READ_WRITE_MODE READ_WRITE}
dict set maxi_interface_dict INSTR_BUS { CHANNEL_NUM 0 BUNDLE INSTR_BUS NUM_READ_OUTSTANDING 16 NUM_WRITE_OUTSTANDING 16 MAX_READ_BURST_LENGTH 16 MAX_WRITE_BURST_LENGTH 16 READ_WRITE_MODE READ_WRITE}
dict set maxi_interface_dict REG_BUS { CHANNEL_NUM 0 BUNDLE REG_BUS NUM_READ_OUTSTANDING 16 NUM_WRITE_OUTSTANDING 16 MAX_READ_BURST_LENGTH 16 MAX_WRITE_BURST_LENGTH 16 READ_WRITE_MODE READ_WRITE}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
	{ INSTR_BUS 1 }
	{ DATA_BUS 1 }
	{ REG_BUS 1 }
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
	{ INSTR_BUS 1 }
	{ DATA_BUS 1 }
	{ REG_BUS 1 }
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
