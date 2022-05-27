#include <iostream>
#include <vector>
#include <queue>
#define SLOTS 10000

typedef struct Frame {};

double random(double a, double b) {
    return (b - a) * (rand() / double(RAND_MAX)) + a;
}

int main()
{

    srand(time(0));
    // USING --- SLOTTED ALOHA --- (PROTOCOL)

    for (int k = 0; k < 10; k++){
        // Length of bits (200-bit) frame
        const int L = 200;

        // Channel transmission capacity (200 kbps)
        const int B = 200000;

        // length of time in a time slot
        const double time_slot_length = double(L) / B;

        // Number of Nodes
        const int N = 50;

        // Probability of transmitting a frame. (We always have a frame to transmit)
        const double p = 1.0 / N;

        int collisions = 0;
        std::queue<Frame*> frames;
        double max_efficiency = 0;
        for (int i = 0; i < SLOTS; i++) {
            std::queue<Frame*> temp;
            for (int j = 0; j < N; j++) {
                if (random(0, 1) <= p) {
                    Frame* frame;
                    temp.push(frame);
                }

            }
            double efficiency = temp.size()* exp(-int(temp.size()));
            if (efficiency > max_efficiency) max_efficiency = efficiency;
            if (temp.size() > 1) {
                collisions++;
                temp.pop();
                while (temp.size() > 0) {
                    frames.push(temp.front());
                    temp.pop();
                }
            }
            else if (temp.size() == 0 && frames.size() > 0) {
                frames.pop();
            }

        }

        // Maximum efficiency according to protocol should be 3.68
        std::cout << "No. of collisions: " << collisions << "\n";
        std::cout << "Rate of collision: " << double(collisions) / SLOTS << "\n";
        std::cout << "Maximum efficiency: " << max_efficiency << "\n";
        std::cout << "Frames left: " << frames.size() << "\n";
        std::cout << "\n\n";
    }
    return 0;
}
