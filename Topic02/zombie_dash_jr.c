#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

// ADD INCLUDES HERE

// Configuration
#define DELAY (10) /* Millisecond delay between game updates */

#define HERO_WIDTH (5)
#define HERO_HEIGHT (5)
#define ZOMBIE_WIDTH (5)
#define ZOMBIE_HEIGHT (5)

// Game state.
bool game_over = false; /* Set this to true when game is over */
bool update_screen = true; /* Set to false to prevent screen update. */

char * hero_image =
/**/	"H   H"
/**/	"H   H"
/**/	"HHHHH"
/**/	"H   H"
/**/	"H   H";

char * zombie_image =
/**/	"ZZZZZ"
/**/	"   Z "
/**/	"  Z  "
/**/	" Z   "
/**/	"ZZZZZ";

char * msg_image =	
/**/"Goodbye and thank-you for playing ZombieDash Jr."
/**/"            Press any key to exit...            ";

// (c) Declare a sprite_id called hero.
sprite_id hero;
// (m) Declare a sprite_id called zombie.
sprite_id zombie;
// Setup game.
void setup(void) {
	// (a) Draw the border (setup).
    draw_line(0,0,screen_width()-1,0,'*');
    draw_line(0,0,0,screen_height()-1,'*');
    draw_line(0,screen_height()-1,screen_width()-1,screen_height()-1,'*');
    draw_line(screen_width()-1,screen_height()-1,screen_width()-1,0,'*');

	// Keep the next line intact.
	show_screen();

	// (d) Set up the hero at the centre of the screen.
    hero = sprite_create((screen_width()-5) /2,(screen_height()-5) /2, 5, 5, hero_image);
	// (e) Draw the hero.
    sprite_draw(hero);
	// Keep the next line intact.
	show_screen();

	// (n)	Set up the zombie at a random location on the screen.
    srand( 2877286 );
    int zx = rand() % (screen_width()-5 -2)+1;
    int zy = rand() % (screen_height()-5 -2)+1;
    zombie = sprite_create(zx,zy,5,5,zombie_image);
	// (o) Draw the zombie.
    sprite_draw(zombie);
	// (p) Set the zombie in motion.
    sprite_turn_to( zombie, 0.1,0.0);
    int angle = rand() %360;
    sprite_turn(zombie, angle);
	// Keep the next line intact.
	show_screen();
}

// Play one turn of game.
void process(void) {
	// (f) Get a character code from standard input without waiting.
	int keyCode= get_char();
	// (y) Test for end of game.
    // if hx == zx && hy == zy {
    //     game_over = true;
    //     draw_string((screen_width()-48) /2, (screen_height()-2) /2, msg_image);
    //     timer_pause(3000);
    // }
    sprite_id text;
    if (keyCode == 'q') {
        
        clear_screen();
        text = sprite_create((screen_width()-48) /2, (screen_height()-2) /2,48,2, msg_image);
        sprite_draw(text);
        show_screen();
        wait_char();
        game_over = true;
    }
	// (g)	Get the current screen coordinates of the hero in integer variables 
	//		by rounding the actual coordinates.
    int hx = round(sprite_x(hero));
    int hy = round(sprite_y(hero));
	// (h) Move hero left according to specification.
    if (keyCode =='a' && hx>1){
        sprite_move(hero,-1,0);
    }
	// (i) Move hero right according to specification.
    if (keyCode =='d' && hx < (screen_width()-1-sprite_width(hero))){
        sprite_move(hero,+1,0);
    }
	// (j) Move hero up according to specification.
    if (keyCode =='w' && hy > 1){
        sprite_move(hero,0,-1);
    }
	// (k) Move hero down according to specification.
    if (keyCode =='s' && hy < (screen_height()-1-sprite_height(hero))){
        sprite_move(hero,0,+1);
    }
	// (q.a) Test to move the zombie if key is 'z' or negative.
    if (keyCode == 'z' || keyCode <0 ) {
		// (r) Zombie takes one step.
    sprite_step(zombie);
		// (s) Get screen location of zombie.
    int zx = round(sprite_x(zombie));
    int zy = round(sprite_y(zombie));
		// (t) Get the displacement vector of the zombie.
    double zdx = sprite_dx(zombie);
    double zdy = sprite_dy(zombie);

		// (u) Test to see if the zombie hit the left or right border.
    if (zx == 0 || zx == screen_width()-sprite_width(zombie)){
        zdx = -zdx;
    }
		// (v) Test to see if the zombie hit the top or bottom border.
    if (zy == 0 || zy == screen_height()-sprite_height(zombie)){
        zdy = -zdy;
    }
		// (w) Test to see if the zombie needs to step back and change direction.
    if (zdy != sprite_dy(zombie) || zdx != sprite_dx(zombie)) {
        sprite_back(zombie);
        sprite_turn_to(zombie,zdx,zdy);
    }
	// (q.b) End else-if test to move the zombie if key is 'z' or negative.
    }
	// Leave next line intact
	clear_screen();

	// (b) Draw the border (process).
    draw_line(0,0,screen_width()-1,0,'*');
    draw_line(0,0,0,screen_height()-1,'*');
    draw_line(0,screen_height()-1,screen_width()-1,screen_height()-1,'*');
    draw_line(screen_width()-1,screen_height()-1,screen_width()-1,0,'*');
	// (l)	Draw the hero.
    sprite_draw(hero);
	// (x)	Draw the zombie.
    sprite_draw(zombie);
}

// Clean up game
void cleanup(void) {
	// STATEMENTS
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

	cleanup();

	return 0;
}