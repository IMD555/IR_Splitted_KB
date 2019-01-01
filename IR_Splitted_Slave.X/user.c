/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/


#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>  /* For true/false definition */

#include "user.h"
#include "swMatrix.h"
#include "../IR_format.h"
#include "ringBuffer.h"


//COMPARE MODE
#define	L2H		0x08
#define	H2L		0x09
#define	TGL		0x02
#define	TGLwR	0x01

uint8_t CRC3(uint8_t data, uint8_t dataLength);

//////ABFGCE.D
const uint8_t bin2seg7[] = {
	0b11101101, // 0
	0b01001000, // 1
	0b11010101, // 2
	0b11011001, // 3
	0b01111000, // 4
	0b10111001, // 5
	0b10111101, // 6
	0b11101000, // 7
	0b11111101, // 8
	0b11111001, // 9
	0b11111100, // A
	0b00111101, // b
	0b00010101, // c
	0b01011101, // d
	0b10110101, // E
	0b10110100, // F
};


/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void initPMD(void)
{
	PMD0bits.SYSCMD = 0;
	PMD0bits.CRCMD = 0;
	PMD0bits.IOCMD = 0;
//	PMD1bits.NCO1MD = 0;
	PMD1bits.TMR2MD = 0;
	PMD1bits.TMR3MD = 0;
	PMD1bits.TMR5MD = 0;
	PMD3bits.CCP1MD = 0;
	PMD3bits.PWM5MD = 0;
	PMD6bits.SMT1MD = 0;
	PMD6bits.DSMMD = 0;
	PMD6bits.CLC1MD = 0;
	PMD7bits.DMA1MD = 0;
}
void initGPIO(void)
{
	/* TODO Initialize User Ports/Peripherals/Project here */

	/* Setup analog functionality and port direction */
	ANSELA = 0x00;
	LATA = 0x3f;
	TRISA = 0x00; //1:Input
	WPUA = 0x00; //1:WPU Enabled
	ODCONA = 0x00; //1:Open drain
	SLRCONA = 0x00; //1:Limited slew rate
	INLVLA = 0xff; //1:ST 0:TTL
	CCDPA = 0x00; //1:H Current control Enabled
	CCDNA = 0x00; //1:L Current control Enabled

	ANSELB = 0x00;
	LATB = 0x00;
	TRISB = 0x00;
	WPUB = 0x00;
	ODCONB = 0x00;
	SLRCONB = 0x00;
	INLVLB = 0xff;
	CCDPB = 0x00;
	CCDNB = 0x00;

	ANSELC = 0x00;
	LATC = 0x0e;
	TRISC = 0x10;
	WPUC = 0x00;
	ODCONC = 0x00;
	SLRCONC = 0x00;
	INLVLC = 0xff;
	CCDPC = 0x00;
	CCDNC = 0x00;

	WPUE = 0x08;
	INLVLE = 0x08;
	
	CCDCON = 0x03; //1mA disabled
	
	//debug outputs
	//	RC0PPS = 0x13; //RC0 = U1TX	test pad long
//	RC0PPS = 0x09; //RC0 = CCP1	test pad long
	//	RC0PPS = 0x01; //RC0 = CLC1	test pad long
	RA7PPS = 0x28; //RA7 = DSM1	test pad short
	//		RA7PPS = 0x0d; //RA7 = PWM5	test pad short
	//	RA7PPS = 0x01; //RA7 = CLC1	test pad short
	//		RA6PPS = 0x26; //RA6 = NCO1	test pad mid
}

void initUI(void)
{
	//SW&LED matrix control
	//488Hz???
	T5GCON = 0x00;
	T5CLK = 0x02;
	T5CON = 0x03;
	TMR5IP = 0;
	
	TMR5IF=0;
	TMR5IE =1;
}

void initReceiver(void)
{
	bufInit(&irRxBuffer,&irRxBuffer1[0]);
	
	SMT1SIGPPS = 0x14;//SMT1IN = RC4
	SMT1PR = 10428;	//36.5*8000/56*2 Stop detect
	SMT1CON0 = 0x88;//inverted input 
	SMT1STAT = 0x20;	
	SMT1CLK = 0x00;	//Fosc/4
	SMT1CON1=0xc3;	//SMT1 Start as high and low time measurement
	SMT1PRAIF = 0;
	SMT1PRAIE = 1;
	SMT1PRAIP = 1;
	SMT1PWAIF = 0;
	SMT1PWAIE = 1;
	SMT1PWAIP = 1;
	SMT1IF = 0;
	SMT1IE = 1;
	SMT1IP = 1;
}
	
