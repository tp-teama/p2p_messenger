#include <iostream>
#include <pqxx/pqxx>

using namespace std;

struct User{
    int user_id;
    string username;
};

class Storage{
public:
    Storage() : database(nullptr){}
    int Connect();
    int InitDB();
    int AddUser(string username);
    User GetUser(int id);
    void CloseDB();
private:
    pqxx::connection *database;
};