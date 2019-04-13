#include <stdio.h>
#include <stdbool.h>

//  (Task 1) Complete the declaration of a new struct type called xy_t. 
//  This structure could be used to record a position in a two-dimensional
//  discrete coordinate system.
// 
//  Members:
//      x - an int which records the horizontal position of the 
//                     point.
//      y - an int which records the vertical position of the 
//                     point.

typedef struct xy_t
{
    //  (Task 1.1) Declare a field called x of type int.
    int x;
    //  (Task 1.2) Declare a field called y of type int.
    int y;
} xy_t;

//  (Task 2) Define a function called xy_read which uses printf and 
//  scanf to get the user to enter a xy_t coordinate pair. 
// 
//  Parameters:
//      xy - the address of a xy_t which must be populated by the 
//      function call.
//
//  Returns:
//      The function must return a boolean value indicating the status of the 
//      I/O operation. The status is true if and only if two integer values 
//      have been successfully parsed and saved in xy.
bool xy_read(int xy[1])
{
    //  (Task 2.1) Declare an integer called items_read with initial value 0.
    int items_read = 0;
    //  (Task 2.2) Display prompt "Please enter x: ".
    printf("Please enter x: ");
    
    //  (Task 2.3) Use scanf to try to read an integer value using scanf into
    //  the xy->x field of the struct pointed at by xy. Add 
    //  the value returned by scanf to items_read.
    xy[0] = scanf;
    items_read = items_read + 1;
    //  (Task 2.4) Display prompt "Please enter y: ".
    printf("Please enter y: ");
    //  (Task 2.5) Use scanf to try to read an integer value into the y 
    //  field of the struct pointed at by xy.
    //  Add the value returned by scanf to items_read.
    xy[1] = scanf;
    items_read = items_read + 1;
    //  (Task 2.6) Return true if and only if items_read is equal to 2.
    if (items_read==2){
        return true;
    }
    else{
        return false;
    }
}

//  (Task 3) Define a function called xy_write which uses printf to 
//  display the value of a xy_t structure. 
// 
//  Parameters:
//      xy - a xy_t structure that will be displayed.
//
//  Returns:
//      Nothing.

void xy_write ( xy_t xy )
{
    //  (Task 3.1) Print the horizontal and vertical position of SCREEN-POS_VAR
    //  with format string "{%d, %d}". Do NOT insert a linefeed.
    printf("{%d, %d}",xy_t.x,xy_t.y);
}

//  (Task 4) Define a function called xy_dist which calculates
//  the city block distance between two xy_t objects.
//  Ref: https://en.wikipedia.org/wiki/Taxicab_geometry
// 
//  Parameters:
//      xy_1 - a xy_t structure.
//      xy_2 - a xy_t structure.
//
//  Returns:
//      An int which is equal to the city block distance between the points
//      represented by the arguments.

int xy_dist ( xy_t xy_1, xy_t xy_2 )
{
    //  (Task 4.1) Compute and return the city block distance between the points 
    //  represented by xy_1 and xy_2.
    double dist = sqrt ((xy_2 * xy_2) + (xy_1 * xy_1));
    return dist;
}

//  (Task 5) Define a function called xy_nearest which finds the
//  xy_t object in a list which is closest to a query point, using
//  city block distance.
// 
//  Parameters:
//      query_xy - a xy_t structure.
//      points - an array of xy_t structures.
//      num_points - an int which tells the function how many elements there 
//      are in the array.
//
//  Returns:
//      A pointer to a xy_t object. If num_points is equal to or less 
//      than 0 this value will be NULL. Otherwise, it will be the address
//      of the xy_t object in the array that is nearest to the query 
//      point. If multiple candidates share the minimum distance to the query 
//      point, return the address of the first object in the list for which 
//      this is so.

