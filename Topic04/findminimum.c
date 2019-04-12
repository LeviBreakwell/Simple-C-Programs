#include <math.h>
#include <stdbool.h>
#include <stdio.h>

//  (a) Begin the definition of a function called minimum_loc
//  which locates the minimum value in an array and returns the 
//  smallest index of the minimum value in the array.
//  
//  Parameters:
//      values   - an array of double precision floating point values.
//      num_vals - an int which specifies the number of items to process.
//
//  Returns:
//      An int indicating the location at which the minimum may be found:
//      *   If num_vals is 0: return -1 to record the fact that there is
//          no data to process.
//      *   Otherwise: return i in 0 .. (num_vals-1) such that:
//          (For all j in 0..(num_vals-1), values[i] <= values[j]) AND 
//          (For any j where values[j] == values[i], j >= i)
//      i.e.
//          values[i] is the "smallest" value in the array, and i is 
//          the "smallest" index where that happens.

 int minimum_loc(double values[],int num_vals){
    if (num_vals <= 0){
        return -1;
    }
    int pos;
    //  (c) Declare variable store index position, initially 0 
    int min = values[0];
    for(int i = 1; i < num_vals; i = i + 1){
            if (values[i] < min){
                min = values[i];
                pos = i;
            }
        } 
    return pos;
}


#define MAX_ITEMS (100)

int main(void)
{
    double items[MAX_ITEMS];
    int array_size;

    // Get number of items.
    printf("Please enter number of items (up to %d) that will be processed: ", MAX_ITEMS);
    scanf("%d", &array_size);

    // if number of items exceeds array size, restrict it to that value.
    if (array_size > MAX_ITEMS)
    {
        array_size = MAX_ITEMS;
    }

    for (int i = 0; i < array_size; i++)
    {
        printf("Please enter (floating point) item %d of %d: ", (i + 1), array_size);
        scanf("%lf", &items[i]);
    }

    int result = minimum_loc(items, array_size);

    printf("The index of the minimum is %d.\n", result);

    return 0;
}