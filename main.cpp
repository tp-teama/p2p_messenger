#include <iostream>
#include "Peer.h"
#include <future>
#include "User.h"
#include "Storage.h"

int main() {
    int port = 0;
    char go = 'd';
    Storage s = Storage();
    s.Connect();
    while(go != 'o') {
        std::cout << "Введи действие reg/auth" << std::endl;
        std::cin >> go;
        if (go == 'r') {
            User nathan(port);
            std::cout << "Введи ник и пароль" << std::endl;
            std::string login, password;
            std::cin >> login >> password;
            std::cout << nathan.registration(login, password) << std::endl;
        } else if (go == 'a') {
            std::cout << "Введи ник и пароль" << std::endl;
            std::string login, password;
            std::cin >> login >> password;
            User nathan(login, port);
            std::cout << nathan.auth(password) << std::endl;
            nathan.hi();
            while(go != 'o')
            {
                std::cout << "Введи действие create_chat/join_chat/send_mes_in_chat/see messages(m)/exit" << std::endl;
                std::cin >> go;
                if(go == 'c')
                {
                    std::cout << "Введи название чата и пароль" << std::endl;
                    std::string login, password;
                    std::cin >> login >> password;
                    nathan.createChat(login, password);
                    std::vector<Chat> chats = nathan.get_chats();
                    while(!chats.empty())
                    {
                        std::cout << chats.back().name << std::endl;
                        chats.pop_back();
                    }
                }
                if(go == 'j')
                {
                    std::cout << "Введи название чата и пароль, к которому хочешь присоединится" << std::endl;
                    std::string login, password;
                    std::cin >> login >> password;
                    nathan.connectNewChat(login, password);
                    std::vector<Chat> chats = nathan.get_chats();
                    while(!chats.empty())
                    {
                        std::cout << chats.back().name << std::endl;
                        chats.pop_back();
                    }
                }
                if(go == 's')
                {
                    std::cout << "Введи сообщение и чат, в который хочешь отправить" << std::endl;
                    std::string mes, chat;
                    std::cin >> mes >> chat;
                    nathan.sendMessage(make_shared<Message>(mes), chat);
                    std::vector<Message> chats = nathan.get_messages(chat);
                    for(auto mes : chats)
                    {
                        std::cout << mes.mes << std::endl;
                    }
                }
                if(go =='m')
                {
                    std::cout << "Введи сообщения из какого чата хочешь посмотреть" << std::endl;
                   std::vector<Chat> chats = nathan.get_chats();
                    while(!chats.empty()) {
                        std::cout << chats.back().name << std::endl;
                        chats.pop_back();
                    }
                    std::string mes, chat;
                    std::cin >> chat;
                    std::vector<Message> messages = nathan.get_messages(chat);
                    for(auto mes : messages)
                    {
                        std::cout << mes.mes << " - "<< mes.name_sender << std::endl;
                    }
                }
                if(go == 'e')
                {
                    nathan.goodbye();
                    break;
                }
            }
            break;
        }

    }
    return 0;
}