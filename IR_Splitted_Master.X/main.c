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
#include "swMatrix.h"
#include "../IR_format.h"

//COMPARE MODE
#define L2H 0x01
#define H2L 0x02
#define TGL 0x03

void checkTimeout(void);
void decodeReport(void);
void waitReport(uint8_t command);
uint8_t sendReport(uint8_t command, uint8_t *data, uint8_t dataCount);
void init(void);

extern uint8_t firstEdgeFlag;
uint8_t sendDreqFlag = 1;
uint8_t sendLedFlag = 0;

	static	uint16_t communicationTimeoutCountLeft = 0;
	static	uint16_t communicationTimeoutCountRight = 0;
	
	
int main(void)
{
	init();

	//	#define	LED_L_BIN 0
	//	#define	LED_L_NUM10 1
	//	#define	LED_L_NUM1 2
	//	#define	LED_R_BIN 3
	//	uint8_t	led[4]={0,0,0,0};
	//	uint8_t ledChangeFlag[4]={1,1,1,1};

	while (1)
	{
		static uint8_t isLeft = 0;
		isLeft = !isLeft;
	
		LATBbits.LATB3 = isLeft;
		
		waitReport(sendReport(isLeft ? DREQL : DREQR, 0, 0));
//		waitReport(sendReport(DREQL, 0, 0));

		
//		checkTimeout();

		APP_KeyboardTasks();
	}
}

void checkTimeout(void){
	if ((uint16_t) (USBGet1msTickCount() - communicationTimeoutCountLeft) > 350) {
			//communication timeout
			for (uint8_t c = firstPush; c != 0xff; c = mSw[c].next) {
				//release all left key
				if (mSw[c].num < 48) {
//					swUnregister(c);
				}
			}
		}

		if ((uint16_t) (USBGet1msTickCount() - communicationTimeoutCountRight) > 350) {
			//communication timeout
			for (uint8_t c = firstPush; c != 0xff; c = mSw[c].next) {
				//release all right key
				if (mSw[c].num >= 48) {
					swUnregister(c);
				}
			}
		}
}

void decodeReport(void)
{	
	static uint8_t countData = 0;
	static uint8_t dataA[16];
	static uint8_t keyListLeft[6];
	static uint8_t keyListRight[6];

	while (bufDataExist(irRxBuffer))
	{
		LATBbits.LATB13 = 0;
		uint8_t data = bufRead(&irRxBuffer);

//		LATBbits.LATB13 = data&1;
//		CVRCONbits.CVR = data;

		if (data < 8)
		{
			if (countData)
			{
				if (countData & 1)
				{
					dataA[countData >> 1] |= data;
				}
				else
				{
					dataA[countData >> 1] = data << 3;
				}
				countData++;
			}
		}
		else if (data == W_START)
		{
			//start
			LATBbits.LATB15 = 1;
			for (uint8_t c = 0; c < 6; c++)
			{
				dataA[c] = -1;
			}
			countData = 1;
			dataA[0] = 0;
		}
		else if (data == W_STOP)
		{
			//stop
			LATBbits.LATB15 = 0;
			if (countData & 1)
			{
				if ((dataA[countData >> 1] >> 3) == checksum(dataA[0], &dataA[1], (countData >> 1) - 1))
				{
					//ChechSum OK!
		LATBbits.LATB13 = 0;
					switch (dataA[0])
					{
					case RPTL:
						//left report
						LED_Off(LED_LEFT_NG);
						LED_On(LED_LEFT_OK);

						for (uint8_t c = 0; c < 6; c++)
						{
							keyListLeft[c] = 0xff;
						}
						for (uint8_t c = 0; c < ((countData - 3) >> 1); c++)
						{
							swRegister(keyListLeft[c] = 47 - dataA[c + 1]); //mirror X & Y
						}

						for (uint8_t c = firstPush; c != 0xff; c = mSw[c].next)
						{
							//release released left key
							if (mSw[c].num < 48)
							{
								uint8_t pushing = 0;
								for (uint8_t d = 0; d < 5; d++)
								{
									if (keyListLeft[d] == mSw[c].num)
									{
										pushing = 1;
										break;
									}
								}
								if (!pushing)
								{
									swUnregister(c);
								}
							}
						}

						communicationTimeoutCountLeft = USBGet1msTickCount();
						//if(countData>3)						sendDreqFlag = 1;
						break;
					case RPTR:
						//right report
						LED_Off(LED_RIGHT_NG);
						LED_On(LED_RIGHT_OK);

						for (uint8_t c = 0; c < 6; c++)
						{
							keyListRight[c] = 0xff;
						}
						for (uint8_t c = 0; c < ((countData - 3) >> 1); c++)
						{
							swRegister(keyListRight[c] = 95 - dataA[c + 1]); //mirror X & Y
						}

						for (uint8_t c = firstPush; c != 0xff; c = mSw[c].next)
						{
							//release released right key
							if (mSw[c].num >= 48)
							{
								uint8_t pushing = 0;
								for (uint8_t d = 0; d < 5; d++)
								{
									if (keyListRight[d] == mSw[c].num)
									{
										pushing = 1;
										break;
									}
								}
								if (!pushing)
								{
									swUnregister(c);
								}
							}
						}

						communicationTimeoutCountRight = USBGet1msTickCount();
						//if(countData>3)						sendDreqFlag = 1;
						break;
					}
				}
				else
				{
					//error checksum
		LATBbits.LATB13 = 1;
					switch (dataA[0]) {
					case RPTL:
						LED_Off(LED_LEFT_OK);
						LED_Off(LED_RIGHT_OK);
						break;
					case RPTR:
						LED_On(LED_LEFT_NG);
						LED_On(LED_RIGHT_NG);
						break;
					default:
						LED_Off(LED_LEFT_OK);
						LED_Off(LED_RIGHT_OK);
						LED_On(LED_LEFT_NG);
						LED_On(LED_RIGHT_NG);
						break;
					}
				}
				//						communicationTimeoutCountRight = USBGet1msTickCount();
			}
			else
			{
				//error even stop
			}
			countData = 0;
			dataA[0] = 0xff;
		}
		else
		{
			//error invalid data
			countData = 0;
			dataA[0] = 0xff;
		}
	}
}

