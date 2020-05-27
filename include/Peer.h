#pragma once

#include "Server.h"
#include "Client.h"
#include "IReceivable.h"
#include "ISendable.h"
#include "Message.h"
#include "Chat.h"

class Peer
        : public ISendable
                , public IReceivable {
public:
    Peer(tcp::endpoint);
    virtual ~Peer();
    void Connect(int);
    void Accept();
    void SendToPort(const std::string&, int port) override;
    bool SendToChat(std::shared_ptr<Message> msg, std::shared_ptr<Chat>, const o_uuid&);
    void Receive() override;
    std::string Authorize(const std::string& login, const std::string& password);
    std::string Registration(const std::string& request);
protected:
    Server server;
    Client client;
private:
    void handleSendToPort(const error::error_code& ec, size_t bytes, const std::string& request);
    void saveChat(const std::string&);
    void handleSendToPortReceive(const error::error_code& ec, size_t bytes, const std::string& response, const std::string& request);
};