#include"rtc_defines.h"
#ifndef _LPC2148_
#include<lpc21xx.h>
#else
#include<lpc214x.h>
#endif

#include"types.h"
#include"define_mac.h"
#include"lcd_defines.h"
#include"LCD.h"
#include"delay.h"
void CmdLcd(U8 cmd)
{
IOCLR0=1<<LCD_RS;
WriteLcd(cmd);
}
void WriteLcd(U8 bytes)
{
IOCLR0=1<<LCD_RW;
WRITEBYTE(IOPIN0,LCD_DATA,bytes);
IOSET0=1<<LCD_EN;
delayms(1);
IOCLR0=1<<LCD_EN;
delayms(2);
}
void Init_Lcd(void)
{
IODIR0|=(0xff<<LCD_DATA);
IODIR0|=(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN);
delayms(15);
CmdLcd(0x30);
delayms(4);
delayus(100);
CmdLcd(0x30);
delayus(100);
CmdLcd(0x30);
CmdLcd(MODE_8BIT_2LINE);
CmdLcd(DSP_ON_CUR_ON);
CmdLcd(CLEAR_LCD);
CmdLcd(SHIFT_CUR_RIGHT);
}
void CharLcd(U8 asciival)
{
IOSET0=1<<LCD_RS;
WriteLcd(asciival);
}
void StrLcd(S8 *str)
{
while(*str)
CharLcd(*str++);
}
void u32Lcd(U32 n)
{
S32 i=0;
U8 a[10];
if(n==0)
CharLcd('0');
else
{
while(n)
{
a[i++]=(n%10)+48;
n/=10;
}
for(--i;i>=0;i--)
CharLcd(a[i]);
}
}
void s32Lcd(S32 num)
{
if(num<0)
{
CharLcd('-');
num=-(num);
}
u32Lcd(num);
}
void f32Lcd(F32 fnum,U32 nDP)
{
U32 num,i;
if(fnum<0.0)
{
CharLcd('-');
fnum=-(fnum);
}
num=fnum;
u32Lcd(num);
CharLcd('.');
for(i=0;i<nDP;i++)
{
fnum=(fnum-num)*10;
num=fnum;
CharLcd(num+48);
}
}
void BuildCGRAM(U8 *p,U8 nbytes)
{
U32 i;
CmdLcd(GOTO_CGRAM_START);
IOSET0=1<<LCD_RS;
for(i=0;i<nbytes;i++)
WriteLcd(p[i]);
CmdLcd(GOTO_LINE1_POS0);
}
