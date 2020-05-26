#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <Storage.h>

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
    string sql_chats;
    string sql_message;

    try {
        pqxx::connection conn("dbname = tp_mess user = postgres password = docker hostaddr = 127.0.0.1 port = 5432");
        if (conn.is_open()) {
            cout << "Opened database successfully: " << conn.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
            return 1;
        }

        sql_chats = "CREATE TABLE chats("  \
                   "chat_id bigserial constraint chats_pk primary key," \
                   "chat_password TEXT    NOT NULL," \
                   "chat_name           TEXT    NOT NULL);";


        sql_message = "CREATE TABLE message("  \
                   "message_id bigserial constraint msg_pk primary key," \
                   "message TEXT    NOT NULL," \
                   "sender_id bigint not null," \
                   "chat_id bigint not null constraint chat_id_fkey references chats);";

        pqxx::work W(conn);
        W.exec(sql_chats);
        W.commit();

        pqxx::work MSG(conn);
        MSG.exec(sql_message);
        MSG.commit();
        cout << "Table created successfully" << endl;
        conn.disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

Chat* Storage::GetUsersChats(uint id) {

}

int Storage::AddChat(string chat_name, string chat_password) {
    string sql_chat;

    try {
        pqxx::connection conn("dbname = tp_mess user = postgres password = docker hostaddr = 127.0.0.1 port = 5432");
        if (conn.is_open()) {
            cout << "Opened database successfully: " << conn.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
            return 1;
        }
        sql_chat = "INSERT INTO chats (chat_name, chat_password) "  \
         "VALUES ('" + chat_name + "', '" + chat_password + "'); ";

        pqxx::work W(conn);

        W.exec(sql_chat );
        W.commit();
        cout << "Inserted successfully" << endl;
        conn.disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

Chat Storage::GetChat(uint id) {
    string sql;
    Chat chat;

    try {
        pqxx::connection conn("dbname = tp_mess user = postgres password = docker hostaddr = 127.0.0.1 port = 5432");
        if (conn.is_open()) {
            cout << "Opened database successfully: " << conn.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
            return Chat{};
        }

        sql = "SELECT * from chats where chat_id = " + to_string(id);
        pqxx::nontransaction N(conn);
        pqxx::result R( N.exec( sql ));

        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            chat.chat_id = c[0].as<int>();
            chat.chat_password = c[1].as<string>();
            chat.chat_name = c[2].as<string>();
        }
        cout << "Select success" << endl;
        conn.disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return Chat{};
    }
    return chat;
}

void Storage::CloseDB() {
    (*database).disconnect();
}

int Storage::AddMessage(uint sender_id, uint chat_id, string msg) {
    string sql_mes;

    try {
        pqxx::connection conn("dbname = tp_mess user = postgres password = docker hostaddr = 127.0.0.1 port = 5432");
        if (conn.is_open()) {
            cout << "Opened database successfully: " << conn.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
            return 1;
        }
        sql_mes = "INSERT INTO message (message, sender_id, chat_id) "  \
         "VALUES ('" + msg + "', '" + to_string(sender_id) + "', '" + to_string(chat_id) + "'); ";

        pqxx::work W(conn);

        W.exec(sql_mes );
        W.commit();
        cout << "Inserted successfully" << endl;
        conn.disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

Message Storage::GetMsg(uint msg_id) {
    string sql;
    Message msg;

    try {
        pqxx::connection conn("dbname = tp_mess user = postgres password = docker hostaddr = 127.0.0.1 port = 5432");
        if (conn.is_open()) {
            cout << "Opened database successfully: " << conn.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
            return Message{};
        }

        sql = "SELECT * from message where message_id = " + to_string(msg_id);
        pqxx::nontransaction N(conn);
        pqxx::result R( N.exec( sql ));

        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            msg.message_id = c[0].as<int>();
            msg.msg = c[1].as<string>();
            msg.sender_id = c[2].as<int>();
            msg.chat_id = c[3].as<int>();
        }
        cout << "Select success" << endl;
        conn.disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return Message{};
    }
    return msg;
}
