#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>


//  (Task 1) Define a function called pixel_level_collision which detects whether
//  two sprites s1 and s2 collide at pixel level. The function must be able 
//  to work correctly even if the ZDK screen has not been set up, and should 
//  make no attempt to use any function or variable declared in 
//  <cab202_graphics.h>, either directly or indirectly.
//
//  Parameters:
//      s1 - the address of a Sprite which has been initialised and placed at 
//      arbitrary position on the screen.
//
//      s2 - the address of a Sprite which has been initialised and placed at 
//      arbitrary position on the screen.
//
//  Returns:
//      A boolean value which is true if and only if there exists a point (x,y)
//      which is opaque in both s1 and s2.
// 
//      Definition: (x,y) is opaque in sprite s if and only if:
//      0 <= (sx = x - round(s->x)) < s->width, and
//      0 <= (sy = y - round(s->y)) < s->height, and
//      offset(s,x,y) = sy * s->width + sx, and
//      s->bitmap[offset(s,x,y)] != ' '.


bool pixel_level_collision ( s_cross->s1, s_plus->s2 )
{
int ctr = 0;
for (sprite_y(s_cross) = 0; sprite_y(s_cross) < sprite_height(s_cross); sprite_y(s_cross)++)
{
        for (sprite_x(s_cross) = 0; sprite_x(s_cross) < sprite_width(s_cross); sprite_x(s_cross)++)
        {
            int offset = sprite_y(s_cross)*s_cross -> sprite_width(s_cross) + sprite_x(s_cross);
            if (s_cross-> bitmap[offset] != ' ')
            {
                    s_cross[ctr].x = round (x + sprite -> x);        
                    s_cross[ctr].y = round (y + sprite -> y);
            }
            ctr++;
            }
        }
    }

    int top1 = round(sprite_y(s1));
    int bottom1 = top1 + sprite_height(s1) - 1;
    int left1 = round(sprite_x(s1));
    int right1 = left1 + sprite_width(s1) - 1;

    int left2 = round(sprite_x(s2));
    int center = left2 + sprite_width(s2) - 3;

    if (center > right1 && center < top1){
        return false;
    }
    else if (center< top1 && center < left1){
        return false;
    }
    else if (center> bottom1 && center > right1){
        return false;
    }
    else if (center> bottom1 && center < left1){
        return false;
    }
    else {
        return true;
    }
}


char * cross = "y   y"
/**/           " y y "
/**/           "  y  "
/**/           " y y "
/**/           "y   y"
;
char * plus = "  z  "
/**/          "  z  "
/**/          "zzzzz"
/**/          "  z  "
/**/          "  z  "
;

int main( void )
{
    setup_screen();
    sprite_id s_cross = sprite_create( 20.9, 8.3, 5, 5, cross );
    sprite_id s_plus = sprite_create( 30.9, 17.9, 5, 5, plus );

    while ( true )
    {
        clear_screen();
        sprite_draw( s_cross );
        sprite_draw( s_plus );
        if ( pixel_level_collision( s_cross, s_plus ) )
        {
            draw_string(0, 0, "Pixel-level collision has been detected!");
        }
        show_screen();

        int key = wait_char();

        if ( key == '2' )
        {
            s_plus->y++;
        }
        else if ( key == '8' )
        {
            s_plus->y--;
        }
        else if ( key == '4' )
        {
            s_plus->x--;
        }
        else if ( key == '6' )
        {
            s_plus->x++;
        }
        else if ( key == 'q' ) {
            break;
        }
    }

    cleanup_screen();

    return 0;
}
