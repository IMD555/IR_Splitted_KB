#define getKeyGroup(kc) (kc & 0xf000)

#define ____	0
#define xxxx	0

#define KEY_NORMAL 0x0000

#define __A_ 0x04 // Keyboard a and A
#define __B_ 0x05 // Keyboard b and B
#define __C_ 0x06 // Keyboard c and C
#define __D_ 0x07 // Keyboard d and D
#define __E_ 0x08 // Keyboard e and E
#define __F_ 0x09 // Keyboard f and F
#define __G_ 0x0a // Keyboard g and G
#define __H_ 0x0b // Keyboard h and H
#define __I_ 0x0c // Keyboard i and I
#define __J_ 0x0d // Keyboard j and J
#define __K_ 0x0e // Keyboard k and K
#define __L_ 0x0f // Keyboard l and L
#define __M_ 0x10 // Keyboard m and M
#define __N_ 0x11 // Keyboard n and N
#define __O_ 0x12 // Keyboard o and O
#define __P_ 0x13 // Keyboard p and P
#define __Q_ 0x14 // Keyboard q and Q
#define __R_ 0x15 // Keyboard r and R
#define __S_ 0x16 // Keyboard s and S
#define __T_ 0x17 // Keyboard t and T
#define __U_ 0x18 // Keyboard u and U
#define __V_ 0x19 // Keyboard v and V
#define __W_ 0x1a // Keyboard w and W
#define __X_ 0x1b // Keyboard x and X
#define __Y_ 0x1c // Keyboard y and Y
#define __Z_ 0x1d // Keyboard z and Z

#define __1_ 0x1e // Keyboard 1 and !
#define __2_ 0x1f // Keyboard 2 and @
#define __3_ 0x20 // Keyboard 3 and #
#define __4_ 0x21 // Keyboard 4 and $
#define __5_ 0x22 // Keyboard 5 and %
#define __6_ 0x23 // Keyboard 6 and ^
#define __7_ 0x24 // Keyboard 7 and &
#define __8_ 0x25 // Keyboard 8 and *
#define __9_ 0x26 // Keyboard 9 and (
#define __0_ 0x27 // Keyboard 0 and )

#define ENT_ 0x28 // Keyboard Return (ENTER)
#define ESC_ 0x29 // Keyboard ESCAPE
#define BSP_ 0x2a // Keyboard DELETE (Backspace)
#define TAB_ 0x2b // Keyboard Tab
#define _SP_ 0x2c // Keyboard Spacebar
#define MIN_ 0x2d // Keyboard - and _
#define EQU_ 0x2e // Keyboard = and +
#define BR_L 0x2f // Keyboard [ and {
#define BR_R 0x30 // Keyboard ] and }
#define BSLA 0x31 // Keyboard \ and |
#define HASH 0x32 // Keyboard Non-US # and ~
#define SEMI 0x33 // Keyboard ; and :
#define APOS 0x34 // Keyboard ' and "
#define GRAV 0x35 // Keyboard ` and ~
#define COMM 0x36 // Keyboard , and <
#define DOT_ 0x37 // Keyboard . and >
#define SLAS 0x38 // Keyboard / and ?
#define CAPS 0x39 // Keyboard Caps Lock

#define _F1_ 0x3a // Keyboard F1
#define _F2_ 0x3b // Keyboard F2
#define _F3_ 0x3c // Keyboard F3
#define _F4_ 0x3d // Keyboard F4
#define _F5_ 0x3e // Keyboard F5
#define _F6_ 0x3f // Keyboard F6
#define _F7_ 0x40 // Keyboard F7
#define _F8_ 0x41 // Keyboard F8
#define _F9_ 0x42 // Keyboard F9
#define F10_ 0x43 // Keyboard F10
#define F11_ 0x44 // Keyboard F11
#define	F12_ 0x45 // Keyboard F12

#define SYSR 0x46 // Keyboard Print Screen
#define SCLK 0x47 // Keyboard Scroll Lock
#define PAUS 0x48 // Keyboard Pause
#define INSE 0x49 // Keyboard Insert
#define HOME 0x4a // Keyboard Home
#define P_UP 0x4b // Keyboard Page Up
#define DEL_ 0x4c // Keyboard Delete Forward
#define END_ 0x4d // Keyboard End
#define P_DN 0x4e // Keyboard Page Down
#define C_RT 0x4f // Keyboard Right Arrow
#define C_LT 0x50 // Keyboard Left Arrow
#define C_DN 0x51 // Keyboard Down Arrow
#define C_UP 0x52 // Keyboard Up Arrow

#define NUML 0x53 // NumLock
#define _N1_ 0x59 // Num 1
#define _N2_ 0x5a
#define _N3_ 0x5b
#define _N4_ 0x5c
#define _N5_ 0x5d
#define _N6_ 0x5e
#define _N7_ 0x5f
#define _N8_ 0x60
#define _N9_ 0x61
#define _N0_ 0x62 //Num 0

