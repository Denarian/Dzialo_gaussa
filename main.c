/*
 * Sterownik_dziala_gaussa.c
 *
 * Created: 19.03.2019 18:08:34
 * Author : Jakub
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "piny.h"
#include "LCD/lcd44780.h"
#include "pp_uart.h"

#define POS1 80
#define POS2 115
#define POS3 130
#define ZMIANA_POS 1500

void czekaj(uint16_t);

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
	
	//zmienne
	double predkosc = 0;
	char buffor[13];
	int miedzyczasy[11];
	int miedzyczasy_ovf[11];
	
	
	//iniclializacja podzespolow
	lcd_init();
	USART_Init(__UBRR);
	czekaj(1000);
	sei();
	
	lcd_str(" Wersja 4.3");
	rsSendStr("Wersja 4.3\n\r");
	
	if (!BR00_STAN) 
		laduj();
	
	while(1)
	{
		 
		if (BR00_STAN && SPUST_STAN)
		{	
		//	for(int i = 0; i<10;i++)
		//		tab_predkosci[i] = 9375;
				
			//wdt_enable(WDTO_15MS); // watchdog na 15ms
			
			CW01_ON;
			timer0_start();
			while(!BR01_STAN);
			CW01_OFF;
			CW02_ON;
			wdt_reset();
			

			miedzyczasy[0] = TCNT0;
			miedzyczasy_ovf[0] = timer0_ovf;

			
			while(!BR02_STAN);
			CW02_OFF;
			CW03_ON;
			wdt_reset();
						

			miedzyczasy[1] = TCNT0;
			miedzyczasy_ovf[1] = timer0_ovf;

			
			while(!BR03_STAN);
			CW03_OFF;
			CW04_ON;
			wdt_reset();
			
			
			miedzyczasy[2] = TCNT0;
			miedzyczasy_ovf[2] = timer0_ovf;

						
			while(!BR04_STAN);
			CW04_OFF;
			CW05_ON;
			wdt_reset();
			

			miedzyczasy[3] = TCNT0;
			miedzyczasy_ovf[3] = timer0_ovf;

			
			
			while(!BR05_STAN);
			CW05_OFF;
			CW06_ON;
			wdt_reset();
			
			miedzyczasy[4] = TCNT0;
			miedzyczasy_ovf[4] = timer0_ovf;
			
			
			while(!BR06_STAN);
			CW06_OFF;
			CW07_ON;
			wdt_reset();
			

			miedzyczasy[5] = TCNT0;
			miedzyczasy_ovf[5] = timer0_ovf;
			
						
			while(!BR07_STAN);
			CW07_OFF;
			CW08_ON;
			wdt_reset();
			
			
			miedzyczasy[6] = TCNT0;
			miedzyczasy_ovf[6] = timer0_ovf;

			
			while(!BR08_STAN);
			CW08_OFF;
			CW09_ON;
			wdt_reset();
			

			miedzyczasy[7] = TCNT0;
			miedzyczasy_ovf[7] = timer0_ovf;

						
			while(!BR09_STAN);
			CW09_OFF;
			CW10_ON;
			wdt_reset();
			

			miedzyczasy[8] = TCNT0;
			miedzyczasy_ovf[8] = timer0_ovf;

						
			while(!BR10_STAN);
			CW10_OFF;
			wdt_disable();

			miedzyczasy[9] = TCNT0;
			miedzyczasy_ovf[9] = timer0_ovf;
			

			while(!BR11_STAN);
			timer0_stop();
			miedzyczasy[10] = TCNT0;
			miedzyczasy_ovf[10] = timer0_ovf;
			
			
			
			/*
						timer0_start();
						_delay_ms(1);
						timer0_stop();
			*/
			
			predkosc = 0.1;
			predkosc /= (((255*miedzyczasy_ovf[10]) + miedzyczasy[10])*0.000004)-(((255*miedzyczasy_ovf[9]) + miedzyczasy[9])*0.000004);
			lcd_cls();
			lcd_str(" Predkosc:");
			dtostrf(predkosc*3.6,6,2,buffor);
			lcd_str(buffor);
			lcd_locate(1,0);
		//	lcd_int(TCNT0);
		//	lcd_str(" | ");
		//	lcd_int(timer0_ovf);
			dtostrf(predkosc,13,5,buffor);
			lcd_str(buffor);
			lcd_str("m/s");
			
				for(int i=1;i<11;i++)
				{
					rsSendStr(dtostrf(((255*miedzyczasy_ovf[i]) + miedzyczasy[i])*0.000004,13,5,buffor));
					rsSendStr(" | ");
				}
				
			rsSendStr("\n\r");
		/*	for(int i=1;i<10;i++)
			{
				rsSendStr(itoa(miedzyczasy[i], buffor,10));
				rsSendStr(" | ");
			}
			rsSendStr("\n\r");
			for(int i=1;i<10;i++)
				{
				rsSendStr(itoa(miedzyczasy_ovf[i], buffor,10));
				rsSendStr(" | ");
				}
			rsSendStr("\n\r");
			rsSendStr("\n\r");
			*/
			laduj();
		}
			
	}
}

void timer0_start()
{
	TCNT0 = 0;
	timer0_ovf = 0;
	TIMSK |= (1<<TOIE0);
	TCCR0 = (1<<CS01) | (1<<CS00); //PRESKALER 64
	
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
	czekaj(ZMIANA_POS);
	serwo_pos(POS2);
	czekaj(ZMIANA_POS);
	if(!BR00_STAN)
	{
		serwo_pos(POS3);
		czekaj(ZMIANA_POS);
	}
	serwo_stop();
}

void czekaj(uint16_t op){
	for(uint16_t i=0;i<op;i++)
	_delay_ms(1);
}