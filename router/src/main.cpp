#include "router.hpp"
#include "stdlib.h"

int main(int argc, char* argv[]) {

    char* ip = argv[1];
    int port = atoi(argv[2]);
    Router router = Router(ip, port);
    router.run();
}