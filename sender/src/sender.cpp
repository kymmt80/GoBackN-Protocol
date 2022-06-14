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
    LAR = -1;
}

void Sender::send_new_frames()
{
    while (LFS - LAR <= SWS)
    {
        cout << "Sending frame " << LFS << "..." << endl;
        sockets[send_fd]->send(get_next_frame());
    }
}

int get_seq_num(string message) {
    return stoi(message.substr(3, message.size() - 3));
}


void Sender::run() {
    int fd;
    int max_sd;
    string input;
    int id,bytes,room_type;
    fd_set master_set, read_set, write_set;
    FD_ZERO(&master_set);
    max_sd = max(receive_fd,send_fd);
    FD_SET(STDIN_FILENO, &master_set);
    FD_SET(send_fd, &master_set);
    FD_SET(receive_fd, &master_set);
    while (1)
    {
        read_set = master_set;
        bytes=select(max_sd + 1, &read_set, NULL, NULL, NULL);
        if (FD_ISSET(receive_fd, &read_set))
        {
            string recv_message = sockets[receive_fd]->receive(); 
            if (recv_message == FIRST_ACK)
                send_new_frames();
            else 
            {
                int seq_num = get_seq_num(recv_message);
                LAR = seq_num;
                cout << recv_message << endl;
                if(!all_frames_sent()){
                        send_new_frames();
                }
            }  
        }
        if(FD_ISSET(STDIN_FILENO, &read_set)){
                sockets[send_fd]->send("$" + to_string(message.get_size()));
                FD_CLR(STDIN_FILENO,&master_set);
        }
    }

}  

frame Sender::get_next_frame() {
    string sent_message=to_string(LFS) + DELIMETER + message.get_frame(LFS);
    LFS++;
    return sent_message; 
}

bool Sender::all_frames_sent(){
    return LFS>message.get_size()-1;
}