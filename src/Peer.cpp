#include "Peer.h"
#include <functional>
#include <thread>
#include "Message.h"
#include "Chat.h"
#include "Storage.h"

Peer::Peer(tcp::endpoint ep)
        : server(ep) {}

Peer::~Peer() {}

void Peer::Accept() {
    std::thread threadServerRunning(&Server::Run, &server);
    threadServerRunning.detach();
}

void Peer::SendToPort(const std::string &request, int port) {
    client.Connect(port);
<<<<<<< HEAD
    client.GetSocket().send(asio::buffer(request));
    if (request.find("command:join_chat") != std::string::npos) {
        auto buf = std::make_shared<std::vector<char>>(1024);
        client.GetSocket().receive(asio::buffer(*buf));
        std::string response = buf->data();
        if (response == "res:true") {
=======
    client.GetSocket().async_send(asio::buffer(request), std::bind(&Peer::handleSendToPort,
                                                                   this, std::placeholders::_1, std::placeholders::_2, request));
    client.Close();
}

void Peer::saveChat(const std::string &request) {
    Storage db;
    std::string info = request.substr(request.find("chat_name:"), request.find(" password:"));
    db.AddChat(info.substr(info.find(':'), info.find(' ')),
               info.substr(info.substr(info.find("password:"),
                                       info.length()).find(':') + 1, info.length()));
}

std::string Peer::Authorize(const std::string& login, const std::string& password) {
    std::string request = "command:login username:" + login + " password:" + password;
    client.Connect(5000);
    client.GetSocket().send(asio::buffer(request));
    auto buf = std::make_shared<std::vector<char>>(1024);
    client.GetSocket().receive(asio::buffer(*buf));
    std::string response = buf->data();
    client.Close();
    return response.substr(response.find(':') + 1, response.length());
}
void Peer::handleSendToPort(const error::error_code &ec, size_t bytes, const std::string &request) {
    if (!ec) {
        if (request.find("command:join_chat") != std::string::npos) {
            auto buf = std::make_shared<std::vector<char>>(1024);
            client.GetSocket().async_receive(asio::buffer(*buf), std::bind(&Peer::handleSendToPortReceive,
                                                                           this, std::placeholders::_1, std::placeholders::_2, buf->data(), request));

        } else if (request.find("command:create_chat") != std::string::npos) {
>>>>>>> 86b49df860fce2ca11af06ba1154200174d383f4
            saveChat(request);
        }
    } else if (request.find("command:create_chat") != std::string::npos) {
        saveChat(request);
    }
    client.Close();
}

void Peer::saveChat(const std::string &request) {
    Storage db;
    std::string info = request.substr(request.find("chat_name:"), request.find(" password:"));
    db.AddChat(info.substr(info.find(':') + 1, info.find(" password:") - info.find(':') - 1),
               info.substr(info.find(' ')).substr(info.find(':') + 1));
}
bool Peer::SendToChat(std::shared_ptr<Message> message, std::shared_ptr<Chat> chat, const o_uuid& uuid) {
    std::string request = "command:get_chat_name chat_name:" + chat->name + " user_id:" + to_string(uuid);
    client.Connect(5000);
    client.GetSocket().send(asio::buffer(request));
    auto buf = std::make_shared<std::vector<char>>(1024);
    client.GetSocket().receive(asio::buffer(*buf));
    std::string response = buf->data();
    int port = stoi(response.substr(response.find(':') + 1, response.length()));
    if (!port) {
        return false;
    }
    std::string requestMessage = "chat_name:" + chat->name + " sender_id:" + to_string(uuid)
                                 + " message:" + message->mes;
    client.Close();
    SendToPort(requestMessage, port);
    return true;
}

void Peer::Receive() {

}

<<<<<<< HEAD
std::string Peer::Authorize(const std::string& login, const std::string& password) {
    std::string request = "command:login username:" + login + " password:" + password;
    client.Connect(5000);
    client.GetSocket().send(asio::buffer(request));
    auto buf = std::make_shared<std::vector<char>>(1024);
    client.GetSocket().receive(asio::buffer(*buf));
    std::string response = buf->data();
    client.Close();
    return response.substr(response.find(':') + 1, response.length());
}
=======

>>>>>>> 86b49df860fce2ca11af06ba1154200174d383f4

std::string Peer::Registration(const std::string& request) {
    client.Connect(5000);
    client.GetSocket().send(asio::buffer(request));
<<<<<<< HEAD
    auto buf = std::make_shared<std::vector<char>>(1024);
    client.GetSocket().receive(asio::buffer(*buf));
    std::string response = buf->data();
    client.Close();
=======
    auto buf = make_shared<std::vector<char>>(1024);
    std::string response;
    client.GetSocket().receive(asio::buffer(*buf, 1024));
    response = buf->data();
>>>>>>> 86b49df860fce2ca11af06ba1154200174d383f4
    return response.substr(response.find(':') + 1, response.length());
}