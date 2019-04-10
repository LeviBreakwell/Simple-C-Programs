#include <stdlib.h>
#include <math.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

#define DELAY 10 /* milliseconds */

bool game_over = false;
bool update_screen = true;

//  (a) Declare a global sprite_id called bomb;
sprite_id bomb;
char * bomb_image = "O";
sprite_id star;
char * star_image = "*";

void setup(void) {
    //  (b) Initialise the bomb to display a 1x1 image consisting of a string
    //      containing a single 'O' character. The sprite should appear at 
    //      initial location (14,6).
bomb = sprite_create(14,6,1,1,bomb_image);
    //  (c) Declare a double precision floating point variable called dx
    //      and set it equal to the difference between the x-coordinate of the 
    //      star and that of the bomb.
double dx = 61 - 14;
    //  (d) Declare a double precision floating point variable called dy
    //      and set it equal to the difference between the y-coordinate of the 
    //      star and that of the bomb.
double dy = 5 - 6;
    //  (e) Declare a double precision floating point value called dist
    //      and set it equal to the distance between the bomb and the star.
    //      The distance can be calculated using dx and dy, and applying the 
    //      Theorem of Pythagoras.
    //      Hint: the right-hand side of the assignment statement should look
    //      like this: sqrt( dx * dx + dy * dy );
double dist = sqrt(dx*dx + dy*dy);
    //  (f) Multiply dx by the desired speed, then divide it by the distance.
dx = (dx*0.15) / dist;
    //  (g) Do the same to dy. 
dy = (dy*0.15) / dist;
    //  (h) Turn the bomb to move towards the star. This involves dx and dy. 
sprite_turn_to(bomb, dx,dy);
    //  (i) Draw the bomb.
sprite_draw(bomb);
    //  (j) Draw the star at its designated location, (61,5).
    star = sprite_create(61,5,1,1,star_image);
    sprite_draw(star);
}

// Play one turn of game.
void process(void) {
    // Keep the next line intact.
    clear_screen();
    //  (k) Move the bomb forward one step.
    sprite_step(bomb);
    //  (l) Draw the bomb.
    sprite_draw(bomb);
    //  (m) Draw the star at its designated location, (61,5).
    sprite_draw(star);
    //  (n) Get the position of the bomb on the screen, and compare it to the 
    //      location of the star. If they are both the same, set game_over true.
    if (round(sprite_x(bomb)) == round(sprite_x(star)) && round(sprite_y(bomb)) == round(sprite_y(star))) {
        game_over = true;
    
    }
}

// Clean up game
void cleanup(void) {
    // STATEMENTS
}

// Program entry point.
int main(void) {
    setup_screen();

#if defined(AUTO_SAVE_SCREEN)
    auto_save_screen(true);
#endif

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
