/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
void LED(uint8_t digit, uint8_t data);
void sendACK(uint8_t report[], uint8_t pushingCount);
void sendReport(uint8_t command, uint8_t* data, uint8_t dataCount);

//////ABFGCE.D
extern const uint8_t bin2seg7[];