#pragma once

#include "Server.h"
#include "Client.h"

class Peer {
public:
    Peer(tcp::endpoint);
    void Connect(std::string, int);
    void Accept();
    void Run();
protected:
    Server server;
    Client client;
private:

};