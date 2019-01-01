/*
 * File:   swMatrix.c
 * Author: imada
 *
 * Created on May 30, 2018, 7:46 PM
 */

#include <xc.h>         /* XC8 General Include File */

//#include <stdint.h>         /* For uint8_t definition */
//#include <stdbool.h>        /* For true/false definition */
//#include <stdlib.h>        

#include "swMatrix.h"
#include "HID_Define.h"

//#define	ON_COUNT	5

#define N_PUSHABLE	10
//
//#define B2(n) n,     n+1,     n+1,     n+2
//#define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
//#define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
//static const unsigned char popCount8bits[] = {
//	B6(0), B6(1), B6(1), B6(2)
//};
//
//static const unsigned char bitOrderSwap[] = {
//	0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
//	0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
//	0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
//	0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
//	0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
//	0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
//	0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
//	0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
//	0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
//	0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
//	0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
//	0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
//	0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
//	0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
//	0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
//	0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
//};

//#define	popCount16bits(x)	(popCount8bits[(unsigned char)x]+popCount8bits[(unsigned char)(x >> 8)])

const uint16_t keymap[] = {
	//	Left
	//0     1     2     3     4     5     6     7  
	ESC_, STOP, MUTE, V_DN, V_UP, PLAY, PREV, NEXT, //0x0n
	BSP_, GRAV, __1_, __2_, __3_, __4_, __5_, __6_, //0x1n
	P_UP, TAB_, __Q_, __W_, __E_, __R_, __T_, __Y_, //0x2n
	xxxx, SMAL, __A_, __S_, __D_, __F_, __G_, xxxx, //0x3n
	P_DN, SH_L, __Z_, __X_, __C_, __V_, __B_, xxxx, //0x4n
	xxxx, KANA, CT_L, GU_L, AL_L, _SP_, FN_L, xxxx, //0x5n

	//Right
	//0     1     2     3     4     5     6     7  
	_F5_, SLEP, MUTE, V_DN, V_UP, PLAY, PREV, NEXT, //0x0n
	__7_, __8_, __9_, __0_, MIN_, EQU_, xxxx, BSP_, //0x1n
	__Y_, __U_, __I_, __O_, __P_, BR_L, BR_R, BSLA, //0x2n
	__H_, __J_, __K_, __L_, SEMI, APOS, xxxx, ENT_, //0x3n
	__N_, __M_, COMM, DOT_, SLAS, SH_R, C_UP, DEL_, //0x4n
	FN_R, xxxx, _SP_, AL_R, xxxx, C_LT, C_DN, C_RT, //0x5n
};

const uint16_t keymapFn[] = {
	//	Left
	//0     1     2     3     4     5     6     7  
	EXIT, STOP, MUTE, V_DN, V_UP, PLAY, TABL, TABR, //0x0n
	DEL_, GRAV, _F1_, _F2_, _F3_, _F4_, _F5_, _F6_, //0x1n
	HOME, ENT_, _F7_, _F8_, __U_, __I_, __O_, __P_, //0x2n
	xxxx, CAPS, NCNV, __H_, __J_, __K_, __L_, xxxx, //0x3n
	END_, SH_L, C_UP, __N_, __M_, COMM, DOT_, xxxx, //0x4n
	xxxx, SMIL, C_LT, C_DN, C_RT, CONV, FN_L, xxxx, //0x5n

	//Right
	//0     1     2     3     4     5     6     7  
	_F5_, SLEP, MUTE, V_DN, V_UP, PLAY, PREV, NEXT, //0x0n
	_F7_, _F8_, _F9_, F10_, F11_, F12_, xxxx, BSP_, //0x1n
	__Q_, __W_, __E_, __R_, __T_, BR_L, BR_R, BSLA, //0x2n
	__A_, __S_, __D_, __F_, __G_, APOS, xxxx, ENT_, //0x3n
	__Z_, __X_, __C_, __V_, __B_, SH_R, C_UP, INSE, //0x4n
	FN_R, xxxx, APP_, AL_R, xxxx, C_LT, C_DN, C_RT, //0x5n
};

