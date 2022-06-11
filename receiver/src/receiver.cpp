#include "receiver.hpp"
#include <iostream>
using namespace std;

Receiver::Receiver(char* ip, int port) {
    this->ip = ip;
    this->port = port;
}

void Receiver::run() {
    cout << "Receiver: run()\n"; 
}  