void waitReport(uint8_t command)
{
	firstEdgeFlag = 1;
//	CVRCONbits.CVR = 10;
	bufClear(&irRxBuffer);

//	while (!PORTBbits.RB4); //wait when active state
	//start receive
	IC1CON1bits.ICM = 0; //reset
	IC1CON1bits.ICM = 1;
	IFS0bits.IC1IF = 0;
	IEC0bits.IC1IE = 1; //start receiving

	TMR4 = 0;
	IFS1bits.T4IF = 0;
	while (!IFS1bits.T4IF)
	{
		//receive in _IC1Interrupt()
		
		decodeReport();
		
		APP_KeyboardTasks();
//	CVRCONbits.CVR = 10;
		CVRCONbits.CVR++;
	}					//Exit by STOP or No reply
	
	IEC0bits.IC1IE = 0; //stop receiving
	irRxBuffer.buffer[irRxBuffer.writeIndex++] = W_STOP;
	
	decodeReport();
//	CVRCONbits.CVR = 0;
}

uint8_t sendReport(uint8_t command, uint8_t *data, uint8_t dataCount)
{	
//	CVRCONbits.CVR = 31;

	uint16_t dataBuf[18]; //Max data length is 5byte

	//0 Command
	dataBuf[0] = 2 * (IR_START + IR_DATA(command & 0x7)); //-2;

	//1～(2x dataCount) data
	for (uint8_t c = 0; c < dataCount; c++)
	{
		dataBuf[c * 2 + 1] = dataBuf[c * 2] + 2 * (IR_DATA(data[c] >> 3));	//Upper3bits
		dataBuf[c * 2 + 2] = dataBuf[c * 2 + 1] + 2 * (IR_DATA(data[c] & 7)); //Lower3bits
	}
	//(2x dataCount +1) Check
	dataBuf[dataCount * 2 + 1] = dataBuf[dataCount * 2] + 2 * (IR_DATA(checksum(command, &data[0], dataCount)));
	//(2x dataCount +2) Stop
	dataBuf[dataCount * 2 + 2] = dataBuf[dataCount * 2 + 1] + 2 * (IR_STOP);
	//	dataBuf[dataCount * 2 + 2] += 100;

	IEC0bits.DMA0IE = 0;
	DMACON = 0x8000;
	DMAL = 0x0000;
	DMAH = 0xffff;
	DMACH0 = 0x0040;  //?
	DMAINT0 = 0x3601; //trigger by OC2

	DMASRC0 = &dataBuf[0];
	DMADST0 = &OC2R;
	DMACNT0 = 3 + dataCount * 2; //pulse count x4 -2, Without Start

	OC2CON1bits.OCM = 0; //OC2 OFF

	MDCONbits.MDOE = 1;
	//	OC2CONbits..EN = 1;
	//	CCP1CONbits.MODE = TGL;
	IFS0bits.DMA0IF = 0;
	DMAINT0 &= 0x3f00;

	DMACH0bits.CHEN = 1; //DMA START
						 //	DMACH0bits.SIRQEN = 1;
						 //	OC2CON1bits.OCM = H2L; //CCP1 High
						 //	OC2R=OC2R;

	//	while(!PORTBbits.RB14);
	//	T2CONbits.ON = 1; //TMR2 START
	OC2R = 0 + 2 * (IR_START); //-2;
	OC2TMR = 0;

	OC2CON1bits.OCM = TGL;

	//	IEC0bits.DMA0IE = 1;
	//	DMAINT0 &= 0x3f01;
	//	IFS0bits.DMA0IF = 1;
	//	IEC0bits.DMA0IE = 1;
	while (!IFS0bits.DMA0IF){
		APP_KeyboardTasks();
//	CVRCONbits.CVR = 31;
		CVRCONbits.CVR++;
	}
	//
	//		MDCONbits.MDOE = 0;
	//
	IFS0bits.OC2IF = 0;
	//	while (!IFS0bits.OC2IF);

	//	CCP1CONbits.EN = 0;
	//	T3CONbits.ON = 0;
	//	T2CONbits.ON = 0; //TMR2 STOP

	MDCONbits.MDOE = 0;

	while (!IFS0bits.OC2IF)	{	
		APP_KeyboardTasks();
//	CVRCONbits.CVR = 31;
		CVRCONbits.CVR++;
	}

	DMACH0bits.CHEN = 0;
	IEC0bits.DMA0IE = 0;
	DMAINT0bits.DONEIF = 0;

	//		IFS0bits.OC2IF = 0;
	//		IEC0bits.OC2IE = 1;
	IEC0bits.T3IE = 1;

	//	while(!PORTBbits.RB4);

	return command;
}

