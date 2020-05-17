#include <iostream>
#include <pqxx/pqxx>
#include <string>

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


int Storage::AddUser(string username) {
    string sql_user;

    try {
        pqxx::connection conn("dbname = tp_mess user = postgres password = docker hostaddr = 127.0.0.1 port = 5432");
        if (conn.is_open()) {
            cout << "Opened database successfully: " << conn.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
            return 1;
        }
        sql_user = "INSERT INTO users (username) "  \
         "VALUES ('" + username + "'); ";

        pqxx::work W(conn);

        W.exec( sql_user );
        W.commit();
        cout << "Inserted successfully" << endl;
        (*database).disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

User Storage::GetUser(int id) {
    string sql;
    User user = User{};

    try {
        pqxx::connection conn("dbname = tp_mess user = postgres password = docker hostaddr = 127.0.0.1 port = 5432");
        if (conn.is_open()) {
            cout << "Opened database successfully: " << conn.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
            return User{};
        }

        sql = "SELECT * from users where user_id = " + to_string(id);
        pqxx::nontransaction N(conn);
        pqxx::result R( N.exec( sql ));

        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            user.user_id = c[0].as<int>();
            user.username = c[1].as<string>();
        }
        cout << "Select success" << endl;
        conn.disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return User{};
    }
    return user;
}


void Storage::CloseDB() {
    (*database).disconnect();
}