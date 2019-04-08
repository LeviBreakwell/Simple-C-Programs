#include "cab202_graphics.h"

void draw_lines(void){
	// (a) Draw a line from (3,18) to (36,10).
	draw_line( 3, 18, 36, 10, '~' );
	// (b) Draw a line from (36,10) to (66,13).
	draw_line( 36, 10, 66, 13, '~' );
	// (c) Draw a line from (66,13) to (49,9).
	draw_line( 66, 13, 49, 9, '~' );
	// (d) Draw a line from (49,9) to (3,18).
	draw_line( 49, 9, 3, 18, '~' );
	// Leave the following instruction unchanged.
	show_screen();
}

int main( void ) {
	setup_screen( );

	draw_lines();

	draw_string( 0, screen_height( ) - 1, "Press any key to finish..." );
	wait_char( );
	cleanup_screen( );
	return 0;
}