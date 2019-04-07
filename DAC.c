#include <stdint.h>
#include "tm4c123gh6pm.h"

//********DAC_Init*****************
// Initialize Max5353 12-bit DAC
// inputs:  initial voltage output (0 to 4095)
// outputs: none
// assumes: system clock rate less than 20 MHz
void DAC_Init(uint16_t data){
  SYSCTL_RCGCSSI_R |= 0x02;       // activate SSI1
  SYSCTL_RCGCGPIO_R |= 0x20;      // activate port F
  while((SYSCTL_PRGPIO_R&0x20) == 0){};	// ready?
  GPIO_PORTF_AFSEL_R |= 0x0E;     // enable alt funct on PD0,1,3
  GPIO_PORTF_DEN_R |= 0x0E;       // configure PD0,1,3 as SSI
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFF000F)+0x00002220;
  GPIO_PORTF_AMSEL_R = 0;         // disable analog functionality on PA
  SSI1_CR1_R = 0x00000000;        // disable SSI, master mode
  SSI1_CPSR_R = 0x02;             // 8 MHz SSIClk 
  SSI1_CR0_R &= ~(0x0000FFF0);    // SCR = 4, SPH = 0, SPO = 1 Freescale
  SSI1_CR0_R |= 0x040F;             // DSS = 16-bit data
  SSI1_DR_R = data;               // load 'data' into transmit FIFO
  SSI1_CR1_R |= 0x00000002;       // enable SSI

}

//********DAC_Out*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: none
void DAC_Out(uint16_t code){   
  //while((SSI1_SR_R&0x00000002)==0){};// SSI Transmit FIFO Not Full
  SSI1_DR_R = code; }                // data out, no reply
  
//********DAC_Out*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: reply is returned
// send the 16-bit code to the SSI, return a reply
uint16_t DAC_Out2(uint16_t code){   uint16_t receive;
  while((SSI1_SR_R&0x00000002)==0){};// SSI Transmit FIFO Not Full
  SSI1_DR_R = code;                  // data out
  while((SSI1_SR_R&0x00000004)==0){};// SSI Receive FIFO Not Empty
  receive = SSI1_DR_R;               // acknowledge response
  return receive;
}

//********DAC_Out*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: none
// send the 16-bit code to the SSI, 
/*
void DAC_OutRaw(uint16_t code){  
  GPIO_PORTA_DATA_R &= ~0x08;        // PA3 FSS low
  
  while((SSI0_SR_R&0x00000002)==0){};// SSI Transmit FIFO Not Full
  SSI0_DR_R = code;                  // data out

  GPIO_PORTA_DATA_R |= 0x08;         // PA3 FSS high
}
*/
