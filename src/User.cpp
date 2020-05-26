#include "User.h"
#include "Chat.h"


bool User::auth(std::string password)
{
    o_uuid id = this -> user_id;
    std::string login = this->username;
    std::string s = to_string(id);
    bool auth = Authorize(id, password);
    return auth;
}
bool User::registration(std::string login,std::string password)
{
    if(login.empty() || password.empty())
    {
        return false;
    }
    o_uuid id = boost::uuids::random_generator()();
    std::string s = to_string(id);
    std::string str = to_string(port);
    std::string init_str = "command:add_user username:" + login + " user_id:" + s + " password:" + password + " port:" + str;
    SendToPort(init_str, 5000);
    return true;
}
void User::hi(){
    o_uuid id = this->user_id;
    std::string s = to_string(id);
    std::string str = to_string(port);
    std::string init_str = "command:update_ip user_id:" + s + " port:" + str;
    SendToPort(init_str, 5000);
}
void User::goodbye()
{
    o_uuid id = this->user_id;
    std::string s = to_string(id);
    std::string init_str = "command:logout user_id:" + s;
    std::shared_ptr<Message> mes = std::make_shared<Message>(init_str);
    SendToPort(init_str, 5000);
}
vector<Chat> User::get_chats()
{
    Storage db;
    vector<Chat> chats = db.getChats();
    return chats;
}
vector <Message> User::get_messages(const std::string& chatName)
{
    Storage db;

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
int User::sendMessage(std::shared_ptr<Message> message, const std::string& chatName)
{
    Storage db;
    shared_ptr<Chat> chat = make_shared<Chat>(db.GetChatByName(chatName));
    SendToChat(message, chat);
}
int User::acceptMessage(std::shared_ptr<Message> message, std::shared_ptr<Storage>)
{

}
