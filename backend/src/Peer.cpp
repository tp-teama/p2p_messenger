#include "../include/Peer.h"
#include <functional>
#include <thread>
#include "../include/Message.h"
#include "../include/Chat.h"
#include "../include/Storage.h"

Peer::Peer(const tcp::endpoint& ep)
        : server(ep) {
    Accept();
}

Peer::~Peer() {}

void Peer::Accept() {
    std::thread threadServerRunning(&Server::Run, &server);
    threadServerRunning.detach();
}

bool Peer::SendToPort(const std::string &request, int port) {
    client.Connect(port);
    client.GetSocket().send(asio::buffer(request));
    if (request.find("command:join_chat") != std::string::npos) {
        auto buf = std::make_shared<std::vector<char>>(1024);
        client.GetSocket().receive(asio::buffer(*buf));
        std::string response = buf->data();
        if (response == "res:true") {
            saveChat(request);
            client.Close();
            return true;
        }
        client.Close();
        return false;
    } else if (request.find("command:create_chat") != std::string::npos) {
        saveChat(request);
        client.Close();
        return true;
    }
    client.Close();
    return false;
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
    int port = stoi(response.substr(response.find(':') + 1));
    if (!port) {
        return false;
    }
    std::string requestMessage = "chat_name:" + chat->name + " sender_id:" + message->name_sender
                                 + " message:" + message->mes;
    Storage db;
    db.AddMessage(message->name_sender, chat->name, message->mes);
    client.Close();
    SendToPort(requestMessage, port);
    return true;
}

void Peer::Receive() {

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

std::string Peer::Registration(const std::string& request) {
    client.Connect(5000);
    client.GetSocket().send(asio::buffer(request));
    auto buf = std::make_shared<std::vector<char>>(1024);
    client.GetSocket().receive(asio::buffer(*buf));
    std::string response = buf->data();
    client.Close();
    return response.substr(response.find(':') + 1, response.length());
}
