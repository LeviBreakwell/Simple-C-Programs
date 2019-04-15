#include <avr/io.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <graphics.h>
#include <lcd.h>
#include <macros.h>
#include "lcd_model.h"
void setup( void ) {
	set_clock_speed(CPU_8MHz);
	//	(a) Enable input from the Left, Right, Up, and Down switches
	//	of the joystick.
    CLEAR_BIT(DDRB,1);
    CLEAR_BIT(DDRD,0);
    CLEAR_BIT(DDRD,1);
    CLEAR_BIT(DDRB,7);
	//	(b) Initialise the LCD display using the default contrast setting.
    clear_screen();
    lcd_init(LCD_DEFAULT_CONTRAST);
	//	(c) Use one of the functions declared in "graphics.h" to display 
	//	your student number, "n10229825", using the background colour, 
	//	positioning the left edge of the text at 17 and the nominal top 
	//	of the text at 16.
    draw_string(17,16, "n10229825",BG_COLOUR);
	//	(d) Use one of the functions declared in "graphics.h" to copy 
	//	the contents of the screen buffer to the LCD.
    show_screen();
}
void process( void ) {
	//  (e) Determine if the Up joystick switch is closed. 
	//	If it is, set the LCD display to turn off all pixels.
    if (BIT_IS_SET(PIND,1)){
        LCD_CMD(lcd_set_display_mode,lcd_display_all_off);
    }
	//  (f) OTHERWISE, determine if the Down joystick switch 
	//	is closed. If it is, set the LCD display to turn on all pixels.
    else if (BIT_IS_SET(PINB,7)){
        LCD_CMD(lcd_set_display_mode, lcd_display_all_on);
    }
	//  (g) OTHERWISE, determine if the Left joystick switch 
	//	is closed. If it is, set the LCD display to enter normal video mode.
    else if (BIT_IS_SET(PINB,1)){
        LCD_CMD(lcd_set_display_mode,lcd_display_normal);
    }
	//  (h) OTHERWISE, determine if the Right joystick switch 
	//	is closed. If it is, set the LCD display to switch to inverse video mode.
    else if (BIT_IS_SET(PIND,0)){
        LCD_CMD(lcd_set_display_mode,lcd_display_inverse); 
    } 
	//	If none of the joystick switches are closed, do nothing.
	//	(Hint: do not insert any more instructions.)
    else{

    }
}
int main(void) {
	setup();
	for ( ;; ) {
		process();
		_delay_ms(100);
	}
	return 0;
}