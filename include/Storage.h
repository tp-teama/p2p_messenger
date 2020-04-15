#pragma once
#include <iostream>
#include <string>
class Storage {
public:
	User& GetUser(unsigned int);
	int UpdateUser(unsigned int, std::string);
	User& CreateUser(std::string);
	User* GetUsersByNick(std::string);
	Chat& CreateChat(unsigned int,unsigned int,std :: string);
	Chat& GetChat(unsigned int);
	Chat* GetAllMyChats (unsigned int);
	int DeleteChat(unsigned int);
	Message& SendMessage(Message);
private:
	std::string conn;
};

