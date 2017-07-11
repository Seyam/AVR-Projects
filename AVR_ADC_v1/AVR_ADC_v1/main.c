/*
 * AVR_ADC.c
 *
 * Created: 7/6/2017 12:33:13 PM
 * Author : nishadur.rahman
 */

#define F_CPU 16000000UL 
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>


#define PULSE_ON		PORTB |= (1<<PORTB3)
#define PULSE_OFF		PORTB &= ~(1<<PORTB3)


#define LED_ON			PORTB |= (1<<PORTB2)
#define LED_OFF			PORTB &= ~(1<<PORTB2)
#define LED_TOGGLE		PINB |= (1<<PINB2)

ISR(TIMER1_COMPA_vect){

	PULSE_ON;
}

ISR(TIMER1_COMPB_vect){

	PULSE_OFF;
}


ISR(ADC_vect)
{
	uint16_t duty = ADC;  //ADCW
	//duty += (ADCH<<8);
	OCR1B = duty;

	PORTD = duty;
	if (duty > 900)
	{
		LED_ON;
	}
	else
	{
		LED_OFF;
	}
	//OCIE1B = duty;
}

void PWM_Init_LED(void){
	TCCR1B  |= (1<<CS10) | (1<<WGM12);   //no prescaler, CTC mode
	TIMSK1  |= (1<<OCIE1A) | (1<<OCIE1B);
	OCR1A = 800;	//(F_CPU/(10000*2*1)-1)
	OCR1B = 400;
}



void ADC_Init(void){
	ADMUX |= (1<<REFS0) | (1<<MUX0);	// | (1<<MUX0=ADC1)   | (1<<REFS1)
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ADC AutoTrigger Enabled, Conversion complete interrupt enabled, ADC prescaler selected maximum(128)
	sei();
}

int main(void)
{	
	DDRD =0xFF;
	DDRB |= (1<<DDB3);//PWM OUTPUT
	DDRB |= (1<<DDB2);//OUTPUT
	//DDRC &= ~(1<<DDC0);//INPUT

	ADC_Init();
	PWM_Init_LED();

    /* Replace with your application code */
    while (1) 
    {
    }

	return(0);
}

