set SynModuleInfo {
  {SRCNAME cortex_m0_top_Pipeline_VITIS_LOOP_5_1 MODELNAME cortex_m0_top_Pipeline_VITIS_LOOP_5_1 RTLNAME cortex_m0_top_cortex_m0_top_Pipeline_VITIS_LOOP_5_1
    SUBMODULES {
      {MODELNAME cortex_m0_top_flow_control_loop_pipe_sequential_init RTLNAME cortex_m0_top_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME cortex_m0_top_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME detect_forwarding MODELNAME detect_forwarding RTLNAME cortex_m0_top_detect_forwarding
    SUBMODULES {
      {MODELNAME cortex_m0_top_sparsemux_11_4_32_1_1 RTLNAME cortex_m0_top_sparsemux_11_4_32_1_1 BINDTYPE op TYPE sparsemux IMPL onehotencoding_realdef}
      {MODELNAME cortex_m0_top_sparsemux_7_2_32_1_1 RTLNAME cortex_m0_top_sparsemux_7_2_32_1_1 BINDTYPE op TYPE sparsemux IMPL onehotencoding_realdef}
    }
  }
  {SRCNAME cortex_m0_top_Pipeline_VITIS_LOOP_634_2 MODELNAME cortex_m0_top_Pipeline_VITIS_LOOP_634_2 RTLNAME cortex_m0_top_cortex_m0_top_Pipeline_VITIS_LOOP_634_2}
  {SRCNAME cortex_m0_top_Pipeline_VITIS_LOOP_590_1 MODELNAME cortex_m0_top_Pipeline_VITIS_LOOP_590_1 RTLNAME cortex_m0_top_cortex_m0_top_Pipeline_VITIS_LOOP_590_1}
  {SRCNAME regfile_update_flags MODELNAME regfile_update_flags RTLNAME cortex_m0_top_regfile_update_flags}
  {SRCNAME execute MODELNAME execute RTLNAME cortex_m0_top_execute
    SUBMODULES {
      {MODELNAME cortex_m0_top_mul_32s_32s_32_5_1 RTLNAME cortex_m0_top_mul_32s_32s_32_5_1 BINDTYPE op TYPE mul IMPL auto LATENCY 4 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME extract_bits MODELNAME extract_bits RTLNAME cortex_m0_top_extract_bits}
  {SRCNAME decode_thumb16_instruction MODELNAME decode_thumb16_instruction RTLNAME cortex_m0_top_decode_thumb16_instruction}
  {SRCNAME cortex_m0_top_Pipeline_VITIS_LOOP_1038_3 MODELNAME cortex_m0_top_Pipeline_VITIS_LOOP_1038_3 RTLNAME cortex_m0_top_cortex_m0_top_Pipeline_VITIS_LOOP_1038_3}
  {SRCNAME cortex_m0_top_Pipeline_VITIS_LOOP_1047_4 MODELNAME cortex_m0_top_Pipeline_VITIS_LOOP_1047_4 RTLNAME cortex_m0_top_cortex_m0_top_Pipeline_VITIS_LOOP_1047_4}
  {SRCNAME cortex_m0_top MODELNAME cortex_m0_top RTLNAME cortex_m0_top IS_TOP 1
    SUBMODULES {
      {MODELNAME cortex_m0_top_sparsemux_11_4_16_1_1 RTLNAME cortex_m0_top_sparsemux_11_4_16_1_1 BINDTYPE op TYPE sparsemux IMPL onehotencoding_realdef}
      {MODELNAME cortex_m0_top_sparsemux_11_4_8_1_1 RTLNAME cortex_m0_top_sparsemux_11_4_8_1_1 BINDTYPE op TYPE sparsemux IMPL onehotencoding_realdef}
      {MODELNAME cortex_m0_top_core_regs_gpr_RAM_AUTO_1R1W RTLNAME cortex_m0_top_core_regs_gpr_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME cortex_m0_top_INSTR_BUS_m_axi RTLNAME cortex_m0_top_INSTR_BUS_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME cortex_m0_top_DATA_BUS_m_axi RTLNAME cortex_m0_top_DATA_BUS_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME cortex_m0_top_REG_BUS_m_axi RTLNAME cortex_m0_top_REG_BUS_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME cortex_m0_top_control_s_axi RTLNAME cortex_m0_top_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
