#include "../include/Config.h"
#include <iostream>
#include <string>
using namespace std;

string Config::GetListenPort(){
    return this->listenPort;
}
string Config::GetDbAdress(){
    return this->dbAdress;
}
int Config::GetDbPort(){
    return this->dbPort;
}
string Config::GetDbName(){
    return this->dbName;
}
string Config::GetDbPassword(){
    return this->dbPassword;
}
string Config::GetDbUser(){
    return this->dbUser;
}
string Config::GetKeyPath(){
    return this->privateKeyPath;
}
Config::Config(string listen, string db_adress , int db_port, string db_name, string db_password, string db_user, string key_path) {
    privateKeyPath = key_path;
    dbUser = db_user;
    dbPassword = db_password;
    listenPort = listen;
    dbAdress = db_adress;
    dbPort = db_port;
    dbName = db_name;
}

Config Config::GetConfig(string path) {
    cout << "getting and parsing config";
    return Config("listen", "dbAdress" , 1, "dbName", "dbPassword", "dbUser", "keyPath");
}

Config::Config() {

}
