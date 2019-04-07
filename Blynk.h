#include <stdint.h>
#include "stdbool.h"
volatile static uint32_t LED;      // VP1
volatile static uint32_t LastF;    // VP74
void TM4C_to_Blynk(uint32_t pin,uint32_t value);
void TM4CtoBlynk(uint32_t pin,char *value);
void Blynk_to_TM4C(void);
void SendInformation(void);
void Blynk_Init(void);
bool getKeypadAccessStatus(void);
uint32_t getBlynkPasswordEntry(void);

#ifndef _PORTFH_
#define _PORTFH_
#define PF0       (*((volatile uint32_t *)0x40025004))
#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
#define PF4       (*((volatile uint32_t *)0x40025040))
#define SWITCHES  (*((volatile uint32_t *)0x40025044))
#define SW1       0x10    // on the left side of the Launchpad board
#define SW2       0x01    // on the right side of the Launchpad board
#define RED       0x02
#define BLUE      0x04
#define GREEN     0x08
	
#endif
