#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include<vector>
#include<string>

class Message
{
private:
    std::vector<std::string> content;
public:
    Message();
    std::string get_frame(int frame_id);
    void store_frame(int frame_id,string frame);
    void read_file();
    void store_file();
    int get_size();
    int get_frame_size();
};




#endif
