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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* Standard C includes */
#include <stdint.h>

/* Microchip library includes */
#include "system.h"

#include "usb.h"
#include "usb_device_hid.h"

/* Demo project includes */
#include "app_led_usb_status.h"
#include "app_device_keyboard.h"

#include "ringBuffer.h"

int main(void)
{
	OSCTUN = 0x9000;
	CLKDIVbits.RCDIV = 0b000;
//	REFOCONH = 500;
//	REFOCONL = 0x8006;

	ANSA = 0;
	ANSB = 0;

//Input PPS
	RPINR7bits.IC1R = 0x04;	//IC1 = RB4
//	RPINR18bits.U1RXR = 0x04;	//U1RX = RB4
	
	IC1TMR = 0;
	IC1CON1 =0x1c01; //IC1 use FOSC/2
	IC1CON2 =0x0000;
	while (IC1CON1bits.ICBNE) {IC1BUF;}
	
//	IPC0bits.IC1IP = 7;
	IFS0bits.IC1IF = 0;
	IEC0bits.IC1IE = 1;
	
	

//	//
//	OC6CON1 = 0x1c06;
//	OC6CON2 = 0x001f;
//	OC6RS = 286;
//	OC6R = OC6RS >> 2;
	

//	U1BRG = 127; //7812.5bps,Calculated by Fosc = 32MHz?
//	U1BRG = 255; //7812.5/2bps,Calculated by Fosc = 32MHz?
//	U1MODE = 0x8000;
//	U1STA = 0x1400;

//	MDCON = 0x8060; 
//	MDSRC = 0x0004;	//U1TX
//	MDCAR = 0x8009; //Low Carrier is OC6

//	RPOR1bits.RP2R = 27;	//RB2 = MDOUT
//	RPOR6bits.RP13R = 27;	//RB13 = MDOUT
//	RPOR7bits.RP14R = 3;	//RB14 = U1TX
//	RPOR7bits.RP15R = 27;	//RB15 = MDOUT
	
//	CNPU1bits.CN1PUE=1;
//	CNPD1bits.CN1PDE=0;
		
		LED_Enable(LED_D7);
//		LED_On(LED_D7);
		
	TRISB &= 0x1ffb;
//	LATBbits.LATB15 = 1;
//	while (1) {}

	SYSTEM_Initialize(SYSTEM_STATE_USB_START);

	USBDeviceInit();
	USBDeviceAttach();
	
	TRISBbits.TRISB14 = 1;
	CVRCON = 0x00c0;
	
	bufInit(&irRxBuffer, &irRxBuffer1[0]);

	while (1) {
		SYSTEM_Tasks();

#if defined(USB_POLLING)
		/* Check bus status and service USB interrupts.  Interrupt or polling
		 * method.  If using polling, must call this function periodically.
		 * This function will take care of processing and responding to SETUP
		 * transactions (such as during the enumeration process when you first
		 * plug in).  USB hosts require that USB devices should accept and
		 * process SETUP packets in a timely fashion.  Therefore, when using
		 * polling, this function should be called regularly (such as once every
		 * 1.8ms or faster** [see inline code comments in usb_device.c for
		 * explanation when "or faster" applies])  In most cases, the
		 * USBDeviceTasks() function does not take very long to execute
		 * (ex: <100 instruction cycles) before it returns. */
		USBDeviceTasks();
#endif

		/* Run the keyboard demo tasks. */
		APP_KeyboardTasks();
	}//end while
}//end main

/*******************************************************************************
 End of File
 */
