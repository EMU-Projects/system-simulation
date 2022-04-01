#include <math.h>
#include <iostream>
#include <stdio.h>

double mean(double data[], int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += data[i];
	}
	return sum / n;
}

// Assume data array is sorted
double median(double data[], int n) {
	if (n % 2 == 0) {
		return (data[n / 2] + data[n / 2 - 1]) / 2;
	}
	return data[n / 2];
}

double stdev(double data[], int n, double mean) {
	double inner_sum = 0;
	for (int i = 0; i < n; i++) {
		inner_sum += powf(data[i] - mean, 2);
	}
	return sqrt(inner_sum / n);
}

void histogram(double data[], int n, int bins[], double min, double max, double m) {
	double width = (max - min) / m;
	for (int i = 0; i < n; i++) {
		double d = data[i];
		if (d < min || d > max) {
			continue;
		}
		int partition = (int)((d - min) / width);
		bins[partition]++;
	}
	printf("Frequency:\t");
	for (int i = 0; i < m; i++) {
		printf("\t%d\t", bins[i]);
	}
	printf("\nRanges:\t\t");
	for (int i = 0; i < m; i++) {
		printf("%.1f\t\t", min + width * i);
	}
	printf("%.1f", max);
}

double corr(double data1[], double data2[], int n) {
	double data1_sum = 0, data2_sum = 0, prod_sum = 0, data1_sqr_sum = 0, data2_sqr_sum = 0;
	for (int i = 0; i < n; i++) {
		data1_sum += data1[i];
		data2_sum += data2[i];
		prod_sum += data1[i] * data2[i];
		data1_sqr_sum += data1[i] * data1[i];
		data2_sqr_sum += data2[i] * data2[i];

	}
	double numerator = (n * prod_sum) - (data1_sum * data2_sum);
	double denomenator = (n * data1_sqr_sum - data1_sum * data2_sum) * (n * data2_sqr_sum - data2_sum * data2_sum);

	return numerator / sqrt(denomenator);
}

int count_lines(char* filename) {
	FILE* file = fopen(filename, "r");
	int size = 0;
	char ch;
	while ((ch = fgetc(file)) != EOF)
	{
		if (ch == '\n')
		{
			size++;
		}
	}
	fclose(file);
	return size;
}
int compare(const void* a, const void* b)
{
	if (*(double*)a < *(double*)b) return -1;
	if (*(double*)a == *(double*)b) return 0;
	if (*(double*)a > *(double*)b) return 1;
}

void print_correlation(char* filename, char* setname) {

	int size = count_lines(filename);

	FILE* file = fopen(filename, "r");

	double* data1 = (double*)malloc(size * sizeof(double));
	double* data2 = (double*)malloc(size * sizeof(double));
	double num1;
	double num2;
	int i = 0;
	while (fscanf(file, "%f %f", &num1, &num2) != EOF) {
		data1[i] = num1;
		data2[i++] = num2;
	}
	printf("The correlation coefficient of %s is: %f\n", setname, corr(data1, data2, size));

	free(data1); free(data2); fclose(file);
}

double function(double x) {
	return exp(-x * x);
}
double mc_integral(double lower_bound, double upper_bound, int iterations) {
	double sum = 0;

	int i = 0;
	while (i < iterations - 1)
	{
		double random = lower_bound + (double(rand()) / RAND_MAX) * (upper_bound - lower_bound);
		double value = function(random);
		sum += value;
		i++;
	}

	return (upper_bound - lower_bound) * sum / iterations;
}
