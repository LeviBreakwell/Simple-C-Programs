#include <avr/io.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <macros.h>
#include <graphics.h>
#include <lcd.h>

void setup( void ) {
	set_clock_speed(CPU_8MHz);

	//	(a) Initialise the LCD display using the default contrast setting
    lcd_init(LCD_DEFAULT_CONTRAST);
	//	(b) Use one of the functions declared in "graphics.h" to display 
	//	your student number, n10229825, using the background colour, 
	//	positioning the left edge of the image at 27 and the nominal top 
	//	of the text at 13.
    //char * text = "n10229825";
    draw_string(27,13, "n10229825",BG_COLOUR);
	//	(c) Use one of the functions declared in "graphics.h" to copy the contents 
	//	of the screen buffer to the LCD.
    show_screen();
}


int main(void) {
	setup();

	for ( ;; ) {
		_delay_ms(10);
	}

	return 0;
}