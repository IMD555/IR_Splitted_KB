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
#include <stdint.h>
#include <string.h>

#include "system.h"
#include "usb.h"
#include "usb_device_hid.h"

#include "app_led_usb_status.h"
#include "HID_Define.h"
#include "ringBuffer.h"
#include "swMatrix.h"
#include "../IR_format.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Constants
// *****************************************************************************
// *****************************************************************************

//Class specific descriptor - HID Keyboard

const struct {
	uint8_t report[HID_RPT01_SIZE];
} hid_rpt01 = {
	{
		0x05, 0x01, // USAGE_PAGE (Generic Desktop)
		0x09, 0x06, // USAGE (Keyboard)
		0xa1, 0x01, // COLLECTION (Application)
		0x85, 0x01, //   Report ID (1)

		0x05, 0x07, //   USAGE_PAGE (Keyboard)
		0x19, 0xe0, //   USAGE_MINIMUM (Keyboard LeftControl)
		0x29, 0xe7, //   USAGE_MAXIMUM (Keyboard Right GUI)
		0x15, 0x00, //   LOGICAL_MINIMUM (0)
		0x25, 0x01, //   LOGICAL_MAXIMUM (1)
		0x75, 0x01, //   REPORT_SIZE (1)
		0x95, 0x08, //   REPORT_COUNT (8)
		0x81, 0x02, //   INPUT (Data,Var,Abs)
		0x95, 0x01, //   REPORT_COUNT (1)
		0x75, 0x08, //   REPORT_SIZE (8)
		0x81, 0x03, //   INPUT (Cnst,Var,Abs)

		0x95, 0x06, //   REPORT_COUNT (6)
		0x75, 0x01, //   REPORT_SIZE (1)
		0x05, 0x08, //   USAGE_PAGE (LEDs)
		0x09, 0x01, //   Usage (Num Lock)
		0x09, 0x02, //   Usage (Mute)
		0x09, 0x03, //   Usage (Mute)
		0x09, 0x06, //   Usage (Mute)
		0x09, 0x07, //   Usage (Mute)
		0x09, 0x09, //   Usage (Mute)
		0x91, 0x02, //   OUTPUT (Data,Var,Abs)
		0x95, 0x01, //   REPORT_COUNT (1)
		0x75, 0x02, //   REPORT_SIZE (2)
		0x91, 0x03, //   OUTPUT (Cnst,Var,Abs)

		0x95, 0x06, //   REPORT_COUNT (6)
		0x75, 0x08, //   REPORT_SIZE (8)
		0x15, 0x00, //   LOGICAL_MINIMUM (0)
		//		0x25, 0x65, //   LOGICAL_MAXIMUM (101)
		0x25, 0xdd, //   LOGICAL_MAXIMUM (???)
		0x05, 0x07, //   USAGE_PAGE (Keyboard)
		0x19, 0x00, //   USAGE_MINIMUM (Reserved (no event indicated))
		//		0x29, 0x65, //   USAGE_MAXIMUM (Keyboard Application)
		0x29, 0xdd, //   USAGE_MAXIMUM (???)
		0x81, 0x00, //   INPUT (Data,Ary,Abs)
		0xc0, // End Collection

		0x05, 0x0C, // Usage Page (Consumer)
		0x09, 0x01, // Usage (Consumer Control)
		0xA1, 0x01, // Collection (Application)
		0x85, 0x02, //   Report ID (2)
		0x05, 0x0C, //   Usage Page (Consumer)
		0x15, 0x00, //   Logical Minimum (0)
		0x25, 0x01, //   Logical Maximum (1)
		0x95, 0x01, //   REPORT_COUNT (1)
		0x75, 0x04, //   REPORT_SIZE (4)
		0x81, 0x03, //   INPUT (Cnst,Var,Abs)
		0x75, 0x01, //   Report Size (1)
		0x95, 0x0a, //   Report Count (10)
		0x09, 0xE9, //   Usage (Volume Increment)
		0x09, 0xEA, //   Usage (Volume Decrement)
		0x09, 0xE2, //   Usage (Mute)
		0x09, 0xCD, //   Usage (Play/Pause)
		0x09, 0xB5, //   Usage (Scan Next Track)
		0x09, 0xB6, //   Usage (Scan Previous Track)
		0x09, 0xB7, //   Usage (Stop)
		0x09, 0xB8, //   Usage (Eject)
		0x09, 0xB3, //   Usage (Fast forward)
		0x09, 0xB4, //   Usage (Rewind)
		0x81, 0x02, //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0x95, 0x01, //   REPORT_COUNT (1)
		0x75, 0x02, //   REPORT_SIZE (2)
		0x81, 0x03, //   INPUT (Cnst,Var,Abs)
		0xC0, // End Collection
	}
};


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Data Types
// *****************************************************************************
// *****************************************************************************


