#include <stdio.h>
#include <math.h>

void f_2_c(void) {
	printf("What is the temperature in Fahrenheit degrees? ");
	double F;
	scanf("%lf", &F);
	double C;
	C = (F-32)*5/9;
	printf("A temperature of %0.5f degrees Fahrenheit is equal to %0.5f degrees Celsius.\n", F, C);
}
int main(void) {
	f_2_c();
	return 0;
}