struct MoniteringSwitch mSw[N_PUSHABLE];
uint8_t firstPush = 0xff;
uint8_t lastPush = 0xff;
uint8_t fnEnable = 0;

//unsigned short sw[N_ROW];
//extern static KEYBOARD_INPUT_REPORT inputReport;
//extern static COMSUMER_INPUT_REPORT inputComsumerReport;


/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */
void swInit(void)
{
	for (uint8_t c = 0; c < N_PUSHABLE; c++) {
		//		mSw[c].count = 0;
		mSw[c].num = 0xff;
		mSw[c].kc = 0;
	}
		inputComsumerReport.buttons.value = 0;
	for (uint8_t c = 0; c < 6; c++) {
		inputReport.keys[c] = 0;
	}
}

void swUnregister(unsigned char c)
{
	switch (getKeyGroup(mSw[c].kc)) {
	case KEY_NORMAL: //Normal keys
		break;
	case KEY_MODIFIER: //Modifier keys
		inputReport.modifiers.value &= ~(1 << (mSw[c].kc & 0x07));
		break;
	case KEY_MEDIA: //Consumer report keys
		inputComsumerReport.buttons.value &= ~(0x01 << (unsigned char) mSw[c].kc);
		break;
	case KEY_SPECIAL: //Special keyboard keys
		switch (mSw[c].kc) {
		case FN_L:
		case FN_R:
			fnEnable = 0;
			break;
		}
		break;
	}

	//	mSw[c].state = 0;
	mSw[c].num = 0xff;
	mSw[c].kc = 0;

	if (mSw[c].next == 0xff) {
		lastPush = mSw[c].pre;
		if (lastPush != 0xff) {
			mSw[lastPush].next = 0xff;
		}
	} else {
		mSw[mSw[c].next].pre = mSw[c].pre;
	}

	if (mSw[c].pre == 0xff) {
		firstPush = mSw[c].next;
		if (firstPush != 0xff) {
			mSw[firstPush].pre = 0xff;
		}
	} else {
		mSw[mSw[c].pre].next = mSw[c].next;
	}
}

void swRegister(unsigned char n)
{
	unsigned char c;

	for (c = 0; c < N_PUSHABLE; c++) {
		if (mSw[c].num == n) {
			return; //Already registered
		}
	}
	
	for (c = 0; c < N_PUSHABLE; c++) {
		if (mSw[c].num == 0xff) {
			mSw[c].num = n;
			mSw[c].kc = fnEnable ? keymapFn[n] : keymap[n];
			//			mSw[c].count = 1;
			mSw[c].next = 0xff;
			if (firstPush == 0xff) {
				firstPush = c;
				mSw[c].pre = 0xff;
			} else {
				mSw[lastPush].next = c;
				mSw[c].pre = lastPush;
			}
			lastPush = c;
			break;
		}
	}

	switch (getKeyGroup(mSw[c].kc)) {
	case KEY_NORMAL: //Normal keys
		break;
	case KEY_MODIFIER: //Modifier keys
		inputReport.modifiers.value |= 1 << (mSw[c].kc & 0x07);
		break;
	case KEY_MEDIA: //Consumer report keys
		inputComsumerReport.buttons.value |= 0x01 << (unsigned char) mSw[c].kc;
		break;
	case KEY_SPECIAL: //Special keyboard keys
		switch (mSw[c].kc) {
		case FN_L:
		case FN_R:
			fnEnable = 1;
			break;
		}
		break;
		//	case KEY_ALTCODE: //
		//		if (keyReport.modifierLatch.bits.ShiftL | keyReport.modifierLatch.bits.ShiftR | keyReport.modifier.bits.ShiftL | keyReport.modifier.bits.ShiftR | keyReport.modifier2.bits.ShiftL | keyReport.modifier2.bits.ShiftR) {
		//			if (mSw[c].kc == JBSL) {
		//				mSw[c].kc = UBAR;
		//			} else if (mSw[c].kc == JYEN) {
		//				mSw[c].kc = PIPE;
		//			}
		//		}
		//		altCode = 0xfff & mSw[c].kc;
		//		mainFlags.sendAltCodeReport = 1;
		//		break;
	}
}
