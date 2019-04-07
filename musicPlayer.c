#include "musicStruct.h"
#include <stdint.h>
#include "../../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include <stdbool.h>
#include "SPIDriver.h"
#include "Timers.h"
#include "Systick.h"

SimpleSong *songGlobal;
static uint32_t songcursor=0;
static uint32_t instrumentMelodyCursor;
static uint32_t instrumentHarmonicCursor;
uint32_t stopPlaying=80;
#define PF1             (*((volatile uint32_t *)0x40025008))

extern SimpleSong JINGLE;

void musicStop(void){
	Timer0A_Disarm();
	Timer1A_Disarm();
}

void DisableTimers(void){
	Timer0A_DisableClock();
	Timer1A_DisableClock();
}
void SongChordChange(void){
	songcursor= (songcursor+1);
	if (songcursor>35)
	{
		musicStop();
		DisableTimers();
		songcursor=0;
	}
	Timer1A_Reload(songGlobal->melody[songcursor]);
	instrumentMelodyCursor=0;
	//Timer2A_Reload(songGlobal.harmonic[songcursor]);
	
}

void PlayChord(void){
	static uint16_t  output;
	instrumentMelodyCursor = (instrumentMelodyCursor+1)&0x1F;
	output=(songGlobal->instrument.melody[instrumentMelodyCursor]);
	DACOut(output);
	
}
void playJingleBells(void)
{
	DACInit(0);
	songGlobal = &JINGLE;
	Timer0A_Init(SongChordChange,80000000/4,5);    //80000000/4  is the tempo
	Timer1A_Init(PlayChord,songGlobal->melody[0],6);
	Timer0A_DisableClock();
	Timer1A_DisableClock();
	
	songcursor=0;
	instrumentMelodyCursor=0;
	instrumentHarmonicCursor=0;
}
void playerInit(SimpleSong songLocal){
	DACInit(0);
	songGlobal = &songLocal;
	
	Timer0A_Init(SongChordChange,80000000/4,5);    //80000000/4  is the tempo
	Timer1A_Init(PlayChord,songGlobal->melody[0],6);
	Timer0A_DisableClock();
	Timer1A_DisableClock();
	
	songcursor=0;
	instrumentMelodyCursor=0;
	instrumentHarmonicCursor=0;
	
}
void playerEnableInterrupt(void)
{
	Timer0A_EnableClock();
	Timer1A_EnableClock();
}
void changeSong(SimpleSong songLocal)
{
	songGlobal = &songLocal;
	
	
}
void playFullSong(void)
{
	Timer0A_Init(SongChordChange,80000000/4,5);
	Timer1A_Init(PlayChord,songGlobal->melody[0],6);
	
	Timer0A_EnableClock();
	Timer1A_EnableClock();
}

void PlayOneChord(void){
	static uint16_t  output;
	instrumentHarmonicCursor = (instrumentHarmonicCursor+1)&0x1F;
	output=(songGlobal->instrument.harmonic[instrumentHarmonicCursor]&0x0FF);
	DACOut(output);
}

void PlayOtherChord(void){
	static uint16_t  output;
	instrumentMelodyCursor = (instrumentMelodyCursor+1)&0x1F;
	output=((songGlobal->instrument.melody[instrumentMelodyCursor]+songGlobal->instrument.harmonic[instrumentHarmonicCursor])&0x0FF);
	DACOut(output);
}
void musicPlay(void){
	
	Timer0A_Arm();
	Timer1A_Arm();
	Timer0A_EnableClock();
	Timer1A_EnableClock();
}

void playForASecond(void)
{
	
	Timer1A_Init(PlayOtherChord,songGlobal->melody[0],6);
	Timer0A_Init(PlayOneChord,songGlobal->harmonic[0],5);
	songcursor=0;
	instrumentMelodyCursor=0;
	instrumentHarmonicCursor=0;
	musicPlay();
	//SysTick_Wait(8000000);
	//DisableTimers();
	//musicStop();
}





void musicPlayStop(bool play){
	if (play==true)
		musicPlay();
	else 
		musicStop();
}
