#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <memory>

using boost::asio::ip::tcp;
namespace asio = boost::asio;


class Server {
public:
    Server();
    void Run();
    void Accept();
    void Close();
private:
    asio::io_service ioService;
    tcp::acceptor acceptor;
};
