// program to change brightness of an LED
// demonstration of PWM

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// initialize PWM
void pwm_init()
{
	// initialize timer0 in PWM mode
	TCCR0A |= (1<<WGM00)|(1<<COM0A1)|(1<<WGM01)|(1<<CS00);
	
	// make sure to make OC0 pin (pin PB3 for atmega32) as output pin
	DDRD |= (1<<PORTD3);
}

void main()
{
	uint8_t brightness;
	
	// initialize timer0 in PWM mode
	pwm_init();
	
	// run forever
	while(1)
	{
		// increasing brightness
		for (brightness = 0; brightness < 255; ++brightness)
		{
			// set the brightness as duty cycle
			OCR0A = brightness;
			
			// delay so as to make the user "see" the change in brightness
			_delay_ms(10);
		}
		
		// decreasing brightness
		for (brightness = 255; brightness > 0; --brightness)
		{
			// set the brightness as duty cycle
			OCR0A = brightness;
			
			// delay so as to make the user "see" the change in brightness
			_delay_ms(10);
		}
		
		// repeat this forever
	}
}