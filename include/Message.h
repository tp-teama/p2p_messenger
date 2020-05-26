#pragma once
struct Message
{
    std::string mes;
    std::string name;
    int timestamp;
    Message(std::string str): mes(str)
    {

    }
    Message()
    {}
};