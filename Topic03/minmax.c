#include <stdio.h>

//  (a) Begin the definition a function called Max which returns
//      the maximum of its two double precision floating point arguments.

//      For all pairs of double precision floating point values x and y, the 
//      function must satisfy the following conditions:
//          ((Max(x,y) = x) OR (Max(x,y) = y))
//      AND (Max(x,y) >= x)
//      AND (Max(x,y) >= y)

double Max(double x, double y)
{
    //  (b) If the value of the first argument is greater than or equal to that of the
    //      second argument: return the value of the first argument.
if (x>=y){
    return x;
}
else {
    return y;
}
    //  (c) Otherwise: return the value of the second argument.

}

int main(void) {
    double x, y, maxVal;

    printf("Please enter two numeric values: ");
    scanf("%lf%lf", &x, &y);
    maxVal = Max(x, y);
    printf( "Max(%0.10f, %0.10f) = %0.10f\n", x, y, maxVal);

    return 0;
}