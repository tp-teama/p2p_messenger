#include <Client.h>

Client::Client(): sock(service){

}

void Client::Connect(int port, std::string Ip) {
    tcp::endpoint ep( ip::address::from_string(Ip), port);
    sock.open(ip::tcp::v4());
    sock.async_connect(ep, [&](error_code ec){
        if (ec) {
            std::cerr << "Connect is failed: " << ec.message() << "\n";
        } else{
            std::cout << "Connect is fine" << std::endl;
        }
    });
}

void Client::Close() {
    sock.close();
}