/* This creates a storage type for all of the information required to track the
 * current state of the keyboard. */
typedef struct {
	USB_HANDLE lastINTransmission;
	USB_HANDLE lastOUTTransmission;
	//	unsigned char key;
	//	bool waitingForRelease;
} KEYBOARD;

// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Variables
// *****************************************************************************
// *****************************************************************************
static KEYBOARD keyboard;

#if !defined(KEYBOARD_INPUT_REPORT_DATA_BUFFER_ADDRESS_TAG)
#define KEYBOARD_INPUT_REPORT_DATA_BUFFER_ADDRESS_TAG
#endif
KEYBOARD_INPUT_REPORT inputReport KEYBOARD_INPUT_REPORT_DATA_BUFFER_ADDRESS_TAG;

#if !defined(KEYBOARD_OUTPUT_REPORT_DATA_BUFFER_ADDRESS_TAG)
#define KEYBOARD_OUTPUT_REPORT_DATA_BUFFER_ADDRESS_TAG
#endif
 KEYBOARD_OUTPUT_REPORT outputReport KEYBOARD_OUTPUT_REPORT_DATA_BUFFER_ADDRESS_TAG;

#if !defined(COMSUMER_INPUT_REPORT_DATA_BUFFER_ADDRESS_TAG)
#define COMSUMER_INPUT_REPORT_DATA_BUFFER_ADDRESS_TAG
#endif
COMSUMER_INPUT_REPORT inputComsumerReport COMSUMER_INPUT_REPORT_DATA_BUFFER_ADDRESS_TAG;

#define WAITUSBTX			{keyboard.lastINTransmission = HIDTxPacket(HID_EP, (uint8_t*) & inputReport, sizeof (inputReport)); 			while (HIDTxHandleBusy(keyboard.lastINTransmission));}

// *****************************************************************************
// *****************************************************************************
// Section: Private Prototypes
// *****************************************************************************
// *****************************************************************************
static void APP_KeyboardProcessOutputReport(void);


//Exteranl variables declared in other .c files
extern volatile signed int SOFCounter;

extern uint8_t sendDreqFlag ;

//Application variables that need wide scope
signed int keyboardIdleRate;
signed int LocalSOFCount;
static signed int OldSOFCount;




// *****************************************************************************
// *****************************************************************************
// Section: Macros or Functions
// *****************************************************************************
// *****************************************************************************

void APP_KeyboardInit(void)
{
	//initialize the variable holding the handle for the last
	// transmission
	keyboard.lastINTransmission = 0;

	//	keyboard.key = 4;
	//	keyboard.waitingForRelease = false;

	//Set the default idle rate to 500ms (until the host sends a SET_IDLE request to change it to a new value)
	keyboardIdleRate = 500;

	//Copy the (possibly) interrupt context SOFCounter value into a local variable.
	//Using a while() loop to do this since the SOFCounter isn't necessarily atomically
	//updated and therefore we need to read it a minimum of twice to ensure we captured the correct value.
	while (OldSOFCount != SOFCounter) {
		OldSOFCount = SOFCounter;
	}

	//enable the HID endpoint
	USBEnableEndpoint(HID_EP, USB_IN_ENABLED | USB_OUT_ENABLED | USB_HANDSHAKE_ENABLED | USB_DISALLOW_SETUP);

	//Arm OUT endpoint so we can receive caps lock, num lock, etc. info from host
	keyboard.lastOUTTransmission = HIDRxPacket(HID_EP, (uint8_t*) & outputReport, sizeof (outputReport));
	swInit();
}

