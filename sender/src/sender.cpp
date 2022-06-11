#include "sender.hpp"
#include <iostream>
using namespace std;

Sender::Sender(char* ip, int port) {
    this->ip = ip;
    this->port = port;
}

void Sender::run() {
    cout << "Sender: run()\n"; 
}  