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
	void set(std::string username, std::string txt, int ts)
	{
		name_sender = username;
		mes = txt;
		timestamp = ts;
	}
};