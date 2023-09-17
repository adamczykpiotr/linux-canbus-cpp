#pragma once

#include "BaseCanBus.hpp"
#include "../Frame/CanFrame.hpp"

class CanBus : public BaseCanBus {
public:
    /**
     * @brief Construct a new Can Bus object
     * 
     * @param name 
     */
    CanBus(const char *name) : BaseCanBus(name) {};


    /**
     * @brief Initializes CAN socket connection
     * 
     * @param blocking 
     */
    inline void connect(bool blocking = false) {
        BaseCanBus::connect(blocking);
    }


    /**
     * @brief Terminates socket connection
     */
    inline void disconnect() {
        BaseCanBus::disconnect();
    }


    /**
     * @brief Attempts to read single can_frame from unix socket
     * 
     * @param frame 
     * @return true 
     * @return false 
     */
    inline bool read(can_frame *frame) {
        return BaseCanBus::read(frame, CAN_MTU);
    }


    /**
     * @brief Attempts to read single CanFrame from unix socket
     * 
     * @param frame 
     * @return true 
     * @return false 
     */
    inline bool read(CanFrame *frame) {
        return BaseCanBus::read(&frame->frame, CAN_MTU);
    }


    /**
     * @brief Attempts to write single can_frame to unix socket
     * 
     * @param frame 
     * @return true 
     * @return false 
     */
    inline bool send(can_frame *frame) {
        return BaseCanBus::send(frame, CAN_MTU);
    }


    /**
     * @brief Attempts to write single CanFrame to unix socket
     * 
     * @param frame 
     * @return true 
     * @return false 
     */
    inline bool send(CanFrame *frame) {
        return BaseCanBus::read(&frame->frame, CAN_MTU);
    }
};