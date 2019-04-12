#include <stdio.h>

//  (a) Begin the definition a function called total_array that returns the
//      sum of an array of integer values.
// 
//  Parameters:
//      arr - the address of an array of numeric values of type int.
//      arr_size - and int which specifies the number of items to be 
//      processed.
//
//  Returns:
//      The function must return a result of type long long int
//      (this is NOT a typo!) which is equal to the sum of the 
//      arr_size items referenced by array parameter arr.

long long int total_array(int arr[0], int arr_size){
    //  (b) Declare an accu of type long long int, with initial
    //  value 0.
    //  (c) Start a loop which will iterate over the arr_size items.
    //  to be processed.
    long long int accu =0;
    for(int i=0.0; i<arr_size; i = i +1.0)
    {
        //  (d) Add the current element of the array to the accu.
        accu = accu+ arr[i];
    }

    //  (e) Return the value of the accu.
    return accu;
}


#define MAX_ITEMS (100)

int main(void)
{
    int items[MAX_ITEMS];
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
        printf("Please enter item %d of %d: ", (i+1), array_size);
        scanf("%d", &items[i]);
    }

    long long int result = total_array(items, array_size);

    printf("The sum of the items you entered is %lld.\n", result);

    return 0;
}