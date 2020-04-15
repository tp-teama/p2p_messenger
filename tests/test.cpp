#include "gtest/gtest.h"
#include <string>


extern "C" {
  #include "../src/Server.cpp"
  #include "../src/Router.cpp"
  #include "../src/Config.cpp"
  #include "../src/API.cpp"
  #include "../src/Listen.cpp"
  #include "../src/Storage.cpp"
}

struct conn {
  string address;
} db;


TEST( test, Test2 ){
  Config conf;
  Router rt;
  Server srv;
  Listen lst;
  API api;
  Storage strg;
  Chat ch;
  User usr;
  Storage strg;
  Message msg;

  db.address = "n0n3";
  string req = "n0n3";
  string emptystr = "";
  int x; // Any variable to be used as ref
  Chat chref; // Any variable to be used as chat ref
  vector<Chat> chats;
  int res;


  char* empty = NULL;
  printf("%s\n", "First pack started");
  EXPECT_EQ(1, conf.GetConfig(NULL));
  EXPECT_EQ(1, conf.GetConfig("not-working-path"));

  EXPECT_EQ(1, srv.Run());

  EXPECT_EQ(1, lst.Listen());

  EXPECT_EQ(1, rt.StartRouting());

  EXPECT_EQ(1, api.SendMessage(req));
  EXPECT_EQ(1, api.GetChat(req));
  EXPECT_EQ(1, api.GetAllMyChats(req));
  EXPECT_EQ(1, api.GetUser(req));
  EXPECT_EQ(1, api.UpdateUser(req));
  EXPECT_EQ(1, api.CreateUser(req));
  EXPECT_EQ(1, api.GetUsersByNick(req));

  EXPECT_EQ(1, chat.GetUsersByNick(req));
  EXPECT_EQ(1, chat.SendMessage(12, 12, "test", x));
  // To test inexisting chats
  EXPECT_EQ(1, chat.SendMessage(INT_MAX, 12, "test", x));
  EXPECT_EQ(1, chat.SendMessage(12, INT_MAX, "test", x));
  EXPECT_EQ(1, chat.GetChat(INT_MAX, res));
  chat.GetChat(INT_MAX, res), EXPECT_EQ(1, res);
  chat.GetAllMyChats(INT_MAX, res), EXPECT_EQ(1, res);
  EXPECT_EQ(1, chat.CreateChat(265, 265, x));
  EXPECT_EQ(1, chat.CreateChat(265, INT_MAX, x));
  EXPECT_EQ(1, chat.CreateChat(INT_MAX, 265, x));
  EXPECT_EQ(1, chat.CreateChat(INT_MAX, INT_MAX, x));
  if( !chat.CreateChat(0, 1, x) )
    EXPECT_EQ(1, chat.CreateChat(0, 1, x));

  EXPECT_EQ(1, msg.AddMessage());

  usr.GetUser(INT_MAX, res), EXPECT_EQ(1, res);
  EXPECT_EQ(1, usr.UpdateUser(INT_MAX, "New Name"));
  EXPECT_EQ(1, usr.CreateUser(usr));
  usr.GetUsersByNick("A19A",  res), EXPECT_EQ(1, res);
  usr.GetUsersByNick(emptystr, res), EXPECT_EQ(1, res);

  strg.GetUser(INT_MAX, res), EXPECT_EQ(1, res);
  EXPECT_EQ(1, strg.UpdateUser(INT_MAX, "nickname"));
  strg.CreateUser(usr, res), EXPECT_EQ(1, res);
  strg.GetUsersByNick("Nickname", res), EXPECT_EQ(1, res);
  strg.SendMessage(msg, res), EXPECT_EQ(1, res);
  strg.GetChat(INT_MAX, res), EXPECT_EQ(1, res);
  strg.GetAllMyChats(INT_MAX, res), EXPECT_EQ(1, res);
  EXPECT_EQ(1, strg.DeleteChat(INT_MAX));
  EXPECT_EQ(1, strg.CreateChat(INT_MAX, 2));
  EXPECT_EQ(1, strg.CreateChat(1, INT_MAX));
  if( strg.CreateChat(1, 2) )
    EXPECT_EQ(1, strg.CreateChat(1, 2));
  if( !strg.CreateChat(1, 2) )
    EXPECT_EQ(1, strg.CreateChat(1, 2))

  // Further positive tests will be aviable after basic functions realization
  // and after you step on from trial version and purchase the product
}
