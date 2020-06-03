#include "../include/Server.h"
#include "../include/Storage.h"
#include <boost/lexical_cast.hpp>


const int MAX_CONN = 5;

void Server::Run() {
    accept();
    ioService.run();
}

void Server::Close() {
    acceptor.close();
}

void Server::accept() {
    acceptor.listen(MAX_CONN);
    auto socket = std::make_shared<tcp::socket>(ioService);
    acceptor.async_accept(*socket,std::bind(&Server::handleAccept,
                                            this, std::placeholders::_1, socket));
}

// "chat_id:id sender_id:id message:msg"
void Server::handleAccept(const error::error_code& ec, std::shared_ptr<tcp::socket> socket) {
    if (!ec) {
        vectorSocket.emplace_back(socket);
        std::cout << socket->remote_endpoint() << std::endl;
        auto buf = std::make_shared<std::vector<char>>(1024);
        asio::async_read(*socket, asio::buffer(*buf), std::bind(&Server::handleRead,
                                                                this, std::placeholders::_1, std::placeholders::_2, buf));
        std::string msg(buf->data());
        std::string chatName = msg.substr(msg.find(':') + 1, msg.find(' ') - msg.find(':') - 1);
        msg = msg.substr(msg.find(' ') + 1);
        std::string senderId = msg.substr(msg.find(':') + 1, msg.find(' ') - msg.find(':') - 1);
        msg = msg.substr(msg.find(' ') + 1);
        std::string message = msg.substr(msg.find(':') + 1);
        Storage db;
        db.AddMessage(senderId, chatName, message);
        accept();
    }
}


void Server::handleRead(const error::error_code& ec, size_t bytes, std::shared_ptr<std::vector<char>> buf) {
    if (!ec) {
        std::string msg = buf->data();
        std::cout << "привет" << std::endl;
        std::string chatName = msg.substr(msg.find(':') + 1, msg.find(' ') - msg.find(':'));
        int senderIdIndex = msg.substr(msg.find("sender_id:"),
                                       msg.length() - msg.find("sender_id:")).find(':') + 1;
        std::string senderId = msg.substr(senderIdIndex, msg.substr(senderIdIndex).length()
                                                         - msg.substr(senderIdIndex).find(" message:") - 1);
        std::string message = msg.substr(msg.substr(msg.find("message:")).find(':') + 1);

        Storage db;
        db.AddMessage(senderId, chatName, message);
    }
}
