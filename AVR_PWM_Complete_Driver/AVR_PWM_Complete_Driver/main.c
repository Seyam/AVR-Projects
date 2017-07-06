/*
 * AVR_PWM.c
 *
 * Created: 7/6/2017 4:16:29 PM
 * Author : nishadur.rahman
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
//#include <util/delay.h>
#include <avr/interrupt.h>


#define LED_ON	 PORTB |= (1<<PORTB3)
#define LED_OFF		PORTB &= ~(1<<PORTB3)
#define LED_TOGGLE		PINB |= (1<<PINB3)

ISR(TIMER1_COMPA_vect){

	LED_ON;
}

ISR(TIMER1_COMPB_vect){

	LED_OFF;
}

ISR(TIMER0_COMPA_vect){

	uint16_t period = OCR1A; //16 bit timer value
	uint16_t duty = OCR1B;	//16 bit timer value

	if (duty < period)
	{
		duty++;
	} 
	else
	{
		duty=0;
	}
	OCR1B = duty;
}


void millis_timer(uint8_t millis){
	TCCR0A |= (1<<WGM01);				//set to CTC mode
	TCCR0B |= (1<<CS02) | (1<<CS00);	//set prescaler of 1024(clock select)
	OCR0A= millis*78125-1;
	TIMSK0 |= (1<<OCIE0A);
}


void PWM_Init(void){
	TCCR1B  |= (1<<CS10) | (1<<WGM12);  //no prescaler,  CTC mode
	TIMSK1  |= (1<<OCIE1A) | (1<<OCIE1B); //output compare IRQ
	OCR1A = 800;		//(F_CPU/10,000*2*1)-1
	OCR1B = 400;		//starting duty cycle. will be eventually set to 0 while in loop

}

void PWM_Increase_duty(void){

		uint16_t period = OCR1A; //16 bit timer value
		uint16_t duty = OCR1B;	//16 bit timer value

		if (duty < period)
		{
			duty++;
		}
		else
		{
			duty=0;
		}
		OCR1B = duty;
}

void PWM_Decrease_duty(void){

	uint16_t period = OCR1A; //16 bit timer value
	uint16_t duty = OCR1B;	//16 bit timer value

	if (duty > 0)
	{
		duty--;
	}
	else
	{
		duty=0;
	}
	OCR1B = duty;
}



int main(void)
{	
	DDRB |=(1<<DDB3);
	millis_timer(1); //delay before updating duty cycle
	PWM_Init();
	sei();
    /* Replace with your application code */
    while (1) 
    {
    }
	return(0);
}

