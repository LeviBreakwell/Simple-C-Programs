#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>


//  (Task 1) Define a struct called coordinates_t which represents a two-dimensional
//  position on the terminal window with fields x and y, both of which are type int.

typedef struct coordinates_t{
    int x;
    int y;
}coordinates_t;

//  (Task 2) Define a function called get_opaque_coords which populates an
//  array with a list of screen positions at which a Sprite image will be opaque
//  when displayed by sprite_draw. The space char (' ') is transparent; all others
//  will be inserted into the display and are therefore opaque.
//
//  Parameters:
//      sprite - the address of a Sprite struct which has been initialised 
//      and placed at arbitrary position on the screen.
//
//      coords - an array of coordinates_t in which the list of occupied screen 
//      positions will be returned. A screen position is considered to be 
//      occupied if it is not the space character ' '.
//
//      max_coords - the maximum number of points to add to the list. Do not 
//      add more than this many points to the list, even if the sprite bitmap 
//      has more than max_coords non-space characters.
//
//  Returns:
//      The number of points that have been added to the list. This value will 
//      be greater than or equal to 0, and less than or equal to max_coords.

int get_opaque_coords (Sprite * sprite, coordinates_t * coords, int max_coords)
{
    //  (Task 2.1) Declare an int called ctr, initially 0. This will keep 
    //  track of the number of items that have been added to the list and 
    //  therefore the location of the next unused coordinates_t in the array.
    int ctr = 0;
    //  (Task 2.2) Use a for loop to iterate vertically down the sprite.
    //  Let the counter be y; start from 0 and continue while y is less than 
    //  the height of the sprite.
    for (int y = 0; y < sprite_height(sprite); y++)
    {
        //  (Task 2.3)  Use a for loop to iterate horizontally across the sprite.
        //  Let the counter be x; start from 0 and continue while x is less than 
        //  the width of the sprite.
        for (int x = 0; x < sprite_width(sprite); x++)
        {
            //  (Task 2.3.1) The nested for loop is visiting every screen pixel 
            //  within the bounds of the sprite. The offset of the corresponding 
            //  character in the bitmap is equal to y * sprite->width + x. Get 
            //  this value in a variable.
            int offset = y*sprite -> width + x;
            //  (Task 2.3.2) If the character in the bitmap with the current offset
            //  is not a space (' '):
            if (sprite-> bitmap[offset] != ' ')
            {
                //  (Task 2.3.3) Assign the horizontal screen location of the current 
                //  "pixel" into the x field of the coordinates_t at index position ctr in 
                //  the array. Hint: round(x + sprite->x).
                    coords[ctr].x = round (x + sprite -> x);        
                //  (Task 2.3.4) Assign the vertical screen location of the current 
                //  "pixel" into the x field of the coordinates_t at index position ctr in 
                //  the array. Hint: round(y + sprite->y).
                    coords[ctr].y = round (y + sprite -> y);

                //  (Task 2.3.5) Increment ctr.
                ctr++;
            }
        }
    }

    //  (Task 2.4) Return ctr.
    return ctr;
}


char * box = "xxxxxxx"
/**/         "x     x"
/**/         "xxxxxxx"
;
char * cross = "y   y"
/**/           " y y "
/**/           "  y  "
/**/           " y y "
/**/           "y   y"
;
char * zed = "zzzzz"
/**/         "   z "
/**/         "  z  "
/**/         " z   "
/**/         "zzzzz"
;

void print_points(char * label, coordinates_t points[], int num_points)
{
    printf("Occupied screen points in %s:\n", label);

    for (int i = 0; i < num_points; i++)
    {
        printf("\t%d\t%d\n", points[i].x, points[i].y);
    }

    printf("\n");
}

#define MAX_ITEMS (100)

int main(void)
{
    setup_screen();
    sprite_id s_box = sprite_create(10.4, 11.6, 7, 3, box);
    sprite_id s_cross = sprite_create(20.9, 21.3, 5, 5, cross);
    sprite_id s_zed = sprite_create(30.9, 31.9, 5, 5, zed);

    sprite_draw(s_box);
    sprite_draw(s_cross);
    sprite_draw(s_zed);
    show_screen();

    wait_char();
    cleanup_screen();

    assert(strlen(box) < MAX_ITEMS);
    assert(strlen(cross) < MAX_ITEMS);
    assert(strlen(zed) < MAX_ITEMS);

    coordinates_t occupied_points[MAX_ITEMS];
    int num_points;

    num_points = get_opaque_coords(s_box, occupied_points, MAX_ITEMS);
    print_points("box", occupied_points, num_points);

    num_points = get_opaque_coords(s_cross, occupied_points, MAX_ITEMS);
    print_points("cross", occupied_points, num_points);

    num_points = get_opaque_coords(s_zed, occupied_points, MAX_ITEMS);
    print_points("zed", occupied_points, num_points);

    return 0;
}