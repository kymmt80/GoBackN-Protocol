#ifndef __ROUTER_HPP__
#define __ROUTER_HPP__

class Router {
    public:
        Router(char* ip, int port);
        void run();
    private:
        char* ip;
        int port;
};

#endif