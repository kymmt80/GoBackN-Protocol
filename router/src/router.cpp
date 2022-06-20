#include "router.hpp"
#include "../../utils/defs.hpp"


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
    srand((unsigned)time(NULL));
    int max_sd;
    int bytes;
    fd_set master_set, read_set;
    FD_ZERO(&master_set);
    max_sd = receiver_receive_fd;
    FD_SET(STDIN_FILENO, &master_set);
    FD_SET(sender_receive_fd, &master_set);
    FD_SET(sender_send_fd, &master_set);
    FD_SET(receiver_receive_fd, &master_set);
    FD_SET(receiver_send_fd, &master_set);
    string recieved_message;
    while (1)
    {
        read_set = master_set;
        bytes=select(max_sd + 1, &read_set, NULL, NULL, NULL);
        if (FD_ISSET(sender_receive_fd, &read_set))
        {
            recieved_message=sockets[sender_receive_fd]->receive();

            float drop = float(rand())/RAND_MAX;
            if(drop <= DROP_PROB && recieved_message[0]!='$'){
                cout<<"Oops I dropped packet no."<< recieved_message[0] <<" :)))"<<endl<<LOG_DELIM;
            }else{
                //sockets[receiver_send_fd]->send(recieved_message);
                //cout<<"Transmitting message \""<< recieved_message <<"\" from sender to receiver..."<<endl<<LOG_DELIM;   //uncomment this section for without-buffer mode
                add_to_buffer(recieved_message); //comment this section for without-buffer mode
            }
        }
        if (FD_ISSET(receiver_receive_fd, &read_set))
        {
            recieved_message=sockets[receiver_receive_fd]->receive();
            sockets[sender_send_fd]->send(recieved_message);
            cout<<"Transmitting message \""<< recieved_message <<"\" from receiver to sender..."<<endl<<LOG_DELIM;
        }
        if(buffer_timeout()){//comment this section for without-buffer mode
            pop_buffer();
        }
    }

}  

void Router::pop_buffer(){
    if(!buffer.empty()){
        frame message = buffer.front();
        sockets[receiver_send_fd]->send(message);
        buffer.pop();

        cout<<"Transmitting Message \""<< message <<"\" from buffer..."<<endl<<LOG_DELIM;
    }
}

bool Router::buffer_timeout(){
    if((clock()-last_send)/(CLOCKS_PER_SEC/1000)>BUFFER_SEND_THRESHOLD){
        last_send=clock();
        cout<<"BUFFER-PROCESSING DONE"<<endl<<LOG_DELIM;
        return true;
    }
    return false;
}


void Router::add_to_buffer(frame message) {
    if(message[0]=='$'){
        sockets[receiver_send_fd]->send(message);
        cout<<"Transmitting message \""<< message <<"\" from sender to receiver..."<<endl<<LOG_DELIM;
        return;
    }
    if (buffer.size() <= MAX_BUFFER_SIZE)
    {
        buffer.push(message);
        cout << "Buffered Message \""<< message <<"\""<< endl << LOG_DELIM;
        return;
    }else{
        cout<<"Oops the buffer is full -> dropped message: \""<< message <<"\""<<endl<<LOG_DELIM;
    }
    return;
}
