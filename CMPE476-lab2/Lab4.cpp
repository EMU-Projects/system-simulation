#include <iostream>
#include "lab2.h"
#include <queue>
#define MAX_SIZE 5000

using namespace std;

typedef struct Packet {
	float bits_remaining;
	double time_arrived;
	double time_started;
	double time_ended;
};

// Since it is first come first serve
// 
// waiting_time = time_started - time_arrived
// process_time = time_ended - time_started

void main() {
	srand(time(0));
	/*
	 * Processing capacity 10,000 bps
	 *
	 * Packet sizes are chosen from an exponential distribution; average size is 1,000 bits.
	 *
	 * Packet arrival process is Poisson
	 *
	 */

	// Total simulation time 5,000 seconds = 5,000,000 ms;
	double total_time = 5000000;

	// lambda = 1/mean
	double lambda = 1.0 / 1000;

	/* utilization level U.
	 * Total_time x U =
	 * 
	 * 
	 */
	double utilization = 0.05;


	// value of queue is packet sizes
	queue<Packet*> packets;

	double last_time = 0;
	while (last_time < total_time) {
		double inter_arrival = 1000*exponential(utilization);
		//cout << "Time: " << last_time << "\n";
		float packet_size = (float)exponential(lambda);
		Packet* packet = new Packet;
		packet->bits_remaining = packet_size;
		packet->time_arrived = last_time;
		packet->time_started = NULL;
		packet->time_ended = NULL;
		packets.push(packet);
		last_time += inter_arrival;
	}

	double total_idle = 0;
	double total_wait = 0;
	double total_process = 0;

	double last_leave = 0;
	// Simulation per millisecond loop
	for (int i = 0; i < total_time && packets.size(); i++) {
		// 10,000 bits per second = 10 bits per millisecond
		float no_bits = 10;
		Packet* current = packets.front();
		if (current->time_arrived > i) {
			// do nothing wait
			continue;
		}
		if (current->time_started == NULL) {
			current->time_started = i;
			total_wait += i - current->time_arrived;
			total_idle += i - last_leave;
		}
		if (no_bits > current->bits_remaining) {
			current->bits_remaining = 0;
			current->time_ended = i;
			total_process += current->time_ended - current->time_arrived;
			last_leave = i;
			packets.pop();
			continue;
		}
		current->bits_remaining -= no_bits;
		
	}

	total_time = (total_wait + total_process + total_idle);

	cout << "Total idle: " << total_idle / 1000 << " seconds" << "\n";
	cout << "Total wait: " <<  total_wait / 1000 << " seconds" << "\n";
	cout << "Total process: " << total_process / 1000 << " seconds" << "\n";
	cout << "Total (wait + idle + process): " <<  total_time / 1000 << " seconds" << "\n"; // total time to finish off processing everything
	cout << "Average packet delay: " << total_wait / total_time << " seconds" << "\n";


}