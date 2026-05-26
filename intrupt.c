//external intrupt 1 int 1 using 8051  
	#include <reg51.h>
	#include "lcd_4bit.h"
	
	sbit red = P2^0; //red led for ISR
	sbit green = P2^1; // green led for normal information
	
	void Intrupt1(void) interrupt 2
	{
	clear_display();
	red = 1;
	green = 0;

set_cursor(0,0);
lcd_string("ISR running");
set_cursor(2,1);
lcd_string("Red led on");		
	}
	void main(){
		P3 = 0x08;  // P3.3 is set to high 
		IE = 0x84 ;   // INT1 enable 
		IT1 = 1 ;  // falling edge trigger enable
		lcd_init();
		
	while(1){
	clear_display()	;
	red = 0;
	green = 1;
set_cursor(0,0);
lcd_string("normal operation");
set_cursor(2,1);
lcd_string("green led on");		
	}
	}
	