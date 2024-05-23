	cd corev_apu/fpga/
    open_project ariane_test.xpr
	synth_design -mode out_of_context -flatten_hierarchy rebuilt -top alu
	report_utilization -force -hierarchical -file alu_metrics/[lindex $argv 0]_alu
	close_project
	quit