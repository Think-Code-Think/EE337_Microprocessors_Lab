#include <at89c5131.h>
/*************************************************
 	lcd.h: Header file for 16x2 LCD interfacing  
**************************************************/

//Functions contained in this header file
void msdelay(unsigned int);																	//fn takes integer value as an input and generates corresponding delay in milli seconds
void lcd_init(void);																				//Initialize LCD
void lcd_cmd(unsigned int i);																//Sends commands to lcd
void lcd_char(unsigned char ch);														//display character on a lcd corresponding to input ascii
void lcd_write_string(unsigned char *s);										//takes pointer of a string which ends with null and display on a lcd 
//void lcd_print (row, column, value, digits)


//Signals to LCD
sbit RS=P0^0;	//Register select
sbit RW=P0^1;	//Read from or write to register
sbit EN=P0^2;	//Enable pin of lcd


//Function definitions
/************************************************
   lcd_init():
	Initializes LCD port and 
	LCD display parameters
************************************************/
void lcd_init(void)
{
	P2=0x00;
	EN=0;
	RS=0;
	RW=0;
	
	lcd_cmd(0x38);	// Function set: 2 Line, 8-bit, 5x7 dots
	msdelay(4);
	lcd_cmd(0x06);	// Entry mode, auto increment with no shift
	msdelay(4);
	lcd_cmd(0x0C);	// Display on, Curson off
	msdelay(4);
	lcd_cmd(0x01);	// LCD clear
	msdelay(4);
	lcd_cmd(0x80);	//Move cursor to Row 1 column 0
}

/**********************************************************
   msdelay(<time_val>): 
	Delay function for delay value <time_val>ms
***********************************************************/	
void msdelay(unsigned int time)
{
	int i,j;
	for(i=0;i<time;i++)
	{
		for(j=0;j<382;j++);
	}
}

/**********************************************************
    lcd_cmd(<char command>):
	Sends 8 bit command
	LCD display parameters
***********************************************************/	
void lcd_cmd(unsigned int i)
{
	RS=0;
	RW=0;
	EN=1;
	P2=i;
	msdelay(10);
	EN=0;
}


/**********************************************************
   lcd_write_char(<char data>):
	Sends 8 bit character(ASCII)
	to be printed on LCD
***********************************************************/	
void lcd_write_char(unsigned char ch)
{
	RS=1;
	RW=0;
	EN=1;
	P2=ch;
	msdelay(10);
	EN=0;
}


/***********************************************************
  lcd_write_string(<string pointer>):
	Prints string on LCD. Requires string pointer 
	as input argument.
***********************************************************/	
void lcd_write_string(unsigned char *s)
{
	while(*s!='\0')
	{
		lcd_write_char(*s++);
	}
}



code unsigned char display_msg0[]="    Keyboard    ";	
code unsigned char display_msg1[]="     Sa(low)    ";						//Display msg on 1st line of lcd
code unsigned char display_msg2[]="       Re       ";						//Display msg on 2st line of lcd
code unsigned char display_msg3[]="       Ga       ";		
code unsigned char display_msg4[]="       Ma       ";		
code unsigned char display_msg5[]="       Pa       ";		
code unsigned char display_msg6[]="      Dha       ";		
code unsigned char display_msg7[]="       Ni       ";		
code unsigned char display_msg8[]="     Sa(high)   ";		
code unsigned char display_msg9[]="     Silence    ";		

sbit ROW1=P3^4;
sbit ROW2=P3^5;
sbit ROW3=P3^6;
sbit ROW4=P3^7;
sbit COL1=P3^0;
sbit COL2=P3^1;
sbit COL3=P3^2;
sbit COL4=P3^3;

int TEMP1;
int TEMP2;
int TEMP3;
int TEMP4;

sbit music=P0^7;

int freq[8] = {240,270,300,318,356,394,442,470};
//int dur[9] = {500,750,1000,500,1000,750,1000,500};

int count_freq;


void note(int freq)
{
	count_freq = (int) (65534 - (1000000/(freq-1)));
	TH0 = count_freq/256;
	TL0 = count_freq%256;
	TR0 = 1;
}

void musical_note () interrupt 1
{ 
	music = ~music;
	TH0 = count_freq/256;
	TL0 = count_freq%256; 
}


void debounce_delay(void)
{
	int a,b;
	for(a=0;a<20;a++)
	{
		for(b=0;b<382;b++);
	}
	
}

