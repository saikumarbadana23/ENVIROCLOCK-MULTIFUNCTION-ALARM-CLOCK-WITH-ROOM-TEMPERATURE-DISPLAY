//pin_connect_block.c
#include<Lpc21xx.h>
void cfgPortpinFunc(unsigned int portno,unsigned int pinno,unsigned int pinfunc)
{
	if(portno==0)
	{
		if(pinno<=15)
		{
			PINSEL0=((PINSEL0 & ~(3<<(pinno*2))) | (pinfunc<<(pinno*2)));
		}
		else if((pinno>=16) && (pinno<=31))
		{
			PINSEL1=((PINSEL1 & ~(3<<((pinno-16)*2))) | (pinfunc<<((pinno-16)*2)));
		}
	}
}
