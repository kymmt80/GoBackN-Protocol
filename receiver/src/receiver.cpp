#include "receiver.hpp"
#include <iostream>

using namespace std;


Receiver::Receiver(
            char* ip,
            int port_to_router,
            int port_from_router
        ) {

    sockets=vector<Socket*>(10);
    Socket* socket;
    
    socket=new Socket(ip,port_to_router);
    sockets[socket->fd]=socket;
    send_fd=socket->fd;
    
    socket=new Socket(ip,port_from_router);
    sockets[socket->fd]=socket;
    receive_fd=socket->fd;
}

void Receiver::run() {
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
    max_sd = receive_fd;
    FD_SET(STDIN_FILENO, &master_set);
    FD_SET(receive_fd, &master_set);
    FD_SET(send_fd, &master_set);
    write_to = server_fd;
    while (1)
    {
        read_set = master_set;
        bytes=select(max_sd + 1, &read_set, NULL, NULL, NULL);
        if (FD_ISSET(receive_fd, &read_set))
        {
           cout<<sockets[receive_fd]->receive()<<endl;
        }
        if(FD_ISSET(STDIN_FILENO, &read_set)){
            cin>>input;
            sockets[send_fd]->send(input);
        }
        memset(buffer, 0, 1024);
    }

}  