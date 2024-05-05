/**********************************************************
EE337: ADC IC MCP3008 interfacing with pt-51
(1) Complete spi_init() function from spi.h 

***********************************************************/

#include <at89c5131.h>
#include "lcd.h"																				//Driver for interfacing lcd 
#include "mcp3008.h"																		//Driver for interfacing ADC ic MCP3008


char adc_ip_data_ascii[6]={0,0,0,0,0,'\0'};	//string array for saving ascii of input sample
char adc_ip_data_ascii2[6]={0,0,0,0,0,'\0'};
char adc_ip_data_ascii3[6]={0,0,0,0,0,'\0'};
code unsigned char display_msg1[]="Volt.: ";						//Display msg on 1st line of lcd
code unsigned char display_msg2[]=" mV";								//Display msg on 2nd line of lcd

unsigned int voltage[10];
int j = 0;
void main(void)
{
	unsigned int adc_data=0;
	spi_init();																					
	adc_init();
  lcd_init();
	
	while(1)
	{
	 	unsigned int x;
		x = adc(3);			//Read analog value from 0th channel of ADC Ic MCP3008
		adc_data = (unsigned int) (x*3.2258); 							//Converting received 10 bits value to milli volt (50*i/p /1023)
    int_to_string(x,adc_ip_data_ascii);
		int_to_string(adc_data,adc_ip_data_ascii2);
	  voltage[j] = adc_data;
	  j++;
	lcd_cmd(0x80);													//Move cursor to 2nd line of LCD
	lcd_write_string("Volt.: ");
	lcd_write_string(adc_ip_data_ascii2);		
	lcd_write_string(display_msg2);	
	
	}
}