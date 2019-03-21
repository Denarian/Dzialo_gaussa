/*
 * pp_uart.c
 *
 *  Created on: 14-02-2016
 *      Author: xemax
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <string.h>

#include "pp_uart.h"

//****************************funkcje obs³ugi UART

#if  defined (__AVR_ATmega644__)||(__AVR_ATmega644P__)||(__AVR_ATmega644PA__)
// ***** ta sekcja dotyczy MCU atmega 644X

void USART_Init(uint16_t baud) { //inicjalizacja uart
    /* Ustawienie prêdkosci */
    UBRR0H = (uint8_t) (baud >> 8);
    UBRR0L = (uint8_t) baud;
    /* Za³¹czenie nadajnika z obs³ug¹ przerwañ odbiorczych */
    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1<<RXCIE0);
    /* Ustawienie formatu ramki: 8bitów danych, 1 bit stopu
     *
     * jesli Atmega644 to nic nie robic bo rejestry usart s¹ domyœlnie poustawiane jak nam potrzeba
     * */
}

#elif defined (__AVR_ATmega16A__)||(__AVR_ATmega16__)||(__AVR_ATmega32__)||(__AVR_ATmega32A__)
// ***** ta sekcja dotyczy MCU atmega 16-32-32A

void USART_Init(uint16_t baud) { //inicjalizacja uart
    /* Ustawienie prêdkosci */
    UBRRH = (uint8_t) (baud >> 8);
    UBRRL = (uint8_t) baud;
    /* Za³¹czenie nadajnika z obs³ug¹ przerwañ odbiorczych*/
    UCSRB = (1 << TXEN) | (1 << RXEN) | (1<<RXCIE);
    // Ustawienie formatu ramki: 8bitów danych, 1 bit stopu
    UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
}
#endif

/*wysy³anie jednego bajta danych przez uart funkcja napisana
 * tak jak to jest w nocie aplikacyjnej
 */
void rsSend(unsigned data) {

	#if defined (__AVR_ATmega644__)||(__AVR_ATmega644P__)||(__AVR_ATmega644PA__)
	/* Wait for empty transmit buffer*/
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    /* Put data into buffer, sends the data*/
    UDR0 = data;
#elif defined (__AVR_ATmega16A__)||(__AVR_ATmega16__)||(__AVR_ATmega32__)||(__AVR_ATmega32A__)
	/* Wait for empty transmit buffer*/
    while (!(UCSRA & (1 << UDRE)))
        ;
    /* Put data into buffer, sends the data*/
    UDR = data;
#endif
}

//przesy³anie stringów przez uart
void rsSendStr(volatile char *s) {
    for (; *s; s++)
        rsSend(*s);
}

//przesy³anie stringów przez uart
void rsSendStr_P(const char *s) {
	register char c;
    while((c = pgm_read_byte( s++ ) )) rsSend(c);
}

// definiujemy procedurê obs³ugi przerwania odbiorczego
#if defined (__AVR_ATmega644__)||(__AVR_ATmega644P__)||(__AVR_ATmega644PA__)
ISR( USART_RXC_vect ) {
	char znak;

	//sprawdzamy czy nie przekroczylismy wielkosci bufora odczytu
	if( strlen((char*)UART_RxBuf) < UART_RX_BUF_SIZE ){
		znak = UDR0;
		//pobieramy bajt danych z bufora sprzêtowego i zapisujemy w buforze odczytu
		UART_RxBuf[strlen((char*)UART_RxBuf)] = znak;
		}
	else {
		//jesli bufor jest pelen to ustaw flage ale nie zapisuj juz do bufora
		//przepusc tylko znak z powrotem do nadawcy
		bufor_full = 1;
		znak = UDR0;
	}
	//odeslij znak z powrotem
	rsSend(znak);

}

#elif defined (__AVR_ATmega16A__)||(__AVR_ATmega16__)||(__AVR_ATmega32__)||(__AVR_ATmega32A__)
ISR( USART_RXC_vect ) {
	char znak;

	//sprawdzamy czy nie przekroczylismy wielkosci bufora odczytu
	if( strlen((char*)UART_RxBuf) < UART_RX_BUF_SIZE ){
		znak = UDR;
		//pobieramy bajt danych z bufora sprzêtowego i zapisujemy w buforze odczytu
		UART_RxBuf[strlen((char*)UART_RxBuf)] = znak;
		}
	else {
		//jesli bufor jest pelen to ustaw flage ale nie zapisuj juz do bufora
		//przepusc tylko znak z powrotem do nadawcy
		bufor_full = 1;
		znak = UDR;
	}
	//odeslij znak z powrotem
	rsSend(znak);

}
#endif
//****************************koniec obs³ugi UART
