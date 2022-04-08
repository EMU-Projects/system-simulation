#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <math.h>
#include "lab3.h"
void main() {
	srand(time(0));

	binary_channel_error_sim(0.25, 100000);
	//printf("Integration: %lf", phi_z(3));

}