#############################################################
## PSX PMOD interface
#############################################################
##Pmod Header JB
set_property -dict { PACKAGE_PIN Y18 IOSTANDARD LVCMOS33 } [get_ports { s_pin_atn1_0 }];  #ATN1  ATN1
set_property -dict { PACKAGE_PIN Y19 IOSTANDARD LVCMOS33 } [get_ports { s_pin_atn2_0 }];  #ATN2  ATN2
set_property -dict { PACKAGE_PIN W18 IOSTANDARD LVCMOS33 } [get_ports { s_pin_cmd_0 }];   #LED   CMD
set_property -dict { PACKAGE_PIN W19 IOSTANDARD LVCMOS33 } [get_ports { s_pin_clk_0 }];   #N/C   CLOCK

##Pmod Header JC
set_property -dict { PACKAGE_PIN W14 IOSTANDARD LVCMOS33 } [get_ports { s_pin_ack_0 }];   #BTN   ACK
set_property -dict { PACKAGE_PIN Y14 IOSTANDARD LVCMOS33 } [get_ports { s_pin_data_0 }];  #PULSE DATA
#set_property -dict { PACKAGE_PIN T12 IOSTANDARD LVCMOS33 } [get_ports {  }]; #N/C   N/C
#set_property -dict { PACKAGE_PIN U12 IOSTANDARD LVCMOS33 } [get_ports {  }]; #N/C   N/C

#############################################################
## VGA Display Pins
#############################################################
set_property -dict { PACKAGE_PIN F19 IOSTANDARD LVCMOS33 } [get_ports { VGA_Output_0_red }];    # VGA Red
set_property -dict { PACKAGE_PIN F20 IOSTANDARD LVCMOS33 } [get_ports { VGA_Output_0_green }];  # VGA Green
set_property -dict { PACKAGE_PIN G19 IOSTANDARD LVCMOS33 } [get_ports { VGA_Output_0_blue }];   # VGA Blue
set_property -dict { PACKAGE_PIN P19 IOSTANDARD LVCMOS33 } [get_ports { VGA_Output_0_hsync }];  # VGA HSync
set_property -dict { PACKAGE_PIN R19 IOSTANDARD LVCMOS33 } [get_ports { VGA_Output_0_vsync }];  # VGA VSync
