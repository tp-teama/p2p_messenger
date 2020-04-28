#include <string>

class Config {
protected:
  int port;
  string dbpath;
public:
  Config(int port, string dbpath);
  Config(string confpath)
}

struct Message {
  string uuid;
  int datetime;
  string text;
}

enum Method {
  get_messages,
  message_send,
  join,
  get_ips,
}