#define APP_ 0x65 // Keyboard Application

#define F13_ 0x68 // Keyboard F13
#define F14_ 0x69 // Keyboard F14
#define F15_ 0x6a // Keyboard F15
#define F16_ 0x6b // Keyboard F16
#define F17_ 0x6c // Keyboard F17 not work on Win10
#define F18_ 0x6d // Keyboard F18 not work on Win10
#define F19_ 0x6e // Keyboard F19 not work on Win10
#define F20_ 0x6f // Keyboard F20 not work on Win10
#define F21_ 0x70 // Keyboard F21 not work on Win10
#define F22_ 0x71 // Keyboard F22 not work on Win10
#define F23_ 0x72 // Keyboard F23 not work on Win10
#define	F24_ 0x73 // Keyboard F24 not work on Win10

#define HELP 0x75 // Keyboard Help not work on Win10 
#define CLER 0x9c // Keyboard Clear not work on Win10 
#define INT1 0x87 // Keyboard F23 not work on Win10 
#define	LNG1 0x90 // Keyboard F24 not work on Win10 


#define CONV F13_ // Keyboard F13
#define NCNV F14_ // Keyboard F13
#define IMON F15_ // Keyboard F13

//Japanese key
#define JAT_    BR_L    //ok
#define JBRL    BR_R    //ok
#define JBRR    HASH    //ok
#define JCOL    APOS    //ok
#define JFH_    GRAV    //ok
#define JCON    0x8a    //NG on RN42
#define JNCO    0x8b    //NG on RN42
//#define JCOL    


////Modifier keys
//#define KEY_MODIFIER_LATCH 0x1000
//
//#define CTLL (KEY_MODIFIER_LATCH| 0x00) // Keyboard Left Control
//#define SHLL (KEY_MODIFIER_LATCH| 0x01) // Keyboard Left Shift
//#define ALLL (KEY_MODIFIER_LATCH| 0x02) // Keyboard Left Alt
//#define GULL (KEY_MODIFIER_LATCH| 0x03) // Keyboard Left GUI
//#define CTRL (KEY_MODIFIER_LATCH| 0x04) // Keyboard Right Control
//#define SHRL (KEY_MODIFIER_LATCH| 0x05) // Keyboard Right Shift
//#define ALRL (KEY_MODIFIER_LATCH| 0x06) // Keyboard Right Alt
//#define GURL (KEY_MODIFIER_LATCH| 0x07) // Keyboard Right GUI


//Modifier keys
#define KEY_MODIFIER 0x2000

#define CT_L (KEY_MODIFIER | 0x00) // Keyboard Left Control
#define SH_L (KEY_MODIFIER | 0x01) // Keyboard Left Shift
#define AL_L (KEY_MODIFIER | 0x02) // Keyboard Left Alt
#define GU_L (KEY_MODIFIER | 0x03) // Keyboard Left GUI
#define CT_R (KEY_MODIFIER | 0x04) // Keyboard Right Control
#define SH_R (KEY_MODIFIER | 0x05) // Keyboard Right Shift
#define AL_R (KEY_MODIFIER | 0x06) // Keyboard Right Alt
#define GU_R (KEY_MODIFIER | 0x07) // Keyboard Right GUI


//Madia keys
#define KEY_MEDIA 0x3000

#define V_UP (KEY_MEDIA|0x04)	//Volume up
#define V_DN (KEY_MEDIA|0x05)	//Volume down
#define MUTE (KEY_MEDIA|0x06)	//Mute
#define PLAY (KEY_MEDIA|0x07)	//Play/Pause
#define NEXT (KEY_MEDIA|0x08)	//Next Track
#define PREV (KEY_MEDIA|0x09)	//Previous Track
#define STOP (KEY_MEDIA|0x0a)	//Stop
#define EJCT (KEY_MEDIA|0x0b)	//Eject
#define FAST (KEY_MEDIA|0x0c)	//Fast forward
#define REWD (KEY_MEDIA|0x0d)	//Rewind
//#define STEJ (KEY_MEDIA|0x0e)	//Stop/Eject
#define SLEP (KEY_MEDIA|0x0e)	//Sleep

//Alt codes
#define KEY_ALTCODE 0x6000

#define JYEN (KEY_ALTCODE|0x157)	//Yen
#define JBSL (KEY_ALTCODE|0x092)	//BackSlash
#define PIPE (KEY_ALTCODE|0x124)	//|
#define UBAR (KEY_ALTCODE|0x095)	//_
#define OMEG (KEY_ALTCODE|0x234)	//Omega
#define HALF (KEY_ALTCODE|0x171)	//1/2
#define QUTR (KEY_ALTCODE|0x172)	//1/4
#define _MU_ (KEY_ALTCODE|0x230)	//Mu
#define PLMN (KEY_ALTCODE|0x241)	//+-
#define DIV_ (KEY_ALTCODE|0x246)	//Division
#define SQUA (KEY_ALTCODE|0x253)	//^2
#define SQRT (KEY_ALTCODE|0x251)	//root
#define NOMT (KEY_ALTCODE|0x243)	//Not more than
#define NOLT (KEY_ALTCODE|0x242)	//Not less than
#define _PI_ (KEY_ALTCODE|0x227)	//Pi

