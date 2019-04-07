#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "PLL.h"
#include <stdbool.h>

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

void (*PeriodicTask0)(void);   // user function
void (*PeriodicTask1)(void);   // user function
void (*PeriodicTask2)(void);   // user function
void (*PeriodicTask3)(void);   // user function
void (*PeriodicTask4)(void);   // user function
void (*PeriodicTask5)(void);   // user function

//TimerInit()
//Input:Reload,Priority
void Timer0A_Init(void(*task)(void),uint32_t period, uint32_t priority){
  // **** general initialization ****
	  volatile uint32_t delay;
  DisableInterrupts();
  // **** general initialization ****
  SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer0
	PeriodicTask0 = task;         // user function

  delay = SYSCTL_RCGCTIMER_R;      // allow time to finish activating
  TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable timer0A during setup
  TIMER0_CFG_R = 0;                // configure for 32-bit timer mode
  TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
	TIMER0_TAPR_R = 0;  
	// configure for periodic mode 
  TIMER0_TAILR_R = period;         // operates every second //seconds = period/busclock
  TIMER0_IMR_R |= TIMER_IMR_TATOIM;// enable timeout (rollover) interrupt
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// clear timer0A timeout flag
    // enable timer0A 32-b, periodic, interrupts
  // **** interrupt initialization ****
  priority = (priority &0x07)<<29;                             // Timer0A=priority 2
  NVIC_PRI4_R = (NVIC_PRI4_R&0x0FFFFFFF)+priority; // top 3 bits
  NVIC_EN0_R = 1<<19;              // enable interrupt 19 in NVIC
	TIMER0_CTL_R |= TIMER_CTL_TAEN;
	EnableInterrupts();
}
void Timer0A_EnableClock(void){
	TIMER0_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 32-b, periodic, interrupts
}
void Timer0A_DisableClock(void){
	TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable timer0A during setup
}

void Timer0A_Reload(uint32_t period){
	TIMER0_TAILR_R = period; 
}
void Timer0A_Arm(void){
	NVIC_EN0_R = 1<<19;              // enable interrupt 19 in NVIC
}
void Timer0A_Disarm(void){
	NVIC_DIS0_R = 1<<19;              // enable interrupt 19 in NVIC
}
void Timer0A_Ack(void){
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;
}
void Timer0A_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER2A timeout
  (*PeriodicTask0)();               // execute user task
}



//Timer1A
void Timer1A_Init(void(*task)(void),uint32_t period, uint32_t priority){
  volatile uint32_t delay;
	DisableInterrupts();
  SYSCTL_RCGCTIMER_R |= 0x02;   						// 0) activate TIMER1
	PeriodicTask1 = task;         // user function

  delay = SYSCTL_RCGCTIMER_R;   						// allow time to finish activating
  TIMER1_CTL_R &= ~TIMER_CTL_TAEN;   							// 1) disable TIMER1A during setup
  TIMER1_CFG_R = 0x00000000;    						// 2) configure for 32-bit mode
  TIMER1_TAMR_R = TIMER_TAMR_TAMR_PERIOD;   // 3) configure for periodic mode, down-count 
  TIMER1_TAILR_R = period;  								// 4) reload value resets every 20ms second
  TIMER1_TAPR_R = 0;            						// 5) bus clock resolution
	TIMER1_IMR_R |= TIMER_IMR_TATOIM;
	TIMER1_ICR_R = TIMER_ICR_TATOCINT;
	 priority = (priority &0x07)<<13; 
  NVIC_PRI5_R = (NVIC_PRI5_R&0xFFFF00FF); // 8) priority 4 // 15-13  0 1 2 3    4 5 6 7    8 9 10 11    12 13 14 15
	NVIC_PRI5_R = NVIC_PRI5_R | priority;
  NVIC_EN0_R = 1<<21;           						// 9) enable IRQ 21 in NVIC must do
	TIMER1_CTL_R |= TIMER_CTL_TAEN;
	EnableInterrupts();
	
}
void Timer1A_EnableClock(void){
	TIMER1_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 32-b, periodic, interrupts
}
void Timer1A_DisableClock(void){
	TIMER1_CTL_R &= ~TIMER_CTL_TAEN; // disable timer0A during setup
}

void Timer1A_Reload(uint32_t period){
	TIMER1_TAILR_R = period; 
}
void Timer1A_Arm(void){
	NVIC_EN0_R = 1<<21;              // enable interrupt 19 in NVIC
}
void Timer1A_Disarm(void){
	NVIC_DIS0_R = 1<<21;              // enable interrupt 19 in NVIC
}
void Timer1A_Ack(void){
	TIMER1_ICR_R = TIMER_ICR_TATOCINT;
}
void Timer1A_Handler(void){
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER2A timeout
  (*PeriodicTask1)();               // execute user task
}



