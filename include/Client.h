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
    void Connect(int, std::string);
    void Close();
private:
    asio::io_service service;
    tcp::socket sock;
};