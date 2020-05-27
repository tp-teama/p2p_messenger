#pragma once
#include "Chat.h"
#include "Storage.h"
#include "Message.h"

#include <iostream>
#include <memory>
#include <vector>
#include "Peer.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>
     // streaming operators etc.

namespace b_uuid = boost::uuids;
typedef boost::uuids::uuid o_uuid;


class User: public Peer
{
public:
    User(std::string login, int Port):port(Port), username(login),Peer(tcp::endpoint(tcp::v4(), Port))
    {

    }
    User(int Port):port(Port),Peer(tcp::endpoint(tcp::v4(), Port))
    {

    }
    bool auth(const std::string&);
    bool registration( const std::string&, const std::string&);
    void hi();
    void goodbye();
    std::vector<Chat> get_chats();
    std::vector <Message> get_messages(const std::string&);
    int connectChat(const std::string&);
    int createChat(const std::string&, const std::string&);
    int connectNewChat(const std::string&, const std::string&);
    bool sendMessage(std::shared_ptr<Message> , const std::string&);
    int acceptMessage(std::shared_ptr<Message>, std::shared_ptr<Storage>);
private:
    o_uuid user_id;
    int port;
    std::string username;
    std::string publicKey;
    std::string ipAdress;
    std::vector <std::shared_ptr<Chat>> chats;
};