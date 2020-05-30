#include <iostream>
#include "Peer.h"
#include "User.h"
#include "Storage.h"
#include <future>

int main() {
    std::cout << "Какой порт?" << std::endl;
    int port;
    std::cin >> port;
    char go = 'd';
    Storage s = Storage();
    s.Connect();
    // s.InitDB();
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
        }
    }

    while(1) {}
    return 0;
}