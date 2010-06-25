/* Candle simulator with AVR + LED 
By Chris Lockfort (devnull@csh.rit.edu)
*/

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>

#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))

int main(void)
{
	CPU_PRESCALE(0); //16 MHz clock
	
	DDRB |= (1<<7); //PB7 set output
	
	TCCR0A = 0x00; //timer & prescaler
	TCCR0B = 0x05;
	
	// pwm enable
	TCCR0A = (1<<COM0A1) | (1<<WGM00); 
	TCCR0B = (1<<CS01);
	
	unsigned char i;
	while(1){
		if(rand()<21300){//steady state (65% chance)
			OCR0A = 240;
		}
		else{ //flicker
			if(rand()<16384){ //flicker pattern #1
				for(i=240; i>80; --i){
					OCR0A = i;
					_delay_ms(3);
				}
				for(i=80; i<240; ++i){
					OCR0A = i;
					_delay_ms(4);
				}
			}
			else{ //flicker pattern #2
				OCR0A = 40;
				_delay_ms(400);
				OCR0A = 240;
			}
		}	
		_delay_ms(1500);
	}
}