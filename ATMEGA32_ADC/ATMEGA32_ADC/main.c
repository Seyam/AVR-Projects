#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>

#define LED_ON		PORTD |= (1<<PORTD2)
#define LED_OFF		PORTD &= ~(1<<PORTD2)
//#include "adc.h"


void ADC_init(void)
{
	ADMUX|=(1<<REFS0)|(1<<REFS1); //1.reference selection
	ADCSRA|=(1<<ADPS1)|(1<<ADPS2);//2.pre-sclar selection
	ADCSRA&=~(1<<ADPS0);
	ADCSRA|=(1<<ADEN);           //3.enable ADC

}
uint16_t read_data(void)
{
	ADMUX|=(1<<MUX0);            //4.channel selection   ADC1
	ADCSRA|=(1<<ADSC);           //5.start conversion
	while(ADCSRA & (1<<ADSC))
	{

	}
	return ADCW;

}






int main(void)
{
    //DDRB=0xFF;
	DDRD=0xFF;

    uint16_t adc_val=2;
    ADC_init();

    while(1)
    {
        adc_val=read_data();

		//PORTB=adc_val;
		
        if(adc_val > 128)
            LED_OFF;
        else
			LED_ON;
            
			
         _delay_ms(400);
    }
    return 0;
}
