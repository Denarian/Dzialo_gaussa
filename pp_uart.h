/*
 * pp_uart.h
 *
 *  Created on: 14-02-2016
 *      Author: xemax
 *      prosta bilbioteka do obs³ugi UART bez wodotrysków
 *      TYLKO NADAWANIE Z MCU ATMEGA644xx i ATMEGA16/32xx
 *      byæ mo¿e ¿e bêdzie te¿ hulaæ na innych po drobnych zmianach
 *
 *
 */

#ifndef PP_UART_H_
#define PP_UART_H_

#define UART_BAUD 9600      // tu definiujemy interesuj¹c¹ nas prêdkoœæ
#define __UBRR ((F_CPU+UART_BAUD*8UL) / (16UL*UART_BAUD)-1) // obliczamy UBRR dla U2X=0

#define UART_RX_BUF_SIZE 32 // definiujemy bufor o rozmiarze 32 bajtów

volatile char UART_RxBuf[UART_RX_BUF_SIZE];		// bufor odbiorczy UART
volatile uint8_t bufor_full;					// flaga przepe³nienia bufora odbiorczego

void USART_Init(uint16_t baud);
void rsSend(unsigned data);
void rsSendStr(volatile char *s);
void rsSendStr_P(const char *s);


#endif /* PP_UART_H_ */
