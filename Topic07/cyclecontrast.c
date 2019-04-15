#include <avr/io.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <macros.h>
#include <graphics.h>
#include <lcd.h>
#include "lcd_model.h"
void new_lcd_init(uint8_t contrast) {
    // Set up the pins connected to the LCD as outputs
    SET_OUTPUT(DDRD, SCEPIN); // Chip select -- when low, tells LCD we're sending data
    SET_OUTPUT(DDRB, RSTPIN); // Chip Reset
    SET_OUTPUT(DDRB, DCPIN);  // Data / Command selector
    SET_OUTPUT(DDRB, DINPIN); // Data input to LCD
    SET_OUTPUT(DDRF, SCKPIN); // Clock input to LCD

    CLEAR_BIT(PORTB, RSTPIN); // Reset LCD
    SET_BIT(PORTD, SCEPIN);   // Tell LCD we're not sending data.
    SET_BIT(PORTB, RSTPIN);   // Stop resetting LCD

    LCD_CMD(lcd_set_function, lcd_instr_extended);
    LCD_CMD(lcd_set_contrast, contrast);
    LCD_CMD(lcd_set_temp_coeff, 0);
    LCD_CMD(lcd_set_bias, 3);

    LCD_CMD(lcd_set_function, lcd_instr_basic);
    LCD_CMD(lcd_set_display_mode, lcd_display_normal);
    LCD_CMD(lcd_set_x_addr, 0);
    LCD_CMD(lcd_set_y_addr, 0);
}
void setup( void ) {
	set_clock_speed(CPU_8MHz);

	//	(a) Enable input from the joystick-left switch and joystick-right switch.
    CLEAR_BIT(DDRB,1);
    CLEAR_BIT(DDRD,0);
	//	(b) Initialise the LCD display using the default contrast setting.
	clear_screen();
    new_lcd_init(LCD_DEFAULT_CONTRAST);
	//	(c) Use one of the functions declared in "graphics.h" to display 
	//	your student number, "n10229825", using the foreground colour, 
	//	positioning the left edge of the text at 20 and the nominal top 
	//	of the text at 14.
    draw_string(20,14, "n10229825",FG_COLOUR);
	//	(d) Use one of the functions declared in "graphics.h" to copy the contents 
	//	of the screen buffer to the LCD.
    show_screen();
}

//	(e) Declare a global variable of type int named Contrast and 
//	initialise it to the default LCD contrast.

uint8_t contrast = 0;

void process(void) {
	//	(f) Test pin corresponding to joystick-right switch. If closed,
	//	decrement Contrast by 6. If the result is less than zero,
	//	set Contrast to the maximum permitted LCD contrast value.
    if ( BIT_IS_SET(PIND, 0)){
        contrast -= 6;
		if (contrast < 0){
			contrast = 127;
		}
    }
	//	(g) Test pin corresponding to joystick-left switch. If closed,
	//	increment Contrast by 6. If the result is greater
	//	then the maximum permitted LCD contrast value, set Contrast 
	//	to zero.
    if ( BIT_IS_SET(PINB, 1)){
        contrast+=6;
		if (contrast >127){
			contrast = 0;
		}

    }
	//	(h) Send a sequence of commands to the LCD to enable extended
	//	instructions, set contrast to the current value of Contrast, 
	//	and finally retore the LCD to basic instruction mode.
	LCD_CMD(lcd_set_function,lcd_instr_extended);
	LCD_CMD(lcd_set_contrast, contrast);
	LCD_CMD(lcd_set_function,lcd_instr_basic);
}


int main(void) {
	setup();

	for ( ;; ) {
		process();
		_delay_ms(100);
	}

	return 0;
}
