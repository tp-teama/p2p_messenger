#include "Server.h"
#include "Storage.h"
#include <boost/lexical_cast.hpp>


const int MAX_CONN = 1;

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
                                                                this, std::placeholders::_1, std::placeholders::_2, buf->data()));
        accept();
    }
}


void Server::handleRead(const error::error_code& ec, size_t bytes, const std::string& msg) {
    if (!ec) {
        std::string chatId = msg.substr(msg.find("chat_id:") + 1, msg.find(' '));
        std::string senderId = msg.substr(msg.find(chatId) + 2, msg.find(" message"));
        std::string message = msg.substr(msg.find(senderId) + 2, msg.length());
        Storage db;
        db.AddMessage(senderId, chatId, message);
    }
}