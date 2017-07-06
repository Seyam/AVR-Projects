/*
 * PROJETO_DIMMER.cpp
 *
 * Created: 11/06/2015 01:15:48
 *  Author: Marcos
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR)) // ADC Voltage Reference: 5V
uint8_t brightness;


void ADC_init(void)
{
    ADMUX|=(0<<REFS0) | (1<<REFS1)|(0<<MUX0); // ADC Voltage Reference: 5V(internal)
    ADCSRA|=(1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
    DIDR0 |=(0<<ADC0D);// ADC in A0 at pin PC0 potentiometer 10K
}


void PWM_init()
{
        // initialize timer0 in PWM mode Phase Correct PWM
        //Clear OC0A on Compare Match when up-counting. Set OC0A onCompare Match when down-counting.
        
        TCCR0A= (1<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (1<<WGM00);
        
        //(No prescaling)
        
        TCCR0B= (0<<WGM02) | (0<<CS02) | (0<<CS01) | (1<<CS00);
        TCNT0=0x00;
        OCR0A=0x00;
        OCR0B=0x00;
        
        // make sure to make OC0 pin (pin PB6 for atmega328P) as output pin
        DDRD |= (1<<PIND6);
        
        // Timer/Counter 0 Interrupt(s) initialization
        //TIMSK0=(0<<OCIE0B) | (0<<OCIE0A) | (1<<TOIE0);
}
unsigned int ADC_Converter(unsigned char valor)
{
    ADMUX= valor| ADC_VREF_TYPE; // ADC Voltage Reference: 5V(internal)
    // Delay needed for the stabilization of the ADC input voltage
    _delay_us(10);
    // Start the AD conversion
    ADCSRA|=(1<<ADSC);
    // Wait for the AD conversion to complete
    while ((ADCSRA & (1<<ADIF))==0);
    ADCSRA|=(1<<ADIF);
    _delay_us(10);
    return ADCW;
}
 
int main(void)
{
    
    ADC_init();
    PWM_init();
    while(1)
    {
        ADC_Converter(0);
        brightness =ADCW/4; // converter 1023 to 255
        
        switch (brightness)
        {
            case 255:
            OCR0A=0xFF;
            _delay_ms(10);
            break;
            case 0:
            OCR0A=0x00;
            _delay_ms(10);
            break;
        }
        if (brightness > 0 || brightness < 255)
        {
            OCR0A = brightness ;
            _delay_ms(10);
        }    
                
    }
    
}