void initTransmitter(void)
{
	T2CLK = 0x01; //freerun 56kHz
	T2RST = 0x04;
	//	T2HLT = 0x04;
	T2PR = 142;
	T2CON = 0x80;
	CCPTMRS1bits.P5TSEL = 0x01; //PWM5 use TMR2
	PWM5CON = 0x80;
	PWM5DCH = T2PR / 2;

	//CLC1 = PWM5/2
	CLC1POL = 0;
	CLC1SEL0 = 0x18; //CLC1D1 = PWM5
	CLC1SEL1 = 0x24; //CLC1D2 = CLC1out

	CLC1GLS0 = 0x02; //LC1G1:CLK = CLC1D1
	CLC1GLS1 = 0x04; //LC1G2:DIN = !CLC1D2
	CLC1GLS2 = 0x00; //LC1G3:RST = 0
	CLC1GLS3 = 0x00; //LC1G4:SET = 0

	CLC1CON = 0x84; //D-FF with SR

	//	//CLC1 = PWM5
	//	CLC1POL = 0x0e;
	//	CLC1SEL0 = 0x18; //CLC1D1 = PWM5
	//
	//	CLC1GLS0 = 0x01; //LC1G1:A = CLC1D1
	//	CLC1GLS1 = 0x00; //LC1G2:B = CLC1D1
	//	CLC1GLS2 = 0x00; //LC1G3:C = CLC1D1
	//	CLC1GLS3 = 0x00; //LC1G4:D = CLC1D1
	//
	//	CLC1CON = 0x82; //4 input AND

	//for CCP1
	TMR3H = 0;
	TMR3L = 0;
	//	T3CLK = 0x01; //FOSC/4
	T3CLK = 0x0d; //CLC1
	T3CON = 0x06; //DISABLED

	CCPTMRS0bits.C1TSEL = 0x02; //CCP1 use TMR3
	//	CCPR1L = 0;
	//	CCPR1H = 0;
	//	CCP1CONbits.MODE = H2L;
	
//	///???????????????????????????????
//	CCPR1 = 100;
//	CCP1CONbits.MODE = TGL;
//	CCP1CONbits.EN = 1;

	//	NCO1CLK = 0xa1; //HFINTOSC 4MHz? duty
	//	NCO1CLK = 0x81; //HFINTOSC 16MHz? duty
	//	NCO1INC = 14680; //56kHz
	//	NCO1INC = 14680/4; //56*2kHz by
	//	NCO1CON = 0x80;

	MD1CON0 = 0x00; //disabled
	MD1CON1 = 0x00;
//	MD1CON1bits.CHSYNC = 1;
	MD1CARL = 0x1f; //ZERO input
	//	MD1CARH = 0x0e; //Sync with NCO1
	MD1CARH = 0x08; //Sync with PWM5
	MD1SRC = 0x02; //Input is CCP1
	MD1CARHPPS = 0x00;

	RC2PPS = 0x28; //RC2 = DSM1	IR LED
}

void initInterrupt(void)
{
	/* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

	/* Enable interrupts */
	DMA1PR = 0;
	ISRPR = 1;
	MAINPR = 2;
	__asm("BANKSEL PRLOCK");
	__asm("	MOVLW 0x55");
	__asm("	MOVWF PRLOCK");
	__asm("MOVLW 0xAA");
	__asm("	MOVWF PRLOCK");
	__asm("	BSF PRLOCK,0");

	INTCON0bits.IPEN  =1;
	INTCON0bits.GIE  =1;
	INTCON0bits.GIEL  =1;
}

void InitApp(void)
{
	initPMD();
	initGPIO();
	initUI();
	initReceiver();
	initTransmitter();
	initInterrupt();
}

void LED(uint8_t digit, uint8_t data)
{
	CCDPB = 0x00;
	CCDCONbits.EN = !!data;
	CCDPB = data;
	LATC |= 0xe0;
	LATB = data;
	TRISB = 0x00;
	if (digit > 2)digit = 2;
	LATC &= ~(0x80 >> digit);
}

