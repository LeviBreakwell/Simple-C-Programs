#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

// Configuration
#define DELAY (10) /* Millisecond delay between game updates */

#define ZOMBIE_WIDTH (5)
#define ZOMBIE_HEIGHT (5)

// Game state.
bool game_over = false; /* Set this to true when game is over */
bool update_screen = true; /* Set to false to prevent screen update. */

char * zombie_image =
/**/	"ZZZZZ"
/**/	"   Z "
/**/	"  Z  "
/**/	" Z   "
/**/	"ZZZZZ";

//	(a) Declare a sprite_id called zombie
sprite_id zombie;
// Setup game.
void setup(void) {
    //  (b) Assign a value to zombie by creating a sprite at integer 
    //      coordinates (x,y). Use integer arithmetic to calculate 
    //      the location relative to the screen dimensions:
    //      x = 30% of available horizontal space on the screen.
    //      y = 70% of available vertical space on the screen.
    //      Use the formula set out in the statement of the problem.
    zombie = sprite_create((screen_width()-5-1)*0.3, (screen_height()-5-1)*0.7,5,5,zombie_image);
    //	(c) Draw the zombie.
    sprite_draw(zombie);
}

// Play one turn of game.
void process(void) {
    //	(d) Get a character code from standard input without waiting.
    int keyCode = get_char();
    //  (e) Get the current screen coordinates of the zombie in integer variables 
    //      by rounding the actual coordinates. Store the coordinates in a pair of
    //      variables called x and y, both of type int.
    int x = round(sprite_x(zombie));
    int y = round(sprite_y(zombie));
    //	(f) Move zombie left, ensuring that it always remains within the screen.
    if (keyCode == '4'&& x >0){
        sprite_move(zombie,-1,0);
    }
    //	(g) Move zombie right, ensuring that it always remains within the screen.
    else if (keyCode == '6'&& x <= screen_width() - sprite_width(zombie)-1){
        sprite_move(zombie,+1,0);
    }
    //	(h) Move zombie up, ensuring that it always remains within the screen.
    else if (keyCode == '8'&& y >0){
        sprite_move(zombie,0,-1);
    }
    //	(i) Move zombie down according to specification.
    else if (keyCode == '2'&& y <screen_height() - sprite_height(zombie)-1){
        sprite_move(zombie,0,+1);
    }
    //	(j) If the key is 'q', set game_over to true.
    else if(keyCode == 'q'){
        game_over = true;
    
    }
    // Leave next line intact.
    clear_screen();

    //	(k)	Draw the zombie.
    sprite_draw(zombie);
}

// Program entry point.
int main(void) {
	setup_screen();
	setup();
	show_screen();

	while ( !game_over ) {
		process();

		if ( update_screen ) {
			show_screen();
		}

		timer_pause(DELAY);
	}

	return 0;
}