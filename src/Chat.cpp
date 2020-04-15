#include "Сhat.h"

Chat::Chat(unsigned int user1Id, unsigned int user2Id, std::string database)
    : user1Id(user1Id)
    , user2Id(user2Id)
    , database(database) {}

int Chat::SendMessage(unsigned int charId, unsigned int sender, std::string text) {
    return 0;
}

Chat& Chat::GetChat(unsigned int chatId) {
    throw NULL;
}

std::vector<Chat> Chat::GetAllMyChats(unsigned int userId) {
    throw NULL;
}