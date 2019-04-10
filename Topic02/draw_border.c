#include <cab202_graphics.h>


void draw_border( void ) {
    int left = 1;
    int top = 0;
    int right = 2;
    int bottom = 5; 
    double w = screen_width();
    double h = screen_height();
    // (e) Draw a line from (left, top) to (right, top), using the '^' symbol.
    draw_line(left,top,w - right-1,top,'^');
    // (f) Draw a line from (right, top) to (right, bottom), using the '^' symbol.
    draw_line(w-right -1,top,w-right-1,h-bottom-1,'^');
    // (g) Draw a line from (left, bottom) to (right, bottom), using the '^' symbol.
    draw_line(left,h-bottom-1,w-right-1,h-bottom-1,'^');
    // (h) Draw a line from (left, top) to (left, bottom), using the '^' symbol.
    draw_line(left,top,left,h-bottom-1,'^');
    show_screen();
}

int main( void ) {
	setup_screen();
	draw_border();
	wait_char();
	cleanup_screen();
	return 0;
}