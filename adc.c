//ADC 0804 interfacing with 8051
#include <reg52.h>
#include "4bit_lcd.h"
#include <stdio.h>

sbit wr = P3^0;
sbit rd = P3^1;
sbit intr = P3^2;

unsigned int adc(void);


void main(){
int digital;
float analog;
char di[10];
char	an[10];
lcd_init();	
while(1)
{
digital = adc();
analog = ((digital)*(4.0/255.0));
	
sprintf(di,"%d",digital);
sprintf(an,"%.3f",analog);
set_cursor(0,0);
	print("D:");
 	print(di);
	
set_cursor(0,1);
	print("A:");
 	print(an);
 delay(1000);
 clr();	
}

}


unsigned int adc(void){

int d ;
	wr = 0;
	rd = 1;
	wr = 1;  //start of conversion
	
	while(intr == 1); // wait till conversion
	rd = 0; //data latch to output
  d = P1 ;
	
	return d ;
 

}