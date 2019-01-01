/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
 *******************************************************************************/

#include "system.h"
#include "usb.h"
#include "leds.h"
#include "buttons.h"
#include "../IR_format.h"
#include "ringBuffer.h"

/** CONFIGURATION Bits **********************************************/
// CONFIG4
#pragma config DSWDTPS = DSWDTPS1F      // Deep Sleep Watchdog Timer Postscale Select bits (1:68719476736 (25.7 Days))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select (DSWDT uses LPRC as reference clock)
#pragma config DSBOREN = OFF            // Deep Sleep BOR Enable bit (DSBOR Disabled)
#pragma config DSWDTEN = OFF            // Deep Sleep Watchdog Timer Enable (DSWDT Disabled)
#pragma config DSSWEN = OFF             // DSEN Bit Enable (Deep Sleep operation is always disabled)
#pragma config PLLDIV = DIVIDE2         // USB 96 MHz PLL Prescaler Select bits (Oscillator input divided by 1 (4 MHz input))
#pragma config I2C1SEL = DISABLE        // Alternate I2C1 enable bit (I2C1 uses SCL1 and SDA1 pins)
#pragma config IOL1WAY = OFF            // PPS IOLOCK Set Only Once Enable bit (The IOLOCK bit can be set and cleared using the unlock sequence)

// CONFIG3
#pragma config WPFP = WPFP127           // Write Protection Flash Page Segment Boundary (Page 127 (0x1FC00))
#pragma config SOSCSEL = ON             // SOSC Selection bits (SOSC circuit selected)
#pragma config WDTWIN = PS25_0          // Window Mode Watchdog Timer Window Width Select (Watch Dog Timer Window Width is 25 percent)
#pragma config PLLSS = PLL_FRC          // PLL Secondary Selection Configuration bit (PLL is fed by the on-chip Fast RC (FRC) oscillator)
#pragma config BOREN = ON               // Brown-out Reset Enable (Brown-out Reset Enable)
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable (Disabled)
#pragma config WPCFG = WPCFGDIS         // Write Protect Configuration Page Select (Disabled)
#pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select (Write Protect from WPFP to the last page of memory)

// CONFIG2
#pragma config POSCMD = NONE            // Primary Oscillator Select (Primary Oscillator Disabled)
#pragma config WDTCLK = LPRC            // WDT Clock Source Select bits (WDT uses LPRC)
#pragma config OSCIOFCN = ON            // OSCO Pin Configuration (OSCO/CLKO/RA3 functions as port I/O (RA3))
#pragma config FCKSM = CSECMD           // Clock Switching and Fail-Safe Clock Monitor Configuration bits (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)
#pragma config FNOSC = FRCPLL           // Initial Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
#pragma config ALTRB6 = APPEND          // Alternate RB6 pin function enable bit (Append the RP6/ASCL1/PMPD6 functions of RB6 to RA1 pin functions)
#pragma config ALTCMPI = CxINC_RB       // Alternate Comparator Input bit (C1INC is on RB13, C2INC is on RB9 and C3INC is on RA0)
#pragma config WDTCMX = WDTCLK          // WDT Clock Source Select bits (WDT clock source is determined by the WDTCLK Configuration bits)
#pragma config IESO = OFF               // Internal External Switchover (Disabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler Select (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler Ratio Select (1:128)
#pragma config WINDIS = OFF             // Windowed WDT Disable (Standard Watchdog Timer)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT disabled in hardware; SWDTEN bit disabled)
#pragma config ICS = PGx1               // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC1/PGED1)
#pragma config LPCFG = OFF              // Low power regulator control (Disabled - regardless of RETEN)
#pragma config GWRP = OFF               // General Segment Write Protect (Write to program memory allowed)
#pragma config GCP = OFF                // General Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (Disabled)

uint8_t bufferRX[20];

/*********************************************************************
 * Function: void SYSTEM_Initialize( SYSTEM_STATE state )
 *
 * Overview: Initializes the system.
 *
 * PreCondition: None
 *
 * Input:  SYSTEM_STATE - the state to initialize the system into
 *
 * Output: None
 *
 ********************************************************************/
