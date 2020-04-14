#pragma once
#include <iostream>
#include <string>
class User
{
private:
std::string nickname;
std::string privateKeyPath;
uuid userUuid;
public:
	std::string& GetUser(std::string);
	int UpdateUser(int, std::string);
};

