#pragma once
#include <iostream>
#include <string>
using namespace std;
class Storage
{
public:
	string& GetUser(string);
	User& CreateUser(string, string);
	Chat& CreateChat(int, int, string);
	int GetUserId(string);
	Chat& GetChat(int, int);
	int AddMessage(string, int);
	int UpdateUser(int, string);
};

