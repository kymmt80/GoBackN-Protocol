#include "router.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>

using namespace std;

Router::Router(
            char* ip,
            int port_to_sender,
            int port_from_sender,
            int port_to_receiver,
            int port_from_receiver
        ) {
    sockets=vector<Socket*>(10);
    Socket* socket;
    
    socket=new Socket(ip,port_to_sender);
    sockets[socket->fd]=socket;
    sender_send_fd=socket->fd;

    socket=new Socket(ip,port_from_sender);
    sockets[socket->fd]=socket;
    sender_receive_fd=socket->fd;
    
    socket=new Socket(ip,port_to_receiver);
    sockets[socket->fd]=socket;
    receiver_send_fd=socket->fd;
    
    socket=new Socket(ip,port_from_receiver);
    sockets[socket->fd]=socket;
    receiver_receive_fd=socket->fd;
}

void Router::run() {
    int fd;
    int server_fd, room_fd=-1, max_sd, write_to;
    char buff[1049] = {0};
    char buffer[1024] = {0};
    char QandA[1024]={0};
    char tmp[1049]={0};
    string input;
    int id,bytes,room_type;
    fd_set master_set, read_set, write_set;
    FD_ZERO(&master_set);
    max_sd = receiver_receive_fd;
    FD_SET(STDIN_FILENO, &master_set);
    FD_SET(sender_receive_fd, &master_set);
    FD_SET(sender_send_fd, &master_set);
    FD_SET(receiver_receive_fd, &master_set);
    FD_SET(receiver_send_fd, &master_set);
    write_to = server_fd;
    while (1)
    {
        read_set = master_set;
        bytes=select(max_sd + 1, &read_set, NULL, NULL, NULL);
        if (FD_ISSET(sender_receive_fd, &read_set))
        {
           //recv(receive_fd, buffer, 1024, 0);
           //cout<<buffer<<endl;
           sockets[receiver_send_fd]->send(sockets[sender_receive_fd]->receive());
           cout<<"sender sent a message :("<<endl;
        }
        if (FD_ISSET(sender_receive_fd, &read_set))
        {
           //recv(receive_fd, buffer, 1024, 0);
           //cout<<buffer<<endl;
           sockets[sender_send_fd]->send(sockets[receiver_receive_fd]->receive());
           cout<<"receiver sent a message :("<<endl;
        }
        memset(buffer, 0, 1024);
    }

}  