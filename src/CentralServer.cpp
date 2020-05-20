#include <CentralServer.h>

bool CentralServer::AddUser(o_uuid user_id, string ip, string username) {
    if (ip == ""){
        return false;
    }

    User u;
    u.public_key = "";
    //todo: add public key
    u.ip_adress = ip;
    u.username = username;
//    o_uuid user_id = b_uuid::random_generator()();
    users.insert(pair<o_uuid, User>(user_id, u));

    return true;
}

bool CentralServer::UpdateIpAdress(o_uuid user_id, string newIp) {
    if (newIp == "" || users.find(user_id) == users.end()){
        return false;
    }

    std::map<o_uuid, User>::iterator it = users.find(user_id);
    it->second.ip_adress = newIp;
}

User CentralServer::GetUserByID(o_uuid user_id) {
    if (users.find(user_id) == users.end()){
        return User{};
    }

    User u = users.find(user_id)->second;
    return u;
}

void CentralServer::SendBack() {

}

void CentralServer::ParseRequest() {

}
