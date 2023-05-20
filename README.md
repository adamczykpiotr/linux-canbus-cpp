# linux-canbus-cpp

Small &amp; easy to use wrapper library for CAN &amp; CAN-FD

## Examples:

* [Standard frames](example/example-can.cpp)
* [FD frames](example/example-canfd.cpp)

## Building:

```bash
g++ ./example/example-can.cpp -o 
```

## Testing:

### Setup virtual CAN network:

```bash
## Setup VCAN
ip link add dev vcan0 type vcan   # Create virtual can interface
ip link set dev vcan0 up          # Start newly created interface

## Setup VCAN FD
ip link add dev vcan1 type vcan   # Create virtual can interface
ip link set vcan1 mtu 72          # Set maximum transmission unit to 72 bytes (fd frame size)
ip link set dev vcan1 up          # Start newly created interface
```

## TODOs:

- [x] Receiving frames
    - [x] Blocking mode
    - [x] Non-blocking mode
    - [ ] Socket-based filtering
- [x] Sending frames
- [x] CAN-FD Support