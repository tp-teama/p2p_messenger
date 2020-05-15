#pragma once

#include "Server.h"
#include "Client.h"
#include "IReceivable.h"
#include "ISendable.h"

class Peer
        : public ISendable
        , public IReceivable {
public:
    Peer(tcp::endpoint);
    void Connect(std::string, int);
    void Accept();
    void Send() override;
    void Receive() override;
protected:
    Server server;
    Client client;
private:

};