#pragma once

#include <string>
#include <iostream>
#include "Config.h"
using namespace std;

class Listen{
private:
public:
    Listen();
    bool DoListen(Config);
};