# 
# Synthesis run script generated by Vivado
# 

set TIME_start [clock seconds] 
proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
set_param synth.incrementalSynthesisCache ./.Xil/Vivado-271709-desktop/incrSyn
set_msg_config -id {Synth 8-256} -limit 10000
set_msg_config -id {Synth 8-4480} -limit 1000
set_msg_config -id {Synth 8-638} -limit 10000
set_msg_config  -id {[Synth 8-5858]}  -new_severity {INFO} 
create_project -in_memory -part xc7k325tffg900-2

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_msg_config -source 4 -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property webtalk.parent_dir /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/ariane.cache/wt [current_project]
set_property parent.project_path /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/ariane.xpr [current_project]
set_property XPM_LIBRARIES {XPM_CDC XPM_FIFO XPM_MEMORY} [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property board_part digilentinc.com:genesys2:part0:1.1 [current_project]
set_property ip_output_repo /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/ariane.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
set_property include_dirs {
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/axi_sd_bridge/include
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/include
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/axi/include
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/register_interface/include
} [current_fileset]
read_verilog {
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/include/common_cells/registers.svh
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/genesysii.svh
}
set_property file_type "Verilog Header" [get_files /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/include/common_cells/registers.svh]
set_property is_global_include true [get_files /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/include/common_cells/registers.svh]
set_property file_type "Verilog Header" [get_files /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/genesysii.svh]
set_property is_global_include true [get_files /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/genesysii.svh]
read_verilog -library xil_defaultlib -sv {
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/cf_math_pkg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/addr_decode.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/include/cv64a6_imafdc_sv39_config_pkg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/include/riscv_pkg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/riscv-dbg/src/dm_pkg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/include/ariane_pkg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/alu.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/amo_buffer.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/apb_timer/apb_timer.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/register_interface/src/apb_to_reg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/axi/src/axi_pkg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/include/ariane_axi_pkg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/include/cvxif_pkg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/ariane.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/tb/ariane_soc_pkg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/tb/ariane_axi_soc_pkg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane_peripherals_xilinx.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/ariane_regfile_ff.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/axi2apb/src/axi2apb_64_32.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/axi_mem_if/src/axi2mem.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/axi_adapter.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/axi_slice/src/axi_ar_buffer.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/axi/src/axi_atop_filter.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/axi_slice/src/axi_aw_buffer.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/axi_slice/src/axi_b_buffer.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/axi/src/axi_demux.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/axi/src/axi_err_slv.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/axi/src/axi_id_prepend.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/include/axi_intf.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/clint/axi_lite_interface.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/axi/src/axi_mux.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/axi_slice/src/axi_r_buffer.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/src/axi_riscv_atomics/src/axi_res_tbl.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/src/axi_riscv_atomics/src/axi_riscv_amos.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/src/axi_riscv_atomics/src/axi_riscv_amos_alu.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/src/axi_riscv_atomics/src/axi_riscv_atomics.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/src/axi_riscv_atomics/src/axi_riscv_atomics_wrap.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/src/axi_riscv_atomics/src/axi_riscv_lrsc.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/axi_shim.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/axi_slice/src/axi_single_slice.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/axi_slice/src/axi_w_buffer.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/axi/src/axi_xbar.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/axis_gmii_rx.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/axis_gmii_tx.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/frontend/bht.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/bootrom/bootrom_32.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/bootrom/bootrom_64.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/branch_unit.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/frontend/btb.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/include/std_cache_pkg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cache_subsystem/cache_ctrl.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/cdc_2phase.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/clint/clint.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/src/tech_cells_generic/src/deprecated/cluster_clk_cells.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/commit_stage.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/compressed_decoder.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpu_div_sqrt_mvp/hdl/defs_div_sqrt_mvp.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpu_div_sqrt_mvp/hdl/control_mvp.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/controller.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/counter.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/csr_buffer.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/csr_regfile.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cva6.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/include/wt_cache_pkg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cache_subsystem/cva6_icache.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cache_subsystem/cva6_icache_axi_wrapper.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cvxif_example/include/cvxif_instr_pkg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cvxif_example/cvxif_example_coprocessor.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cvxif_fu.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/riscv-dbg/debug_rom/debug_rom.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/decoder.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/delta_counter.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpu_div_sqrt_mvp/hdl/div_sqrt_top_mvp.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/riscv-dbg/src/dm_csrs.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/riscv-dbg/src/dm_mem.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/riscv-dbg/src/dm_sba.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/riscv-dbg/src/dm_top.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/riscv-dbg/src/dmi_cdc.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/riscv-dbg/src/dmi_jtag.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/riscv-dbg/src/dmi_jtag_tap.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/dromajo_ram.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/dualmem_widen.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/dualmem_widen8.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/eth_mac_1g.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/eth_mac_1g_rgmii.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/eth_mac_1g_rgmii_fifo.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/ex_stage.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/exp_backoff.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/fan_ctrl.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/deprecated/fifo_v1.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/deprecated/fifo_v2.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/fifo_v3.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpnew_pkg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpnew_cast_multi.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpnew_classifier.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpnew_divsqrt_multi.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpnew_fma.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpnew_fma_multi.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpnew_noncomp.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpnew_opgroup_block.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpnew_opgroup_fmt_slice.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpnew_opgroup_multifmt_slice.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpnew_rounding.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpnew_top.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu_wrap.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/framing_top.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/frontend/frontend.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/id_stage.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/iddr.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cvxif_example/instr_decoder.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/frontend/instr_queue.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/instr_realign.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/frontend/instr_scan.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/issue_read_operands.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/issue_stage.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpu_div_sqrt_mvp/hdl/iteration_div_sqrt_mvp.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/lfsr.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/lfsr_8bit.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/load_store_unit.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/load_unit.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/lsu_bypass.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/lzc.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cache_subsystem/miss_handler.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/mmu_sv39/mmu.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/tb/common/mock_uart.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/mult.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/multiplier.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpu_div_sqrt_mvp/hdl/norm_div_sqrt_mvp.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpu_div_sqrt_mvp/hdl/nrbd_nrsc_mvp.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/oddr.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/perf_counters.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/rv_plic/rtl/plic_regmap.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/rv_plic/rtl/plic_top.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/pmp/src/pmp.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/pmp/src/pmp_entry.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/popcount.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/fpu/src/fpu_div_sqrt_mvp/hdl/preprocess_mvp.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/mmu_sv39/ptw.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/src/tech_cells_generic/src/deprecated/pulp_clk_cells.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/frontend/ras.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/re_name.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/register_interface/src/reg_intf.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/rgmii_core.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/rgmii_lfsr.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/rgmii_phy_if.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/rgmii_soc.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/rr_arb_tree.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/rstgen.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/rstgen_bypass.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/rv_plic/rtl/rv_plic_gateway.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/rv_plic/rtl/rv_plic_target.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/scoreboard.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/serdiv.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/shift_reg.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/spill_register.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/spill_register_flushable.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/local/util/sram.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane-ethernet/ssio_ddr_in.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cache_subsystem/std_cache_subsystem.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cache_subsystem/std_nbdcache.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/store_buffer.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/store_unit.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/stream_arbiter.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/stream_arbiter_flushable.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/stream_demux.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/stream_mux.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/stream_register.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cache_subsystem/tag_cmp.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/src/tech_cells_generic/src/rtl/tc_clk.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/src/tech_cells_generic/src/fpga/tc_sram_xilinx.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/local/util/tc_sram_xilinx_wrapper.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/apb_timer/timer.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/mmu_sv39/tlb.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/common/submodules/common_cells/src/unread.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cache_subsystem/wt_axi_adapter.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cache_subsystem/wt_cache_subsystem.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cache_subsystem/wt_dcache.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cache_subsystem/wt_dcache_ctrl.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cache_subsystem/wt_dcache_mem.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cache_subsystem/wt_dcache_missunit.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/core/cache_subsystem/wt_dcache_wbuffer.sv
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/ariane_xilinx.sv
}
read_vhdl -library xil_defaultlib {
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/apb_uart/src/apb_uart.vhd
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/apb_uart/src/slib_clock_div.vhd
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/apb_uart/src/slib_counter.vhd
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/apb_uart/src/slib_edge_detect.vhd
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/apb_uart/src/slib_fifo.vhd
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/apb_uart/src/slib_input_filter.vhd
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/apb_uart/src/slib_input_sync.vhd
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/apb_uart/src/slib_mv_filter.vhd
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/apb_uart/src/uart_baudgen.vhd
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/apb_uart/src/uart_interrupt.vhd
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/apb_uart/src/uart_receiver.vhd
  /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/src/apb_uart/src/uart_transmitter.vhd
}
read_ip -quiet /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_dwidth_converter_dm_master/xlnx_axi_dwidth_converter_dm_master.srcs/sources_1/ip/xlnx_axi_dwidth_converter_dm_master/xlnx_axi_dwidth_converter_dm_master.xci
set_property used_in_synthesis false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_dwidth_converter_dm_master/xlnx_axi_dwidth_converter_dm_master.srcs/sources_1/ip/xlnx_axi_dwidth_converter_dm_master/xlnx_axi_dwidth_converter_dm_master_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_dwidth_converter_dm_master/xlnx_axi_dwidth_converter_dm_master.srcs/sources_1/ip/xlnx_axi_dwidth_converter_dm_master/xlnx_axi_dwidth_converter_dm_master_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_dwidth_converter_dm_master/xlnx_axi_dwidth_converter_dm_master.srcs/sources_1/ip/xlnx_axi_dwidth_converter_dm_master/xlnx_axi_dwidth_converter_dm_master_ooc.xdc]

