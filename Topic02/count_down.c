#include <stdio.h>

void count_down( void ) {
	printf("Reverse order list of integers greater than 57, beginning at 316, stepping by -5.\n");
	int counter;
    counter = 316;
    while (counter>57)
    {
        printf("%i\n",counter);
        counter = counter -5;
    }
}
int main( void ) {
	count_down();
	return 0;
}