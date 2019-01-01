/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

struct MoniteringSwitch
{
	uint8_t count;
	uint8_t state;
	uint8_t num;
	uint8_t pre;
	uint8_t next;
};

void StandbyUiBoardIO(void);
void InitUiBoardIO(void);
void swProcess(void);

#define N_PUSHABLE	3

extern struct MoniteringSwitch mSw[];
extern uint8_t firstPush;
extern uint8_t lastPush;
extern uint8_t nPushing;
extern uint8_t sw[];
extern uint8_t report[];
