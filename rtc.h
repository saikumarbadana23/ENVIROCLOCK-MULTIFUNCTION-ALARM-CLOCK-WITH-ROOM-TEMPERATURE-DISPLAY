//#ifndef RTC_H
//#define RTC_H

#include "types.h"

void RTC_Init(void);
void GetRTCTimeInfo(S32 *,S32 *,S32 *);
void DisplayRTCTime(S32,S32,S32);
void GetRTCDateInfo(S32 *,S32 *,S32 *);
void DisplayRTCDate(U32,U32,U32);

void SetRTCTimeInfo(U32,U32,U32);
void SetRTCDateInfo(U32,U32,U32);

void GetRTCDay(S32 *);
void DisplayRTCDay(S32);
void SetRTCDay(U32);

void SetRTCHour(U32);
void SetRTCMin(U32);
void SetRTCSec(U32);
void SetRTCDate(U32);
void SetRTCMonth(U32);
void SetRTCYear(U32);
void SetRTCDay(U32);

void GetRTCHour(S32 *);
void GetRTCMin(S32 *);
void GetRTCSec(S32 *);
void GetRTCDate(S32 *);
void GetRTCMonth(S32 *);
void GetRTCYear(S32 *);
void GetDay(void);

//#endif
