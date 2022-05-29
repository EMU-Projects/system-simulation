#include <iostream>
#define SLOTS 10000


double random(double a, double b) {
    return (b - a) * (rand() / double(RAND_MAX)) + a;
}

int main()
{

    srand(time(0));
    // USING --- SLOTTED ALOHA --- (PROTOCOL)

    for (int k = 0; k < 9; k++){
        // Length of bits (200-bit) frame
        const int L = 200;

        // Channel transmission capacity (200 kbps)
        const int B = 200000;

        // length of time in a time slot
        const double time_slot_length = double(L) / B;

        // Number of Nodes
        const int N = 50;

        // Probability of transmitting a frame. (We always have a frame to transmit)
        // For k < 3 try p = 1/N
        // for k < 6 try p = 1/2*N
        // for the last 3 tries p = 2/N
        const double p = k < 3 ? (1.0 / N) : k < 6 ? (1.0 / (2*N)): (2.0/N);

        // Total no. of collisions that happened throughout the simulation
        int collisions = 0;
        
        // No. of frames
        int frames = 0;

        // Maximum efficiency -> e = G * e^(-G)
        // For G is the no. of nodes that were sending a frame per time slot
        double max_efficiency = 0;

        for (int i = 0; i < SLOTS; i++) {
            
            // No. of nodes that that are sending a frame
            int nodes_sending = 0;
            
            for (int j = 0; j < N; j++) {
                // Checking the probability of sending a frame per node
                if (random(0, 1) <= p) {
                    nodes_sending++;
                }

            }

            // calculating efficiency with maximum algorithm
            double efficiency = nodes_sending* exp(-int(nodes_sending));
            if (efficiency > max_efficiency) max_efficiency = efficiency;

            // If more than 1 node is sending -> collision happens
            if (nodes_sending > 1) {
                collisions++;
                frames += nodes_sending;
            }

            // If there is a slot with no nodes sending a frame, send previous frames
            // i.e subtract the number of frames that are queueing to be sent from previous collisions 
            else if (nodes_sending == 0 && frames > 0) {
                frames--;
            }

        }

        // Maximum efficiency according to protocol should be 3.68
        std::cout << "Probability: " << p << std::endl;
        std::cout << "No. of collisions: " << collisions << std::endl;
        std::cout << "Rate of collision: " << double(collisions) / SLOTS << std::endl;
        std::cout << "Maximum efficiency: " << max_efficiency << std::endl;
        std::cout << "Frames left: " << frames << std::endl;
        std::cout << std::endl << std::endl;
    }
    return 0;
}