void APP_KeyboardTasks(void)
{
		return;
	
	
//	CVRCONbits.CVR = 20;
	static KEYBOARD_INPUT_REPORT oldInputReport;
	static COMSUMER_INPUT_REPORT oldInputReportC;

	
	signed int TimeDeltaMilliseconds;
	unsigned char i;
	bool needToSendNewReportPacket;
	bool needToSendNewReportPacketC;

	inputReport.id = 1;
	inputComsumerReport.id = 2;

	/* If the USB device isn't configured yet, we can't really do anything
	 * else since we don't have a host to talk to.  So jump back to the
	 * top of the while loop. */
	if (USBGetDeviceState() < CONFIGURED_STATE) {
		return;
	}

	/* If we are currently suspended, then we need to see if we need to
	 * issue a remote wakeup.  In either case, we shouldn't process any
	 * keyboard commands since we aren't currently communicating to the host
	 * thus just continue back to the start of the while loop. */
	if (USBIsDeviceSuspended() == true) {
		//Check if we should assert a remote wakeup request to the USB host,
		//when the user presses the pushbutton.
		if (BUTTON_IsPressed(BUTTON_USB_DEVICE_REMOTE_WAKEUP) == 0) {
			//Add code here to issue a resume signal.
		}

		return;
	}

	//Copy the (possibly) interrupt context SOFCounter value into a local variable.
	//Using a while() loop to do this since the SOFCounter isn't necessarily atomically
	//updated and we need to read it a minimum of twice to ensure we captured the correct value.
	while (LocalSOFCount != SOFCounter) {
		LocalSOFCount = SOFCounter;
	}

	//Compute the elapsed time since the last input report was sent (we need
	//this info for properly obeying the HID idle rate set by the host).
	TimeDeltaMilliseconds = LocalSOFCount - OldSOFCount;
	//Check for negative value due to count wraparound back to zero.
	if (TimeDeltaMilliseconds < 0) {
		TimeDeltaMilliseconds = (32767 - OldSOFCount) + LocalSOFCount;
	}
	//Check if the TimeDelay is quite large.  If the idle rate is == 0 (which represents "infinity"),
	//then the TimeDeltaMilliseconds could also become infinity (which would cause overflow)
	//if there is no recent button presses or other changes occurring on the keyboard.
	//Therefore, saturate the TimeDeltaMilliseconds if it gets too large, by virtue
	//of updating the OldSOFCount, even if we haven't actually sent a packet recently.
	if (TimeDeltaMilliseconds > 5000) {
		OldSOFCount = LocalSOFCount - 5000;
	}


	/* Check if the IN endpoint is busy, and if it isn't check if we want to send
	 * keystroke data to the host. */
	if (HIDTxHandleBusy(keyboard.lastINTransmission) == false) {
		//		/* Clear the INPUT report buffer.  Set to all zeros. */
		//		memset(&inputReport, 0, sizeof (inputReport));

		///////////////////////////
		

			uint8_t mediaExist = 0xff;
			uint8_t macroExist = 0xff;
			uint8_t altCodeExist = 0xff;
			uint8_t combiExist = 0xff;
			uint8_t normalExist = 0xff;

//		CVRCONbits.CVR = count;


		for (uint8_t c = 0; c < 6; c++)
		{
			inputReport.keys[c] = 0;
		}
		for (uint8_t c = firstPush; c != 0xff; c = mSw[c].next) {
			switch (getKeyGroup(mSw[c].kc)) {
			case KEY_MEDIA: 
				mediaExist = c;
				break;
			case KEY_MACRO: 
				macroExist = c;
				break;
			case KEY_ALTCODE: 
				altCodeExist = c;
				break;
			case KEY_COMBI: 
				combiExist = c;
				break;
			case KEY_MODIFIER:
			case KEY_NORMAL:
				normalExist = c;
				break;
			}
		}

		if (mediaExist != 0xff) {
			for (uint8_t c = firstPush; c != 0xff; c = mSw[c].next) {
				switch (getKeyGroup(mSw[c].kc)) {
				case KEY_ALTCODE:
				case KEY_COMBI:
				case KEY_MACRO:
				case KEY_MODIFIER:
				case KEY_NORMAL:
					swUnregister(c);
					break;
				}
			}
		}
		if (altCodeExist != 0xff) {
			for (uint8_t c = firstPush; c != 0xff; c = mSw[c].next) {
				switch (getKeyGroup(mSw[c].kc)) {
				case KEY_COMBI:
				case KEY_MACRO:
				case KEY_MODIFIER:
				case KEY_NORMAL:
					swUnregister(c);
					break;
				}
			}
		}
		if (combiExist != 0xff) {
			for (uint8_t c = firstPush; c != 0xff; c = mSw[c].next) {
				switch (getKeyGroup(mSw[c].kc)) {
				case KEY_MACRO:
				case KEY_MODIFIER:
				case KEY_NORMAL:
					swUnregister(c);
					break;
				}
			}

			inputReport.modifiers.value = (mSw[combiExist].kc >> 8)&0x0f;
			inputReport.keys[0] = mSw[combiExist].kc & 0xff;
			WAITUSBTX;
			inputReport.modifiers.value = 0;
			inputReport.keys[0] = 0;
			needToSendNewReportPacketC = true;
		}
		if (macroExist != 0xff) {
			for (uint8_t c = firstPush; c != 0xff; c = mSw[c].next) {
				switch (getKeyGroup(mSw[c].kc)) {
				case KEY_MODIFIER:
				case KEY_NORMAL:
					swUnregister(c);
					break;
				}
			}
			
			switch (mSw[macroExist].kc) {
			case KANA:
				inputReport.modifiers.value = (LGJP >> 8)&0x0f;
				inputReport.keys[0] = LGJP & 0xff;
				WAITUSBTX
				inputReport.modifiers.value = (IMON >> 8)&0x0f;
				inputReport.keys[0] = IMON & 0xff;
				WAITUSBTX
				inputReport.modifiers.value = 0;
				inputReport.keys[0] = 0;
				break;
			case SMAL:
				inputReport.modifiers.value = (LGUS >> 8)&0x0f;
				inputReport.keys[0] = LGUS & 0xff;
				WAITUSBTX
				inputReport.modifiers.bits.leftShift = 1;
				WAITUSBTX
				inputReport.modifiers.value = 0;
				inputReport.keys[0] = 0;
				break;
			case SMIL:
				inputReport.modifiers.value = 0;
				inputReport.keys[0] = _SP_;
				WAITUSBTX
				inputReport.modifiers.bits.leftShift = 1;
				inputReport.keys[0] = SEMI;
				WAITUSBTX
				inputReport.keys[0] = __0_;
				WAITUSBTX
				inputReport.modifiers.value = 0;
				inputReport.keys[0] = 0;
				break;
			}
			mSw[macroExist].kc = 0; // OFF
		}
		if (normalExist != 0xff) {
			uint8_t d = 0;
			//normal keys
			for (uint8_t c = firstPush; c != 0xff; c = mSw[c].next) {
				switch (getKeyGroup(mSw[c].kc)) {
				case KEY_MODIFIER:
					//								inputReport.modifiers.value |= mSw[c].kc & 0x0f;
					break;
				case KEY_NORMAL:
					if (d < 6) {
						inputReport.keys[d++] = mSw[c].kc;
					}
					break;
				}
			}
		}
		
//							if (getKeyGroup(keymap[47 - dataA[c + 1]]) == KEY_NORMAL) {
//								inputReport.keys[c] = keymap[47 - dataA[c + 1]];
//								//								inputComsumerReport.modifiers.bits.v_dn = 1;
//							} else if (getKeyGroup(keymap[47 - dataA[c + 1]]) == KEY_MEDIA) {
//								inputComsumerReport.buttons.value |= 1 << (keymap[47 - dataA[c + 1]] & 0x0f);
//							}
//						for (; c < 6; c++) {
//							inputReport.keys[c] = 0;
//						}

		//Check to see if the new packet contents are somehow different from the most
		//recently sent packet contents.
		needToSendNewReportPacket = false;
		for (i = 0; i < sizeof (inputReport); i++) {
			if (*((uint8_t*) & oldInputReport + i) != *((uint8_t*) & inputReport + i)) {
				needToSendNewReportPacket = true;
				break;
			}
		}
		needToSendNewReportPacketC = false;
		for (i = 0; i < sizeof (inputComsumerReport); i++) {
			if (*((uint8_t*) & oldInputReportC + i) != *((uint8_t*) & inputComsumerReport + i)) {
				needToSendNewReportPacketC = true;
				break;
			}
		}

		//Check if the host has set the idle rate to something other than 0 (which is effectively "infinite").
		//If the idle rate is non-infinite, check to see if enough time has elapsed since
		//the last packet was sent, and it is time to send a new repeated packet or not.
		if (keyboardIdleRate != 0) {
			//Check if the idle rate time limit is met.  If so, need to send another HID input report packet to the host
			if (TimeDeltaMilliseconds >= keyboardIdleRate) {
				needToSendNewReportPacket = true;
				needToSendNewReportPacketC = true;
			}
		}

		//		if(active_protocol  ==1){
		//Now send the new input report packet, if it is appropriate to do so (ex: new data is
		//present or the idle rate limit was met).
		if (needToSendNewReportPacket == true) {
			//Save the old input report packet contents.  We do this so we can detect changes in report packet content
			//useful for determining when something has changed and needs to get re-sent to the host when using
			//infinite idle rate setting.
			oldInputReport = inputReport;

			/* Send the 8 byte packet over USB to the host. */
			keyboard.lastINTransmission = HIDTxPacket(HID_EP, (uint8_t*) & inputReport, sizeof (inputReport));
			OldSOFCount = LocalSOFCount; //Save the current time, so we know when to send the next packet (which depends in part on the idle rate setting)
		}
		if (needToSendNewReportPacketC == true) {
			//Save the old input report packet contents.  We do this so we can detect changes in report packet content
			//useful for determining when something has changed and needs to get re-sent to the host when using
			//infinite idle rate setting.
			oldInputReportC = inputComsumerReport;

			/* Send the 8 byte packet over USB to the host. */
			keyboard.lastINTransmission = HIDTxPacket(HID_EP, (uint8_t*) & inputComsumerReport, sizeof (inputComsumerReport));
			OldSOFCount = LocalSOFCount; //Save the current time, so we know when to send the next packet (which depends in part on the idle rate setting)
		}
		//	}

	}//if(HIDTxHandleBusy(keyboard.lastINTransmission) == false)


	/* Check if any data was sent from the PC to the keyboard device.  Report
	 * descriptor allows host to send 1 byte of data.  Bits 0-4 are LED states,
	 * bits 5-7 are unused pad bits.  The host can potentially send this OUT
	 * report data through the HID OUT endpoint (EP1 OUT), or, alternatively,
	 * the host may try to send LED state information by sending a SET_REPORT
	 * control transfer on EP0.  See the USBHIDCBSetReportHandler() function. */
	if (HIDRxHandleBusy(keyboard.lastOUTTransmission) == false) {
		APP_KeyboardProcessOutputReport();

		keyboard.lastOUTTransmission = HIDRxPacket(HID_EP, (uint8_t*) & outputReport, sizeof (outputReport));
	}
}

