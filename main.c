#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "PLL.h"
#include "Timers.h"
#include "UART.h"
#include "Ports.h"
#include "esp8266.h"
#include "Blynk.h"
#include "stepper.h"
#include "Limit_Sensor.h"
#include "matrix.h"
#include "stateprocessor.h"
#include "LCDDriver.h"
#include "SPIDriver.h"
#include "musicStruct.h"
#include "musicPlayer.h"
//


void EnableInterrupts(void);    // Defined in startup.s
void DisableInterrupts(void);   // Defined in startup.s
void WaitForInterrupt(void);    // Defined in startup.s


char Buffer[4];
char Password[4]="1234";
uint32_t KeyCount;

LockState lockState = {false,false,0,"1234","    ",0,{0,1,2,3},0,false};
extern SimpleSong BADSOUND;
extern SimpleSong JINGLE;
extern SimpleSong GOODSOUND;

int main(void){
  PLL_Init(Bus80MHz);   // Bus clock at 80 MHz
  DisableInterrupts();  // Disable interrupts until finished with inits
  

	uint32_t i=0;
	InitializeLCD();
	//Blynk_Init();	//timer 2 3
	Matrix_Init();				//Timer 5
	playerInit(JINGLE); //Timer0 1
	Limit_Sensor_Init();
	Stepper_Init();
	//blynks every two seconds
	//playerInit(TEST1);

	EnableInterrupts();
	//while(1){door_Open(50*speed);}
  while(1) {
		Buffer[i] = Matrix_InChar();
		processInput(lockState.state[lockState.indexState],Buffer[i],0);
    i = (i+1)&0x03;
   // WaitForInterrupt(); // low power mode
  }
}
