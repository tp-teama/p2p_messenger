#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <memory>

using boost::asio::ip::tcp;
namespace asio = boost::asio;
using boost::system::error_code;


class Server {
public:
    explicit Server(const tcp::endpoint& endp)
            : acceptor(ioService, endp) {
        acceptor.set_option(tcp::acceptor::reuse_address(true));
    }
    
    void Run();
    void Close();

private:
    asio::io_service ioService;
    tcp::acceptor acceptor;
    std::vector<std::shared_ptr<tcp::socket>> vectorSocket; // client vector

    void accept();
};
