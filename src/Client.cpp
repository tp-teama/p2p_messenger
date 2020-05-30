#include "Client.h"

Client::Client(): sock(service) {}

void Client::Connect(int port) {
    tcp::endpoint ep(tcp::v4(), port);
    sock.open(ip::tcp::v4());
    sock.async_connect(ep, std::bind(&Client::handleConnect, this, std::placeholders::_1));
}

void Client::Close() {
    sock.close();
}

tcp::socket& Client::GetSocket() {
    return sock;
}

void Client::handleConnect(const error_code& ec) {
    if (!ec) {
        std::cout << sock.remote_endpoint();
    }
}