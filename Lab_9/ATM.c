#include <at89c5131.h>
#include "lcd.h"		// Header file with LCD interfacing functions
#include "serial_atm.h"	// Header file with UART interfacing functions


char a_c1_money[6]={0,0,0,0,0,'\0'};
char a_c2_money[6]={0,0,0,0,0,'\0'};
char five_hundred_notes[6] = {0,0,0,0,0,'\0'};
char one_hundred_notes[6] = {0,0,0,0,0,'\0'};


// Main function
void main(void)
{
	unsigned char ch=0;
	unsigned char ac;
	unsigned char units;
	unsigned char tens;
	int unit;
	int ten;
	int amount;
	int five;
	int one;
	int ac1_money = 10000;
  int ac2_money = 10000;

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
			switch(ch)
			{
				case 'A':
				case 'a':
				  transmit_string("Hello, Please enter Account Number\r\n");
				  ac = receive_char();
				  switch(ac)
					{
						case '1':
						transmit_string("Account Holder: Steven\r\n");
	          transmit_string("Account Balance: ");
						int_to_string(ac1_money,a_c1_money);
						transmit_string(a_c1_money);
						transmit_string("\r\n");
						ch = 0;
            break;
						
						case '2':
						transmit_string("Account Holder: Gordon\r\n");
	          transmit_string("Account Balance: ");
						int_to_string(ac2_money,a_c2_money);
						transmit_string(a_c2_money);
						transmit_string("\r\n");
						ch = 0;
            break;
						
						default:
						transmit_string("No such account, please enter valid details\r\n");
						ch = 0;
						break;
					}
				
					break;
				
				case 'W':
				case 'w':
				  transmit_string("Withdraw state, enter account number\r\n");
				  ac = receive_char();
				  switch(ac)
					{
						case '1':
						transmit_string("Account Holder: Steven\r\n");
	          transmit_string("Account Balance: ");
						int_to_string(ac1_money,a_c1_money);
						transmit_string(a_c1_money);
						transmit_string("\r\n");
						transmit_string("Enter Amount, in hundreds\r\n");
						tens = receive_char();
						units = receive_char();
						ten = (int)tens - 48;
						unit = (int)units - 48;
						if(ten > 10 | ten < 0 | unit > 10 | unit < 0 )
						{
						transmit_string("Invalid Amount\r\n");
            ch =0;
						break;
            }
            amount = (ten * 10 + unit * 1)*100;
						if(amount >  ac1_money)
						{
						transmit_string("Insufficient Funds\r\n");
             ch =0;
						break;
            }
						ac1_money = ac1_money - amount;
						five = amount/500;
						one=(amount%500)/100;
						transmit_string("Remaining Balance: ");
						int_to_string(ac1_money,a_c1_money);
						transmit_string(a_c1_money);
						transmit_string("\r\n");
						transmit_string("500 Notes: ");
						int_to_string(five,five_hundred_notes);
						transmit_string(five_hundred_notes);
						transmit_string("\r\n");
						transmit_string("100 Notes: ");
						int_to_string(one,one_hundred_notes);
						transmit_string(one_hundred_notes);
						transmit_string("\r\n");
						ch =0;
						break;
						
						case '2':
						transmit_string("Account Holder: Gordon\r\n");
	          transmit_string("Account Balance: ");
						int_to_string(ac2_money,a_c2_money);
						transmit_string(a_c2_money);
						transmit_string("\r\n");
						transmit_string("Enter Amount, in hundreds\r\n");
						tens = receive_char();
						units = receive_char();
						ten = (int)tens - 48;
						unit = (int)units - 48;
						if(ten > 10 | ten < 0 | unit > 10 | unit < 0 )
						{
            ch =0;
						break;
            }
            amount = (ten * 10 + unit * 1)*100;
						if(amount >  ac2_money)
						{
             ch =0;
						break;
            }
						ac2_money = ac2_money - amount;
						five = amount/500;
						one=(amount%500)/100;
						transmit_string("Remaining Balance: ");
						int_to_string(ac2_money,a_c2_money);
						transmit_string(a_c2_money);
						transmit_string("\r\n");
						transmit_string("500 Notes: ");
						int_to_string(five,five_hundred_notes);
						transmit_string(five_hundred_notes);
						transmit_string("\r\n");
						transmit_string("100 Notes: ");
						int_to_string(one,one_hundred_notes);
						transmit_string(one_hundred_notes);
						transmit_string("\r\n");
						ch =0;
            break;
						
						default:
						transmit_string("No such account, please enter valid details\r\n");
						break;
					}
					
					break;
							
				default:
					transmit_string("Press A for Account display and W for withdrawing cash\r\n");
					ch = receive_char();
				  break;
			}
			msdelay(100);
	}
}
