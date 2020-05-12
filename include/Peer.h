#pragma once

#include "Server.h"
#include "Client.h"

class Peer {
public:
    void Connect();
    void Accept();
    void Run();
protected:
    Server server;
    Client client;
private:

};