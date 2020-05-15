#include <iostream>
#include "Peer.h"
#include <future>

int main() {
    Peer peer(tcp::endpoint(tcp::v4(), 5000));
    peer.Accept();

    Peer pppp(tcp::endpoint(tcp::v4(), 3000));
    pppp.Accept();

    peer.Connect("127.0.0.1", 3000);
    pppp.Connect("127.0.0.1", 5000);

    while(1) {}
    return 0;
}