//Main function
void main(void)
{
	
	while(1)
	{
	 ROW1 = 0;
	 ROW2 = 0;
	 ROW3 = 0;
	 ROW4 = 0;
	 do{
	 do{
	 P3 = P3 & 0X0F;
	 }
	 while(COL1 & COL2 & COL3 & COL4 == 0);
	 do{P3 = P3 & 0X0F;}
	 while(COL1 & COL2 & COL3 & COL4 != 0);
	 debounce_delay();
	 P3 = P3 & 0X0F;
 }
   while(COL1 & COL2 & COL3 & COL4 != 0);	 
   
	 ROW1 = 1;
	 ROW2 = 1;
	 ROW3 = 1;
	 ROW4 = 0;
   
   do
   {
	 TEMP1 = ROW1;
	 TEMP2 = ROW2;
	 TEMP3 = ROW3;
	 TEMP4 = ROW4;
		
	 ROW1 = TEMP4;
	 ROW2 = TEMP1;
	 ROW3 = TEMP2;
	 ROW4 = TEMP3;
	 P3 = P3 & 0XFF;
	 }
   while(COL1 & COL2 & COL3 & COL4 != 0);
	 
	   //activate global interrupts
	 
	 switch (P3)
	 {
		 case 0XEE:
			 lcd_init();
	     lcd_cmd(0x80);													//Move cursor to first line
       msdelay(4);
	     lcd_write_string(display_msg0);
		   msdelay(1000);	
		  
		   break;
		 
		 case 0XED:
			 lcd_init();
	     lcd_cmd(0x80);													//Move cursor to first line
       msdelay(4);
	     lcd_write_string(display_msg1);
		   TMOD = 0x11; //mode 1 timer 0 and timer 1
		   ET0 = 1;
	     EA = 1;
			 count_freq = (int) (65534 - (1000000/(freq[0]-1)));
	     TH0 = count_freq/256;
	     TL0 = count_freq%256;
	     TR0= 1;
		   while(P3 == 0XED);
       TR0= 0;
		   break;
		 
		 case 0XEB:
			 lcd_init();
	     lcd_cmd(0x80);													//Move cursor to first line
       msdelay(4);
	     lcd_write_string(display_msg2);
		   TMOD = 0x11; //mode 1 timer 0 and timer 1
	     ET0 = 1; //activate interrupts for timer 0 and timer 1
	     EA = 1;
		   
			 note(freq[1]);
		   while(P3 == 0XEB);
       TR0= 0;
		   break;
		 
		 case 0XE7:
			 lcd_init();
	     lcd_cmd(0x80);													//Move cursor to first line
       msdelay(4);
	     lcd_write_string(display_msg3);
		   TMOD = 0x11;
	     ET0 = 1; //activate interrupts for timer 0 and timer 1
	     EA = 1;
			 note(freq[2]);
		   while(P3 == 0XE7);
       TR0= 0;
		   break;
		 
		 case 0XDE:
			 lcd_init();
	     lcd_cmd(0x80);													//Move cursor to first line
       msdelay(4);
	     lcd_write_string(display_msg4);
		   TMOD = 0x11; //mode 1 timer 0 and timer 1
	     ET0 = 1; //activate interrupts for timer 0 and timer 1
	     EA = 1;
			 note(freq[3]);
		 	 while(P3 == 0XDE);
       TR0= 0;
		   break;
		 case 0XDD:
			 lcd_init();
	     lcd_cmd(0x80);													//Move cursor to first line
       msdelay(4);
	     lcd_write_string(display_msg5);
		   TMOD = 0x10; //mode 1 timer 0 and timer 1
	     ET0 = 1; //activate interrupts for timer 0 and timer 1
	     EA = 1;
			 note(freq[4]);
		   while(P3 == 0XDD);
       TR0= 0;
		   break;
		 case 0XDB:
			 lcd_init();
	     lcd_cmd(0x80);													//Move cursor to first line
       msdelay(4);
	     lcd_write_string(display_msg6);
		   TMOD = 0x11; //mode 1 timer 0 and timer 1
	     ET0 = 1; //activate interrupts for timer 0 and timer 1
	     EA = 1;
			 note(freq[5]);
			 while(P3 == 0XDB);
       TR0= 0;
		   break;
		 case 0XD7:
			 lcd_init();
	     lcd_cmd(0x80);													//Move cursor to first line
       msdelay(4);
	     lcd_write_string(display_msg7);
		   TMOD = 0x11; //mode 1 timer 0 and timer 1
	     ET0 = 1; //activate interrupts for timer 0 and timer 1
	     EA = 1;
			 note(freq[6]);
	     while(P3 == 0XD7);
       TR0= 0;
		   break;
		 case 0XBE:
			 lcd_init();
	     lcd_cmd(0x80);													//Move cursor to first line
       msdelay(4);
	     lcd_write_string(display_msg8);
		   TMOD = 0x11; //mode 1 timer 0 and timer 1
	     ET0 = 1; //activate interrupts for timer 0 and timer 1
	     EA = 1;
			 note(freq[7]);
       while(P3 == 0XBE);
       TR0= 0;
		   break;
		 case 0XBD:
			 lcd_init();
	     lcd_cmd(0x80);													//Move cursor to first line
       msdelay(4);
	     lcd_write_string(display_msg9);
		   break;
		 default :
			 break;
	 
	 }		 
	}
}





