#pragma once
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

string trunc(string, int);
string msg_header(string, int);
string wrap(const string, size_t);
vector<string> split(const string&, char);
vector<string> wrap_text(string, size_t);
