#pragma once
#include <iostream>
#include <pqxx/pqxx>
#include "Chat.h"

using namespace std;

//struct Message{
////    uint message_id;
//    string chat_name;
//    string mes;
//    string name_sender;
//};
//
//struct Chat{
//    uint chat_id;
//    string name;
//    string password;
//    vector<Message> messages;
//};


class Storage{
public:
    Storage() : database(nullptr){}
    int Connect();
    int InitDB();
    int AddMessage(string sender, string chat_name, string msg);
    Message GetMsg(uint msg_id);
    int AddChat(string chat_name, string chat_password);
    Chat GetChat(uint id);
    vector<Chat> GetUsersChats();
    Chat GetChatByName(string chat_name);
    Message GetLastMsg(string chat_name);
    void CloseDB();
private:
    pqxx::connection *database;
};