#include <iostream>
#include <string>
#include <map>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

using namespace std;

namespace b_uuid = boost::uuids;
typedef boost::uuids::uuid o_uuid;

struct User{
    string public_key;
    string ip_adress;
    string username;
};

class CentralServer{
public:
    bool AddUser(o_uuid user_id, string ip, string username);
    bool UpdateIpAdress(o_uuid user_id, string newIp);
    void ParseRequest();
    void SendBack();
    User GetUserByID(o_uuid user_id);
private:
    map<o_uuid , User> users;
};