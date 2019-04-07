#ifndef _STATEPROCESSORH_
#define _STATEPROCESSORH_

#include "stdbool.h"
#include "stdint.h"
struct LockState{
	bool wifiCommunication;
	bool reEnterNewPassword;
	uint8_t passwordAttempts;
	char passwordBuffer[4];
	char inputPasswordbuffer[4];
	uint8_t indexInputPasswordBuffer;
	uint8_t state[4];
	uint8_t indexState;
	uint8_t lockInputs;
};
typedef struct LockState LockState;

void correctPasswordChangeState(bool change);
bool validComparison(void);
void reEnterNewPasswordState(void);
bool deletePassword(void);
bool comparePasswords(bool compare);
void removeBufferInput(void);
void processEditPasswordState(char input);
void processOpenState(char input);
void processEnterPasswordState(char input);
void processClosedState(char  input);
void processInput(uint32_t currentState,char input, uint32_t passwordSize);
void addValueToInputBuffer(char input);

//Blynk
void changePasswordBlynk(uint32_t num,bool password_reset_mode);
void stateChangeToRstPassword(void);
void setState(void);
void updateToOpenState(void);
void updateToClosedState(void);
typedef struct LockState LockState;
#endif


