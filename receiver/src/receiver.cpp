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
            handle_recv_msg(sockets[receive_fd]->receive());            
            //cout<<sockets[receive_fd]->receive()<<endl;
        }
        if(FD_ISSET(STDIN_FILENO, &read_set)){
            cin>>input;
            sockets[send_fd]->send(input);
        }
        memset(buffer, 0, 1024);
    }

}  

void Receiver::handle_recv_msg(std::string message) {
    if (message[0] == '$')
    {
        this->message.set_size(stoi(message.substr(1, (int)(message.size()) - 1)));
        cout<<message<<endl;
        sockets[send_fd]->send("ACK$");
    }else{
        cout<<message<<endl;
        int seq_num = getSeqNum(message);
        string data = getData(message);
        cout << seq_num << " " << data << endl;
        sockets[send_fd]->send("ACK" + to_string(seq_num));
        this->message.store_frame(seq_num, data);
    }

}

int getSeqNum(string message) {
    string num = "";
    for (int i = 0; i < message.size(); i++)
    {
        if (message[i] == ';')
            return stoi(num);
        num += message[i];
    }
}

string getData(string message) {
    string data = "";
    int i = 0;
    for (i = 0; i < message.size(); i++)
        if (message[i] == ';')
            break;
    i++;
    for (i; i < message.size(); i++)
        data += message[i];
    return data;
}