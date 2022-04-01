#include <stdio.h>
#include <Windows.h>
#include <iostream>
//#include "lab1.h"
#include "lab2.h"

int main() {
	/*
	COORD ScreenBufferSize{ 1500, 300 };
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND ConsoleWindow = GetConsoleWindow();

	SetConsoleScreenBufferSize(ConsoleHandle, ScreenBufferSize);
	ShowWindow(ConsoleWindow, SW_MAXIMIZE);*/
	
	srand(time(0));

	for (int i = 0; i < 30; i++)
		printf("%f\n",exponential(8));

	/*std::cout << "\n\nUniform distribution\n\n";
	for (int i = 0; i < 10; i++) {
		std::cout << uniform(0, 1) << "  ";
	}
	std::cout << "\n\nNormal distribution\n\n";
	for (int i = 0; i < 10; i++) {
		std::cout << normal(5,1.3) << "  ";
	}
	double data[1000];
	for (int i = 0; i < 1000; i++) {
		data[i] = normal(5, 1.3);
	}
	int bins[] = {0,0,0,0,0,0,0};
	printf("\n");
	histogram(data, 1000, bins, 0, 10, 7);*/

	return 0;
}