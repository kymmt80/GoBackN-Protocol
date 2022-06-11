#ifndef __RECEIVER_HPP__
#define __RECEIVER_HPP__

#include <string>
#include <vector>

#include "./../../utils/Socket.hpp"

class Receiver {
    public:
        Receiver(
            char* ip,
            int port_to_router,
            int port_from_router
        );
        void run();
    private:
        char* ip;
        int port;
        int send_fd;
        int receive_fd;
        std::vector<Socket*>sockets;

};

#endif