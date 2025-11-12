set ModuleHierarchy {[{
"Name" : "cortex_m0_top", "RefName" : "cortex_m0_top","ID" : "0","Type" : "sequential",
"SubInsts" : [
	{"Name" : "grp_cortex_m0_top_Pipeline_VITIS_LOOP_5_1_fu_2046", "RefName" : "cortex_m0_top_Pipeline_VITIS_LOOP_5_1","ID" : "1","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_5_1","RefName" : "VITIS_LOOP_5_1","ID" : "2","Type" : "pipeline"},]},
	{"Name" : "grp_detect_forwarding_fu_2052", "RefName" : "detect_forwarding","ID" : "3","Type" : "sequential"},
	{"Name" : "grp_cortex_m0_top_Pipeline_VITIS_LOOP_634_2_fu_2080", "RefName" : "cortex_m0_top_Pipeline_VITIS_LOOP_634_2","ID" : "4","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_634_2","RefName" : "VITIS_LOOP_634_2","ID" : "5","Type" : "pipeline"},]},
	{"Name" : "grp_cortex_m0_top_Pipeline_VITIS_LOOP_590_1_fu_2092", "RefName" : "cortex_m0_top_Pipeline_VITIS_LOOP_590_1","ID" : "6","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_590_1","RefName" : "VITIS_LOOP_590_1","ID" : "7","Type" : "pipeline"},]},
	{"Name" : "grp_execute_fu_2104", "RefName" : "execute","ID" : "8","Type" : "sequential",
		"SubInsts" : [
		{"Name" : "call_ln736_regfile_update_flags_fu_2091", "RefName" : "regfile_update_flags","ID" : "9","Type" : "sequential"},
		{"Name" : "call_ln721_regfile_update_flags_fu_2114", "RefName" : "regfile_update_flags","ID" : "10","Type" : "sequential"},
		{"Name" : "call_ln704_regfile_update_flags_fu_2129", "RefName" : "regfile_update_flags","ID" : "11","Type" : "sequential"},
		{"Name" : "call_ln695_regfile_update_flags_fu_2144", "RefName" : "regfile_update_flags","ID" : "12","Type" : "sequential"},
		{"Name" : "call_ln686_regfile_update_flags_fu_2159", "RefName" : "regfile_update_flags","ID" : "13","Type" : "sequential"},
		{"Name" : "call_ln678_regfile_update_flags_fu_2174", "RefName" : "regfile_update_flags","ID" : "14","Type" : "sequential"},
		{"Name" : "call_ln747_regfile_update_flags_fu_2202", "RefName" : "regfile_update_flags","ID" : "15","Type" : "sequential"},
		{"Name" : "call_ln341_regfile_update_flags_fu_2916", "RefName" : "regfile_update_flags","ID" : "16","Type" : "sequential"},
		{"Name" : "call_ln334_regfile_update_flags_fu_2943", "RefName" : "regfile_update_flags","ID" : "17","Type" : "sequential"},
		{"Name" : "call_ln327_regfile_update_flags_fu_2954", "RefName" : "regfile_update_flags","ID" : "18","Type" : "sequential"},
		{"Name" : "call_ln322_regfile_update_flags_fu_2973", "RefName" : "regfile_update_flags","ID" : "19","Type" : "sequential"},
		{"Name" : "call_ln311_regfile_update_flags_fu_2984", "RefName" : "regfile_update_flags","ID" : "20","Type" : "sequential"},
		{"Name" : "call_ln304_regfile_update_flags_fu_2995", "RefName" : "regfile_update_flags","ID" : "21","Type" : "sequential"},
		{"Name" : "call_ln296_regfile_update_flags_fu_3036", "RefName" : "regfile_update_flags","ID" : "22","Type" : "sequential"},
		{"Name" : "call_ln220_regfile_update_flags_fu_3251", "RefName" : "regfile_update_flags","ID" : "23","Type" : "sequential"},
		{"Name" : "call_ln208_regfile_update_flags_fu_3262", "RefName" : "regfile_update_flags","ID" : "24","Type" : "sequential"},
		{"Name" : "call_ln202_regfile_update_flags_fu_3306", "RefName" : "regfile_update_flags","ID" : "25","Type" : "sequential"},
		{"Name" : "call_ln195_regfile_update_flags_fu_3317", "RefName" : "regfile_update_flags","ID" : "26","Type" : "sequential"},
		{"Name" : "call_ln188_regfile_update_flags_fu_3328", "RefName" : "regfile_update_flags","ID" : "27","Type" : "sequential"},
		{"Name" : "call_ln181_regfile_update_flags_fu_3339", "RefName" : "regfile_update_flags","ID" : "28","Type" : "sequential"},
		{"Name" : "call_ln174_regfile_update_flags_fu_3350", "RefName" : "regfile_update_flags","ID" : "29","Type" : "sequential"},
		{"Name" : "call_ln163_regfile_update_flags_fu_3361", "RefName" : "regfile_update_flags","ID" : "30","Type" : "sequential"},
		{"Name" : "call_ln153_regfile_update_flags_fu_3436", "RefName" : "regfile_update_flags","ID" : "31","Type" : "sequential"},
		{"Name" : "call_ln137_regfile_update_flags_fu_3468", "RefName" : "regfile_update_flags","ID" : "32","Type" : "sequential"},
		{"Name" : "call_ln120_regfile_update_flags_fu_3532", "RefName" : "regfile_update_flags","ID" : "33","Type" : "sequential"},
		{"Name" : "call_ln27_regfile_update_flags_fu_3607", "RefName" : "regfile_update_flags","ID" : "34","Type" : "sequential"},]},
	{"Name" : "grp_decode_thumb16_instruction_fu_2118", "RefName" : "decode_thumb16_instruction","ID" : "35","Type" : "sequential",
		"SubInsts" : [
		{"Name" : "grp_extract_bits_fu_2302", "RefName" : "extract_bits","ID" : "36","Type" : "sequential"},
		{"Name" : "grp_extract_bits_fu_2312", "RefName" : "extract_bits","ID" : "37","Type" : "sequential"},
		{"Name" : "grp_extract_bits_fu_2322", "RefName" : "extract_bits","ID" : "38","Type" : "sequential"},
		{"Name" : "grp_extract_bits_fu_2332", "RefName" : "extract_bits","ID" : "39","Type" : "sequential"},
		{"Name" : "grp_extract_bits_fu_2342", "RefName" : "extract_bits","ID" : "40","Type" : "sequential"},
		{"Name" : "grp_extract_bits_fu_2352", "RefName" : "extract_bits","ID" : "41","Type" : "sequential"},
		{"Name" : "grp_extract_bits_fu_2362", "RefName" : "extract_bits","ID" : "42","Type" : "sequential"},]},
	{"Name" : "grp_cortex_m0_top_Pipeline_VITIS_LOOP_1038_3_fu_2123", "RefName" : "cortex_m0_top_Pipeline_VITIS_LOOP_1038_3","ID" : "43","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_1038_3","RefName" : "VITIS_LOOP_1038_3","ID" : "44","Type" : "pipeline"},]},
	{"Name" : "grp_cortex_m0_top_Pipeline_VITIS_LOOP_1047_4_fu_2132", "RefName" : "cortex_m0_top_Pipeline_VITIS_LOOP_1047_4","ID" : "45","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_1047_4","RefName" : "VITIS_LOOP_1047_4","ID" : "46","Type" : "pipeline"},]},]
}]}