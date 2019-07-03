.PHONY: project clean bitstream open_gui

PROJ_NAME=Game
TOP_LVL=$(PROJ_NAME)_wrapper
IMPL_DEF=vivado/$(PROJ_NAME).runs/impl_1/$(TOP_LVL).sysdef
HW_SPEC=sdk/$(TOP_LVL).hdf
SDK_HWPROJ=sdk/hw1

project: bd/$(PROJ_NAME).bxml ;

bitstream: project $(IMPL_DEF) ;

clean:
	git clean -fdX

open_gui: project
	vivado -mode gui vivado/$(PROJ_NAME).xpr

open_sdk: $(SDK_HWPROJ)
	xsdk -wait -workspace sdk

bd/$(PROJ_NAME).bxml:
	vivado -mode batch -source scripts/recreate_prj.tcl

$(IMPL_DEF):
	vivado -mode batch -source scripts/build_bitstream.tcl

$(HW_SPEC): $(IMPL_DEF)
	cp $(IMPL_DEF) $(HW_SPEC)

$(SDK_HWPROJ): $(HW_SPEC)
	xsdk -batch -source scripts/recreate_sdk_prj.tcl \
		sdk $(TOP_LVL).hdf ps7_cortexa9_0 freertos10_xilinx
