#pragma once
#include "Chat.h"
#include "Storage.h"
#include "Message.h"

#include <iostream>
#include <memory>
#include <vector>
#include "Peer.h"

class User: public Peer
{
public:
    void hi();
    void goodbye();
    int connectChat();
    int createChat(std::shared_ptr<Storage>);
    int connectNewChat(std::shared_ptr<Storage>);
    int sendMessage(const message&, std::shared_ptr<Storage>);
    int acceptMessage(const message&, std::shared_ptr<Storage>);
private:
    std::string publicKey;
    int ipAdress;
    std::vector <std::shared_ptr<Chat>> chats;
};