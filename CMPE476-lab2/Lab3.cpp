/*
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <math.h>
#include "lab3.h"
void main() {
	srand(time(0));
	double P, s_sqr;
	int no_bits;
	printf("Enter Variance: ");
	scanf("%lf", &s_sqr);
	printf("Enter the no of bits to test: ");
	scanf("%d", &no_bits);
	// The varying parameter would be power for SNR
	FILE* file = fopen("output.dat", "w");
	double capacity = 0;
	int iter = 1;
	for (int i = -20; i <= 20; i++) {
		P = s_sqr * pow(10, i / 10.0);
		printf("Test no. %d\n\n", iter++);
		binary_channel_error_sim(P, s_sqr, no_bits, capacity);
		printf("\n\n\n");
		fprintf(file, "%d %lf\n",i,capacity);
	}
	fclose(file);
	system("pip install matplotlib");
	system("python plot.py");
}
*/