read_ip -quiet /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_dwidth_converter_dm_slave/xlnx_axi_dwidth_converter_dm_slave.srcs/sources_1/ip/xlnx_axi_dwidth_converter_dm_slave/xlnx_axi_dwidth_converter_dm_slave.xci
set_property used_in_synthesis false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_dwidth_converter_dm_slave/xlnx_axi_dwidth_converter_dm_slave.srcs/sources_1/ip/xlnx_axi_dwidth_converter_dm_slave/xlnx_axi_dwidth_converter_dm_slave_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_dwidth_converter_dm_slave/xlnx_axi_dwidth_converter_dm_slave.srcs/sources_1/ip/xlnx_axi_dwidth_converter_dm_slave/xlnx_axi_dwidth_converter_dm_slave_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_dwidth_converter_dm_slave/xlnx_axi_dwidth_converter_dm_slave.srcs/sources_1/ip/xlnx_axi_dwidth_converter_dm_slave/xlnx_axi_dwidth_converter_dm_slave_ooc.xdc]

read_ip -quiet /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_mig_7_ddr3/xlnx_mig_7_ddr3.srcs/sources_1/ip/xlnx_mig_7_ddr3/xlnx_mig_7_ddr3.xci
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_mig_7_ddr3/xlnx_mig_7_ddr3.srcs/sources_1/ip/xlnx_mig_7_ddr3/xlnx_mig_7_ddr3/user_design/constraints/xlnx_mig_7_ddr3_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_mig_7_ddr3/xlnx_mig_7_ddr3.srcs/sources_1/ip/xlnx_mig_7_ddr3/xlnx_mig_7_ddr3/user_design/constraints/xlnx_mig_7_ddr3.xdc]

