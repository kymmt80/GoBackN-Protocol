#ifndef __SENDER_HPP__
#define __SENDER_HPP__

class Sender {
    public:
        Sender(char* ip, int port);
        void run();
    private:
        char* ip;
        int port;
};

#endif