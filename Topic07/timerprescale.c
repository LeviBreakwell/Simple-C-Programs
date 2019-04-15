// Replace 0 with the correct value for each unknown cell.
double pre_scale_factor_001 = 1;
double pre_scale_factor_010 = 8;
double pre_scale_factor_011 = 64;
double pre_scale_factor_100 = 256;
double pre_scale_factor_101 = 1024;
double count_frequency_001 = 8000000;
double count_frequency_010 = 1000000;
double count_frequency_011 = 125000;
double count_frequency_100 = 31250;
double count_frequency_101 = 7812.5;
double overflow_period_001 = 256*0.000032;
double overflow_period_010 = 256*0.000256;
double overflow_period_011 = 256*0.002048;
double overflow_period_100 = 256*0.008192;
double overflow_period_101 = 256*0.032768;
double overflow_frequency_001 = 1/(256*0.000032);
double overflow_frequency_010 = 1/(256*0.000256);
double overflow_frequency_011 = 1/(256*0.002048);
double overflow_frequency_100 = 1/(256*0.008192);
double overflow_frequency_101 = 1/(256*0.032768);

// There is no test driver for this program.

int main() {
	for ( ;; ) {
	}

	return 0;
}
