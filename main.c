/*
 * Sterownik_dziala_gaussa.c
 *
 * Created: 19.03.2019 18:08:34
 * Author : Jakub
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "piny.h"
#include "LCD/lcd44780.h"

#define POS1 90
#define POS2 115
#define POS3 130
#define ZMIANA_POS 1500

void timer0_start();
void timer0_stop();


void serwo_pos(int);
void serwo_stop();
void serwo_start();

void laduj();

volatile int timer0_ovf = 0;


int main(void)
{
	// kofiguracja io wszystkie pozostale wejscia maja zewnetrzne rezystory podciagajace.
	DDRA = CW01 | CW02 | SERWO;
	DDRC = 255;
	PORTB = BR00 | BR11;
	double predkosc = 0;
	char buffor[13];
	lcd_init();
	sei();
	lcd_str("Wersja 4.0");

	laduj();
	
	while(1)
	{
		 
		if (BR00_STAN && SPUST_STAN)
		{

			CW01_ON;
			while(!BR01_STAN);
			CW01_OFF;
			CW02_ON;
			
			while(!BR02_STAN);
			CW02_OFF;
			CW03_ON;
			
			while(!BR03_STAN);
			CW03_OFF;
			CW04_ON;
			
			while(!BR04_STAN);
			CW04_OFF;
			CW05_ON;
			
			while(!BR05_STAN);
			CW05_OFF;
			CW06_ON;
			
			while(!BR06_STAN);
			CW06_OFF;
			CW07_ON;
			
			while(!BR07_STAN);
			CW07_OFF;
			CW08_ON;
			
			while(!BR08_STAN);
			CW08_OFF;
			CW09_ON;
			
			while(!BR09_STAN);
			CW09_OFF;
			CW10_ON;
			
			while(!BR10_STAN);
			CW10_OFF;
			timer0_start();
			while(!BR11_STAN);
			timer0_stop();
			/*
						timer0_start();
						_delay_ms(1);
						timer0_stop();
			*/
			
			predkosc = 1562.5;
			predkosc /= ((255*timer0_ovf) + TCNT0);
			lcd_cls();
			lcd_str("Predkosc: ");
			dtostrf(predkosc*3.6,6,2,buffor);
			lcd_str(buffor);
			lcd_locate(1,0);
		//	lcd_int(TCNT0);
		//	lcd_str(" | ");
		//	lcd_int(timer0_ovf);
			dtostrf(predkosc,13,5,buffor);
			lcd_str(buffor);
			lcd_str("m/s");
			
			laduj();
		}
			
	}
}

void timer0_start()
{
	TCNT0 = 0;
	timer0_ovf = 0;
	TIMSK |= (1<<TOIE0);
	TCCR0 = (1<<CS02) | (1<<CS00);
	
}
void timer0_stop()
{
	TCCR0 = 0;
}

ISR(TIMER0_OVF_vect)
{
	timer0_ovf++;	

}
ISR(TIMER1_OVF_vect)
{
TCNT1 = 25536;
SERWO_ON;	
}
ISR(TIMER1_COMPA_vect)
{
SERWO_OFF;
}

void serwo_pos(int pos)
{
	OCR1A = 26136 + 22*(pos+30);
	if(TCCR1B == 0)
		serwo_start();
	
}
void serwo_stop()
{
	TCCR1B = 0;
}
void serwo_start()
{
	TCNT1 = 25536;
	TIMSK |= (1<<TOIE1) | (1<<OCIE1A);
	TCCR1B = (1<<CS11);
}

void laduj()
{
	serwo_pos(POS1);
	_delay_ms(ZMIANA_POS);
	serwo_pos(POS2);
	if(!BR00_STAN)
	{
		_delay_ms(ZMIANA_POS);
		serwo_pos(POS3);
	}
}