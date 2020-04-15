#include "Message.h"

Message::Message(std::string text, unsigned int userId, unsigned int chatId, std::string database)
    : text(text)
    , userId(userId)
    , chatId(chatId)
    , database(database){}

int Message::AddMessage() {
    return 0;
}
