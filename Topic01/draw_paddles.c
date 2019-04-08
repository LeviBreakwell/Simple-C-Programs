#include "cab202_graphics.h"
void draw_paddles( void ) {
	// left paddle
	double leftypos;
	double rightypos;
	double rightxpos;
	double h;
	double w;
	double l;
	l = 7;
	w = screen_width();
	h = screen_height();
	
	leftypos = ((h - l)/2) - 3;
	draw_line(3, leftypos, 3, leftypos+l,'~');
	
	rightypos = ((h-l)/2) + 2;
	rightxpos = w -3;
	draw_line(rightxpos,rightypos, rightxpos, rightypos + l, '~');
	show_screen( );
}
int main( void ) {
	setup_screen();
	draw_paddles();
	draw_string( 0, screen_height( ) - 1, "Press any key to finish..." );
	wait_char();
	cleanup_screen();
	return 0;
}