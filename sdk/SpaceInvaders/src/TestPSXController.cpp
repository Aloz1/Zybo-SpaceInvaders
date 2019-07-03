#include <stdint.h>
#include <xil_printf.h>
#include <sleep.h>

#include "xparameters.h" // Hardware Register locations etc.
#include "drivers/GIC.h"

//#define PSXInterfaceDataReg    (*(volatile uint32_t *) (XPAR_PMOD_PSX_0_S_AXI_BASEADDR+4))
//#define PSXInterfaceControlReg (*(volatile uint32_t *) (XPAR_PMOD_PSX_0_S_AXI_BASEADDR))

struct PSXRegs {
	uint32_t ctrl;
	uint32_t data;
};

#define select2         (1 << 31)
#define select1         (1 << 30)
#define start           (1 << 29)
#define clr_err         (1 << 28)
#define frameError      (1 << 2)
#define waitingForACK   (1 << 1)
#define busy            (1 << 0)

#define TX_LSB 24
#define RX_MASK ((1 << 8) - 1);

using PSX_Intr = GIC<XPAR_PS7_SCUGIC_0_DEVICE_ID>;

PSXRegs* const psx_regs = reinterpret_cast<PSXRegs*>(XPAR_PMOD_PSX_0_S_AXI_BASEADDR);

void waitUntilNotBusy() {
   uint32_t sav = 0;
   while (((sav = psx_regs->ctrl) & busy) != 0) {
	   asm("nop");
   }
}

void TxRx(uint8_t TxValue, uint8_t &RxValue ) {
   psx_regs->data = ((uint32_t)TxValue << TX_LSB);
   psx_regs->ctrl |= start;
   waitUntilNotBusy();
   RxValue = psx_regs->data & RX_MASK;
}

/*
int main() {
   uint8_t dummy, RxValue2, ControllerType, Buttons1,Buttons2,RJoyX,RJoyY,LJoyX,LJoyY;
   
   xil_printf("Starting\r\n");
   for(;;) {
      // Select the controller
      psx_regs->ctrl = select1;
      waitUntilNotBusy();
      
      // Start the controller
      TxRx(0x01, dummy);

      // Get button data
      TxRx(0x42, ControllerType); // 41 or 73
      TxRx(0xFF, RxValue2);       // 5A
      TxRx(0xFF, Buttons1);       // LEFT DOWN RGHT  UP  STRT JOYL JOYR SLCT
      TxRx(0xFF, Buttons2);       //  []    X    O    ^   R1   L1   R2   L2
      
      if (ControllerType == 0x73) { // read extended data from analogue controller
         TxRx(0xFF, RJoyX);       // Right Joy 0x00 = Left 0xFF = Right
         TxRx(0xFF, RJoyY);       // Right Joy 0x00 = Up   0xFF = Down
         TxRx(0xFF, LJoyX);       // Left  Joy 0x00 = Left 0xFF = Right
         TxRx(0xFF, LJoyY);       // Left  Joy 0x00 = Up   0xFF = Down
	 }
         
      // Deselect the controller
      psx_regs->ctrl &= ~(select1);
      
      // Report Controller data
      xil_printf("Rx values T=%x, A=%x, B1=%x, B2=%x", ControllerType, RxValue2, Buttons1, Buttons2);
      if (ControllerType != 0x73)
         xil_printf("\r\n");
      else
         xil_printf(", LJX=%d, LJY=%d, RJX=%d, RJY=%d\r\n", LJoyX, LJoyY, RJoyX, RJoyY);

      usleep(5000);
   }
   return 0;
}
*/
