#pragma once
#include <string>
#include <iostream>
using namespace std;

class Config{
private:
    string listenPort;
    string dbAdress;
    int dbPort;
    string dbName;
    string dbPassword;
    string dbUser;
    string privateKeyPath;
public:
    Config();
    Config(string, string, int, string, string, string, string);
    Config GetConfig(string);
    string GetListenPort();
    string GetDbAdress();
    int GetDbPort();
    string GetDbName();
    string GetDbPassword();
    string GetDbUser();
    string GetKeyPath();
};