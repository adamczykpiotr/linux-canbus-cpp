#include "../src/Bus/CanFdBus.hpp"

#include "util-print-frame.hpp"

/**
 * @brief Entrypoint
 * 
 * @return int 
 */
int main() {
    // Initialize CanFdBus
    CanFdBus fdBus("vcan0");
    fdBus.connect();

    CanFdFrame fdFrame;
    while (true) {
        if (fdBus.read(&fdFrame) == false) {
            continue;
        }

        // Do something with FD frame
        printFrame(&fdFrame);
        break;
    }

    // Re-transmit last FD frame
    fdBus.send(&fdFrame);

    // Gracefully shutdown socket
    fdBus.disconnect();

    return 0;
}