read_ip -quiet /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_clk_gen/xlnx_clk_gen.srcs/sources_1/ip/xlnx_clk_gen/xlnx_clk_gen.xci
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_clk_gen/xlnx_clk_gen.srcs/sources_1/ip/xlnx_clk_gen/xlnx_clk_gen_board.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_clk_gen/xlnx_clk_gen.srcs/sources_1/ip/xlnx_clk_gen/xlnx_clk_gen.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_clk_gen/xlnx_clk_gen.srcs/sources_1/ip/xlnx_clk_gen/xlnx_clk_gen_ooc.xdc]

read_ip -quiet /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_clock_converter/xlnx_axi_clock_converter.srcs/sources_1/ip/xlnx_axi_clock_converter/xlnx_axi_clock_converter.xci
set_property used_in_synthesis false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_clock_converter/xlnx_axi_clock_converter.srcs/sources_1/ip/xlnx_axi_clock_converter/xlnx_axi_clock_converter_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_clock_converter/xlnx_axi_clock_converter.srcs/sources_1/ip/xlnx_axi_clock_converter/xlnx_axi_clock_converter_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_clock_converter/xlnx_axi_clock_converter.srcs/sources_1/ip/xlnx_axi_clock_converter/xlnx_axi_clock_converter_ooc.xdc]

