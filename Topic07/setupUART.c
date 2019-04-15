#include <stdint.h>
#include <stdio.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include <cpu_speed.h>

#include <graphics.h>
#include <macros.h>
#include "lcd_model.h"

//	(a) Implement a function called setup_uart which requires no arguments and
//	returns no value.
void setup_uart(){
	//	(a.a) Set the data transmission rate to 9600 bits per second,
	//	using the formula provided in the Topic 10 Technical Notes.
    cli();
    uint32_t baud = 9600;
    UBRR1 = (F_CPU/8/ baud - 1)/2;
	//	(a.b) Set the UART speed to normal speed.
    
    UCSR1A = (0<<U2X1);
	//	(a.c) Enable receive and transmit, but do not enable any UART-related
	//	interrupts.
    UCSR1B = (1<<RXEN1) | (1<<TXEN1)| (0<<RXCIE1) | (0<<TXCIE1);
	//	(a.d) Set the character size to 7 bits, with no parity
	//	and 2 stop bits.
    //UCSR1C = (1<<UCSZ11);
    UCSR1C =(0<<UCSZ10)|(1<<UCSZ11) | (1<<USBS1) | (0<<UPM10)|(0<<UPM11);
//	(b) End of function setup_uart
}

int main(void) {
	setup_uart();

	for ( ;; ) {}
}
