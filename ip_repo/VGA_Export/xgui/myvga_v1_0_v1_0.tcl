# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0" -display_name {FrameBuffer}]
  set_property tooltip {FrameBuffer} ${Page_0}
  ipgui::add_param $IPINST -name "C_MEMSIZE" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_NUM_WE" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_PORT_AWIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_PORT_DWIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_S00_AXI_ADDR_WIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_S00_AXI_DATA_WIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_S00_AXI_FREQ_HZ" -parent ${Page_0}


}

proc update_PARAM_VALUE.C_MEMSIZE { PARAM_VALUE.C_MEMSIZE } {
	# Procedure called to update C_MEMSIZE when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_MEMSIZE { PARAM_VALUE.C_MEMSIZE } {
	# Procedure called to validate C_MEMSIZE
	return true
}

proc update_PARAM_VALUE.C_NUM_WE { PARAM_VALUE.C_NUM_WE } {
	# Procedure called to update C_NUM_WE when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_NUM_WE { PARAM_VALUE.C_NUM_WE } {
	# Procedure called to validate C_NUM_WE
	return true
}

proc update_PARAM_VALUE.C_PORT_AWIDTH { PARAM_VALUE.C_PORT_AWIDTH } {
	# Procedure called to update C_PORT_AWIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_PORT_AWIDTH { PARAM_VALUE.C_PORT_AWIDTH } {
	# Procedure called to validate C_PORT_AWIDTH
	return true
}

proc update_PARAM_VALUE.C_PORT_DWIDTH { PARAM_VALUE.C_PORT_DWIDTH } {
	# Procedure called to update C_PORT_DWIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_PORT_DWIDTH { PARAM_VALUE.C_PORT_DWIDTH } {
	# Procedure called to validate C_PORT_DWIDTH
	return true
}

proc update_PARAM_VALUE.C_S00_AXI_ADDR_WIDTH { PARAM_VALUE.C_S00_AXI_ADDR_WIDTH } {
	# Procedure called to update C_S00_AXI_ADDR_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S00_AXI_ADDR_WIDTH { PARAM_VALUE.C_S00_AXI_ADDR_WIDTH } {
	# Procedure called to validate C_S00_AXI_ADDR_WIDTH
	return true
}

proc update_PARAM_VALUE.C_S00_AXI_DATA_WIDTH { PARAM_VALUE.C_S00_AXI_DATA_WIDTH } {
	# Procedure called to update C_S00_AXI_DATA_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S00_AXI_DATA_WIDTH { PARAM_VALUE.C_S00_AXI_DATA_WIDTH } {
	# Procedure called to validate C_S00_AXI_DATA_WIDTH
	return true
}

proc update_PARAM_VALUE.C_S00_AXI_FREQ_HZ { PARAM_VALUE.C_S00_AXI_FREQ_HZ } {
	# Procedure called to update C_S00_AXI_FREQ_HZ when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S00_AXI_FREQ_HZ { PARAM_VALUE.C_S00_AXI_FREQ_HZ } {
	# Procedure called to validate C_S00_AXI_FREQ_HZ
	return true
}


proc update_MODELPARAM_VALUE.C_MEMSIZE { MODELPARAM_VALUE.C_MEMSIZE PARAM_VALUE.C_MEMSIZE } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_MEMSIZE}] ${MODELPARAM_VALUE.C_MEMSIZE}
}

proc update_MODELPARAM_VALUE.C_PORT_DWIDTH { MODELPARAM_VALUE.C_PORT_DWIDTH PARAM_VALUE.C_PORT_DWIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_PORT_DWIDTH}] ${MODELPARAM_VALUE.C_PORT_DWIDTH}
}

proc update_MODELPARAM_VALUE.C_PORT_AWIDTH { MODELPARAM_VALUE.C_PORT_AWIDTH PARAM_VALUE.C_PORT_AWIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_PORT_AWIDTH}] ${MODELPARAM_VALUE.C_PORT_AWIDTH}
}

proc update_MODELPARAM_VALUE.C_NUM_WE { MODELPARAM_VALUE.C_NUM_WE PARAM_VALUE.C_NUM_WE } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_NUM_WE}] ${MODELPARAM_VALUE.C_NUM_WE}
}

proc update_MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH { MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH PARAM_VALUE.C_S00_AXI_DATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S00_AXI_DATA_WIDTH}] ${MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH}
}

proc update_MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH { MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH PARAM_VALUE.C_S00_AXI_ADDR_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S00_AXI_ADDR_WIDTH}] ${MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH}
}

proc update_MODELPARAM_VALUE.C_S00_AXI_FREQ_HZ { MODELPARAM_VALUE.C_S00_AXI_FREQ_HZ PARAM_VALUE.C_S00_AXI_FREQ_HZ } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S00_AXI_FREQ_HZ}] ${MODELPARAM_VALUE.C_S00_AXI_FREQ_HZ}
}

