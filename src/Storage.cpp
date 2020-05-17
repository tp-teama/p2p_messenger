#include <iostream>
#include <pqxx/pqxx>

using namespace std;


int Storage::Connect() {
    try {
        pqxx::connection conn("dbname = tp_mess user = postgres password = docker hostaddr = 127.0.0.1 port = 5432");
        if (conn.is_open()) {
            cout << "Opened database successfully: " << conn.dbname() << endl;
            database = &conn;
        } else {
            cout << "Can't open database" << endl;
            return 1;
        }
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

int Storage::InitDB() {
    char * sql_user;

    try {
        pqxx::connection conn("dbname = tp_mess user = postgres password = docker hostaddr = 127.0.0.1 port = 5432");
        if (conn.is_open()) {
            cout << "Opened database successfully: " << conn.dbname() << endl;
            database = &conn;
        } else {
            cout << "Can't open database" << endl;
            return 1;
        }
        sql_user = "CREATE TABLE users("  \
  "user_id INT PRIMARY KEY     NOT NULL," \
  "username           TEXT    NOT NULL);";

        pqxx::work W(conn);

        W.exec( sql_user );
        W.commit();
        cout << "Table created successfully" << endl;
        conn.disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

void Storage::CloseDB() {
    (*database).disconnect();
}