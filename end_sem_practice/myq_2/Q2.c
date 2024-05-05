#include <at89c5131.h>
#include "lcd.h"		    // Header file with LCD interfacing functions
#include "serial.h"	// Header file with UART interfacing functions

int quantity[5] = {0,8,6,4,4};
int quantity_max[5] = {0,8,6,4,4};
// Main function
void main(void)
{
	unsigned char state=0;
	unsigned char index_char;
	int index;
	unsigned char quant_char;
	int quant;
  unsigned char ch;
	// Call initialization functions
	lcd_init();
	uart_init();

	// These strings will be printed in terminal software
	
	while(1)
	{
			// Receive a character
			// ch = receive_char();
			// Decide which test function to run based on character sent
     	// Displays the string on the terminal software
			switch(state)
			{
				case 'I':
				case 'i':
				  transmit_string("Enter micro-controller to be borrowed: \r\n");
				  index_char = receive_char();
				  index = index_char - 48;
				  transmit_string("Enter Quantity: \r\n");
				  quant_char = receive_char();
				  quant = quant_char - 48;
				  if(quant > quantity[index])
						{
						transmit_string("Requested micro-controller not available...\r\n");
						}
						else
						{
						transmit_string("Requested micro-controller allocated!\r\n");
						quantity[index] = quantity[index] - quant;
						}
				  state = 0;
					break;
				
				case 'R':
				case 'r':
				  transmit_string("Enter micro-controller to be returned: \r\n");
				  index_char = receive_char();
				  index = index_char - 48;
				  if(quantity[index] == quantity_max[index])
					{
					transmit_string("You can’t return what you don’t have...\r\n");
					state = 0;
					break;
					}
					else
					{
				  transmit_string("Enter Quantity: \r\n");
				  quant_char = receive_char();
				  quant = quant_char - 48;
					if(quant + quantity[index] > quantity_max[index])
						{
						transmit_string("Returned micro-controller out of bounds...\r\n");
						}
						else
						{
						transmit_string("Returned micro-controller received!\r\n");
						quantity[index] = quantity[index] + quant;
						}
				  state = 0;
					break;
				  }
						
				default:
					transmit_string("Micro-controllers available: 8051-8 TIVA-6 AT328-4 STM32-4.\r\n");
				  transmit_string("Micro-controllers available: 8051-");
				  ch = quantity[0]+48;
				  transmit_char(ch);
				  transmit_string(" TIVA-");
				  ch = quantity[1]+48;
				  transmit_char(ch);
				  transmit_string(" AT328-");
				  ch = quantity[2]+48;
				  transmit_char(ch);
				  transmit_string(" STM32-");
				  ch = quantity[3]+48;
				  transmit_char(ch);
				  transmit_string(".\r\n");
				  transmit_string("Press I for Issue and R for Return\r\n");
					ch = receive_char();
				  break;
			}
			msdelay(100);
	}
}
