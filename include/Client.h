#include <string>
#include "BasicClasses.h"

class Client: Config {
private:
  string private;
public:
  bool Join(int chat_id, string participant_ip);
  bool GetMsgs(int chat_id, int offset, int count);
  bool SendMsgs(int chat_id, std::vector<Message> msgs);
  bool GetIPs(int chat_id);
  bool Register(string uuid);
  bool SetIp(string new_ip);
  bool SignUp(string& data);

  bool Save();
  bool Load();
}
