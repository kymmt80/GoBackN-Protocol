#ifndef __RECEIVER_HPP__
#define __RECEIVER_HPP__

#include <string>

class Receiver {
    public:
        Receiver(char* ip, int port);
        void run();
    private:
        char* ip;
        int port;
};

#endif