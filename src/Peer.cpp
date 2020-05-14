#include "Peer.h"
#include <functional>
#include <thread>


Peer::Peer(tcp::endpoint ep)
    : server(ep) {

}

void Peer::Connect(std::string ip, int port) {
    client.Connect(port, ip);
}

void Peer::Accept() {
    server.Run();
}

void Peer::Run() {
    Accept();
}

