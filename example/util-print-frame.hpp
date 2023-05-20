#pragma once

#include <iostream>
#include <iomanip>

#include "../src/Frame/CanFrame.hpp"
#include "../src/Frame/CanFdFrame.hpp"

/**
 * @brief Helper function for printing frame contents
 * 
 * @param frame 
 */
void printFrame(BaseCanFrame *frame) {
    std::cout << std::hex << std::uppercase << frame->id() << " [" << std::dec << (int) frame->length() << "]: ";

    for (int i = 0; i < frame->length(); i++) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << (int) (frame->data()[i]) << ' ';
    }

    std::cout << std::endl << std::flush;
}

/**
 * @brief Fallbackc helper function for printing frame contents
 * 
 * @param frame 
 */
void printFrame(can_frame *frame) {
    printFrame(new CanFrame(*frame));
}

/**
 * @brief Fallback helper function for printing frame contents
 * 
 * @param frame 
 */
void printFrame(canfd_frame *frame) {
    printFrame(new CanFdFrame(*frame));
}