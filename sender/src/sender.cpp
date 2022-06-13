#include "sender.hpp"
#include "../../utils/defs.hpp"

using namespace std;

typedef string frame;


Sender::Sender(
            char* ip, 
            int port_from_router,
            int port_to_router
        ) {
    sockets=vector<Socket*>(10);
    Socket* socket;
    
    socket=new Socket(ip,port_to_router);
    sockets[socket->fd]=socket;
    send_fd=socket->fd;
    
    socket=new Socket(ip,port_from_router);
    sockets[socket->fd]=socket;
    receive_fd=socket->fd;

    message.read_file();

    LFS = 0;
}

void Sender::run() {
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

    bool flag=false;
    bool flag2=false;

    while (1)
    {
        read_set = master_set;
        bytes=select(max_sd + 1, &read_set, NULL, NULL, NULL);
        if (FD_ISSET(receive_fd, &read_set))
        {
           cout<<sockets[receive_fd]->receive()<<endl;
           if(!flag){
                sockets[send_fd]->send(get_next_frame());
                flag=true;
           }
           
        }
        if(FD_ISSET(STDIN_FILENO, &read_set)){
            //cin>>input;
            //sockets[send_fd]->send(input);
            if(!flag2){
                sockets[send_fd]->send("$" + to_string(message.get_size()));
                flag2=true;
            }
        }
        memset(buffer, 0, 1024);
    }

}  

frame Sender::get_next_frame() {
    return to_string(LFS) + DELIMETER + message.get_frame(LFS++);
}