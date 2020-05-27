#pragma once
struct Message
{
    std::string chat_name;
    std::string mes;
    std::string name_sender;
    int timestamp;
    Message(std::string str): mes(str)
    {

    }
    Message()
    {}
};