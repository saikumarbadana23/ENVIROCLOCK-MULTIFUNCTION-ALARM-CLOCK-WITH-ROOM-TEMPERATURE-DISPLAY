 #include "types.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "kpm_defines.h"
#include "kpm.h"
#include "delay.h"
#include "rtc_defines.h"
#include "rtc.h"
#include<lpc21xx.h>
void Space(U32 *);
extern S32 alaram_hour,alaram_min,ent_flag;
extern signed int hour,min,sec,date,month,year,day;
U8 key;
U32 i;
void Alaram(void);
void edit(S32 *hour,S32 *min,S32 *sec,S32 *day,S32 *date,S32 *month,S32 *year);
void Menu(void)
{

        /* CmdLcd(CLEAR_LCD);
           CmdLcd(GOTO_LINE1_POS0);
           StrLcd("1:RTCEDIT");
           CmdLcd(GOTO_LINE2_POS0);
           StrLcd("2:SETALARM 3:EXT");*/
       // int flag=0;
        while(1)
        {
                Init_Kpm();
                CmdLcd(CLEAR_LCD);
                CmdLcd(GOTO_LINE1_POS0);
                StrLcd("1:RTCEDIT");
                CmdLcd(GOTO_LINE2_POS0);
                StrLcd("2:SETALARM 3:EXT");
                key=KeyScan();
                while(ColScan()==0);
                CmdLcd(CLEAR_LCD);
                if(key=='1')
				{
								key='\0';
                                edit(&hour,&min,&sec,&day,&date,&month,&year);
                                CmdLcd(CLEAR_LCD);
                              }
                        else if(key=='2')
						{
						key='\0';
								Alaram();
                             }

                        else if(key=='3')
						{
					//	flag=1;
                                 break;
						   }

                       else
					   {key='\0'; 
								CmdLcd(CLEAR_LCD);
                                 CmdLcd(GOTO_LINE1_POS0);
                                 StrLcd("INVALID INPUT");
                                 delays(1);
								 }
                

                //if(flag==1)
                      //  break;
        }
		}

void Alaram(void)
{		
U8 key1;
			alaram_hour=0;
		alaram_min=0;
		 i=0;
       // U8 key;
	   while(1)
	   {
      m:  CmdLcd(CLEAR_LCD);
        CmdLcd(GOTO_LINE1_POS0);
        StrLcd("1:SET HOUR");
		CmdLcd(GOTO_LINE2_POS0);
		StrLcd("2:SET MIN 3:EXT");
        //CmdLcd(GOTO_LINE1_POS0);
		key1=KeyScan();
		while(ColScan()==0);
		if(key1=='1')
		{
			CmdLcd(CLEAR_LCD);
			CmdLcd(GOTO_LINE1_POS0);
			StrLcd("ENTER HOUR 0-23");
				CmdLcd(GOTO_LINE2_POS0);
			alaram_hour=ReadNum(2);
			if(alaram_hour>=0 && alaram_hour<24)
			{
			CmdLcd(CLEAR_LCD);
			CmdLcd(GOTO_LINE1_POS0);
			StrLcd("ALARAM HOUR SET");
			CmdLcd(GOTO_LINE2_POS0);
			u32Lcd(alaram_hour);
			delayms(500);
			}
			else
			{
			CmdLcd(CLEAR_LCD);
			CmdLcd(GOTO_LINE1_POS0);
			StrLcd("INVALID HOUR");
			delayms(500);
			}
			goto m;
		}
		else if(key1=='2')
		{
			 CmdLcd(CLEAR_LCD);
			CmdLcd(GOTO_LINE1_POS0);
			StrLcd("ENTER MIN 0-59");
				CmdLcd(GOTO_LINE2_POS0);
			alaram_min=ReadNum(2);
			
				if(alaram_min>=0 && alaram_min<59)
			{
			CmdLcd(CLEAR_LCD);
			CmdLcd(GOTO_LINE1_POS0);
			StrLcd("ALARAM MIN SET");
			CmdLcd(GOTO_LINE2_POS0);
			u32Lcd(alaram_min);
			delayms(500);
			}
			else
			{
			CmdLcd(CLEAR_LCD);
			CmdLcd(GOTO_LINE1_POS0);
			StrLcd("INVALID MIN");
			delayms(500);
			}
			goto m;
			}
			else if(key1=='3')
			break;
			else
			{
			CmdLcd(CLEAR_LCD);
			CmdLcd(GOTO_LINE1_POS0);
			StrLcd("INVALID INPUT");
			delayms(500);
		
			CmdLcd(CLEAR_LCD);
				goto m;
			}
				 }
		
}            