//Timer2

void Timer2A_Init(void(*task)(void),uint32_t period, uint32_t priority){
	volatile uint32_t delay;
	SYSCTL_RCGCTIMER_R |= 0x04;   						// 0) activate TIMER2
  PeriodicTask2 = task;         // user function
	delay = SYSCTL_RCGCTIMER_R;   						// allow time to finish activating
	DisableInterrupts();
  TIMER2_CTL_R = 0x00000000;   							// 1) disable TIMER2A during setup
  TIMER2_CFG_R = 0x00000000;    						// 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x02;									   // 3) configure for periodic mode, down-count 
  TIMER2_TAILR_R = period-1;  								// 4) reload value resets every 64ms second
  TIMER2_TAPR_R = 0;            						// 5) bus clock resolution
	TIMER2_IMR_R = 0x01;
	TIMER2_ICR_R = 0x00000001;
	priority = (priority&0x07)<<29;					// 
  //NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF); // 8) priority 4 // 15-13  0 1 2 3    4 5 6 7    8 9 10 11    12 13 14 15
	NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000;
  NVIC_EN0_R = 1<<23;           						// 9) enable IRQ 21 in NVIC must do
	TIMER2_CTL_R = 0x00000001;
}

void Timer2A_EnableClock(void){
	TIMER2_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 32-b, periodic, interrupts
}
void Timer2A_DisableClock(void){
	TIMER2_CTL_R &= ~TIMER_CTL_TAEN; // disable Timer1A during setup
}

void Timer2A_Reload(uint32_t period){
	TIMER2_TAILR_R = period; 
}
void Timer2A_Arm(void){
	NVIC_EN0_R = 1<<23;              // enable interrupt 19 in NVIC
}
void Timer2A_Disarm(void){
	NVIC_DIS0_R = 1<<23;              // enable interrupt 19 in NVIC
}

void Timer2A_Ack(void){
	TIMER2_ICR_R = TIMER_ICR_TATOCINT;
}


void Timer2A_Handler(void){
  TIMER2_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER2A timeout
  (*PeriodicTask2)();               // execute user task
}


//Timer3
void Timer3A_Init(void(*task)(void), uint32_t period, uint32_t priority){
	volatile uint32_t delay;
	SYSCTL_RCGCTIMER_R |= 0x08;   						// 0) activate TIMER2
	PeriodicTask3 = task;         						// user function
  delay = SYSCTL_RCGCTIMER_R;   						// allow time to finish activating
	DisableInterrupts();
  TIMER3_CTL_R = 0x00000000;   							// 1) disable TIMER2A during setup
  TIMER3_CFG_R = 0x00000000;    						// 2) configure for 32-bit mode
  TIMER3_TAMR_R = 0x00000002;   					  // 3) configure for periodic mode, down-count 
  TIMER3_TAILR_R = period;  								// 4) reload value resets every 64ms second
  TIMER3_TAPR_R = 0;            						// 5) bus clock resolution
	TIMER3_IMR_R = 0x00000001;    
	TIMER3_ICR_R = 0x00000001; 
	priority = (priority&0x07)<<29;
  NVIC_PRI8_R = (NVIC_PRI8_R&0x00FFFFFF); // 8) priority 4 // 15-13  0 1 2 3    4 5 6 7    8 9 10 11    12 13 14 15
	NVIC_PRI8_R = (NVIC_PRI8_R|priority);
  NVIC_EN1_R = 1 << 3; 
	TIMER3_CTL_R |= 0x00000001;    
}

void Timer3A_EnableClock(void){
	TIMER3_CTL_R |= TIMER_CTL_TAEN;  // enable Timer2A 32-b, periodic, interrupts
}
void Timer3A_DisableClock(void){
	TIMER3_CTL_R &= ~TIMER_CTL_TAEN; // disable Timer2A during setup
}

void Timer3A_Reload(uint32_t period){
	TIMER3_TAILR_R = period; 
}
void Timer3A_Arm(void){
	NVIC_EN1_R = 1<<3;              // enable interrupt 19 in NVIC
}
void Timer3A_Disarm(void){
	NVIC_DIS1_R = 1<<3;              // enable interrupt 19 in NVIC
}
void Timer3A_Ack(void){
	TIMER3_ICR_R = TIMER_ICR_TATOCINT;
}

void Timer3A_Handler(void){
  TIMER3_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER2A timeout
  (*PeriodicTask3)();               // execute user task
}


