/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>

#include "ringBuffer.h"        /* For true/false definition */
#include "../IR_format.h"
#include "user.h"
#include "swMatrix.h"

extern uint8_t led[];

uint8_t countNoDreq = 0;

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

// High-priority
void __interrupt(irq(SWINT),low_priority) SWINT_ISR(void)
{
	LATA6 = 1;
//	SWIF = 0;
	Reset();
}

//void __interrupt(irq(U1RX)) U1RX_ISR(void)
//{
//	U1RXIF = 0;
//}
//
//void __interrupt(irq(U1TX)) U1TX_ISR(void)
//{
//	U1TXIF = 0;
//}

// Default ISR for all unhandled interrupts with IVTBASE=default (0x0008)
void __interrupt(irq(default)) DEFAULT_ISR(void)
{
	LATA6 = 1;
	// Unhandled interrupt code
	Reset();
}

void __interrupt(irq(SMT1PRW)) SMT1PRW_ISR(void){
	LATA6 = 1;
	//low pulse?
	uint32_t diff = 0;
	uint8_t data = -1;
		
//			LATC0 ^=1;// 0;
	SMT1PWAIF = 0;
	
	diff = SMT1CPW;
		diff = (uint32_t) diff * 56UL;

		//		if (diff < 32) {
		//			CVRCONbits.CVR = diff;
		//		}

		if (diff < ((IR_DATA(-1) + IR_DATA(0)) * 8000UL)) {
			//error too short
			data = -1;
//			edgeN = 0;
		} else if (diff < ((IR_DATA(0) + IR_DATA(1)) * 8000UL)) {
			data = 0;
		} else if (diff < ((IR_DATA(1) + IR_DATA(2)) * 8000UL)) {
			data = 1;
		} else if (diff < ((IR_DATA(2) + IR_DATA(3)) * 8000UL)) {
			data = 2;
		} else if (diff < ((IR_DATA(3) + IR_DATA(4)) * 8000UL)) {
			data = 3;
		} else if (diff < ((IR_DATA(4) + IR_DATA(5)) * 8000UL)) {
			data = 4;
		} else if (diff < ((IR_DATA(5) + IR_DATA(6)) * 8000UL)) {
			data = 5;
		} else if (diff < ((IR_DATA(6) + IR_DATA(7)) * 8000UL)) {
			data = 6;
		} else if (diff < ((IR_DATA(7) + IR_DATA(8)) * 8000UL)) {
			data = 7;
		} else{// if (diff < ((IR_START + IR_STOP) * 8000UL)) {
			//START
			data = 9;
//			edgeN = 1;
//		} else {
//			//not STOP
//			data = -1;
//			data = 9;
////			data = 10;
////			edgeN = 0;
		}
	bufWriteIntIC1(&irRxBuffer,data);
	
//	TMR5 = -10080;	//1.26ms?
//	TMR5IF = 0;
//	TMR5IE = 1;
//	T5CONbits.ON = 1;
	
	SMT1PR = 10428;	//36.5*8000/56*2 Stop detect
	SMT1IF = 0;
	SMT1IE = 1;	//stop detect enable
	SMT1PRAIF = 0;
	SMT1PRAIE = 1;
	LATA6 = 0;

	DOE = 0;
}

void __interrupt(irq(SMT1PRA)) SMT1PRA_ISR(void){
	LATA6 = 1;
	//high pulse?
	uint32_t diff = 0;
	uint8_t data = -1;
		
//			LATC0 ^=1;// 0;
	SMT1PRAIF = 0;
	
	diff = SMT1CPR;
		diff = (uint32_t) diff * 56UL;

		//		if (diff < 32) {
		//			CVRCONbits.CVR = diff;
		//		}

		if (diff < ((IR_DATA(-1) + IR_DATA(0)) * 8000UL)) {
			//error too short
			data = -1;
//			edgeN = 0;
		} else if (diff < ((IR_DATA(0) + IR_DATA(1)) * 8000UL)) {
			data = 0;
		} else if (diff < ((IR_DATA(1) + IR_DATA(2)) * 8000UL)) {
			data = 1;
		} else if (diff < ((IR_DATA(2) + IR_DATA(3)) * 8000UL)) {
			data = 2;
		} else if (diff < ((IR_DATA(3) + IR_DATA(4)) * 8000UL)) {
			data = 3;
		} else if (diff < ((IR_DATA(4) + IR_DATA(5)) * 8000UL)) {
			data = 4;
		} else if (diff < ((IR_DATA(5) + IR_DATA(6)) * 8000UL)) {
			data = 5;
		} else if (diff < ((IR_DATA(6) + IR_DATA(7)) * 8000UL)) {
			data = 6;
		} else if (diff < ((IR_DATA(7) + IR_DATA(8)) * 8000UL)) {
			data = 7;
		} else if (diff < ((IR_START + IR_STOP) * 8000UL)) {
//			not START
			data = -1;
//			data = 9;
//			edgeN = 1;
		} else {
			//STOP
//			goto SMT1PRA_ISR_NO_DATA;
			data = 10;
//			edgeN = 0;
		}
	bufWriteIntIC1(&irRxBuffer,data);
	SMT1PRA_ISR_NO_DATA:
	
	SMT1IE = 0;//stop detect disable
	SMT1PR = 0xffffff;
	SMT1PWAIF = 0;
	SMT1PWAIE = 1;
	LATA6 = 0;

	DOE = 0;
}

void __interrupt(irq(SMT1)) SMT1_ISR(void)
{
	LATA6 = 1;
	//stop detect
	SMT1IF = 0;
	SMT1IE = 0;
	SMT1PR = 0xffffff;
	bufWriteIntIC1(&irRxBuffer, 10);
	LATC0 ^= 1;
	LATA6 = 0;

	DOE = 0;
}


void __interrupt(irq(TMR5)) TMR5_ISR(void)
{
	static uint8_t c = 0;
	
	TMR5IF = 0;
	swProcess();
	LED(c,led[c]);
	c++;
	if(c>2){c=0;}
	
	countNoDreq++;
}

void __interrupt(irq(IOC)) IOC_ISR(void)
{
//	IOCAF = 0;
	IOCBF = 0;
//	IOCCF = 0;
//	IOCEF = 0;
}

void __interrupt(irq(DMA1SCNT)) DMA1SCNT_ISR(void)
{
	DMA1SCNTIF = 0;

//	DOE = 0;
}

void __interrupt(irq(CCP1)) CCP1_ISR(void)
{
	CCP1IF = 0;

	DOE = 0;
}

