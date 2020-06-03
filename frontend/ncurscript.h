#pragma once

#define NCURSES_NOMACROS

#include "App.h"
#include "vector"
#include "User.h"

#define BACKSPACE 7
#define ENTER 10
#define ESC 27
#define UP 3
#define DOWN 2
#define LEFT 4
#define RIGHT 5

using namespace std;

bool login(User& usr, bool isReg);
bool login_try(User& usr, string& name, string& p455wd, Action& act);
bool chat_window(User& usr);
bool selectFunction(User& usr);
bool isempty(string s);
void ChatLogFunc(User& usr, bool isCreate, vector<Chat>& chats_v);
bool tryAuth(User& usr, string name, string pass, bool isCreate);
void refocus(int& cur_sel, int& prev_sel, int& cur_chat, bool up, string text, vector<Chat> v, const int max_focus, Action login_act);
Chat makeChat(string name);
