
//#include "musicStruct.h"
#ifndef _MUSICPLAYER_H
#define _MUSICPLAYER_H
void playerInit(struct SimpleSong);
void musicPlay(void);
void musicStop(void);
void changeSong(SimpleSong songLocal);
void SongChordChange(void);
void PlayChord(void);
void changeSong(SimpleSong songLocal);
void PlayTwoChords(void);
void PlayAChordForASecond(void);
void generateSongForOneSecond(void);
void playerEnableInterrupt(void);
void PlayAChordForASecond(void);
void playFullSong(void);
void playForASecond(void);
void DisableTimers(void);
void playJingleBells(void);
#endif
