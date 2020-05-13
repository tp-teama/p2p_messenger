#include "Server.h"
#include <array>

void Server::Run() {

}

void Server::Accept() {
    tcp::socket socket(ioService);
    acceptor.accept(socket);
}

void Server::Close() {
    acceptor.close();
}