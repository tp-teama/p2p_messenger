#pragma once

#include <string.h>
#include <iostream>
#include "Config.h"
using namespace std;

class Listen{
private:
public:
    Listen() = delete;
    bool DoListen(Config);
};