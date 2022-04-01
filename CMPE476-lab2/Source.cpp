#include <stdio.h>
#include <Windows.h>
#include <iostream>
//#include "lab1.h"
#include "lab2.h"
#define M 1000
#define H_SIZE 100
#define H_DIV 10

void print_info(double data[], int bins[], char* name) {
	for (int i = 0; i < H_DIV; i++)
		bins[i] = 0;
	std::cout << "\n\n\n\nPrepare to print " << name << " data" << "\n\n";
	system("pause");
	std::cout << "The histogram:" << "\n\n";
	histogram(data, M, bins, 0, H_SIZE, H_DIV);
	double avg = mean(data, M);
	std::cout << "\n\nThe mean is: " << avg << "\n\n";
	std::cout << "The standard deviation is: " << stdev(data, M, avg) << "\n\n";
}

int main() {

	COORD ScreenBufferSize{ 1500, 300 };
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND ConsoleWindow = GetConsoleWindow();

	SetConsoleScreenBufferSize(ConsoleHandle, ScreenBufferSize);
	ShowWindow(ConsoleWindow, SW_MAXIMIZE);


	srand(time(0));

	double geo_data[M], bi_data[M], p_data[M], uni_data[M], exp_data[M], norm_data[M];
	double
		geo_p{ 0.1 },
		bi_p{ 0.4 },
		p_lambda{ 35 },
		uni_a{ 0 },
		uni_b{ 100 },
		exp_lambda{ 0.1 },
		norm_mean{ 30 },
		norm_std{ 3 };

	int  bi_n{ 100 }, bins[H_SIZE];
	for (int i = 0; i < M; i++) {
		geo_data[i] = geometric(geo_p);
		bi_data[i] = binomial(bi_n, bi_p);
		p_data[i] = poisson(p_lambda);
		uni_data[i] = uniform(uni_a, uni_b);
		exp_data[i] = exponential(exp_lambda);
		norm_data[i] = normal(norm_mean, norm_std);
	}

	print_info(geo_data, bins, (char*)"geometric distribution");
	print_info(bi_data, bins, (char*)"binomial distribution");
	print_info(p_data, bins, (char*)"poisson distribution");
	print_info(uni_data, bins, (char*)"uniform distribution");
	print_info(exp_data, bins, (char*)"exponential distribution");
	print_info(norm_data, bins, (char*)"normal distribution");



	return 0;
}