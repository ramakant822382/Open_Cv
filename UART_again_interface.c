// UART / Serial communication with 8051

#include <reg52.h>
#include "4bit_lcd.h"
#include <stdio.h>

sbit D11 = P2^0;
sbit D2 = P2^1;
sbit D3 = P2^2;
sbit D4 = P2^3;

void s_init(void); // serial initialization

void s_tx(unsigned char);       // serial transmit
unsigned char s_rx();       // serial receive 

void tx_msg(unsigned char *p);
void rx_msg(unsigned char *k);

void main()
{ 
	unsigned char rx;
	P2 = 0x00;
	s_init();
	lcd_init();
	set_cursor(0,0);
	print("Home Automation");
	set_cursor(1,1);
	print("using BT UART");
	delay(2000);
	clr();
	set_cursor(0,0);
	print("D1:");
	set_cursor(7,0);
	print("D2:");
	set_cursor(0,1);
	print("D3:");
	set_cursor(7,1);
	print("D4:");
	
	
	while(1)
	{
	  rx = s_rx();
		if(rx == 'A')
		{
			D11 = 1;   //led1 on
			tx_msg("Device 1 ON\n");
			set_cursor(3,0);
	    print("On ");
			
		}
		else if(rx == 'a')
		{
			D11 = 0;
			tx_msg("Device 1 OFF\n");
			set_cursor(3,0);
	    print("off");
		}
		else if(rx == 'B')
		{
			D2 = 1;
			tx_msg("Device 2 On\n");
			set_cursor(10,0);
	    print("on ");
		}
		else if(rx == 'b')
		{
			D2 = 0;
			tx_msg("Device 2 off\n");
			set_cursor(10,0);
	    print("off");
		}
		else if(rx == 'C')
		{
			D3 = 1;
			tx_msg("Device 3 On\n");
			set_cursor(3,1);
	    print("on ");
		}
		else if(rx == 'c')
		{
			D3 = 0;
			tx_msg("Device 3 off\n");
			set_cursor(3,1);
	    print("off");
		}
		else if(rx == 'D')
		{
			D4 = 1;
			tx_msg("Device 4 On\n");
			set_cursor(10,1);
	    print("on ");
		}
		else if(rx == 'd')
		{
			D4 = 0;
			tx_msg("Device 4 off\n");
			set_cursor(10,1);
	    print("off");
		}
		
	}
}

void s_init(void)
{
	SCON = 0x50;    // 8bit mode with Baud rate
	TMOD = 0x20;    //Timer 1 in 8bit AUTO Reload G C/T M0 M1 00100000
	TH1  = 0xFD;    // 9600 baud rate
	TR1  = 1;
}
void s_tx(unsigned char t)
{
	SBUF = t;
	while(TI == 0);  // wait unill whole byte is transmitted 
	TI = 0;   //reset transmit flag
}

unsigned char s_rx()
{
	unsigned char rxd;
	while(RI == 0);
	rxd = SBUF;
	RI = 0; //reset rx flag
	return rxd;
}

void tx_msg(unsigned char *p)
{
	int i=0;
	while(p[i] != '\0')
	{
		s_tx(p[i++]);
	}
}
void rx_msg(unsigned char *k)
{
	int j=0;
	while(j<10)
	{
		k[j] = s_rx();
		j++;
	}
} 