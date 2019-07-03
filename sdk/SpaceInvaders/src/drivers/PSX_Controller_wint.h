#ifndef _HEADER_PSX_CONTROLLER_H_
#define _HEADER_PSX_CONTROLLER_H_

#include <stdint.h>
//#include <xil_printf.h>
//#include <sleep.h>

#include "drivers/GIC.h"

//#define PSXInterfaceDataReg    (*(volatile uint32_t *) (XPAR_PMOD_PSX_0_S_AXI_BASEADDR+4))
//#define PSXInterfaceControlReg (*(volatile uint32_t *) (XPAR_PMOD_PSX_0_S_AXI_BASEADDR))



template <uint32_t PSX_ADDR>
class PSX {
	struct PSX_AXI {
		uint32_t ctrl;
		uint32_t data;
	};

	struct PSX_intr_AXI {
		uint32_t global_enable;
		uint32_t enable;
		uint32_t status;
		uint32_t acknowledge;
		uint32_t pending;
	};

	enum PSX_Type {
		PSX_DIGITAL_PAD = 0x41,
		PSX_ANALOG_RED  = 0x73
	};

	enum PSX_ReadState {
		IDLE,
		INIT,
		START_DUMP,
		DUMP,
		FINISHED
	};

	enum PSX_CMD {
		CMD_START = 0x1,
		CMD_DUMP  = 0x42,
		CMD_IDLE  = 0xff
	};

	const uint32_t TX_LSB    = 24;
	const uint32_t RX_MASK   = ((1 << 8) - 1);

	const uint32_t SELECT_2  = (1 << 31);
	const uint32_t SELECT_1  = (1 << 30);
	const uint32_t FRAME_ERR = (1 << 2);
	const uint32_t WAIT_ACK  = (1 << 1);
	const uint32_t BUSY      = (1 << 0);

	const uint8_t BUFF_LEN = 9;

	PSX_AXI* const psx_axi;
	PSX_Int_AXI* const psx_int_axi;
	PSX_ReadState read_state;

	bool running;
	bool is_valid;

	uint8_t buff_pos;
	uint8_t buffer[BUFF_LEN];

protected:
	inline void tx_cmd(PSX_CMD cmd) {
	   psx_regs->data = ((uint32_t)cmd << TX_LSB);
	}

	inline uint8_t rx_data() {
		return psx_regs->data & RX_MASK;
	}

public:
	PSX(const uint32_t PSX_ADDR, const uint32_t PSX_INTR_ADDR):
			psx_axi(reinterpret_cast<PSX_AXI*const>(PSX_INTR_ADDR)),
			psx_int_axi(reinterpret_cast<PSX_intr_AXI*const>(PSX_INTR_ADDR))
	{
		running = false;
		is_valid = false;
		buff_pos = 0;
		memset(buffer, 0xff, sizeof(uint8_t)*buff_pos);
		read_state = IDLE;
	}

	void start() {
		running = true;
	}

	void handle() {
		switch(read_state) {
			case IDLE: break;
			case INIT:
				tx_cmd(CMD_START);
				read_state = START_DUMP;
				break;

			case START_DUMP:
				buffer[buff_pos] = rx_data();
				buff_pos++;

				if((psx_axi->ctrl & FRAME_ERR) || !(buffer[0] == PSX_DIGITAL_PAD || buffer[0] == PSX_ANALOG_RED)) {
					is_valid = false;
					read_state = FINISHED;
				} else {
					tx_data(CMD_DUMP);
				}
				break;

			case DUMP:
				buffer[buff_pos] = rx_data();
				buff_pos++;

				if((psx_axi->ctrl & FRAME_ERR) || !(buffer[0] == PSX_DIGITAL_PAD || buffer[0] == PSX_ANALOG_RED)) {
					is_valid = false;
					read_state = FINISHED;
				} else {
					tx_data(CMD_DUMP);
				}
				break;

			case FINISHED:
				is_valid = true;
				running = false;
				break;
		}
	}
};


PSXRegs* const psx_regs = reinterpret_cast<PSXRegs*>(XPAR_PMOD_PSX_0_S_AXI_BASEADDR);

#endif
