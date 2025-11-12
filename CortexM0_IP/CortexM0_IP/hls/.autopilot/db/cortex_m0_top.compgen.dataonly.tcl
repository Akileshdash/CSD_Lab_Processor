# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_control {
instr_mem { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 16
	offset_end 27
}
data_mem { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 28
	offset_end 39
}
reg_out { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 40
	offset_end 51
}
}
dict set axilite_register_dict control $port_control


