#pragma once

#define NCURSES_NOMACROS

#include "App.h"
#include "vector"

#define BACKSPACE 7
#define ENTER 10
#define ESC 27
#define UP 3
#define DOWN 2
#define LEFT 4
#define RIGHT 5

using namespace std;

bool login(bool isReg);
bool login_try(string& name, string& p455wd, Action& act);
bool chat_window();
bool selectFunction();
bool isempty(string s);
void ChatLogFunc(bool isCreate, vector<Chat>& chats_v);
bool tryAuth(string name, string pass, bool isCreate);
void refocus(int& cur_sel, int& prev_sel, int& cur_chat, bool up, string text, vector<Chat> v, const int max_focus, Action login_act);
Chat makeChat(string name);