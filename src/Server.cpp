#include <string>
#include <iostream>
// #include "../src/Router.cpp"
#include "../include/Server.h"


bool Server::listen(){
  std::cout << "listen...\n";

  // Status: proceeded without any errors
  return 0;
}

bool Server::GetConfig(std::string FileName){
  srand(time(0));

  if( rand() % 2 ){
    std::cout << "I've got a config\n";
    return 0;
  }
  else{
    std::cout << "An error occured. Try once more to succeed\n";
    return 1;
  }
}
