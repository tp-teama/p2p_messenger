#include <string>

class Server: Config {
public:
  bool RecvMsgs(string data);
  bool NotifyJoin();
  bool ReturnMsgs();
  bool CheckSign();
  

  bool listen();
}
