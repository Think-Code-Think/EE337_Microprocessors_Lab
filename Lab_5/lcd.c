#include <at89c5131.h>
#include "lcd.h"
#include <math.h>
code unsigned char display_msg1[]="    Input 1:    ";	//Display msg on 1st line of lcd
code unsigned char display_msg2[]="    Input 2:    ";	//Display msg on 2st line of lcd
code unsigned char display_msg3[]="  Prediction :  ";	                                                        
code unsigned char display_msg4[]="P(Class 1)=";
code unsigned char display_msg5[]="P(Class 2)=";
void main()
{
	int w0 = -37;
	int w1 = 5;
	int w2 = 7;
	int x1, x2;
	int y;
	float z;
	lcd_init();
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg1);
	msdelay(5000);
	x1 = P1 & 0x0f;
	
	lcd_init();
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg2);
	msdelay(5000);
	x2 = P1 & 0x0f;
	
	y = 1*w0 + x1*w1 + x2*w2;
	z = 1/(1+exp(-y));

  lcd_init();
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg4);
	lcd_float(1-z);
	lcd_cmd(0xC0);													//Move cursor to 2nd line of LCD
	msdelay(4);
	lcd_write_string(display_msg5);
	lcd_float(z);
	
	
	while(1);
		
}