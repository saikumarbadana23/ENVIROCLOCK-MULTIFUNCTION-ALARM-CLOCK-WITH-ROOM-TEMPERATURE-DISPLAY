#include<lpc214x.h>
#include"PIN_CONNECT_BLOCK.h"
#include"PIN_FUNC_DEFINE.h"
#include"adc_defines.h"
#include"types.h"
#include"delay.h"
void Init_ADC(void)
{
AD0CR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
cfgPortpinFunc(0,28,PIN_FUNC2);
}
void Read_ADC(U32 ch_no,U32 *adcdval,F32 *ear)
{
AD0CR&=0xffffff00;
AD0CR|=(1<<ch_no)|(1<<ADC_START_BIT);
delayus(3);
while(((AD0GDR>>DONE_BIT)&1)==0);
AD0CR&=~(1<<ADC_START_BIT);
*adcdval=(AD0GDR>>RESULT_BITS)&1023;
*ear=(*adcdval*(3.3/1023));
}
