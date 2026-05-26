//UART SERIAL COMMUNICATION WITH 8052
#include <reg52.h>
#include "4bit_lcd.h"
#include <stdio.h>

void s_init(void); //serial init
void s_tx();       //serial transmit
void s_rx();       //serial receive

void main(){
	 s_init();
while(1){

s_tx();
s_rx();

}

}


void s_init(void){
SCON = 0x50;  //8BIT MODE WITH
TMOD = 0x20;       // TIMER 1 IN 8BIT AUTO RELOAD 00100000	
TH1  = 0XFD;   //9600 BAUD RATE
TR1  = 1 ;	
}


void s_tx(){
SBUF  = 'A';
while(TI==0);   //wait untill whole byte is transmitted
TI = 0 ;       //reset transmit flag
}

void s_rx(){
	unsigned char rxd;
  while(RI == 0);
	rxd = SBUF ; 
  P1 = rxd ;
	RI = 0 ;  //reset trnsmit flag 

}