read_ip -quiet /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_gpio/xlnx_axi_gpio.srcs/sources_1/ip/xlnx_axi_gpio/xlnx_axi_gpio.xci
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_gpio/xlnx_axi_gpio.srcs/sources_1/ip/xlnx_axi_gpio/xlnx_axi_gpio_board.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_gpio/xlnx_axi_gpio.srcs/sources_1/ip/xlnx_axi_gpio/xlnx_axi_gpio_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_gpio/xlnx_axi_gpio.srcs/sources_1/ip/xlnx_axi_gpio/xlnx_axi_gpio.xdc]

read_ip -quiet /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_dwidth_converter/xlnx_axi_dwidth_converter.srcs/sources_1/ip/xlnx_axi_dwidth_converter/xlnx_axi_dwidth_converter.xci
set_property used_in_synthesis false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_dwidth_converter/xlnx_axi_dwidth_converter.srcs/sources_1/ip/xlnx_axi_dwidth_converter/xlnx_axi_dwidth_converter_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_dwidth_converter/xlnx_axi_dwidth_converter.srcs/sources_1/ip/xlnx_axi_dwidth_converter/xlnx_axi_dwidth_converter_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_dwidth_converter/xlnx_axi_dwidth_converter.srcs/sources_1/ip/xlnx_axi_dwidth_converter/xlnx_axi_dwidth_converter_ooc.xdc]

read_ip -quiet /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_quad_spi/xlnx_axi_quad_spi.srcs/sources_1/ip/xlnx_axi_quad_spi/xlnx_axi_quad_spi.xci
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_quad_spi/xlnx_axi_quad_spi.srcs/sources_1/ip/xlnx_axi_quad_spi/xlnx_axi_quad_spi_board.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_quad_spi/xlnx_axi_quad_spi.srcs/sources_1/ip/xlnx_axi_quad_spi/xlnx_axi_quad_spi.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_quad_spi/xlnx_axi_quad_spi.srcs/sources_1/ip/xlnx_axi_quad_spi/xlnx_axi_quad_spi_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/xilinx/xlnx_axi_quad_spi/xlnx_axi_quad_spi.srcs/sources_1/ip/xlnx_axi_quad_spi/xlnx_axi_quad_spi_clocks.xdc]

# Mark all dcp files as not used in implementation to prevent them from being
# stitched into the results of this synthesis run. Any black boxes in the
# design are intentionally left as such for best results. Dcp files will be
# stitched into the design at a later time, either when this synthesis run is
# opened, or when it is stitched into a dependent implementation run.
foreach dcp [get_files -quiet -all -filter file_type=="Design\ Checkpoint"] {
  set_property used_in_implementation false $dcp
}
read_xdc /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/constraints/genesys-2.xdc
set_property used_in_implementation false [get_files /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/constraints/genesys-2.xdc]

read_xdc /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/constraints/ariane.xdc
set_property used_in_implementation false [get_files /home/dizzy/Documents/PHD/cva6_dir/cva6/corev_apu/fpga/constraints/ariane.xdc]

read_xdc dont_touch.xdc
set_property used_in_implementation false [get_files dont_touch.xdc]
set_param ips.enableIPCacheLiteLoad 1
close [open __synthesis_is_running__ w]

synth_design -top ariane_xilinx -part xc7k325tffg900-2 -retiming


# disable binary constraint mode for synth run checkpoints
set_param constraints.enableBinaryConstraints false
write_checkpoint -force -noxdef ariane_xilinx.dcp
create_report "synth_1_synth_report_utilization_0" "report_utilization -file ariane_xilinx_utilization_synth.rpt -pb ariane_xilinx_utilization_synth.pb"
file delete __synthesis_is_running__
close [open __synthesis_is_complete__ w]