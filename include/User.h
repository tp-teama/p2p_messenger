#pragma once
#include <iostream>
#include <string>
class User
{
private:
std::string nickname;
unsigned int uuid;
public:
	User& GetUser(unsigned int);
	int UpdateUser(unsigned int, std::string);
	User& CreateUser(std::string);
	User* GetUsersByNick(std::string);
	User();
	User(std::string, unsigned int);
};

