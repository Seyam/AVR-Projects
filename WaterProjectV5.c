#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>  // header file to use time delay


#define MOTOR_ON		PORTB |=(1<<PORTB5)
#define MOTOR_OFF		PORTB &=~(1<<PORTB5)

#define LIGHT_ON		PORTB |=(1<<PORTB4)
#define LIGHT_OFF		PORTB &=~(1<<PORTB4)


int counter = 0;

int main (void)
{
	
	DDRB |=(1<<DDB5); //OUTPUT-MOTOR-ARDUINO PIN 13
	DDRB |=(1<<DDB4); //OUTPUT-LIGHT-ARDUINO PIN 12
	
	DDRD &= ~(1 << DDD2); //INPUT-1-BOTTOM WATER LEVEL
	DDRD &= ~(1 << DDD3); //INPUT-2-TOP WATER LEVEL
	DDRD &= ~(1 << DDD4); //INPUT-3-IR1
	DDRD &= ~(1 << DDD5); //INPUT-4-IR2


	

	while (1)
	{



		// if (!(PIND & (1<<PIND2))  &&  !(PIND & (1<<PIND3))){ //IF LOW

		// 	MOTOR_OFF;
		// }
		// else if ((PIND & (1<<PIND2))  &&  (PIND & (1<<PIND3))){//IF HIGH

		// 	MOTOR_ON;
		// }






		//while(		!(PIND & (1<<PIND4)) 	&&		 !(PIND & (1<<PIND5))		);


		if(		(PIND & (1<<PIND4)	)		){//IF HIGH
			
			// _delay_ms(1000);

			entryLoop();

			
			// counter++;

			while(	(PIND & (1<<PIND4)) || (PIND & (1<<PIND5))	);
			
			

		}

		else if(		(PIND & (1<<PIND5))  	){//IF HIGH

			// _delay_ms(1000);

			exitLoop();
			// counter--;

			while(		(PIND & (1<<PIND5)) || (PIND & (1<<PIND4)) 		);
			
		}


		if(counter>0){

			LIGHT_ON;
		}

		else if(counter<=0){

			LIGHT_OFF;
		}
		
	}
	// return 0;
}


void entryLoop(){

	
for (int i=0; i<5; i++)
	{
	

		if(		(PIND & (1<<PIND5))		){
			counter++;
			MOTOR_ON;
		}
	}



}

void exitLoop(){
	for (int i=0; i<5; i++)
	{

		if(			(PIND & (1<<PIND4))		){
			counter++;
			MOTOR_OFF;
		}
	}

}