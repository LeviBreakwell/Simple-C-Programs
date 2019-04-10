#include <stdio.h>

void list_integers( void ) {
    printf("Counting from 25 up to 332...\n");
    int counter;
    counter = 25;
	// (c) Begin a WHILE statement that will execute its loop body if the
	//     counter is less than or equal to the end value.
    while (counter<=332) 
		{
    		printf("%i\n",counter);
        	counter = counter +1;
		}
}
int main( void ) {
	list_integers();
	return 0;
}