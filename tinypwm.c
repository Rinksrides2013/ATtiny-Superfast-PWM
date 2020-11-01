/*
A snipet and very basic program to setup Timer 1 on an attiny25/45/85
without and with deatime control
 */
#include <C:\attiny\io.h>


int main(){
	
	//setup	
	PLLCSR	=	0x6;	//enable PLL clock for PWM high frequency clock to TCNT1
	DDRB	=	0x3;	//output PB0 & PB1 (OC0A / OC1A)
	TCCR1	=	0x51;	//PWM1A on, OC1A cleared / !OC1A set, clock select 1:1
	OCR1A	=	2;		//PWM 127 ~50%
	OCR1C	=	127;	//PWM freq 1:1 (clears TCNT1 on match)
	DTPS1	=	0;		//dead time prescaler 2-bit
	DT1A	=	0x33;	//dead time H[7..4] & L[3..0]
	
	//loop	
	while(1){}
	
}