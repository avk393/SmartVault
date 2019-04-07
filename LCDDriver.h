
#ifndef _LCDDRIVERH_
#define _LCDDRIVERH_
#include <stdint.h>
void DisplayWrongPassword(void);
void DisplayClosed(void);
void DisplayOpen(void);
void DisplayWifi(void);
void DisplayClosedEnterPassword(void);
void DisplayPasswordDisabled(void);
void DisplayGuide(void);
void DisplayAstrick(int);
void RemoveAstrick(int);
void DisplaEnterPassword(void);
void DisplayNewPassword(void);
void DisplayEnterAgain(void);
void DisplayNotMatch(void);
void OpenPage(void);
void ClosePage(void);
void EnterPasswordPage(void);
void WrongPasswordPage(void);
void CloseDisabledPage(void);
void NewPasswordPage(void);
void EnterAgainPage(void);
void NotMatchPage(void);
void InitializeLCD(void);
#endif
