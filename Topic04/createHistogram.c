#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

int create_hist(double values[], int num_vals, int output[26]) {
	if (num_vals <= 0){
        for(int i = 0; i<=26; i = i + 1){
            output[i] = 0;
        }
        return *output;
    }
    for (int i = 0; i <= 26; i = i + 1){
       output[i] = 0;
    }
    if (num_vals< 26){
        for(int i = 0; i<num_vals; i = i + 1){
          int intval = values[i];
          output[intval] = output[intval]+1;
        }
        // for (int i = 26 - num_vals; i<= 26; i = i + 1){
        //     output[i] = 0;
        // }
        return *output;
    }
    else{
        for(int i = 0; i<num_vals; i = i + 1){
          int intval = values[i];
          output[intval] = output[intval]+1;
        }
        return *output;
    }
    return *output;
}

void call_function( const char * label, double x[], int count ) {
	int hist[26 + 1];
	create_hist( x, count, hist );
	printf( "%s\n", label );
	printf( "\tInput data:\n" );

	for ( int i = 0; i < count; i++ ) {
		printf( "\t%d\t%f\n", i, x[i] );
	}

	printf( "\tHistogram:\n" );

	for ( int i = 0; i <= 26; i++ ) {
		printf( "\t%d\t%d\n", i, hist[i] );
	}

	printf( "\n" );
}

int main( void ) {
	srand( time( NULL ) );

	double x1[] = { 0 };
	call_function( "Count == 0", x1, 0 );

	double x2[] = { 0, 0, 0 };
	call_function( "Three equal values", x2, 3 );

	double x3[26 + 1];
	for ( int i = 0; i <= 26; i++ ) {
		x3[i] = i;
	}
	call_function( "One value in each bucket", x3, 26 + 1 );

	double x4[26 * 2 + 1];
	for ( int i = 0; i <= 26 * 2; i++ ) {
		x4[i] = (26+1) * ( double ) rand() / RAND_MAX;
	}
	call_function( "Random values", x4, 26 * 2 + 1 );

	return 0;
}