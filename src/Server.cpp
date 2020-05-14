#include "Server.h"
#include <array>

const int MAX_CONN = 1;

void Server::Run() {
    accept();
    ioService.run();
}

void Server::Close() {
    acceptor.close();
}

void Server::accept() {
    acceptor.listen(MAX_CONN);
    auto socket = std::make_shared<tcp::socket>(ioService);
    acceptor.async_accept(*socket, [&, socket] (error_code ec) {
        if (ec) {
            std::cerr << "accept failed: " << ec.message() << std::endl;
        } else {
            vectorSocket.emplace_back(socket);
            std::cout << socket->remote_endpoint() << std::endl;
            accept();
        }
    });
}
