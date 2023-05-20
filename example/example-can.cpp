#include "../src/Bus/CanBus.hpp"

#include "util-print-frame.hpp"

/**
 * @brief Entrypoint
 * 
 * @return int 
 */
int main() {

    // Initialize CanBus
    CanBus bus("vcan0");
    bus.init();

    CanFrame frame;
    while (true) {
        if (bus.read(&frame) == false) {
            continue;
        }

        // Do something with frame
        printFrame(&frame);
        break;
    }

    // Re-transmit last frame
    bus.send(&frame);

    return 0;
}