void SYSTEM_Initialize(SYSTEM_STATE state)
{
	switch (state) {
	case SYSTEM_STATE_USB_START:
		//Make sure that the general purpose output driver multiplexed with
		//the VBUS pin is always consistently configured to be tri-stated in
		//USB applications, so as to avoid any possible contention with the host.
		//(ex: maintain TRISBbits.TRISB6 = 1 at all times).
		TRISBbits.TRISB6 = 1;

		LED_Enable(LED_USB_DEVICE_STATE);
		LED_Enable(LED_USB_DEVICE_HID_KEYBOARD_CAPS_LOCK);
		LED_Enable(LED_USB_DEVICE_HID_KEYBOARD_KANA);

		BUTTON_Enable(BUTTON_USB_DEVICE_HID_KEYBOARD_KEY);
		break;

	case SYSTEM_STATE_USB_SUSPEND:
		//If developing a bus powered USB device that needs to be USB compliant,
		//insert code here to reduce the I/O pin and microcontroller power consumption,
		//so that the total current is <2.5mA from the USB host's VBUS supply.
		//If developing a self powered application (or a bus powered device where
		//official USB compliance isn't critical), nothing strictly needs
		//to be done during USB suspend.

		USBSleepOnSuspend();
		break;

	case SYSTEM_STATE_USB_RESUME:
		//If you didn't change any I/O pin states prior to entry into suspend,
		//then nothing explicitly needs to be done here.  However, by the time
		//the firmware returns from this function, the full application should
		//be restored into effectively exactly the same state as the application
		//was in, prior to entering USB suspend.

		//Additionally, before returning from this function, make sure the microcontroller's
		//currently active clock settings are compatible with USB operation, including
		//taking into consideration all possible microcontroller features/effects
		//that can affect the oscillator settings (such as internal/external 
		//switchover (two speed start up), fail-safe clock monitor, PLL lock time,
		//external crystal/resonator startup time (if using a crystal/resonator),
		//etc.

		//Additionally, the official USB specifications dictate that USB devices
		//must become fully operational and ready for new host requests/normal 
		//USB communication after a 10ms "resume recovery interval" has elapsed.
		//In order to meet this timing requirement and avoid possible issues,
		//make sure that all necessary oscillator startup is complete and this
		//function has returned within less than this 10ms interval.

		break;

	default:
		break;
	}
}

#if defined(USB_INTERRUPT)

void __attribute__((interrupt, auto_psv)) _USB1Interrupt()
{
	USBDeviceTasks();
}
#endif

void __attribute__((interrupt, auto_psv)) _IC1Interrupt()
{
	static uint16_t old = 0;
	uint16_t new = 0;
	uint32_t diff = 0;

//	static uint8_t edgeN = 0;

	while (IC1CON1bits.ICBNE) {
		uint8_t data = -1;

		//		CVRCONbits.CVR = 31;
		new = IC1BUF;
		diff = new - old;
		diff = (uint32_t) diff * 56UL;

		//		if (diff < 32) {
		//			CVRCONbits.CVR = diff;
		//		}

		if (diff < ((IR_DATA(-1) + IR_DATA(0)) * 16000UL)) {
			//error too short
			data = -1;
//			edgeN = 0;
		} else if (diff < ((IR_DATA(0) + IR_DATA(1)) * 16000UL)) {
			data = 0;
		} else if (diff < ((IR_DATA(1) + IR_DATA(2)) * 16000UL)) {
			data = 1;
		} else if (diff < ((IR_DATA(2) + IR_DATA(3)) * 16000UL)) {
			data = 2;
		} else if (diff < ((IR_DATA(3) + IR_DATA(4)) * 16000UL)) {
			data = 3;
		} else if (diff < ((IR_DATA(4) + IR_DATA(5)) * 16000UL)) {
			data = 4;
		} else if (diff < ((IR_DATA(5) + IR_DATA(6)) * 16000UL)) {
			data = 5;
		} else if (diff < ((IR_DATA(6) + IR_DATA(7)) * 16000UL)) {
			data = 6;
		} else if (diff < ((IR_DATA(7) + IR_DATA(8)) * 16000UL)) {
			data = 7;
		} else if (diff < ((IR_START + IR_STOP) * 16000UL)) {
			//START
			data = 9;
//			edgeN = 1;
		} else {
			//STOP
			data = 10;
//			edgeN = 0;
		}
		bufWriteIntIC1(&irRxBuffer,data);

//		LATBbits.LATB15 = data & 1;
		old = new;
	}
	IFS0bits.IC1IF = 0;
}

