#pragma once

#include <iostream>
#include <vector>
#include "Message.h"

class Chat {
public:
    Chat() = delete;
    explicit Chat(unsigned int user1Id, unsigned int user2Id, std::string database);
    int SendMessage(unsigned int charId, unsigned int sender, std::string text);
    Chat& GetChat(unsigned int chatId);
    std::vector<Chat> GetAllMyChats(unsigned int userId);
private:
    unsigned int chatId;
    unsigned int user1Id;
    unsigned int user2Id;
    std::vector<Message> messages;
    std::string database;
};