//void sendACK(uint8_t report[], uint8_t pushingCount)
//{
//	while (U1FIFObits.TXBF);
//	U1TXB = SENDER | ACK | CRC3(0, 0);
//}


void sendReport(uint8_t command, uint8_t* data, uint8_t dataCount)
{
	uint16_t dataBuf[18]; //Max data length is 5byte
	
//SMT1CON1bits.GO = 0;
	SMT1IE = 0;	//stop detect enable
	SMT1PRAIE = 0;
	SMT1PWAIE = 0;
	
	for(uint16_t c=0;c<250;c++){
		Nop();
	}

//0 Command
//	dataBuf[0] =  IR_START + IR_DATA(command & 0x7);
	dataBuf[0] =  IR_START + IR_DATA(command & 0x7) + 20;

	//1～(2x dataCount) data
	for (uint8_t c = 0; c < dataCount; c++) {
		dataBuf[c * 2 + 1] = dataBuf[c * 2] + IR_DATA(data[c] >> 3); //Upper3bits
		dataBuf[c * 2 + 2] = dataBuf[c * 2 + 1] +  IR_DATA(data[c] & 7); //Lower3bits
	}
	//(2x dataCount +1) Check
	dataBuf[dataCount * 2 + 1] = dataBuf[dataCount * 2] +  IR_DATA(checksum(command,&data[0],dataCount));
	//(2x dataCount +2) Stop
	dataBuf[dataCount * 2 + 2] = dataBuf[dataCount * 2 + 1] + IR_STOP;
//	dataBuf[dataCount * 2 + 2] += 100;

	DMA1CON0 = 0x00;
	DMA1SSA = &dataBuf[0];
	DMA1DSA = &CCPR1;
	DMA1CON1 = 0x43;
	DMA1SSZ = 6 + dataCount * 4; //pulse count x4 -2, Without Start
	DMA1DSZ = 2; //2byte per edge

	DMA1SIRQ = 35; //CCP1

//	CCPR1 = 0 + IR_START;		//32
	CCPR1 = 0 + IR_START + 20;		//32+@
	TMR3H = 0xff;
	TMR3L = 0xff;

	TMR2= 0xff;
	CLC1POLbits.G3POL =1;
	CLC1POLbits.G3POL =0;
	
	MD1CON0bits.EN = 1;
	CCP1CONbits.EN = 1;
//	CCP1CONbits.MODE = TGL;
	T3CONbits.ON = 1; //TMR3 START
	DMA1CON0bits.EN = 1;
	DMA1CON0bits.SIRQEN = 1; //DMA START
	CCP1CONbits.MODE = H2L; //CCP1 High
	T2CONbits.ON = 1; //TMR2 START
	CCP1CONbits.MODE = TGL;

	LATA6 = 1;

	PIR2bits.DMA1SCNTIF = 0;
//	PIE2bits.DMA1SCNTIE = 1;
	
	CPUDOZEbits.DOZE = 7;	//1:256
	ROI = 1;
	DOE = 1;
	DOZEN = 1;

	while (!PIR2bits.DMA1SCNTIF);

	MD1CON0bits.EN = 0;
	
	CCP1IF = 0;
//	CCP1IE = 1;
	
	DOZEN = 0;
	while (!CCP1IF);
				
	DOZEN = 0;

	CCP1CONbits.EN = 0;
	T3CONbits.ON = 0;
	T2CONbits.ON = 0; //TMR2 STOP

	//	for (uint8_t c = 0; c < pushingCount; c++) {
	//		while (U1FIFObits.TXBF);
	//		U1TXB = report[c];
	//	}

	LATA6 = 0;

//	SMT1CON1bits.GO = 1;
//	SMT1IF = 0;	//stop detect enable
//	SMT1IE = 0;	//stop detect enable
//	SMT1PRAIF = 0;
//	SMT1PRAIE = 1;
	SMT1PWAIF = 0;
	SMT1PWAIE = 1;
}

uint8_t CRC3(uint8_t data, uint8_t dataLength)
{
	return 0x02;
	CRCXOR = 0x0000;
	CRCCON0 = 0x90;
	CRCCON1 = 0x03 | (dataLength << 4);

	return data & 0x07;
};
