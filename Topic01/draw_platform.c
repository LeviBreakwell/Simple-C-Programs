#include "cab202_graphics.h"

void draw_platform(void) {
	// (a) Get the horizontal position of the left end of the platform
	//     using integer arithmetic and storing it in an integer value.
	double hori_pos;
	double vert_pos;
	hori_pos = (screen_width( ) - 11)/2;
	// (b) Get the vertical position of the platform.
	vert_pos = screen_height( ) -1 -2;
	// (c) Draw a horizontal line 11 units long starting at the position 
	//     you have calculated, using '~' symbols.
	draw_string(hori_pos,vert_pos, "~~~~~~~~~~~");
	// Leave the following line intact.
	show_screen();
}


int main( void ) {
	setup_screen( );

	draw_platform( );

	draw_string( 0, screen_height( ) - 1, "Press any key to finish..." );
	wait_char( );
	cleanup_screen( );
	return 0;
}