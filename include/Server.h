#include <string>
// #include "../src/Router.cpp"

class Server{
  private:
    int ServerPort;
    std::string DBAddress;
    std::string DBPort;
  public:
    bool listen();
    bool GetConfig(std::string);
};
