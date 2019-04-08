#include "cab202_graphics.h"

void draw_bubbles(void){
	// (a) Draw a bubble at (31,20)
	draw_char( 31, 20, 'O' );
	// (b) Draw a bubble at (39,6)
	draw_char( 39, 6, 'O' );
	// (c) Draw a bubble at (74,11)
	draw_char( 74, 11, 'O' );
	// (d) Draw a bubble at (62,12)
	draw_char( 62, 12, 'O' );
	// Keep the following line without change.
	show_screen();
}

int main( void ) {
	setup_screen();

	draw_bubbles();

	draw_string( 0, screen_height() - 1, "Press any key to finish..." );
	wait_char();
	cleanup_screen();
	return 0;
}