#include <stdint.h>
#include <stdlib.h>
#include "tm4c123gh6pm.h"
#include "SysTick.h"
#include "Limit_Sensor.h"

void Limit_Sensor_Init(void){
	  // **** general initialization ****
  SYSCTL_RCGCGPIO_R |= 0x00000020; // (a) activate clock for port F
  while((SYSCTL_PRGPIO_R & 0x00000020) == 0){};
	GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x11;           // allow changes to PF4-0
  GPIO_PORTF_DIR_R &= ~0x11;    			// (c) make PF0,1 in
  GPIO_PORTF_AFSEL_R &= ~0x11; 			 	//     disable alt funct on PF0,1
	GPIO_PORTF_DEN_R |= 0x11;     			//     enable digital I/O on PF0,1   
  GPIO_PORTF_PCTL_R = 0x00000000; 	// configure PF as GPIO
  GPIO_PORTF_AMSEL_R = 0;       			//     disable analog functionality on PF0,1
	GPIO_PORTF_PUR_R |= 0x11;
  //GPIO_PORTE_IS_R &= ~0x03;     			// 		 PF0,1 is edge-sensitive
  //GPIO_PORTE_IBE_R &= ~0x03;     			//     PF0,1 is NOT both edges
	//GPIO_PORTE_IEV_R |= 0x03;						//	PF0,1 is rising edge

  //Door_Close = doorclose;           // user function 
  //Door_Open = dooropen;       		// user function 
	//GPIOLimitArm();
}

uint8_t getDoorStatus(void){
	//make sure limit sensor output when pressed is 1
	if(GPIO_PORTF_DATA_R&0x01) return CLOSED;
	else if(GPIO_PORTF_DATA_R&0x10) return OPEN;
	else return LIMBO;
}
