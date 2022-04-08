
#include "lab2.h"

// f(x) = e^((-x^2)/2)
double f_x(double x) {
	return exp(-(x * x) / 2);
}

// g(y) = sqrt( -2ln(y) )
double g_y(double y) {
	return sqrt(-2 * log(y));
}

double phi_z_mc(double z) {
	/*
	* In order to integrate we need to have a proper boundary
	* Integration of g(y)dy from 0 -> 1
	*				+
	* Integration of f(x)dx from 0 -> z
	*/
	int iterations = 10000;
	if (z < 0)
		return 1 - (1 / sqrt(2 * PI)) * (mc_integral(0, 1, iterations, g_y) + mc_integral(0, -z, iterations, f_x));
	else
		return (1 / sqrt(2 * PI)) * (mc_integral(0, 1, iterations, g_y) + mc_integral(0, z, iterations, f_x));

}

double phi_z(double z) {
	double c1 = 0.127414796;
	double c2 = -0.142248368;
	double c3 = 0.710706871;
	double c4 = -0.726576013;
	double c5 = 0.530702714;
	double p = 0.2316419;
	double t = 1 / (1 + p * z);
	double r = t * (c1 + t * (c2 + t * (c3 + t * (c4 + t * c5))));
	if (z < 0)
		return 1 - phi_z(-z);
	return 1 - r * exp(-(z * z) / 2);
}


/*
* Monte Carlo Simulation of Binary Transmission over a Gaussian Channel
*
* Noise is distributed as normal( 0 , sigma^2 )
*
* i  <- Discrete time
* Yi <- Received signal
* Xi <- RV denoting transmitted signal
* Zi <- Noise == normal( 0 , sigma^2 )
*
* Receiver detects "0" if Y <= 0
* Receiver detects "1" if Y > 0
*
* We provide SNR (Signal to noise ratio)
*
* Noise power sigma^2 = 0.25 (ex.)
*
* SNR = P / (sigma^2) -> 10log( P / (sigma^2) ) in dB
*
* parameters ( SNR(dB) , )
*
*/

void binary_channel_error_sim(double P, double sigma_sqr, int no_bits, double &capacity) {
	double sqrt_P = sqrt(P);
	double SNR_DB = 10 * log10(P / sigma_sqr);
	int correct = 0;
	for (int i = 0; i < no_bits; i++) {
		// X == sqrt_P is "1", X == -sqrt_P is "0"
		double X = round(uniform(0, 1)) ? sqrt_P : -sqrt_P;
		double Z = normal(0, sqrt(sigma_sqr));
		double Y = X + Z;
		// if Y is "1"
		if (Y > 0) {
			if (X == sqrt_P) correct++;
		}
		// if Y is "0"
		else {
			if (X == -sqrt_P) correct++;
		}
	}
	int incorrect = no_bits - correct;
	double e = double(incorrect) / no_bits;

	double e_theoretical = 1 - phi_z(sqrt_P / sqrt(sigma_sqr));
	double bin_entropy = 0;
	if (e != 0)
		bin_entropy = -e * log2(e) - (1 - e) * log2(1 - e);
	capacity = 1 - bin_entropy;
	std::cout << "SNR in dB: " << SNR_DB << std::endl;
	std::cout << "Total no. of bits: " << no_bits << std::endl;
	std::cout << "Total no. of correct bits: " << correct << std::endl;
	std::cout << "Total no. of incorrect bits: " << incorrect << std::endl;
	std::cout << "Rate of failure ('e' estimate): " << e << std::endl;
	std::cout << "Probability 'e' theoretical: " << e_theoretical << std::endl;
	std::cout << "Capacity: " << capacity << std::endl;


}