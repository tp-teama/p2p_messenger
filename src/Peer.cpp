#include "Peer.h"
#include <thread>
#include <future>

void Peer::Connect(int port, std::string Ip)
{
    client.Connect(port, Ip);
}
void Peer::Accept()
{
    server.Run();
}
void Peer::Run() {
    std::thread thr(&Peer::Accept, this);
    thr.detach();
    std::cout << "Lol";
}


int  main()
{
    tcp::endpoint ep(tcp::v4(), 5000);
    Peer peer(ep);
    peer.Run();
    return 0;
}