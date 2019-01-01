/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>        /* XC8 General Include File */

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>
#include <string.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "swMatrix.h"
#include "ringBuffer.h"          /* User funct/params, such as InitApp */
#include "../IR_format.h"

#define	COUNT_TO_SLEEP	3
//Define in Configuration
/////////////////////////////////
////#define	SLAVE_L		//RIGHT KB : Comment out this row
/////////////////////////////////

#ifdef	SLAVE_L
#define	DREQ	DREQL
#define	DATA	DATAL
#define	RPT		RPTL
#define	LED		(led[0] | led[1] | led[2])
#else
#define	SLAVE_R
#define	DREQ	DREQR
#define	DATA	DATAR
#define	RPT		RPTR
#define	LED		(led[0])
#endif

void powerSave(void);
void transceiverEnable(uint8_t enable);
void disableAllPMD(void);

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

//uint8_t led[8] = {0x55,0x55,0x55,0,0,0,0,0};
uint8_t led[8] = {0,0,0,0,0,0,0,0};

extern uint8_t countNoDreq;

void main(void)
{
	disableAllPMD();
	
	/* Configure the oscillator for the device */
	ConfigureOscillator();

	/* Initialize I/O and Peripherals for application */
	InitApp();

//	powerSave();
//	led[0] = 0x01;
	
	while (1) {
		uint8_t data;
		uint8_t fSendReport = 0;
		static uint8_t countZeroPushing = COUNT_TO_SLEEP+1;
		static uint8_t countData = 0;
		static uint8_t dataA[32];

		if (countZeroPushing > COUNT_TO_SLEEP) {
			if (LED) {
				transceiverEnable(0);
				CPUDOZEbits.IDLEN = 1; //CPU sleep
				Sleep();
			} else {
				powerSave();
				countData = 0;
				countZeroPushing = 0;
				TMR5IF = 1; //Call UI interrupt
			}
		} else {
			CPUDOZEbits.IDLEN = 1; //CPU sleep
			Sleep();
		}
		
		if(nPushing){
			countZeroPushing = 0;
			transceiverEnable(1);
		}
		
//		if (!bufDataExist(irRxBuffer)) {
//			CPUDOZEbits.DOZE = 4; //1:256
//			ROI = 1;
//			DOE = 1;
//			DOZEN = 1;
//		}
		while (bufDataExist(irRxBuffer)) {
			data = bufRead(&irRxBuffer);
			
			if (data < 8) {
				if (countData) {
					if (countData & 1) {
						dataA[countData >> 1] |= data;
					} else {
						dataA[countData >> 1] = data << 3;
					}
					if(countData<20){countData++;}
				}
			} else if (data == 9) {
				//start
				for (uint8_t c = 0; c < 6; c++) {
					dataA[c] = -1;
				}
				dataA[0] = 0;
				countData = 1;
				//			LATC0 = 1;
			} else if (data == 10) {
				//stop
				if (countData & 1) {
					uint8_t a=(dataA[countData >> 1] >> 3);
					uint8_t b=checksum(&dataA[0], &dataA[1], (countData >> 1) - 1);
					if ((dataA[countData >> 1] >> 3) == checksum(dataA[0], &dataA[1], (countData >> 1) - 1)) {
						switch (dataA[0]) {
						case DREQ:
							//TODO: Check CRC
							fSendReport = 1;
							//			LATC0 = 0;
							countNoDreq = 0;
							break;
						case DATA:
							//TODO: Check CRC
							led[(dataA[1] >> 3)&7] = ((dataA[1]&7) << 6) | dataA[2];
							break;
						}
					} else {
						//error checksum
					}
				} else {
					//error even stop
				}
				countData = 0;
			} else {
				//error invalid data
				countData = 0;
			}
		}

		if (fSendReport) {
			fSendReport = 0;
			if (nPushing || countZeroPushing <= COUNT_TO_SLEEP) {
				uint8_t reportCopy[1 + N_PUSHABLE];

				TMR5IE = 0;
				for (uint8_t c = 0; c < 1 + N_PUSHABLE; c++) {
					reportCopy[c] = report[c];
				}
				TMR5IE = 1;

				sendReport(RPT, &reportCopy[0], nPushing);
				if (!nPushing) {
					countZeroPushing++;
				}
			}
		}
		if (countNoDreq > 32) {
			if (!nPushing) {
				countNoDreq = 0;
				countZeroPushing++;
			}
		}
	}
}

void transceiverEnable(uint8_t enable)
{
	if (enable) {
		TRISCbits.TRISC4 = 1;
		LATC3 = 0; //Enable Transceiver
		if (enable == 1) {
			while (!PORTCbits.RC4); //wait H level(about 200us)
			SMT1IF = 0;
			SMT1IE = 1;
		}
	} else {
		SMT1IE = 0;
		LATC3 = 1;	//Disable Transceiver
//		LATCbits.LATC4 = 0;
//		TRISCbits.TRISC4 = 0;
	}
}

void disableAllPMD(void){
	PMD0 = 0xff;
	PMD1 = 0xff;
	PMD2 = 0xff;
	PMD3 = 0xff;
	PMD4 = 0xff;
	PMD5 = 0xff;
	PMD6 = 0xff;
	PMD7 = 0xff;
}

void disableAllInterrupt(void)
{
	INTCON0bits.GIEH  =0;
	INTCON0bits.GIEL  =0;
	
	PIE0 = 0;
	PIE1 = 0;
	PIE2 = 0;
	PIE3 = 0;
	PIE4 = 0;
	PIE5 = 0;
	PIE6 = 0;
	PIE7 = 0;
	PIE8 = 0;
	PIE9 = 0;
	PIE10 = 0;
}

void powerSave(void)
{	
	disableAllInterrupt();
	disableAllPMD();
	PMD0bits.IOCMD = 0; //enable IOC
	transceiverEnable(0);
	
	
	LATC |= 0xe0;	//LED all off
	LATA &= 0xc0;	//enable all switch row
	TRISB = 0xff;	//input all column
	WPUB = 0xff;	
	CCDPB = 0;
	CCDCON = 0; 
		
	IOCBF = 0;
	IOCBN = 0xff;
	IOCIE = 1;
	
	CPUDOZEbits.IDLEN = 0; //0 = all peripheral sleep
	Sleep();	//wait for key press
			
	transceiverEnable(2);	//Pre enable to fastest wakeup
	
	InitApp();
}
