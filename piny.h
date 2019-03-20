#include<avr/io.h>

#define BR00 (1<<PINB2)
#define BR00_STAN (PINB & BR00)

#define BR01 (1<<PINB3)
#define BR01_STAN (PINB & BR01)

#define BR02 (1<<PINB4)
#define BR02_STAN (PINB & BR02)

#define BR03 (1<<PINB5)
#define BR03_STAN (PINB & BR03)

#define BR04 (1<<PINB6)
#define BR04_STAN (PINB & BR04)

#define BR05 (1<<PINB7)
#define BR05_STAN (PINB & BR05)

#define BR06 (1<<PIND2)
#define BR06_STAN (PIND & BR06)

#define BR07 (1<<PIND3)
#define BR07_STAN (PIND & BR07)

#define BR08 (1<<PIND4)
#define BR08_STAN (PIND & BR08)

#define BR09 (1<<PIND5)
#define BR09_STAN (PIND & BR09)

#define BR10 (1<<PIND6)
#define BR10_STAN (PIND & BR10)

#define BR11 (1<<PINB1)
#define BR11_STAN (PINB & BR11)

#define SPUST (1<<PINB0)
#define SPUST_STAN !(PINB & SPUST)
 

#define CW01 (1<<PINA6)
#define CW01_ON PORTA |= CW01
#define CW01_OFF PORTA &= ~CW01

#define CW02 (1<<PINA7)
#define CW02_ON PORTA |= CW02
#define CW02_OFF PORTA &= ~CW02

#define CW03 (1<<PINC7)
#define CW03_ON PORTC |= CW03
#define CW03_OFF PORTC &= ~CW03

#define CW04 (1<<PINC6)
#define CW04_ON PORTC |= CW04
#define CW04_OFF PORTC &= ~CW04

#define CW05 (1<<PINC5)
#define CW05_ON PORTC |= CW05
#define CW05_OFF PORTC &= ~CW05

#define CW06 (1<<PINC4)
#define CW06_ON PORTC |= CW06
#define CW06_OFF PORTC &= ~CW06

#define CW07 (1<<PINC3)
#define CW07_ON PORTC |= CW07
#define CW07_OFF PORTC &= ~CW07

#define CW08 (1<<PINC2)
#define CW08_ON PORTC |= CW08
#define CW08_OFF PORTC &= ~CW08

#define CW09 (1<<PINC1)
#define CW09_ON PORTC |= CW09
#define CW09_OFF PORTC &= ~CW09

#define CW10 (1<<PINC0)
#define CW10_ON PORTC |= CW10
#define CW10_OFF PORTC &= ~CW10

#define SERWO (1<<PINA0)
#define SERWO_ON PORTA |= SERWO
#define SERWO_OFF PORTA &= ~SERWO



