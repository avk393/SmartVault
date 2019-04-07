// TM4C123       ESP8266-ESP01 (2 by 4 header)
// PE5 (U5TX) to Pin 1 (Rx)
// PE4 (U5RX) to Pin 5 (TX)
// PE3 output debugging
// PE2 nc
// PE1 output    Pin 7 Reset
// PE0 input     Pin 3 Rdy IO2
//               Pin 2 IO0, 10k pullup to 3.3V  
//               Pin 8 Vcc, 3.3V (separate supply from LaunchPad 
// Gnd           Pin 4 Gnd  
// Place a 4.7uF tantalum and 0.1 ceramic next to ESP8266 3.3V power pin
// Use LM2937-3.3 and two 4.7 uF capacitors to convert USB +5V to 3.3V for the ESP8266
// http://www.ti.com/lit/ds/symlink/lm2937-3.3.pdf
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "stdbool.h"
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Timers.h"
#include "UART.h"
#include "esp8266.h"
#include "Blynk.h"
#include "stateprocessor.h"
#include "Limit_Sensor.h"
#include "stepper.h"
#include "LCDDriver.h"


extern LockState lockState;
void EnableInterrupts(void);    // Defined in startup.s
void DisableInterrupts(void);   // Defined in startup.s
void WaitForInterrupt(void);    // Defined in startup.s

#define FALSE 0
#define TRUE 1
// These 6 variables contain the most recent Blynk to TM4C123 message
// Blynk to TM4C123 uses VP0 to VP15
/*
VP Lists
VP0 --> initializes password change
VP2 --> saves password numerical input
VP1 --> password numerical input
VP3 --> toggle lock on keypad input
VP4 --> turn off alarm

VP70 --> displays status of door
*/
char serial_buf[64];
char Pin_Number[2]   = "99";       // Initialize to invalid pin number
char Pin_Integer[8]  = "0000";     //
char Pin_Float[8]    = "0.0000";   //
uint32_t pin_num; 
uint32_t pin_int;

volatile uint32_t password_entry;
volatile bool keypad_access = TRUE;
volatile bool password_reset_mode = FALSE;
volatile bool keypad_flag = FALSE;					// tells us status of keypad when resetting password

char open [5] = {'o','p','e','n','\0'};
char closed [7] = {'c','l','o','s','e','d','\0'};
char moving[7]={'m','o','v','i','n','g','\0'};
 
