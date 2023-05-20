#pragma once

#include "BaseCanBus.hpp"
#include "../Frame/CanFdFrame.hpp"

class CanFdBus : public BaseCanBus {

public:

    /**
     * @brief Construct a new Can Bus Fd object
     * 
     * @param name 
     */
    CanFdBus(const char *name) : BaseCanBus(name) {};


    /**
     * @brief Initializes CAN socket connection
     * 
     * @param blocking 
     */
    void init(bool blocking = false) {
        BaseCanBus::init(blocking);

        // Add support for CAN-FD frames
        int canFdEnabled = 1;
        if (setsockopt(this->socketFd, SOL_CAN_RAW, CAN_RAW_FD_FRAMES, &canFdEnabled, sizeof(canFdEnabled))) {
            throw "error when enabling CAN FD support\n";
        }
    }


    /**
     * @brief Attempts to read single canfd_frame from unix socket
     * 
     * @param frame 
     * @return true 
     * @return false 
     */
    inline bool read(canfd_frame *frame) {
        return BaseCanBus::read(frame, CANFD_MTU);
    }


    /**
     * @brief Attempts to read single CanFdFrame from unix socket
     * 
     * @param frame 
     * @return true 
     * @return false 
     */
    inline bool read(CanFdFrame *frame) {
        return BaseCanBus::read(frame & frame->frame, CANFD_MTU);
    }

    /**
     * @brief Attempts to write single canfd_frame to unix socket
     * 
     * @param frame 
     * @return true 
     * @return false 
     */
    inline bool send(canfd_frame *frame) {
        return BaseCanBus::send(frame, CANFD_MTU);
    }


    /**
     * @brief Attempts to write single CanFdFrame to unix socket
     * 
     * @param frame 
     * @return true 
     * @return false 
     */
    inline bool send(CanFdFrame *frame) {
        return BaseCanBus::send(&frame->frame, CANFD_MTU);
    }
};