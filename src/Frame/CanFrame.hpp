#pragma once

#include "BaseCanFrame.hpp"

class CanFrame : public BaseCanFrame {
public:
    can_frame frame;


    /**
     * @brief Construct a new Can Frame object
     * 
     * @param frame 
     */
    CanFrame(can_frame frame = {}) : frame(frame) {}


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
     * Older versions of linux kernel didn't support .len accessor,
     * only can_dlc. Although nowadays using can_dlc is deprecated,
     * still plenty of modern linux don't support it
     * 
     * @return uint8_t 
     */
    inline virtual uint8_t length() {
        return this->frame.can_dlc;
    }


    /**
     * @brief Data accessor
     * 
     * @return uint8_t* 
     */
    inline virtual uint8_t *data() {
        return this->frame.data;
    }
};