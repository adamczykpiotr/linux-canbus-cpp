#pragma once

#include <net/if.h>         // ifreq
#include <sys/ioctl.h>      // ioctl, SIOCGIFINDEX
#include <unistd.h>         // read, write, close
#include <fcntl.h>          // fcntl
#include <cstring>          // strcpy
#include <linux/can/raw.h>  // sockaddr_can, SOL_CAN_RAW

class BaseCanBus {

protected:
    const char * interfaceName;
    int socketFd;


    /**
     * @brief Construct a new Base Can Bus object
     * 
     * @param interfaceName 
     */
    BaseCanBus(const char * interfaceName): interfaceName(interfaceName) {
    }
    

    /**
     * @brief Destroy the Base Can Bus object
     * 
     */
    ~BaseCanBus() {
        ::close(this->socketFd);
    }


    /**
     * @brief Initializes CAN socket connection
     * 
     * @param blocking 
     */
    void init(bool blocking = false) {
        // Connect to unix socket
        this->socketFd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
        if(this->socketFd < 0) {
             throw "Unable to open unix CAN socket";
        }

        // Bind interface name
        ifreq ifr;
        strcpy(ifr.ifr_name, this->interfaceName);
        ioctl(this->socketFd, SIOCGIFINDEX, &ifr);

        sockaddr_can addr = {};
        addr.can_family = AF_CAN;    
        addr.can_ifindex = ifr.ifr_ifindex;
        if(bind(this->socketFd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            throw "Unable to connect to interface";
        }

        // Connection estabilished at this point
        if(blocking == false) {
            return;
        }

        // Handle non-blocking mode

        // Get flags
        int flags = fcntl(this->socketFd, F_GETFL, 0);
        if(flags == -1) {
            throw "Unable to set non-blocking mode";
        }

        // Set non-blocking flag
        if (fcntl(this->socketFd, F_SETFL, flags | O_NONBLOCK) == -1) {
            throw "Unable to set non-blocking mode";
        }
    }


    /**
     * @brief Attempts to read single can frame from unix socket
     * 
     * @param frame can_frame or canfd_frame ptr
     * @param size CAN_MTU or CANFD_MTU respectively
     * @return true
     * @return false
     */
    inline bool read(void * frame, size_t size) {
        return ::read(this->socketFd, frame, size) > 0;
    }


    /**
     * @brief Attempts to write single can_frame to unix socket
     * 
     * @param frame can_frame or canfd_frame ptr
     * @param size CAN_MTU or CANFD_MTU respectively
     * @return true 
     * @return false 
     */
    inline bool send(void * frame, size_t size) {
        return ::write(this->socketFd, frame, size) == size;
    }
};