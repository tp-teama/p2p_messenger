#include <iostream>

int main() {
    Client c;
    c.Connect(5000, "127.0.0.1");
    tcp::endpoint ep( tcp::v4(), 5000);
    Server s(ep);
    s.Run();
    return 0;
}