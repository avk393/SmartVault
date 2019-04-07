// Timer2.h
// Runs on LM4F120/TM4C123
// Use Timer2 in 32-bit periodic mode to request interrupts at a periodic rate
// Daniel Valvano
// September 20, 2018


/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2018
  Program 7.5, example 7.6

 Copyright 2018 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

#ifndef __TIMERS_H__ // do not include more than once
#define __TIMERS_H__
void Timer0A_Init(void(*task)(void),uint32_t period, uint32_t priority);
void Timer0A_EnableClock(void);
void Timer0A_DisableClock(void);
void Timer0A_Reload(uint32_t period);
void Timer0A_Arm(void);
void Timer0A_Disarm(void);
void Timer0A_Ack(void);
void Timer0A_Handler(void);

void Timer1A_Init(void(*task)(void),uint32_t period, uint32_t priority);
void Timer1A_EnableClock(void);
void Timer1A_DisableClock(void);
void Timer1A_Reload(uint32_t period);
void Timer1A_Arm(void);
void Timer1A_Disarm(void);
void Timer1A_Ack(void);
void Timer1A_Handler(void);

void Timer2A_Init(void(*task)(void),uint32_t period, uint32_t priority);
void Timer2A_EnableClock(void);
void Timer2A_DisableClock(void);
void Timer2A_Reload(uint32_t period);
void Timer2A_Arm(void);
void Timer2A_Disarm(void);
void Timer2A_Ack(void);
void Timer2A_Handler(void);

void Timer3A_Init(void(*task)(void),uint32_t period, uint32_t priority);
void Timer3A_EnableClock(void);
void Timer3A_DisableClock(void);
void Timer3A_Reload(uint32_t period);
void Timer3A_Arm(void);
void Timer3A_Disarm(void);
void Timer3A_Ack(void);
void Timer3A_Handler(void);


void Timer4A_Init(void(*task)(void),uint32_t period, uint32_t priority);
void Timer4A_EnableClock(void);
void Timer4A_DisableClock(void);
void Timer4A_Reload(uint32_t period);
void Timer4A_Arm(void);
void Timer4A_Disarm(void);
void Timer4A_Ack(void);

void Timer5A_Init(void(*task)(void),uint32_t period, uint32_t priority);
void Timer5A_EnableClock(void);
void Timer5A_DisableClock(void);
void Timer5A_Reload(uint32_t period);
void Timer5A_Arm(void);
void Timer5A_Disarm(void);
void Timer5A_Ack(void);


#endif // __TIMER3INTS_H__
