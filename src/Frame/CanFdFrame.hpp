#pragma once

#include "BaseCanFrame.hpp"

class CanFdFrame: public BaseCanFrame {
public:
    canfd_frame frame;


    /**
     * @brief Construct a new Can Fd Frame object
     * 
     * @param frame 
     */
    CanFdFrame(canfd_frame frame = {}): frame(frame) {}


    /**
     * @brief Raw ID accessor
     * 
     * @return canid_t 
     */
    inline virtual canid_t rawId() {
        return this->frame.can_id;
    }


    /**
     * @brief Unified length accessor (len/can_dlc)
     * 
     * @return uint8_t 
     */
    inline virtual uint8_t length() {
        return this->frame.len;
    }


    /**
     * @brief Data accessor
     * 
     * @return uint8_t* 
     */
    inline virtual uint8_t* data() {
        return this->frame.data;
    }
};