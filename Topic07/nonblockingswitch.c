#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <cpu_speed.h>

#include <graphics.h>
#include <macros.h>
#include "lcd_model.h"

void setup(void)
{
    set_clock_speed(CPU_8MHz);
    lcd_init(LCD_DEFAULT_CONTRAST);
    lcd_clear();

    //	(a) Initialise Timer 0 in normal mode so that it overflows
    //	with a period of approximately 0.008 seconds.
    //	Hint: use the table you completed in a previous exercise.
    TCCR0A = 0;
    TCCR0B = 4;
    //	(b) Enable timer overflow interrupt for Timer 0.
    TIMSK0 = 1;
    //	(c) Turn on interrupts.
    sei();
    //	(d) Enable the joystick centre switch for digital input.
    CLEAR_BIT(DDRB, 0);
    //	(e) Display your student number, "n10229825", with nominal
    //	top-left corner at screen location (15,23).
    draw_string(15, 23, "n10229825", FG_COLOUR);
    // Keep the next instruction intact.
    show_screen();
}

//	(f) Create a volatile global variable called bit_count.
//	The variable should be an 8-bit unsigned integer.
//	Initialise the variable to 0.
volatile uint8_t bit_count = 0;
//	(g) Define a volatile global 8-bit unsigned global variable
//	called switch_state which will store the current state of the switch.
volatile uint8_t switch_state;
//	(h) Define an interrupt service routine to process timer overflow
//	interrupts for Timer 0. Every time the interrupt service
//	routine is called, bit_count should:
//		(h.a) Left-shift bit_count one place;
//		(h.b) Bitwise AND with a mask in which the 3 bits on the right
//			are 1 and the others are 0.
//		(h.c) Use bitwise OR to add the current open/closed value of the
//			joystick centre switch to the history.
//		(h.d) If bit_count is equal to the bit mask, then the switch has been
//			observed 3 times in a row to be closed. Assign the value 1 to
//			switch_state, indicating that the switch should now be considered to be
//			officially "closed".
//		(h.e) If bit_count is equal to 0, then the switch has been observed
//			to be open at least 3 in a row, so store 0 in switch_state,
//			indicating that the switch should now be considered to be officially "closed".
ISR(TIMER0_OVF_vect)
{
    bit_count = bit_count << 1;
    uint8_t mask = 0b00000111;
    bit_count = bit_count & mask;
    bit_count = bit_count | BIT_IS_SET(PINB, 0);
    if (bit_count == mask)
    {
        switch_state = 1;
    }
    else if (bit_count == 0)
    {
        switch_state = 0;
    }
}

// -------------------------------------------------
// Test driver.
// -------------------------------------------------

void process(void)
{
    static uint8_t prevState = 0;
    if (switch_state != prevState)
    {
        prevState = switch_state;
        draw_string(30, 40, prevState ? "closed" : "open  ", FG_COLOUR);
        show_screen();
    }
}

int main(void)
{
    setup();

    for (;;)
    {
        process();
    }
}