#ifndef __SENDER_HPP__
#define __SENDER_HPP__

#include<vector>

#include "../../utils/include/socket.hpp"

class Sender {
    public:
        Sender(
            char* ip, 
            int port_from_router,
            int port_to_router
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