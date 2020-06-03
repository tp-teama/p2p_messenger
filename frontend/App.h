#pragma once
#define NCURSES_NOMACROS
#include <string>
#include "constants.h"

#define HOR ACS_HLINE
#define VER ACS_VLINE
#define HOR_SEC ACS_HLINE
#define PSWD_SYM '*'

void App(WindowType app_win, Action act);
void Panel(int y0, int x0, int height, int width, WindowType app_win, Action act);
void ChatWindow(int y0, int x0, int height, int width, WindowType app_win, Action act);
void ChatList(int y0, int x0, int height, int width, WindowType app_win, Action act);
void JoinButton(int y0, int x0, int height, int width, WindowType app_win, Action act);
void CreateChat(int y0, int x0, int height, int width, WindowType app_win, Action act);
void ChatHeader(int y0, int x0, int height, int width, WindowType app_win, Action act);
void ChatBlock(int y0, int x0, int height, int width, WindowType app_win, Action act);
void InputField(int y0, int x0, int height, int width, WindowType app_win, Action act);
void LoginWindow(int y0, int x0, int height, int width, WindowType app_win, Action act);
void Sign(int y0, int x0, int height, int width, WindowType app_win, Action act);
void SelectWindow(int y0, int x0, int height, int width, WindowType app_win, Action act);