int xy_nearest ( xy_t.query_xy, xy_t.points[], int num_points)
{
    //  (Task 5.1) If num_points equal to or less than 0, return NULL.
    if (num_points<= 0){
        return NULL;
    }
    //  (Task 5.2) Declare and initialise a pointer to xy_t called nearest.
    //  The initial value is the address of the first element in the array.
    nearest *xy_t = xy_t[0];
    //  (Task 5.3) Declare and initialise an integer called min_dist.
    //  The initial value is the city block distance from the query to
    //  the first element of the array.
    //  Hint: use xy_dist.
    int min_dist = xy_dist(query_xy,xy_t[0])
    //  (Task 5.4) Set up a for loop to iterate over the array.
    //  Skip the first element of the array, because we already know
    //  the distance from the first element to the query.
    FOR ( int i = 0; i < num_points; i ++)
    {
        //  (Task 5.4.1) Compute the city block distance from the query
        //  to the current element of the array. This is the current
        //  distance. Make sure you remember it somehow.

        //  (Task 5.4.2) If the current distance is less than min_dist:
        IF ( SOMETHING )
        {
            //  (Task 5.4.3) Overwrite min_dist with the current distance.
            //  Overwrite nearest with the address of the current element of
            //  the array.
        }
    }

    //  (Task 5.5) Return nearest.
}


#define MAX_ITEMS (100)

