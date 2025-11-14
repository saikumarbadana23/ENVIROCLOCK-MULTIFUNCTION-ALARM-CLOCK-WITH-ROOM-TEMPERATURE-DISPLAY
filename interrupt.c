#include"pin_func_define.h"
#include"pin_connect_block.h"
#include"lcd_defines.h"
#include"lcd.h"
#include"kpm_defines.h"
#include"kpm.h"
//#include"rtc.c"
#include"rtc.h"
#include"delay.h"
#include"interrupt.h"
#include<lpc21xx.h>
#define EINT0_VIC_CHN0 14

void eint0_isr(void) __irq;
extern U32 ent_flag;
void Init_Interrupt(void)
{
cfgPortpinFunc(0,1,EINT0_0_1);

	  VICIntEnable=1<<EINT0_VIC_CHN0;
	 
	  VICVectCntl0=(1<<5)|EINT0_VIC_CHN0;

	  VICVectAddr0=(U32)eint0_isr;
			 EXTMODE=1<<0;
	 
	  }

void eint0_isr(void) __irq
{
ent_flag=1;
EXTINT=1<<0;
VICVectAddr=0;
}
   	 	 