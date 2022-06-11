#include "router.hpp"
#include <iostream>
using namespace std;

Router::Router(char* ip, int port) {
    this->ip = ip;
    this->port = port;
}

void Router::run() {
    cout << "Router: run()\n"; 
}  