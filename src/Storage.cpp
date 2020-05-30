#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include "Storage.h"

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
                   "chat_name           TEXT  unique  NOT NULL);";


        sql_message = "CREATE TABLE message("  \
                   "message_id bigserial constraint msg_pk primary key," \
                   "message TEXT    NOT NULL," \
                   "sender text not null," \
                   "chat_name text not null);";


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
            chat.password = c[1].as<string>();
            chat.name = c[2].as<string>();
        }
        cout << "Select success" << endl;
        conn.disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return Chat{};
    }
    return chat;
}

Chat Storage::GetChatByName(string chat_name) {
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

        sql = "SELECT * from chats where chat_name = '" + chat_name + "';";
        pqxx::nontransaction N(conn);
        pqxx::result R( N.exec( sql ));

        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            chat.chat_id = c[0].as<int>();
            chat.password = c[1].as<string>();
            chat.name = c[2].as<string>();
        }
        cout << "Select success" << endl;
        conn.disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return Chat{};
    }

    vector<Message> msgs;

    try {
        pqxx::connection conn("dbname = tp_mess user = postgres password = docker hostaddr = 127.0.0.1 port = 5432");
        if (conn.is_open()) {
            cout << "Opened database successfully: " << conn.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
            return Chat{};
        }

        sql = "SELECT * from message where chat_name = '" + chat.name + "';";
        pqxx::nontransaction N(conn);
        pqxx::result R( N.exec( sql ));

        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            Message msg;
//            msg.message_id = c[0].as<int>();
            msg.mes = c[1].as<string>();
            msg.name_sender = c[2].as<string>();
            msg.chat_name = c[3].as<string>();
            msgs.push_back(msg);
        }
        cout << "Select success" << endl;
        conn.disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return Chat{};
    }
    chat.messages = msgs;

    return chat;
}

vector<Chat> Storage::GetUsersChats() {
    vector<Chat> chats;
    string sql;

    try {
        pqxx::connection conn("dbname = tp_mess user = postgres password = docker hostaddr = 127.0.0.1 port = 5432");
        if (conn.is_open()) {
            cout << "Opened database successfully: " << conn.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
            return chats;
        }

        sql = "select * from chats";
        pqxx::nontransaction N(conn);
        pqxx::result R( N.exec( sql ));

        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            Chat chat;
            chat.chat_id = c[0].as<int>();
            chat.password = c[1].as<string>();
            chat.name = c[2].as<string>();
            chats.push_back(chat);
        }
        cout << "Select success" << endl;
        conn.disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return chats;
    }
    return chats;
}

void Storage::CloseDB() {
    (*database).disconnect();
}

int Storage::AddMessage(string sender, string chat_name, string msg) {
    string sql_mes;

    try {
        pqxx::connection conn("dbname = tp_mess user = postgres password = docker hostaddr = 127.0.0.1 port = 5432");
        if (conn.is_open()) {
            cout << "Opened database successfully: " << conn.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
            return 1;
        }
        sql_mes = "INSERT INTO message (message, sender, chat_name) "  \
         "VALUES ('" + msg + "', '" + sender + "', '" + chat_name + "'); ";

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
//            msg.message_id = c[0].as<int>();
            msg.mes = c[1].as<string>();
            msg.name_sender = c[2].as<string>();
            msg.chat_name = c[3].as<string>();
        }
        cout << "Select success" << endl;
        conn.disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return Message{};
    }
    return msg;
}

Message Storage::GetLastMsg(string chat_name) {
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

        sql = "SELECT * from message where chat_name = '" + chat_name + "' order by message_id DESC LIMIT 1";
        pqxx::nontransaction N(conn);
        pqxx::result R( N.exec( sql ));

        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
//            msg.message_id = c[0].as<int>();
            msg.mes = c[1].as<string>();
            msg.name_sender = c[2].as<string>();
            msg.chat_name = c[3].as<string>();
        }
        cout << "Select success" << endl;
        conn.disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return Message{};
    }
    return msg;
}