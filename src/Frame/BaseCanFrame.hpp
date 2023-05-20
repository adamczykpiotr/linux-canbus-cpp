#pragma once

#include <stdint.h>
#include <linux/can.h>

class BaseCanFrame {
public:
    /**
     * @brief Raw ID accessor
     * 
     * @return canid_t
     */
    inline virtual canid_t rawId() = 0;


    /**
     * @brief Formatted ID accessor
     * 
     * @return canid_t 
     */
    inline virtual canid_t id() {
        canid_t rawId = this->rawId();

        return (rawId & CAN_EFF_FLAG) // Test for extended ID
            ? rawId & CAN_EFF_MASK    // SFF Format
            : rawId & CAN_SFF_MASK;   // EFF Format
    };


    /**
     * @brief Unified length accessor (len/can_dlc)
     * 
     * @return uint8_t 
     */
    inline virtual uint8_t length() = 0;


    /**
     * @brief Data accessor
     * 
     * @return uint8_t* 
     */
    inline virtual uint8_t* data() = 0;
};