void Timer4A_Init(void(*task)(void),uint32_t period, uint32_t priority){
	volatile uint32_t delay;
	SYSCTL_RCGCTIMER_R |= 0x10;   						// 0) activate TIMER5
  delay = SYSCTL_RCGCTIMER_R;   						// allow time to finish activating
	PeriodicTask4 = task;         						// user function
	DisableInterrupts();
  TIMER4_CTL_R = 0x00000000;   							// 1) disable TIMER2A during setup
  TIMER4_CFG_R = 0x00000000;    						// 2) configure for 32-bit mode
  TIMER4_TAMR_R = TIMER_TAMR_TAMR_PERIOD;   // 3) configure for periodic mode, down-count 
  TIMER4_TAILR_R = period;  								// 4) reload value resets every 64ms second
  TIMER4_TAPR_R = 0;            						// 5) bus clock resolution
	TIMER4_IMR_R = TIMER_IMR_TATOIM;
	TIMER4_ICR_R = TIMER_ICR_TATOCINT; 
	priority = (priority&0x07)<<21;
  NVIC_PRI17_R = (NVIC_PRI17_R&0xFF1FFFFF); // 8) priority 4 // 15-13  0 1 2 3    4 5 6 7    8 9 10 11    12 13 14 15
	NVIC_PRI17_R = (NVIC_PRI17_R|priority);
  NVIC_EN2_R = 1 << 6; 
	TIMER4_CTL_R |= TIMER_CTL_TAEN;
	EnableInterrupts();
	//21-23   70
}


void Timer4A_EnableClock(void){
	TIMER4_CTL_R |= TIMER_CTL_TAEN;  // enable Timer2A 32-b, periodic, interrupts
}
void Timer4A_DisableClock(void){
	TIMER4_CTL_R &= ~TIMER_CTL_TAEN; // disable Timer2A during setup
}

void Timer4A_Reload(uint32_t period){
	TIMER4_TAILR_R = period; 
}
void Timer4A_Arm(void){
	NVIC_EN2_R = 1<<6;              // enable interrupt 19 in NVIC
}
void Timer4A_Disarm(void){
	NVIC_DIS2_R = 1<<6;              // enable interrupt 19 in NVIC
}
void Timer4A_Ack(void){
	TIMER4_ICR_R = TIMER_ICR_TATOCINT;
}

void Timer4A_Handler(void){
  TIMER4_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER2A timeout
  (*PeriodicTask4)();               // execute user task
} 
//todo timer 5A
void Timer5A_Init(void(*task)(void),uint32_t period, uint32_t priority){
	volatile uint32_t delay;
	SYSCTL_RCGCTIMER_R |= 0x20;   						// 0) activate TIMER2
  delay = SYSCTL_RCGCTIMER_R;   						// allow time to finish activating
	PeriodicTask5 = task;         						// user function
	DisableInterrupts();
  TIMER5_CTL_R = 0x00000000;   							// 1) disable TIMER2A during setup
  TIMER5_CFG_R = 0x00000000;    						// 2) configure for 32-bit mode
  TIMER5_TAMR_R = TIMER_TAMR_TAMR_PERIOD;   // 3) configure for periodic mode, down-count 
  TIMER5_TAILR_R = period;  								// 4) reload value resets every 64ms second
  TIMER5_TAPR_R = 0;            						// 5) bus clock resolution
	TIMER5_IMR_R = TIMER_IMR_TATOIM;
	TIMER5_ICR_R = TIMER_ICR_TATOCINT; 
	priority = (priority&0x07)<<5;
  NVIC_PRI23_R = (NVIC_PRI23_R&0xFFFFFF1F); // 8) priority 4 // 15-13  0 1 2 3    4 5 6 7    8 9 10 11    12 13 14 15
	NVIC_PRI23_R = (NVIC_PRI23_R|priority);
  NVIC_EN2_R = 1 << 28; 
	TIMER5_CTL_R |= TIMER_CTL_TAEN;
	EnableInterrupts();
	//nvic 22 13-15
	//irq 92
}


void Timer5A_EnableClock(void){
	TIMER5_CTL_R |= TIMER_CTL_TAEN;  // enable Timer2A 32-b, periodic, interrupts
}
void Timer5A_DisableClock(void){
	TIMER5_CTL_R &= ~TIMER_CTL_TAEN; // disable Timer2A during setup
}

void Timer5A_Reload(uint32_t period){
	TIMER5_TAILR_R = period; 
}
void Timer5A_Arm(void){
	NVIC_EN2_R = 1<<28;              // enable interrupt 19 in NVIC
}
void Timer5A_Disarm(void){
	NVIC_DIS2_R = 1<<28;              // enable interrupt 19 in NVIC
}
void Timer5A_Ack(void){
	TIMER5_ICR_R = TIMER_ICR_TATOCINT;
}
void Timer5A_Handler(void){
  TIMER5_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER2A timeout
  (*PeriodicTask5)();               // execute user task
}
