#include "rtc_defines.h"
#ifndef _LPC2148_
#include <LPC21xx.H>
#else
#include<lpc214x.h>
#endif


#include "lcd_defines.h"
#include "lcd.h"
#include "types.h"


// Array to hold names of days of the week
S8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};


/*
Initialize the Real-Time Clock (RTC)
This function disables the RTC, sets the prescaler values, 
and then enables the RTC.
*/
void RTC_Init(void) 
{
  // Disable and reset the RTC
	CCR = RTC_RESET;
  
  // Set prescaler integer and fractional parts
  #ifndef _LPC2148_
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
	#else
	CCR=((1<<0)|(1<<4));
	#endif
  
  // Enable the RTC
	//CCR = RTC_ENABLE;  
}

/*
Get the current RTC time
hour Pointer to store the current hour
minute Pointer to store the current minute
second Pointer to store the current second
*/
void GetRTCTimeInfo(S32 *hour, S32 *minute, S32 *second)
{
	*hour = HOUR;
	*minute = MIN;
	*second = SEC;

}

/*
Display the RTC time on LCD
hour value (0 23)
minute value (0 59)
second value (0 59) seperated by ':'
*/
void DisplayRTCTime(S32 hour, S32 minute, S32 second)
{
		CmdLcd(GOTO_LINE1_POS0);
		CharLcd((hour/10)+48);
		CharLcd((hour%10)+48);
		CharLcd(':');
		CharLcd((minute/10)+0x30);
		CharLcd((minute%10)+0x30);
		CharLcd(':');
		CharLcd((second/10)+'0');
		CharLcd((second%10)+'0');

}

/*
Get the current RTC date
date Pointer to store the current date (1 31)
month Pointer to store the current month (1 12)
year Pointer to store the current year (four digits)
*/
void GetRTCDateInfo(S32 *date, S32 *month, S32 *year)
{
	*date = DOM;
	*month = MONTH;
	*year = YEAR;
}

/*
Display the RTC date on LCD
Date of month (1 31)
Month (1 12)
Year (four digits) and seperated by '/'
*/
void DisplayRTCDate(U32 date, U32 month, U32 year)
{
		CmdLcd(GOTO_LINE2_POS0);
		CharLcd((date/10)+48);
		CharLcd((date%10)+48);
		CharLcd('/');
		CharLcd((month/10)+0x30);
		CharLcd((month%10)+0x30);
		CharLcd('/');
		u32Lcd(year);	

}

/*
Set the RTC time
Hour to set (0 23)
Minute to set (0 59)
Second to set (0 59)
*/
void SetRTCTimeInfo(U32 hour, U32 minute, U32 second)
{
	HOUR = hour;
	MIN = minute;
	SEC = second;

}

/*
Set the RTC date
date of month to set (1 31)
month to set (1 12)
year to set (four digits)
*/
void SetRTCDateInfo(U32 date, U32 month, U32 year)
{
	DOM = date;
	MONTH = month;
	YEAR = year;

}

/*
Get the current day of the week
dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)
*/
void GetRTCDay(S32 *dayofweek)
{
	*dayofweek = DOW; 
}

/*
Display the current day of the week on LCD
dow (Day of Week) (0=Sunday, ..., 6=Saturday)
*/
void DisplayRTCDay(S32 dayofweek)
{
	CmdLcd(GOTO_LINE1_POS0+10);
	StrLcd(week[dayofweek]);  
}

/*
Set the day of the week in RTC
Day of Week to set (0=Sunday, ..., 6=Saturday)
*/
void SetRTCDay(U32 dayofweek)
{
		DOW = dayofweek;
}
