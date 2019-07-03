/*
 * PSX_Task.cpp
 *
 *  Created on: 20May,2018
 *      Author: alastair
 */

#include "PSXReader.h"

// Constructor. Cast the given address to a pointer so we can use it for communications
PSXReader::PSXReader(const uint32_t psx_baseaddr) :
    psx_axi(reinterpret_cast<PSX_AXI*const>(psx_baseaddr))
{}

// Wait for the decoder to finish reading/writing the current command/data.
void PSXReader::wait_till_not_busy() {
    uint32_t sav = 0;
    while (((sav = psx_axi->ctrl) & busy) != 0) {}
}

// Transmit/receive the current command/data. Commands are
// predefined as an enum in the header.
bool PSXReader::tx_rx(PSX_cmd cmd, uint8_t *data) {
    // Write command to decoder
    psx_axi->data = ((uint32_t)cmd << TX_LSB);

    // Wait till decoder has finished.
    wait_till_not_busy();

    // If the caller has passed in a buffer, copy the PSX controllers response
    // into it.
    if (data != nullptr) *data = psx_axi->data & RX_MASK;

    // Return to the caller if we were sucessful or not.
    return (psx_axi->ctrl & frameError) == 0;
}

bool PSXReader::read(PSXData &data) {
	bool valid = true;

	// Select the controller
	psx_axi->ctrl = select1;
	wait_till_not_busy();

	// Start controller communications
	valid = valid && tx_rx(CMD_START);

	// Get controller type, and tell the controller to dump
    // button/analog stick state.
	valid = valid && tx_rx(CMD_DUMP, &data.psx_type);
	valid = valid && (data.psx_type == PSX_DIGITAL || data.psx_type == PSX_ANALOG_RED);

	// Send IDLE to the controller so that it can send back 0x52 (not sure why, possibly a
    // data level acknowledge to state that it will now start dumping).
	valid = valid && tx_rx(CMD_IDLE);

    // Buttons
	valid = valid && tx_rx(CMD_IDLE, &data.btns_1); // LEFT DOWN RGHT  UP  STRT JOYL JOYR SLCT
	valid = valid && tx_rx(CMD_IDLE, &data.btns_2); //  []    X    O    ^   R1   L1   R2   L2

    // If the controller indicated it was analog, we can read its analog data as well.
	if (data.psx_type == PSX_ANALOG_RED) {
		valid = valid && tx_rx(CMD_IDLE, &data.analog_r_x);  // Right Joy 0x00 = Left 0xFF = Right
		valid = valid && tx_rx(CMD_IDLE, &data.analog_r_y);  // Right Joy 0x00 = Up   0xFF = Down
		valid = valid && tx_rx(CMD_IDLE, &data.analog_l_x);  // Left  Joy 0x00 = Left 0xFF = Right
		valid = valid && tx_rx(CMD_IDLE, &data.analog_l_y);  // Left  Joy 0x00 = Up   0xFF = Down
	}

	// Deselect the controller
	psx_axi->ctrl &= ~(select1);

    // Let the caller know whether or not we were sucessful
	return valid;
}

