#include <stdio.h>

//  (a) Begin the definition a function called min that returns the
//      minimum of its three double precision floating point 
//      arguments.
// 
//      For all triples of double precision floating point values (x, y, z) the 
//      function must satisfy the following conditions:
//          ((min(x,y,z) = x) OR (min(x,y,z) = y OR (min(x,y,z) = z))
//      AND (min(x,y,z) <= x)
//      AND (min(x,y,z) <= y)
//      AND (min(x,y,z) <= z)

double min( double x, double y, double z)
{
    //  (b) Implement the logic required to calculate the minimum
    //      of the three input values, and return the result.
if (x<=y && x<= z){
    return x;
}
if (y<=x && y<= z){
    return y;
}
else {
    return z;
}
}

int main(void) {
    double x, y, z, minVal;

    printf("Please enter three numeric values: ");
    scanf("%lf%lf%lf", &x, &y, &z);
    minVal = min(x, y, z);
    printf("min(%0.10f, %0.10f, %0.10f) = %0.10f\n", x, y, z, minVal);

    return 0;
}
