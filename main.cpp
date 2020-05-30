#include <iostream>
#include "Peer.h"
#include <future>
#include "User.h"
#include "Storage.h"

int main() {
    std::cout << "Какой порт?" << std::endl;
    int port;
    std::cin >> port;
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
                std::cout << "Введи действие create_chat/join_chat" << std::endl;
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

            }
        }
    }
    while(1) {}
    return 0;
}