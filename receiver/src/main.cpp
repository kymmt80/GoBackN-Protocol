#include "receiver.hpp"
#include "stdlib.h"

int main(int argc, char* argv[]) {

    char* ip = argv[1];
    int port = atoi(argv[2]);
    Receiver receiver = Receiver(ip, port);
    receiver.run();
}