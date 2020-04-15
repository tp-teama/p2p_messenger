#pragma once

#include <iostream>

class API {
public:
    explicit API(std::string database);
    void SendMessage(std::string request);
    void GetChat(std::string request);
    void GetAllMyChats(std::string request);
    void GetUser(std::string request);
    void CreateUser(std::string request);
    void GetUsersByNick(std::string request);
private:
    std::string database;
};