#include "Сhat.h"

Chat::Chat(unsigned int user1Id, unsigned int user2Id, std::string database) {
    user1Id = user1Id;
    user2Id = user2Id;
    database = database;
}

int Chat::SendMessage(unsigned int charId, unsigned int sender, std::string text) {

}

Chat& Chat::GetChat(unsigned int chatId) {

}

std::vector<Chat> Chat::GetAllMyChats(unsigned int userId) {

}