int main(void)
{
    xy_t query;
    printf("Input query point:\n");
    xy_read(&query);

    xy_t ref_points[MAX_ITEMS] = { {0,0} };
    int num_items;

    // Get number of ref_points.
    printf("Please enter number of items (up to %d) that will be processed: ", MAX_ITEMS);
    scanf("%d", &num_items);

    // if number of ref_points exceeds array size, restrict it to that value.
    if (num_items > MAX_ITEMS)
    {
        num_items = MAX_ITEMS;
    }

    for (int i = 0; i < num_items; i++)
    {
        printf("Please enter item %d of %d:\n", (i + 1), num_items);
        xy_read(&ref_points[i]);
    }

    for (int i = 0; i < num_items; i++)
    {
        printf("Distance from ");
        xy_write(ref_points[i]);
        printf(" to ");
        xy_write(query);
        printf(" is %d\n", xy_dist(ref_points[i], query));
    }

    xy_t * nearest = xy_nearest(query, ref_points, num_items);

    if (nearest)
    {
        printf("The closest point is ");
        xy_write(*nearest);
        printf(", at a distance of %d.\n", xy_dist(query, *nearest));
    }
    else
    {
        printf("Collection is empty.\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//  (Task 1) Complete the declaration of a new struct type called coords_t.
//  This structure could be used to record a position in a two-dimensional
//  discrete coordinate system.
//
//  Members:
//      coord_x - an int which records the horizontal position of the
//                     point.
//      coord_y - an int which records the vertical position of the
//                     point.

typedef struct coords_t
{
    //  (Task 1.1) Declare a field called coord_x of type int.
    int coord_x;

    //  (Task 1.2) Declare a field called coord_y of type int.
    int coord_y;
} coords_t;
//  (Task 2) Define a function called coords_read which uses printf and
//  scanf to get the user to enter a coords_t coordinate pair.
//
//  Parameters:
//      coord - the address of a coords_t which must be populated by the
//      function call.
//
//  Returns:
//      The function must return a boolean value indicating the status of the
//      I/O operation. The status is true if and only if two integer values
//      have been successfully parsed and saved in coord.

bool coords_read(coords_t * coord)
{
    //  (Task 2.1) Declare an integer called items_read with initial value 0.
    int items_read = 0;
    //  (Task 2.2) Display prompt "Please enter coord_x: ".
    printf("Please enter coord_x: ");
    //  (Task 2.3) Use scanf to try to read an integer value using scanf into
    //  the coord->coord_x field of the struct pointed at by coord. Add
    //  the value returned by scanf to items_read.
    items_read =+ scanf("%d", &coord->coord_x);
    //  (Task 2.4) Display prompt "Please enter coord_y: ".
    printf("Please enter coord_y: ");
    //  (Task 2.5) Use scanf to try to read an integer value into the coord_y
    //  field of the struct pointed at by coord.
    //  Add the value returned by scanf to items_read.
    items_read += scanf("%d", &coord->coord_y);
    
    //  (Task 2.6) Return true if and only if items_read is equal to 2.
    if (items_read == 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//  (Task 3) Define a function called coords_write which uses printf to
//  display the value of a coords_t structure.
//
//  Parameters:
//      coord - a coords_t structure that will be displayed.
//
//  Returns:
//      Nothing.

void coords_write(coords_t coord)
{
    //  (Task 3.1) Print the horizontal and vertical position of SCREEN-POS_VAR
    //  with format string "{%d, %d}". Do NOT insert a linefeed.
    printf("{%d, %d}", coord.coord_x, coord.coord_y);
}

//  (Task 4) Define a function called coords_dist which calculates
//  the city block distance between two coords_t objects.
//  Ref: https://en.wikipedia.org/wiki/Taxicab_geometry
//
//  Parameters:
//      coord_1 - a coords_t structure.
//      coord_2 - a coords_t structure.
//
//  Returns:
//      An int which is equal to the city block distance between the points
//      represented by the arguments.

int coords_dist(coords_t coord_1, coords_t coord_2)
{
    //  (Task 4.1) Compute and return the city block distance between the points
    //  represented by coord_1 and coord_2.
    int dist = fabs(coord_1.coord_x - coord_2.coord_x) + fabs(coord_1.coord_y - coord_2.coord_y);

    return dist;
}

//  (Task 5) Define a function called coords_nearest which finds the
//  coords_t object in a list which is closest to a query point, using
//  city block distance.
//
//  Parameters:
//      query_coords - a coords_t structure.
//      coords - an array of coords_t structures.
//      num_coords - an int which tells the function how many elements there
//      are in the array.
//
//  Returns:
//      A pointer to a coords_t object. If num_coords is equal to or less
//      than 0 this value will be NULL. Otherwise, it will be the address
//      of the coords_t object in the array that is nearest to the query
//      point. If multiple candidates share the minimum distance to the query
//      point, return the address of the first object in the list for which
//      this is so.

coords_t* coords_nearest(coords_t query_coords, coords_t coords[], int num_coords)
{
    //  (Task 5.1) If num_coords equal to or less than 0, return NULL.
    if (num_coords <= 0)
    {
        return NULL;
    }
    //  (Task 5.2) Declare and initialise a pointer to coords_t called nearest.
    //  The initial value is the address of the first element in the array.
    coords_t * nearest = &coords[0];
    //  (Task 5.3) Declare and initialise an integer called min_dist.
    //  The initial value is the city block distance from the query to
    //  the first element of the array.
    //  Hint: use coords_dist.
    int min_dist = coords_dist(query_coords, coords[0]);
    //  (Task 5.4) Set up a for loop to iterate over the array.
    //  Skip the first element of the array, because we already know
    //  the distance from the first element to the query.
    for (int i = 0; i< num_coords; i++)
    {
        //  (Task 5.4.1) Compute the city block distance from the query
        //  to the current element of the array. This is the current
        //  distance. Make sure you remember it somehow.
        int compare = coords_dist(query_coords, coords[1+i]);
        //  (Task 5.4.2) If the current distance is less than min_dist:
        if (compare < min_dist)
        {
            //  (Task 5.4.3) Overwrite min_dist with the current distance.
            //  Overwrite nearest with the address of the current element of
            //  the array.
            min_dist = compare;
            nearest = &coords[1+i];
        }
    }

    //  (Task 5.5) Return nearest.
    return nearest;
}

#define MAX_ITEMS (100)

int main(void)
{
    coords_t query;
    printf("Input query point:\n");
    coords_read(&query);

    coords_t ref_points[MAX_ITEMS] = {{0, 0}};
    int num_items;

    // Get number of ref_points.
    printf("Please enter number of items (up to %d) that will be processed: ", MAX_ITEMS);
    scanf("%d", &num_items);

    // if number of ref_points exceeds array size, restrict it to that value.
    if (num_items > MAX_ITEMS)
    {
        num_items = MAX_ITEMS;
    }

    for (int i = 0; i < num_items; i++)
    {
        printf("Please enter item %d of %d:\n", (i + 1), num_items);
        coords_read(&ref_points[i]);
    }

    for (int i = 0; i < num_items; i++)
    {
        printf("Distance from ");
        coords_write(ref_points[i]);
        printf(" to ");
        coords_write(query);
        printf(" is %d\n", coords_dist(ref_points[i], query));
    }

    coords_t *nearest = coords_nearest(query, ref_points, num_items);

    if (nearest)
    {
        printf("The closest point is ");
        coords_write(*nearest);
        printf(", at a distance of %d.\n", coords_dist(query, *nearest));
    }
    else
    {
        printf("Collection is empty.\n");
    }

    return 0;
}