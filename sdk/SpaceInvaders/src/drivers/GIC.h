/*
 * GCI.h
 *
 *  Created on: 26Mar.,2018
 *      Author: 2062674
 */

#ifndef SRC_GIC_H_
#define SRC_GIC_H_

#include "xil_exception.h"
#include "xscugic.h"

// A convenience template class for simplifying the interrupt setup process.
template <uint16_t Dev_ID>
class GIC {
    // Some required objects for managing interrupts
	static XScuGic_Config *gic_config;
	static XScuGic intr_ctrl;

public:
    // Initialization. Does all the hard stuff for us.
	static int init() {

		// Get config
		gic_config = XScuGic_LookupConfig(Dev_ID);
		if (gic_config == nullptr)
			return XST_FAILURE;

		// Initialize config
		if (XScuGic_CfgInitialize(&intr_ctrl, gic_config, gic_config->CpuBaseAddress) != XST_SUCCESS)
			return XST_FAILURE;

		// Do a self test
		if (XScuGic_SelfTest(&intr_ctrl) != XST_SUCCESS)
			return XST_FAILURE;

		// Connect interrupt handler for interrupt controller to hardware
		Xil_ExceptionRegisterHandler(
				XIL_EXCEPTION_ID_INT,
				(Xil_ExceptionHandler) XScuGic_InterruptHandler,
				&intr_ctrl);

        // We were sucessful
		return XST_SUCCESS;
	}

    // Attach the handler. Pass the interrupt ID to the handler when called.
	static int attach(const int intr_id, Xil_ExceptionHandler callback) {
		return XScuGic_Connect(&intr_ctrl, intr_id, callback, (void *)&intr_id);
	}

    // Detach the handler
	static void detach(const int intr_id) {
		XScuGic_Disconnect(&intr_ctrl, intr_id);
	}

    // Enable the interrupt
	static void enable(const int intr_id) {
		XScuGic_Enable(&intr_ctrl, intr_id);
	}
};

// Required...because templates
template <uint16_t Dev_ID>
XScuGic_Config *GIC<Dev_ID>::gic_config = nullptr;

// Required...because templates
template <uint16_t Dev_ID>
XScuGic GIC<Dev_ID>::intr_ctrl;

#endif /* SRC_GIC_H_ */
