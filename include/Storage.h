#include <iostream>
#include <pqxx/pqxx>

using namespace std;

struct Chat{
    uint chat_id;
    string chat_name;
    string chat_password;
};

struct Message{
    uint message_id;
    uint chat_id;
    string msg;
    uint sender_id;
};

class Storage{
public:
    Storage() : database(nullptr){}
    int Connect();
    int InitDB();
    int AddMessage(uint sender_id, uint chat_id, string msg);
    Message GetMsg(uint msg_id);
    int AddChat(string chat_name, string chat_password);
    Chat GetChat(uint id);
    void CloseDB();
private:
    pqxx::connection *database;
};