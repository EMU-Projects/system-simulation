#include "lab1.h"
#include <stdlib.h>
#define PI 3.14159265358979
double uniform(double a, double b);
int geometric(double p) {
	double q = 1 - p;
	double u{ uniform(0,1) };
	return int(log(u) / log(q)) + 1;
}
int binomial(int n, double p) {
	double u{ uniform(0,1) };
	double c = p / (1 - p);
	int i = 0;
	double Pi = pow(1 - p, n);
	double F = Pi;
	while (true) {
		if (u < F)
			break;
		Pi = (c * (n - i) / (i + 1)) * Pi;
		F += Pi;
		i++;
	}
	return i;
}
int poisson(double lambda) {
	double u{ uniform(0,1) };
	double p{ exp(-lambda) };
	double F{ p };

	int i = 0;
	while (true) {
		if (u < F)
			break;
		p = (lambda * p) / (i + 1);
		F += p;
		i++;
	}
	return i;
}

// Generate a random number between two numbers
double uniform(double a, double b) {
	return (double(rand()) / RAND_MAX) * (b - a) + a;
}

/*
* Generate a random number using Exponential distribution
*
*/
double exponential(double lambda) {
	double u{ uniform(0,1) };
	return -log(u) / lambda;
}

/*
* Generate a random number using Normal distribution
*
*/
double normal(double mean, double std) {
	double u1{ uniform(0, 1) }, u2{ uniform(0, 1) };
	double r_sqr = -2 * log(u1);
	double r = sqrt(r_sqr);
	double theta = 2 * PI * u2;
	double x = r * cosf(theta);
	double y = r * sinf(theta);

	// random number = stdev * X + mean
	return std * x + mean;
}