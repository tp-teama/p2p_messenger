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

  db.address = "n0n3";
  string req = "n0n3";


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
}
