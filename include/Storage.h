#include <iostream>
#include <pqxx/pqxx>

using namespace std;

class Storage{
public:
    Storage() : database(nullptr){}
    int Connect();
    int InitDB();
    void CloseDB();
private:
    pqxx::connection *database;
};