void init(void)
{
	INTCON1bits.NSTDIS = 0;

	bufInit(&irRxBuffer, irRxBuffer1);

	LATBbits.LATB15 = 1;
	TRISB &= 0x1ff3;
	OSCTUN = 0x9000;
	CLKDIVbits.RCDIV = 0b000;
	//	REFOCONH = 500;
	//	REFOCONL = 0x8006;

	ANSA = 0;
	ANSB = 0;

	//Input PPS
	RPINR0bits.INT1R = 0x04; //INT1 = RB4
	RPINR7bits.IC1R = 0x04;  //IC1 = RB4
							 //	RPINR18bits.U1RXR = 0x04;	//U1RX = RB4

	IC1TMR = 0;
	IC1CON1 = 0x1c01; //IC1 use FOSC/2
	IC1CON2 = 0x0000;
	while (IC1CON1bits.ICBNE)
	{
		IC1BUF;
	}

	//Carrier, 56kHz
	OC1CON1 = 0x1c06;
	OC1CON2 = 0x001f; //reset with RS
	OC1RS = 286;
	//	OC1R = OC1RS >> 1;
	OC1R = OC1RS - (OC1RS >> 2);

		//Stop detect
		PR3 = 932;
		T3CON = 0x8102;

	//Pulse, toggle
	OC2CON1 = 0x0403;
	OC2CON2 = 0x101f; //free-run, inverted
	OC2RS = 0xffff;
	OC2R = 2;

	MDCON = 0x8020; //disabled
	MDSRC = 0x0009; //OC2
	MDCAR = 0x4480; //High Carrier is OC1
	MDCONbits.MDOE = 1;

	LATBbits.LATB15 = 1;
	TRISB &= 0x1ff3;

	RPOR1bits.RP2R = 27;  //RB2 = MDOUT (IR-LED)
//	RPOR6bits.RP13R = 27; //RB13 = MDOUT
						  //	RPOR6bits.RP13R = 18;	//RB13 = OC6
//	RPOR6bits.RP13R = 14; //RB13 = OC2
	CVRCON = 0x00c0;	  //RB14 = CVR 5-bits DAC
						  //	RPOR7bits.RP14R = 14;	//RB14 = OC2
	RPOR7bits.RP15R = 13; //RB15 = OC1  DON'T CHANGE

	IPC5bits.INT1IP = 7;
	IPC6bits.T4IP = 1;
	IPC2bits.T3IP = 7;
	IPC1bits.DMA0IP = 6;
	IPC1bits.OC2IP = 5;
	IPC0bits.IC1IP = 3;
	IPC21bits.USB1IP = 2;

	IFS1bits.INT1IF = 0;
	IEC1bits.INT1IE = 1;

	//Transmit period
	PR4 = 4000;
//	PR4 = 15000; //test 3500;
	T4CON = 0x8010;

	IFS0bits.IC1IF = 0;
	IEC0bits.IC1IE = 0;

	IFS0bits.T3IF = 0;
	IEC0bits.T3IE = 0;

	IFS1bits.T4IF = 0;
	IEC1bits.T4IE = 0;

	CNPU1bits.CN1PUE = 1;
	//	CNPD1bits.CN1PDE=0;

	//		LED_Enable(LED_D7);
	//		LED_On(LED_D7);
	//

	//	while (1) {
	//	}
	//		while(!	IFS0bits.T3IF);
	//	IFS0bits.T3IF = 0;
	//	TMR3= 64000;
	////		sendReport(0,0,0);
	//		uint8_t data[6]={0,1,2,3,4,5};
	//		sendReport(DREQL,&data[0],3);

	//		if(bufDataExist(irRxBuffer))
	//		{
	//			bufRead(&irRxBuffer);
	//		}

//	SYSTEM_Initialize(SYSTEM_STATE_USB_START);
//
//	USBDeviceInit();
//	USBDeviceAttach();

	//	while (1) {
	//	}

	LED_Enable(LED_LEFT_NG);
	LED_Enable(LED_LEFT_OK);
	LED_Enable(LED_RIGHT_NG);
	LED_Enable(LED_RIGHT_OK);
}
