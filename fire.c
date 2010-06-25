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
	
	unsigned char i,current,next;
	while(1){
		if(rand()<24576){//75% chance
			next = 20+rand()/139; //Just implementing a rand floor so for more light
			for(i=current; i<next; ++i){
				OCR0A = i;
				_delay_us(100000/(next-current));
			}
			for(i=current; i>next; --i){
				OCR0A = i;
				_delay_us(100000/(next-current));
			}
			current=next;
		}
		else{
                        next = 245;
                        for(i=current; i<next; ++i){
                                OCR0A = i;
                                _delay_us(100000/(next-current));
                        }
                        for(i=current; i>next; --i){
                                OCR0A = i;
                                _delay_us(100000/(next-current));
                        }
                        current=next;
		}
		_delay_ms(100);
	}
}
