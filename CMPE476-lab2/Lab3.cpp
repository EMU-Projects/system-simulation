#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <math.h>
#include "lab3.h"
void main() {
	srand(time(0));
	double P, s_sqr;
	int no_bits;
	printf("Enter the signal power for 1's and 0's: ");
	scanf("%lf", &P);
	printf("Enter Variance: ");
	scanf("%lf", &s_sqr);
	printf("Enter the no of bits to test: ");
	scanf("%d", &no_bits);
	double* capacity = 0;
	binary_channel_error_sim(P, s_sqr, no_bits, capacity);
	//printf("Integration: %lf", phi_z(3));

}