static void APP_KeyboardProcessOutputReport(void)
{
////	if (outputReport.id != 0x01)return;
//	if (outputReport.data.leds.capsLock) {
//		LED_On(LED_USB_DEVICE_HID_KEYBOARD_CAPS_LOCK);
//	} else {
//		LED_Off(LED_USB_DEVICE_HID_KEYBOARD_CAPS_LOCK);
//	}
//	if (outputReport.data.leds.numLock) {
//		LED_On(LED_USB_DEVICE_HID_KEYBOARD_NUM_LOCK);
//	} else {
//		LED_Off(LED_USB_DEVICE_HID_KEYBOARD_NUM_LOCK);
//	}
//	if (outputReport.data.leds.scrollLock) {
//		LED_On(LED_USB_DEVICE_HID_KEYBOARD_SCROOL_LOCK);
//	} else {
//		LED_Off(LED_USB_DEVICE_HID_KEYBOARD_SCROOL_LOCK);
//	}
}

static void USBHIDCBSetReportComplete(void)
{
	/* 1 byte of LED state data should now be in the CtrlTrfData buffer.  Copy
	 * it to the OUTPUT report buffer for processing */
//	outputReport.id = 0x01;/// TODO: Check
	outputReport.data.value = CtrlTrfData[0];

	/* Process the OUTPUT report. */
	APP_KeyboardProcessOutputReport();
}

void USBHIDCBSetReportHandler(void)
{
	/* Prepare to receive the keyboard LED state data through a SET_REPORT
	 * control transfer on endpoint 0.  The host should only send 1 byte,
	 * since this is all that the report descriptor allows it to send. */
	USBEP0Receive((uint8_t*) & CtrlTrfData, USB_EP0_BUFF_SIZE, USBHIDCBSetReportComplete);
}


//Callback function called by the USB stack, whenever the host sends a new SET_IDLE
//command.

void USBHIDCBSetIdleRateHandler(uint8_t reportID, uint8_t newIdleRate)
{
	//Make sure the report ID matches the keyboard input report id number.
	//If however the firmware doesn't implement/use report ID numbers,
	//then it should be == 0.
	if (reportID == 1) {
		keyboardIdleRate = newIdleRate;
	}
}


/*******************************************************************************
 End of File
 */
