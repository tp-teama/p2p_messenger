#include <Client.h>

Client::Client(): sock(service){

}

void Client::Connect(int port, std::string Ip) {
    tcp::endpoint ep( ip::address::from_string(Ip), port);
    sock.open(ip::tcp::v4());
    sock.async_connect(ep, [&](){});
}

void Client::Close() {
    sock.close();
}

