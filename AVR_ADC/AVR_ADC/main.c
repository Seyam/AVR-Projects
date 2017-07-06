/*
 * AVR_ADC.c
 *
 * Created: 7/6/2017 12:33:13 PM
 * Author : nishadur.rahman
 */ 
 
#include <avr/io.h>
//#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL

#define LED_ON	 PORTB |= (1<<PORTB3)
#define LED_OFF		PORTB &= ~(1<<PORTB3)
#define LED_TOGGLE		PINB |= (1<<PINB3)

#define LED10_ON	PORTB |= (1<<PORTB2)
#define LED10_OFF	PORTB &= ~(1<<PORTB2)

ISR(TIMER1_COMPA_vect){

	LED_ON;
}

ISR(TIMER1_COMPB_vect){

	LED_OFF;
}


ISR(ADC_vect)
{
	uint16_t duty = ADCL;

	if (duty > 128)
	{
		LED10_ON;
	}
	else 
	{
		LED10_OFF;
	}
	OCR1B = duty;
	//OCIE1B = duty;
}

void PWM_Init_LED(void){
	TCCR1B  |= (1<<CS10) | (1<<WGM12);   //no prescaler, CTC mode
	TIMSK1  |= (1<<OCIE1A) | (1<<OCIE1B);
	OCR1A = 800;	//(F_CPU/(10000*2*1)-1)
	OCR1B = 400;
}



void ADC_Init(void){
	ADMUX |= (1<<REFS0);	// | (1<<MUX0)
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	sei();
}

int main(void)
{	
	DDRB |= (1<<DDB3);//OUTPUT
	DDRB |= (1<<DDB2);//OUTPUT
	DDRC &= ~(1<<DDC0);//INPUT

	ADC_Init();
	PWM_Init_LED();

    /* Replace with your application code */
    while (1) 
    {
    }

	return(0);
}

