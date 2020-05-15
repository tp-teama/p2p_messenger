#include "Peer.h"
#include <functional>
#include <thread>


Peer::Peer(tcp::endpoint ep)
    : server(ep) {}

void Peer::Connect(std::string ip, int port) {
    client.Connect(port, ip);
}

void Peer::Accept() {
    std::thread threadServerRunning(&Server::Run, &server);
    threadServerRunning.detach();
}

void Peer::Send() {

}

void Peer::Receive() {

}
