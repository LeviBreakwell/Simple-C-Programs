#include <stdio.h>

void c2f(void) {
	printf("What is the temperature in degrees Celsius? ");
	double C;
	double F;
	scanf("%lf", &C);
	F = (C*9/5)+32;
	printf("Celsius temperature %0.5f is the same as %0.5f measured in Fahrenheit.\n", C, F);
	
}


int main(void) {
	c2f();
	return 0;
}
