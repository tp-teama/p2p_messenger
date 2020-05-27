#include "User.h"
#include "Chat.h"


bool User::auth(const std::string& password)
{
    if(password.empty())
    {
        return false;
    }
    std:string id = Authorize(this->username, password);
    if(id.empty())
    {
        return false;
    }
    this->user_id = boost::lexical_cast<o_uuid>(id);
    return true;
}
bool User::registration(const std::string& login,const std::string& password)
{
    if(login.empty() || password.empty())
    {
        return false;
    }
//    o_uuid id = boost::uuids::random_generator()();
    std::string str = to_string(port);
    std::string init_str = "command:add_user username:" + login +
            " password:" + password + " ip:" + str;
//    SendToPort(init_str, 5000);
    std::string id = Registration(init_str);
    if(id.empty())
    {
        return false;
    }
    this->user_id = boost::lexical_cast<o_uuid>(id);
    this->username = login;
    return true;
}
void User::hi(){
    o_uuid id = this->user_id;
    std::string s = to_string(id);
    std::string str = to_string(port);
    std::string init_str = "command:update_ip user_id:" + s + " ip:" + str;
    SendToPort(init_str, 5000);
}
void User::goodbye()
{
    o_uuid id = this->user_id;
    std::string s = to_string(id);
    std::string init_str = "command:logout user_id:" + s;
    SendToPort(init_str, 5000);
}
std::vector<Chat> User::get_chats()
{
    Storage db;
    std::vector<Chat> chats = db.GetUsersChats();
    if(chats.empty())
    {
        chats.assign(1,0);
    }
    return chats;
}
std::vector <Message> User::get_messages(const std::string& chatName)
{
    if(chatName.empty())
    {
        std::vector<Message> messages;
        std::string error = "error";
        messages.assign(1,error);
        return messages;
    }
    Storage db;
    Chat chat = db.GetChatByName(chatName);
    std::vector<Message> messages = chat.messages;
}
int User::connectChat(const std::string& chatName)
{
    Storage db;
    Chat chat = db.GetChatByName(chatName);
}
int User::createChat(const std::string& chatName, const std::string& pass) {
    std::string init_str = "command:create_chat user_id:" + to_string(this->user_id) +
                           " chat_name:" + chatName + " password:" + pass;
    SendToPort(init_str,5000);
}
int User::connectNewChat(const std::string& chatName, const std::string& pass){
    std::string init_str = "command:join_chat user_id:" + to_string(this->user_id) +
            " chat_name:" + chatName + " password:" + pass;
    SendToPort(init_str,5000);
}
bool User::sendMessage(std::shared_ptr<Message> message, const std::string& chatName)
{
    Storage db;
    std::shared_ptr<Chat> chat = make_shared<Chat>(db.GetChatByName(chatName));
    return SendToChat(message, chat, this->user_id);
}
int User::acceptMessage(std::shared_ptr<Message> message, std::shared_ptr<Storage>)
{

}