//Special keys
#define KEY_SPECIAL 0xf000

#define FN_L (KEY_SPECIAL|0x00)
#define FN_R (KEY_SPECIAL|0x01)
//#define FNLL (KEY_SPECIAL|0x02)
//#define FNRL (KEY_SPECIAL|0x03)
//#define MD_1 (KEY_SPECIAL|0x10)
//#define MD_2 (KEY_SPECIAL|0x11)
//#define MD_3 (KEY_SPECIAL|0x12)
//#define	CONN (KEY_SPECIAL|0x20)
//#define	DISC (KEY_SPECIAL|0x21)
//#define SHDN (KEY_SPECIAL|0x22)
//#define	BATT (KEY_SPECIAL|0x23)	//Battery check
//#define	LASR (KEY_SPECIAL|0x24)	//Battery check
//#define vKey (KEY_SPECIAL|0x0d) // Toggle iPhone virtual keyboard 
//#define	MEM1 KEY_SPECIAL|0x
//#define	MEM2 KEY_SPECIAL|0x0a
//#define	MEM3 KEY_SPECIAL|0x0b


////Mouse axis Keys
//#define KEY_MOUSE_AXIS 0x4000
//
//#define	m_UU (KEY_MOUSE_AXIS | 0x00)
//#define	m_UL (KEY_MOUSE_AXIS | 0x01)
//#define	m_LL (KEY_MOUSE_AXIS | 0x02)
//#define	m_DL (KEY_MOUSE_AXIS | 0x03)
//#define	m_DD (KEY_MOUSE_AXIS | 0x04)
//#define	m_DR (KEY_MOUSE_AXIS | 0x05)
//#define	m_RR (KEY_MOUSE_AXIS | 0x06)
//#define	m_UR (KEY_MOUSE_AXIS | 0x07)
//#define	M_UU (KEY_MOUSE_AXIS | 0x10)
//#define	M_UL (KEY_MOUSE_AXIS | 0x11)
//#define	M_LL (KEY_MOUSE_AXIS | 0x12)
//#define	M_DL (KEY_MOUSE_AXIS | 0x13)
//#define	M_DD (KEY_MOUSE_AXIS | 0x14)
//#define	M_DR (KEY_MOUSE_AXIS | 0x15)
//#define	M_RR (KEY_MOUSE_AXIS | 0x16)
//#define	M_UR (KEY_MOUSE_AXIS | 0x17)
//#define	S_UP (KEY_MOUSE_AXIS | 0xf0)	//Mouse scroll up
//#define	S_DN (KEY_MOUSE_AXIS | 0xf1)	//Mouse scroll down
//
//
////Mouse Keys
//#define KEY_MOUSE 0x5000
//
//#define	CL_L (KEY_MOUSE | 0x01)	//Mouse click left
//#define	CL_M (KEY_MOUSE | 0x02)	//Mouse click right
//#define	CL_R (KEY_MOUSE | 0x03)	//Mouse click middle
//#define	M_FT (KEY_MOUSE | 0x04)	//Fast
//#define	M_SW (KEY_MOUSE | 0x05)	//Slow


//for combination Keys
//use only left modifier keys
#define KEY_MOD_CTRL  0x0100
#define KEY_MOD_SHIFT 0x0200
#define KEY_MOD_ALT   0x0400
#define KEY_MOD_META  0x0800

//Combination Keys
#define KEY_COMBI 0x7000

#define TABR (KEY_COMBI|KEY_MOD_CTRL | TAB_)
#define TABL (KEY_COMBI|KEY_MOD_CTRL | KEY_MOD_SHIFT | TAB_)

#define NFWD (KEY_COMBI|KEY_MOD_ALT | C_RT)   //for nasne
#define NBAK (KEY_COMBI|KEY_MOD_ALT | C_LT)

#define	EXIT (KEY_COMBI|KEY_MOD_ALT | _F4_)
#define	LGUS (KEY_COMBI|KEY_MOD_ALT | KEY_MOD_SHIFT | __0_)
#define	LGJP (KEY_COMBI|KEY_MOD_ALT | KEY_MOD_SHIFT | __1_)


#define KEY_MACRO 0x8000
#define	KANA KEY_MACRO|0x0c	//Set language to Japanese & IME ON
//LGJP,IMON
#define	SMAL KEY_MACRO|0x0d	//Capslock OFF
//LGUS,Shift↓↑
#define	SMIL KEY_MACRO|0x0e	//Smile :)
//Shift↓ ;↓↑ 0↓↑ Shift↑ 