void edit(S32 *hour,S32 *min,S32 *sec,S32 *day,S32 *date,S32 *month,S32 *year)
{
        S32 num;
        U8 key;
l:CmdLcd(CLEAR_LCD);
  CmdLcd(GOTO_LINE1_POS0);
  StrLcd("1.H 2.M 3.S 4.D");
  CmdLcd(GOTO_LINE2_POS0);
  StrLcd("5.DA 6.MO 7.Y 8E");
  //while(ColScan() == 0);
  key=KeyScan();
  while(ColScan() == 0);
  //CharLcd(key);
   //delays(1);
if(key=='1')
  {
          CmdLcd(CLEAR_LCD);
          CmdLcd(GOTO_LINE1_POS0);
          StrLcd("ENTER HOUR(0-23)");
          CmdLcd(GOTO_LINE2_POS0);
        
          num=ReadNum(2);
		   //while(ColScan() == 0);
          if(num>=0 && num<24)
          {
                  *hour=num;
                  SetRTCTimeInfo((U32)*hour,(U32)*min,(U32)*sec);
          }
		  else
		  {
		  CmdLcd(CLEAR_LCD);
		  CmdLcd(GOTO_LINE1_POS0);
		  StrLcd("INALID HOUR");
		  delayms(500);
		  }
          goto l;
          //u32Lcd(num);

  }
  else if(key=='2')
  {
          CmdLcd(CLEAR_LCD);
          CmdLcd(GOTO_LINE1_POS0);
          StrLcd("ENTER MIN(0-59)");
          CmdLcd(GOTO_LINE2_POS0);
         // while(ColScan() == 0);
          num=ReadNum(2);
		   while(ColScan() == 0);
          if(num>=0 && num<=59)
          {
                  *min=num;
                  SetRTCTimeInfo((U32)*hour,(U32)*min,(U32)*sec);
          }
		  else
		  {
		  CmdLcd(CLEAR_LCD);
		  CmdLcd(GOTO_LINE1_POS0);
		  StrLcd("INALID MIN");
		  delayms(500);
		  }
          goto l;
  }
  else if(key=='3')
  {
          CmdLcd(CLEAR_LCD);
          CmdLcd(GOTO_LINE1_POS0);
          StrLcd("ENTER SEC(0-59)");
          CmdLcd(GOTO_LINE2_POS0);
          //while(ColScan() == 0);
          num=ReadNum(2);
		   while(ColScan() == 0);
          if(num>=0 && num<=59)
          {
                  *sec=num;
                  SetRTCTimeInfo((U32)*hour,(U32)*min,(U32)*sec);
          }
		   else
		  {
		  CmdLcd(CLEAR_LCD);
		  CmdLcd(GOTO_LINE1_POS0);
		  StrLcd("INALID SEC");
		  delayms(500);
		  }
          goto l;
  }
  else if(key=='4')
  {
          CmdLcd(CLEAR_LCD);
          CmdLcd(GOTO_LINE1_POS0);
          StrLcd("ENTER DAY(0-6)");
          CmdLcd(GOTO_LINE2_POS0);
         // while(ColScan() == 0);
          num=ReadNum(1);
		   while(ColScan() == 0);
          if(num>=0 && num<=6)
          {
                  *day=num;
                  SetRTCDay((U32)*day);
          }
		   else
		  {
		  CmdLcd(CLEAR_LCD);
		  CmdLcd(GOTO_LINE1_POS0);
		  StrLcd("INALID DAY");
		  delayms(500);
		  }
          goto l;
  }
  else if(key=='5')
  {
          CmdLcd(CLEAR_LCD);
          CmdLcd(GOTO_LINE1_POS0);
          StrLcd("ENTER DATE(1-31)");
          CmdLcd(GOTO_LINE2_POS0);
         // while(ColScan() == 0);
          num=ReadNum(2);
		   while(ColScan() == 0);
          if(num>=1 && num<=31)
          {
                  *date=num;
                  SetRTCDateInfo((U32)*date,(U32)*month,(U32)*year);
          }
		   else
		  {
		  CmdLcd(CLEAR_LCD);
		  CmdLcd(GOTO_LINE1_POS0);
		  StrLcd("INALID DATE");
		  delayms(500);
		  }
          goto l;
  }
 else if(key=='6')
  {
          CmdLcd(CLEAR_LCD);
          CmdLcd(GOTO_LINE1_POS0);
          StrLcd("ENTER MONTH(1-12)");
          CmdLcd(GOTO_LINE2_POS0);
         // while(ColScan() == 0);
          num=ReadNum(2);
		   while(ColScan() == 0);
          if(num>=1 && num<=12)
          {
                  *month=num;
                  SetRTCDateInfo((U32)*date,(U32)*month,(U32)*year);
          }
		   else
		  {
		  CmdLcd(CLEAR_LCD);
		  CmdLcd(GOTO_LINE1_POS0);
		  StrLcd("INALID MONTH");
		  delayms(500);
		  }
          goto l;
  }
  else if(key=='7')
  {
          CmdLcd(CLEAR_LCD);
          CmdLcd(GOTO_LINE1_POS0);
          StrLcd("ENTER YEAR:");
          CmdLcd(GOTO_LINE2_POS0);
         // while(ColScan() == 0);
          num=ReadNum(4);
		   while(ColScan() == 0);
          if(num>=1 && num<=2500)
          {
                  *year=num;
                  SetRTCDateInfo((U32)*date,(U32)*month,(U32)*year);
          }
		   else
		  {
		  CmdLcd(CLEAR_LCD);
		  CmdLcd(GOTO_LINE1_POS0);
		  StrLcd("INALID YEAR");
		  delayms(500);
		  }
          goto l;
  }
  else if(key=='8')
          return;
  else
  {
          CmdLcd(CLEAR_LCD);
          CmdLcd(GOTO_LINE1_POS0);
          StrLcd("INVALID INPUT");
          delays(1);
          CmdLcd(CLEAR_LCD);
          goto l;
  }
}