char *itoa (int32_t value, char *result, int base){
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

void Blynk_Init(void){	
#ifdef DEBUG3
  ST7735_OutString("EE445L Lab 4D\nBlynk example\n");
#endif
#ifdef DEBUG1
  UART_Init(5);         // Enable Debug Serial Port
  UART_OutString("\n\rEE445L Lab 4D\n\rBlynk example");
#endif
  ESP8266_Init();       // Enable ESP8266 Serial Port
  ESP8266_Reset();      // Reset the WiFi module
  ESP8266_SetupWiFi();  // Setup communications to Blynk Server  
  
  Timer2A_Init(&Blynk_to_TM4C,800000,4); 
  // check for receive data from Blynk App every 10ms

  Timer3A_Init(&SendInformation,40000000,4);
  // Send data back to Blynk App every 1/2 second
}

// ----------------------------------- TM4C_to_Blynk ------------------------------
// Send data to the Blynk App
// It uses Virtual Pin numbers between 70 and 99
// so that the ESP8266 knows to forward the data to the Blynk App
void TM4C_to_Blynk(uint32_t pin,uint32_t value){
  if((pin < 70)||(pin > 99)){
    return; // ignore illegal requests
  }
// your account will be temporarily halted if you send too much data
  ESP8266_OutUDec(pin);       // Send the Virtual Pin #
  ESP8266_OutChar(',');
  ESP8266_OutUDec(value);      // Send the current value
  ESP8266_OutChar(',');
  ESP8266_OutString("0.0\n");  // Null value not used in this example
}

void TM4CtoBlynk(uint32_t pin,char *value){
  if((pin < 70)||(pin > 99)){
    return; // ignore illegal requests
  }
// your account will be temporarily halted if you send too much data
  ESP8266_OutUDec(pin);       // Send the Virtual Pin #
  ESP8266_OutChar(',');
  ESP8266_OutString(value);      // Send the current value
  ESP8266_OutChar(',');
  ESP8266_OutString("0.0\n");  // Null value not used in this example
}
 
// -------------------------   Blynk_to_TM4C  -----------------------------------
// This routine receives the Blynk Virtual Pin data via the ESP8266 and parses the
// data and feeds the commands to the TM4C.
void Blynk_to_TM4C(void){int j; char data;
// Check to see if a there is data in the RXD buffer
  if(ESP8266_GetMessage(serial_buf)){  // returns false if no message
    // Read the data from the UART5
#ifdef DEBUG1
    j = 0;
    do{
      data = serial_buf[j];
      UART_OutChar(data);        // Debug only
      j++;
    }while(data != '\n');
    UART_OutChar('\r');        
#endif
           
// Rip the 3 fields out of the CSV data. The sequence of data from the 8266 is:
// Pin #, Integer Value, Float Value.
    strcpy(Pin_Number, strtok(serial_buf, ","));
    strcpy(Pin_Integer, strtok(NULL, ","));       // Integer value that is determined by the Blynk App
    strcpy(Pin_Float, strtok(NULL, ","));         // Not used
    pin_num = atoi(Pin_Number);     // Need to convert ASCII to integer
    pin_int = atoi(Pin_Integer);  
  
  // indicates user wants to reset password or save entered password
    if(pin_num == 0x00)  {
			if(pin_int==1) {
				if(keypad_flag==FALSE) keypad_access = FALSE;
				password_reset_mode = TRUE;
				processOpenState('A');
			}
			else {
				if(keypad_flag==FALSE) keypad_access = TRUE;
				setState();
			}
    }   
		
		//disables user access to keypad
		else if(pin_num == 0x04){
			if(pin_int) {
				keypad_access = FALSE;
				keypad_flag = TRUE;
			}
			else {
				keypad_access = TRUE;
				keypad_flag = FALSE;
			}
		}
		else if (pin_num == 0x06)
		{
			//password_reset_mode = changePasswordBlynk(pin_int,password_reset_mode);
			if(!password_reset_mode) DisplayPasswordChangeSuccessful();
		}
		//snooze speaker
		else if(pin_num == 0x05){
			//if(pin_int>=1) enableSpeaker();
			//else disableSpeaker();
		}
		
		//manual close/open door
		else if(pin_num == 0x02){
			if(getDoorStatus() == CLOSED){
				while(getDoorStatus() != OPEN) door_Open(10*speed);
				updateToOpenState();
			}
			else if(getDoorStatus() == OPEN){
				while(getDoorStatus() != CLOSED) door_Close(10*speed);
				updateToClosedState();
			}
		}
				
#ifdef DEBUG1
    UART_OutString(" Pin_Number = ");
    UART_OutString(Pin_Number);
    UART_OutString("   Pin_Integer = ");
    UART_OutString(Pin_Integer);
    UART_OutString("   Pin_Float = ");
    UART_OutString(Pin_Float);
    UART_OutString("\n\r");
#endif
  }  
}

void SendInformation(void){
// your account will be temporarily halted if you send too much data
	uint8_t door_status = getDoorStatus();
	TM4CtoBlynk(70, &closed[0]);
	/*if(door_status==0) TM4CtoBlynk(70, &closed[0]);
	else if(door_status==1) TM4CtoBlynk(70, &open[0]);
	else if(door_status==2) TM4CtoBlynk(70, &moving[0]);*/
	//TM4C_to_Blynk(70, door_status);
	
#ifdef DEBUG3
    Output_Color(ST7735_WHITE);
    //ST7735_OutString("Send 74 data=");
    //ST7735_OutChar('\n');
#endif
}

bool getKeypadAccessStatus(void){
	return keypad_access;
}

uint32_t getBlynkPasswordEntry(void){
	return password_entry;
}
