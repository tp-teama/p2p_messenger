#pragma once
#include <iostream>

class Message {
public:
    Message() = delete;
    explicit Message(std::string text, unsigned int userId, unsigned int chatId, std::string database);
    int AddMessage();
private:
    unsigned int messageId;
    std::string text;
    unsigned int userId;
    unsigned int chatId;
    std::string database;
};