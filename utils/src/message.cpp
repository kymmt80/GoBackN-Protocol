#include "../include/message.hpp"


using namespace std;
 
void Message::read_file(){
    content={"this","is","a","dumb","test","and","I","am","bored"};
}

void Message::store_file(){
    //TBC
}

string Message::get_frame(int frame_id){
    return content[frame_id];
}

void Message::store_frame(int frame_id,string frame){
    content[frame_id]=frame;
}

int Message::get_size(){
    return content.size();
}
int Message::get_frame_size(){
    return 1;
}