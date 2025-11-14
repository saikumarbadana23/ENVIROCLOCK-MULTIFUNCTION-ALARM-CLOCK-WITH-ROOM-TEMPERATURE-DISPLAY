#include"rtc_defines.h"
//#include<lpc21xx.h>
#ifndef _LPC2148_
#include <lpc21xx.h>
#else
#include<lpc214x.h>
#endif

#include"pin_func_define.h"
#include"pin_connect_block.h"		  
#include "types.h"
#include"delay.h"
#include"kpm_defines.h"
#include"kpm.h"
//include LCD header files
#include "lcd.h"
#include"lcd_defines.h"
#include "rtc.h"

#include"adc.c"
#include"interrupt.h"
#include "editing.h"

U8 clock[8]={0x04,0x0e,0x0e,0x0e,0x1f,0x04,0x00,0x00};
S32 alaram_hour=-1,alaram_min=-1;
U32 adcval,temp;
F32 ear;
S32 ent_flag;
signed int hour,min,sec,date,month,year,day;

// Main function
int main()
{

  // Initialize RTC 
	RTC_Init();
  // Initialize the LCD
	Init_Lcd();
  //Initialize the kpm
	Init_Kpm();
	//Initialize interrupt
	Init_Interrupt();
	//initialize adc
	Init_ADC();
	IODIR0 |=1<<20;
	
  // Set the initial time (hours, minutes, seconds)
	//SetRTCTimeInfo(19,30,00);
	//SetRTCDateInfo(18,10,2025);
	//SetRTCDay(3);
				  
  
  while (1) 
	{
	
    // Get and display the current time on LCD
	                                                                                                                                                                                                                                                                                                                                                      
		GetRTCTimeInfo(&hour,&min,&sec);
		DisplayRTCTime(hour,min,sec);
		GetRTCDateInfo(&date,&month,&year);
		DisplayRTCDate(date,month,year);
		GetRTCDay(&day);
		DisplayRTCDay(day);
		Read_ADC(1,&adcval,&ear);
        temp=ear*100;
        CmdLcd(GOTO_LINE2_POS0+11);
        u32Lcd(temp);
        CharLcd(0xDF);
        CharLcd('C');
			if(((IOPIN0>>22)&1)==1)
			{
		//	IOPIN0=(IOPIN0 & ~(1<<3));
	 	IOCLR0=1<<20;
		alaram_min=-1;
		alaram_hour=-1;
		CmdLcd(CLEAR_LCD);
			}
		if(ent_flag)
		{
       
        Menu();
		 ent_flag=0;
		}
		if(HOUR==alaram_hour && MIN==alaram_min)
		{
    //	IOPIN0=(IOPIN0 & ~(1<<3))|(1<<3);
	IOSET0=1<<20;
		
		BuildCGRAM(clock,8);
		CmdLcd(GOTO_LINE1_POS0+14);
		CharLcd(0);
		CmdLcd(GOTO_LINE1_POS0+14);
		CmdLcd(DSP_ON_CUR_BLINK);
	//	CharLcd(' ');
			//CharLcd(' ');
		}
		else
		{
		IOCLR0=1<<20;
		CmdLcd(GOTO_LINE1_POS0+14);
		 CharLcd(' ');
		}

	}		
	}
						
