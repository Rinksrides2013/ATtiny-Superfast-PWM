# ATtiny-Superfast-PWM
1MHz+ complimentary PWM with variable deadtime supported by Timer1 in ATtiny25/45/85.
1.9MHz at 5 bit resolution complimentary PWM. 500KHz @ 8-bit resolution.

A great series on youtube for working with the ATtiny series (Any ATMEL AVR series really)
https://www.youtube.com/playlist?list=PLNyfXcjhOAwOF-7S-ZoW2wuQ6Y-4hfjMR

#include <C:\attiny\io.h>


int main(){
	
	//setup	
	PLLCSR	=	0x6;	//enable PLL clock for PWM 64MHz clock to TCNT1
	DDRB	  =	0x3;	//output PB0 & PB1 (OC0A / OC1A)
	TCCR1	  =	0x51;	//PWM1A on, OC1A cleared / !OC1A set, clock select 1:1 (PCK)
	OCR1A	  =	127;	//PWM Duty %
	OCR1C	  =	255;	//PWM freq (clears TCNT1 on match, affects resolution) ~500KHz when OCR1C = 0xff
	DTPS1	  =	0;	//dead time prescaler 2-bit
	DT1A	  =	0x33;	//dead time H[7..4] & L[3..0] initially set to 4 clocks separation of OC1A cleared / !OC1A set
	
	//loop	
	while(1){}
	
}

PLLCSR  = 0x06 enables the PLL ClocK (PCK) for the system OR Timer1, since stock settings of the lfuse has the 
internal 8MHz RC clock selected and CDIV/8 for the cpu resulting in 1MHz cpu clock and 64MHz PLL clock for Timer1

Timer 1 control register (TCCR1) bits set so PWM1A selected (OC0A / OC1A = PB0 / PB1), action on compare is to 
toggle and clock prescale is 1:1

OCR1A   = (total dead time + 1)..(OCR1C-1) this represents the duty % of OCR1C. (for PWM to actually toggle, this 
needs to be less than OCR1C, but more than the total dead time.

OCR1C   = 2..255 this register clears TCNT1 on compare, which OCR1A uses to toggle PBO / PB1. This is why OCR1A MUST
be less than OCR1C for PWM to work.

DTPS1   = 0..3 the CK or PCK prescaler for the deadtimes between complimentary outputs 
<0 = 1:1, 3 = 1:8 deatime clock : CK or PCK>
DT1A	= 0x33;	dead time H[7..4] & L[3..0] here I arbitrarily set to 4 clocks separation of OC1A cleared / !OC1A set.
This is useful for controlling high power switching transistors in a syncronised SMPS power supply or H-Bridge. 
  Ideally you adjust the deatimes according to the turn-on/off times of your transistors and drivers so when the complimentary
outputs switch, the duty number is lessened by the total dead time.

A future update might be a C function or possible library, but I want to keep bloat down.
