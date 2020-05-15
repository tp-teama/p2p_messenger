#pragma once

#include "Server.h"
#include "Client.h"

class Peer {
public:
    Peer(tcp::endpoint ep): server(ep), client()
    {

    }
    void Connect(int, std::string);
    void Accept();
    void Run();
protected:
    Server server;
    Client client;
private:

};