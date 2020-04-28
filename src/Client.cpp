#include "Client.h"

bool Client::Join(int chat_id, string participant_ip){
  string method_data;
  Method mtd = join;
  bool res;
  // Filling somehow with chat_id and participant_ip
  res = SignUp(method_data);
  // res check
  res = CumPress(mtd, method_data);
  Request(participant_ip, data);
}

bool Client::GetMsgs(int chat_id, int offset, int count){
}
