#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <memory>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace b_uuid = boost::uuids;
typedef boost::uuids::uuid o_uuid;
using boost::asio::ip::tcp;
namespace asio = boost::asio;
namespace error = boost::system;


class Server {
public:
    explicit Server(const tcp::endpoint& ep)
            : acceptor(ioService, ep) {
        acceptor.set_option(tcp::acceptor::reuse_address(true));
    }
    void Run();
    void Close();

    tcp::acceptor& GetAcceptor() {
        return acceptor;
    }
private:
    asio::io_service ioService;
    tcp::acceptor acceptor;
    std::vector<std::shared_ptr<tcp::socket>> vectorSocket; // client vector

    void accept();
    void handleAccept(const error::error_code&, std::shared_ptr<tcp::socket>);
    void handleRead(const error::error_code&, size_t, const std::string&);
};
