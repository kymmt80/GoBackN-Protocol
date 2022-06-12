#include "../include/socket.hpp"

Socket::Socket(char *ip, int port) {
    int fd;
    int broadcast = 1, opt = 1;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));
    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(ip);
    if (bind(fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        write(STDOUT_FILENO, "Connection Error\n", 29);
    }
    write(STDOUT_FILENO, "Connected to Port\n", 19);
    this->fd = fd;
}

int Socket::send(std::string data){
    return sendto(fd, data.c_str(), data.size(), 0,(struct sockaddr *)&address, sizeof(address));
}

std::string Socket::receive(){
    char buff[1049] = {0};
    recv(fd, buff, 1024, 0);
    return buff;
}