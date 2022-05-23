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


/*
* 
* The code is built with C++ libraries such as iostream, queue
* 
*/

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
	double utilization = 0.95;


	// list containing all packets to be processed
	vector<Packet*> packets;

	double arrival_time = 0;
	while (arrival_time < total_time) {
		float packet_size = (float)exponential(lambda);
		Packet* packet = new Packet;
		packet->bits_remaining = packet_size;
		packet->time_arrived = arrival_time;
		packet->time_started = NULL;
		packet->time_ended = NULL;
		packets.push_back(packet);
		arrival_time += long(1000*exponential(utilization));
	}

	double total_idle = 0; // total time the simulation is doing nothing
	double total_wait = 0; // total time of waiting between arrival of packets and the start of processing them
	double total_process = 0; // total time of processing the packet = finish - start

	// iterator number to keep track of the latest packet that was added to the queue
	int iter_id = 0;

	// queue containing currently waiting packets to be served
	queue<Packet*> queue;

	// packet count per millisecond
	double packet_count = 0;

	// Simulation per millisecond loop
	for (double t = 0; iter_id < packets.size(); t++) {
		// t is the current time in ms in our simulation
		// 10,000 bits per second = 10 bits per millisecond
		const float no_bits_to_subtract = 10;

		while (iter_id < packets.size() && packets[iter_id]->time_arrived <= t) {
			queue.push(packets[iter_id]);
			iter_id++;
		}

		packet_count += queue.size();
		if (queue.size() == 0) {
			// do nothing
			total_idle++;
			continue;
		}

		Packet* current = queue.front();
		if (current->time_started == NULL) {
			current->time_started = t;
			total_wait += t - current->time_arrived;
		}
		if (no_bits_to_subtract > current->bits_remaining) {
			current->bits_remaining = 0;
			current->time_ended = t;
			total_process += t - current->time_started;
			queue.pop();
			continue;
		}
		current->bits_remaining -= no_bits_to_subtract;

	}
	double entire_time = total_idle + total_process;

	std::cout << "Total idle: " << total_idle / 1000 << " seconds" << "\n";
	std::cout << "Total wait: " << total_wait / 1000 << " seconds" << "\n";
	std::cout << "Total process: " << total_process / 1000 << " seconds" << "\n";
	std::cout << "Total time: " << entire_time / 1000 << " seconds" << "\n";
	std::cout << "Average packet delay: " << total_wait / packets.size() << " seconds" << "\n";
	std::cout << "Average no. of packets: " << packet_count / entire_time << " packets" << "\n";
	std::cout << "Total no. of packets: " << packets.size() << " packets" << "\n";

}