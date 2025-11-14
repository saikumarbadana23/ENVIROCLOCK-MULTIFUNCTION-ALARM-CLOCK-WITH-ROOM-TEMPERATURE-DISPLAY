#include<lpc21xx.h>
#include"define_mac.h"
#include"kpm_defines.h"
#include"types.h"
#include"lcd_defines.h"
#include"kpm.h"
#include"lcd.h"
#include"delay.h"
U8 kpmlut[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
void Init_Kpm(void)
{
	WRITENIBBLE(IODIR1,ROWs_4,15);
}
U32 ColScan(void)
{
return (READNIBBLE(IOPIN1,COLs_4)<15)? 0:1;
}
U32 RowCheck(void)
{
U32 r;
for(r=0;r<=3;r++)
{
WRITENIBBLE(IOPIN1,ROWs_4,~(1<<r));
if(ColScan()==0)
break;
}
WRITENIBBLE(IOPIN1,ROWs_4,0);
return r;
}
U32 ColCheck(void)
{
U32 c;
for(c=0;c<=3;c++)
{
if(READBIT(IOPIN1,COL0+c)==0)
{
return c;
}
}
return c;
}
U32 KeyScan(void)
{
U32 r,c,KeyV;
while(ColScan());
r=RowCheck();
c=ColCheck();
KeyV=kpmlut[r][c];
return KeyV;
}
U32 ReadNum(int x)
{
		U32 sum=0;
        U8 key;
		x=x+1;
        while(x)
        {

                key=KeyScan();
				//while(ColScan()==0);
                if((key>='0' && key<='9')||key=='#')
                {
                        if(key>='0' && key<='9')
                        {
                        sum=(sum*10)+(key-48);
                        while(ColScan()==0);
                        //CmdLcd(GOTO_LINE2_POS0+i);
                        CharLcd(key);
						x--;
                        }
						else if(key=='#')
						{
						x++;
						if(sum!=0)
                                Space(&sum);
                                        while(ColScan()==0);
									//	x++;
								if(sum==0)
								x=3;
                         }					 
        }
			else
                {
                        while(ColScan()==0);
                        break;
                }
		}
		if(x==0)
		delayms(200);
        return sum;

}
void Space(U32 *sum)
{
        CmdLcd(SHIFT_DISP_RIGHT-1);
        CharLcd(' ');
        CmdLcd(SHIFT_DISP_RIGHT-1);
        *sum=*sum/10;

}

/*
void ReadNum(S32 *num,U8 *key)
{
*num=0;
while(1)
{
*key=KeyScan();
if(*key>='0' && *key<='9')
{
*num=(*num*10)+(*key-48);
while(ColScan()==0);
}
else
{
while(ColScan()==0);
break;
}
}
}*/
