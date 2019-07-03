
#ifndef SRC_PSXREADER_H_
#define SRC_PSXREADER_H_

#include "../tasks/TaskCPP.h"

// Struct for holding PSX controller data. Additionally has
// inlined decode logic.
struct PSXData {
	uint8_t psx_type;
	uint8_t btns_1;
	uint8_t btns_2;
	uint8_t analog_r_x;
	uint8_t analog_r_y;
	uint8_t analog_l_x;
	uint8_t analog_l_y;

	inline bool btnSelect() { return (~btns_1 & (1 << 0)) != 0; }
	inline bool btnR3()     { return (~btns_1 & (1 << 1)) != 0; }
	inline bool btnL3()     { return (~btns_1 & (1 << 2)) != 0; }
	inline bool btnStart()  { return (~btns_1 & (1 << 3)) != 0; }
	inline bool btnUp()     { return (~btns_1 & (1 << 4)) != 0; }
	inline bool btnRight()  { return (~btns_1 & (1 << 5)) != 0; }
	inline bool btnDown()   { return (~btns_1 & (1 << 6)) != 0; }
	inline bool btnLeft()   { return (~btns_1 & (1 << 7)) != 0; }

	inline bool btnL2()     { return (~btns_2 & (1 << 0)) != 0; }
	inline bool btnR2()     { return (~btns_2 & (1 << 1)) != 0; }
	inline bool btnL1()     { return (~btns_2 & (1 << 2)) != 0; }
	inline bool btnR1()     { return (~btns_2 & (1 << 3)) != 0; }
	inline bool btnTri()    { return (~btns_2 & (1 << 4)) != 0; }
	inline bool btnCirc()   { return (~btns_2 & (1 << 5)) != 0; }
	inline bool btnEx()     { return (~btns_2 & (1 << 6)) != 0; }
	inline bool btnSqr()    { return (~btns_2 & (1 << 7)) != 0; }
};

class PSXReader {
    // Enum containing bit masks for decoder communications.
	enum PSX_bit_mask {
		busy          = (1 << 0),
		waitingForACK = (1 << 1),
		frameError    = (1 << 2),
		clr_err       = (1 << 28),
		start         = (1 << 29),
		select1       = (1 << 30),
		select2       = (1 << 31)
	};

    // Command constants for communicating with the PSX controller
	enum PSX_cmd {
		CMD_START = 0x1,
		CMD_DUMP  = 0x42,
		CMD_IDLE  = 0xff
	};

    // Different PSX controller types.
	enum PSX_Type {
		PSX_DIGITAL    = 0x41,
		PSX_ANALOG_RED = 0x73
	};

    // Proxy struct for talking to memory mapped decoder registers.
	struct PSX_AXI {
		uint32_t ctrl;
		uint32_t data;
	};

	static const uint32_t TX_LSB  = 24;
	static const uint32_t RX_MASK = ((1 << 8) - 1);

    // Pointer to axi comms register
	PSX_AXI *const psx_axi;

	void wait_till_not_busy();
	bool tx_rx(PSX_cmd cmd, uint8_t *data = nullptr);

public:
	PSXReader(const uint32_t psx_baseaddr);
	bool read(PSXData &data);
};

#endif
