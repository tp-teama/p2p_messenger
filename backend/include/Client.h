#pragma once

#include <boost/asio.hpp>
#include <iostream>

namespace asio =  boost::asio;
namespace ip = boost::asio::ip;
using boost::asio::ip::tcp;
using boost::system::error_code;
using boost::asio::streambuf;

class Client {
public:
    Client();
    void Connect(int);
    void Close();
    tcp::socket& GetSocket();
private:
    asio::io_service service;
    tcp::socket sock;

    void handleConnect(const error_code&);
};