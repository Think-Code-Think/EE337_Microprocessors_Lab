#include <at89c5131.h>

sbit music=P0^7;
int freq[8] = {240,270,300,318,356,394,442,470};
int dur[8] = {500,750,1000,500,1000,750,1000,500};
int i,k;
i=1;
k=0;
int count_freq;
int count_dur;

void note(int freq)
{
	TH0 = 0x3C;
	TL0 = 0xB0;
	
	count_freq = (int) (65534 - (1000000/(freq-1)));
	TH1 = count_freq/256;
	TL1 = count_freq%256;
	
	TR0 = 1;
	TR1= 1;
}
void timer0_isr () interrupt 1
{
	i++;
	if(i==1+(dur[k])/25)
	{
		if(k==7)
	  {
	   k=0;
	  }
		 k++;
		i=1;
	}
	
	//if(k>=7) k=7;
	note(freq[k]);
	
}

void musical_note () interrupt 3
{ 
	music = ~music;
	TH1 = count_freq/256;
	TL1 = count_freq%256;
	TR1 = 1;
}

//Main function
void main(void)
{
	TMOD = 0x11; //mode 1 timer 0 and timer 1
	ET0 = 1;
	ET1 = 1; //activate interrupts for timer 0 and timer 1
	EA = 1;  //activate global interrupts
	note(freq[0]);
	
	while(1);
}
