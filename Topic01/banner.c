#include <stdlib.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>
#include <string.h>

// Configuration 
#define DELAY (10) /* Millisecond delay between game updates */

// Game state.
bool game_over = false; /* Set this to true when game is over */
bool update_screen = true; /* Set to false to prevent screen update. */
sprite_id banner;

// Setup game.
void setup( void ) {
	// ASCII art source: http://www.chris.com/ascii/index.php?art=transportation/airplanes
	static char bitmap[] =
		"\\                             \\           _         ______ |     "
		" \\                             \\        /   \\___-=O`/|O`/__|     "
		"  \\      Welcome to CAB202      \\_______\\          / | /    )    "
		"  /                             /        `/-==__ _/__|/__=-|  -GM"
		" /                             /         *             \\ | |     "
		"/                             /                        (o)       ";
	int width = strlen( bitmap ) / 6;
	int height = 6;
	banner = sprite_create( -width, ( screen_height() - height ) / 2, width, height, bitmap );
	sprite_turn_to( banner, 0.1, 0 );
}

// Play one turn of game.
void process( void ) {
	sprite_step( banner );
	clear_screen();
	sprite_draw( banner );
}

// Clean up game
void cleanup( void ) {
	// STATEMENTS
}

// Program entry point.
int main( void ) {
	setup_screen();
	setup();
	show_screen();

	while ( !game_over ) {
		process();

		if ( update_screen ) {
			show_screen();
		}

		timer_pause( DELAY );
	}

	return 0;
}
