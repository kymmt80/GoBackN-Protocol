#include "../include/message.hpp"

 
void read_file(){
    content={"this","is","a","dumb","test","and","I","am","bored"};
}

void store_file(){
    //TBC
}

string Message::get_frame(int frame_id){
    return content[frame_id];
}

void store_frame(int frame_id,string frame){
    content[frame_id]=frame;
}

int Message::get_size(){
    return content.size();
}
int Message::get_frame_size(){
    return 1;
}