// Add exceptions for EXXXTRA Small sizes such as less than basic titles or
//   less that much it's impossible to read(any: vert or horiz)
// Make it colored
// Enable keyboard events 
// Create label inside of input area
// Enable resizing
// Add chat line generator
// Add nice corners
// Some functions(as utilies as elements) work unefficient
// Few key functions: UI update, input, msgs update cos of new msg
// Colors
// Adapt keyboard keys compatibility
// Background color for input
// Perform in-place coordinate transform and any func 
// Make AppAuth 5 cents more effient

#ifndef MESSENGER_FRONTEND
#define MESSENGER_FRONTEND

#include <cstring>
#include <string>
#include <vector>
#include <ncurses.h>
#include "App.h"
#include "utilities.cpp"
#include "constants.cpp"
#include "lang/en.cpp"

#define HOR ACS_HLINE
#define VER ACS_VLINE
#define HOR_SEC '-'
#define VER_SEC '|'
#define PSWD_SYM '*'

// init_pair(index, foreground, background);
#define INVERTED 0

using namespace std;


void App(bool start, bool end, WindowType app_win, Action act){
	if( start ){
		initscr();
		curs_set(0);
	}

	// let height and width be the last block of each axis position
	int height = 0;
	int width = 0;
	getmaxyx(stdscr, height, width);
	height--;
	width--;


	if( app_win == Auth ){
		AppAuth(0, 0, height, width, app_win, act);
	}else if( app_win == Welcome ){
		Greeter(0, 0, height, width, app_win, act);
	}else{
		Panel(0, 0, height, width/4, app_win, act);

		mvwvline(stdscr, 0, width/4 + 1, VER, height+1);

		ChatWindow(0, width/4 + 2, height, width - width/4 - 2, app_win, act);
	}
	
	wrefresh(stdscr);

	if( end )
		endwin();
}

void Panel(int y0, int x0, int height, int width, WindowType app_win, Action act){

	ChatList(y0, x0, height, width, app_win, act);

	mvwhline(stdscr, height - 3, 0, HOR, width+1);

	JoinButton(height - 2, 0, 1, width, app_win, act);

	mvwhline(stdscr, height - 1, 0, HOR, width+1);

	CreateChat(height, 0, 1, width, app_win, act);
}

void ChatList(int y0, int x0, int height, int width, WindowType app_win, Action act){

	vector<Chat> chats = act.payload.chats.chat_v;
	int cur_chat = act.payload.chats.cur_chat;

	for( int i = 0; i < cur_chat && (i+1)*3 < height; ++i ){
		mvwprintw(stdscr, i*3, 1, trunc(chats[i].name, width).c_str());

		mvwprintw(
			stdscr, i*3+1, 0, trunc(chats[i].last_msg, width+1).c_str()
			);
		mvwhline(stdscr, i*3+2, 0, HOR_SEC, width+1);
	}
	mvwprintw(stdscr, cur_chat*3, 1, trunc(chats[cur_chat].name, width).c_str());
	attron(A_REVERSE);
	mvwprintw(
		stdscr, cur_chat*3+1, 0, trunc(chats[cur_chat].last_msg, width+1).c_str()
		);
	attroff(A_REVERSE);
	mvwhline(stdscr, cur_chat*3+2, 0, HOR_SEC, width+1);
	for( int i = cur_chat+1; i < (int)chats.size() && (i+1)*3 < height; ++i ){
		mvwprintw(stdscr, i*3, 1, trunc(chats[i].name, width).c_str());

		mvwprintw(
			stdscr, i*3+1, 0, trunc(chats[i].last_msg, width+1).c_str()
			);
		mvwhline(stdscr, i*3+2, 0, HOR_SEC, width+1);
	}
}

void JoinButton(int y0, int x0, int height, int width, WindowType app_win, Action act){
	mvwaddstr(stdscr, y0, (width - strlen(JOIN_CHAT))/2, JOIN_CHAT);
}

void CreateChat(int y0, int x0, int height, int width, WindowType app_win, Action act){
	mvwaddstr(stdscr, y0, (width - strlen(CREATE_CHAT))/2, CREATE_CHAT);	
}

void ChatWindow(int y0, int x0, int height, int width, WindowType app_win, Action act){
	if( app_win == ChatLogin ){
		ChatAuth(y0, x0, height, width, app_win, act);
	} else {
		ChatHeader(y0, x0, 1, width, app_win, act);

		mvwhline(stdscr, y0 + 1, x0, HOR, width + 1);

		ChatBlock(y0 + 2, x0, height - 4, width, app_win, act);

		mvwhline(stdscr, height - 1, x0, HOR, width + 1);

		InputField(height, x0, 1, width, app_win, act);
	}
}

void ChatHeader(int y0, int x0, int height, int width, WindowType app_win, Action act){

	string chat_name = act.payload.chats.chat_v[act.payload.chats.cur_chat].name;
	int n_mem = 5;
	string members_str = MEMBERS;

	string header = chat_name + "   " + to_string(n_mem) + " " + members_str;

	mvwaddstr(stdscr, y0, x0 + 1, header.c_str());
}

void InputField(int y0, int x0, int height, int width, WindowType app_win, Action act){
	mvwaddstr(stdscr, y0, x0, TEST_MSG);	
}

void ChatBlock(int y0, int x0, int height, int width, WindowType app_win, Action act){
	vector<Message> msgs = act.payload.chats.chat_v[act.payload.chats.cur_chat].msgs;
	string header;
	vector<string> lines;
	int y = y0 + height;
	for( int m = msgs.size() - 1; y >= y0 && m >= 1; --m ){
		lines = wrap_text(msgs[m].text, width);
		for( int l = lines.size() - 1; y >= y0 && l >= 0; --l )
			mvwaddstr(stdscr, y--, x0, lines[l].c_str());
		if(y >= y0)
			mvwaddstr(
				stdscr, y--, x0 + 2, 
				msg_header(msgs[m].name, msgs[m].timestamp).c_str()
				);
		if(y >= y0)
			mvwhline(stdscr, y--, x0, HOR_SEC, width + 1);
	}
	// the first one message, that should be bordered above
	if( y >= y0 ){
		lines = wrap_text(msgs[0].text, width);
		for( int l = lines.size() - 1; y >= y0 && l >= 0; --l )
			mvwaddstr(stdscr, y--, x0, lines[l].c_str());
		if(y >= y0)
			mvwaddstr(
				stdscr, y--, x0 + 2, 
				msg_header(msgs[0].name, msgs[0].timestamp).c_str()
				);
	}
}

void ChatAuth(int y0, int x0, int height, int width, WindowType app_win, Action act){
	mvwaddstr(
		stdscr, 
		y0 + (height - 1)/2 - 1, x0 + (width - strlen(ENTER_CHAT_PSWD))/2,
		ENTER_CHAT_PSWD
		);

	mvwhline(
		stdscr, 
		y0 + (height - 1)/2 + 1, x0 + (width - 7)/2,
		PSWD_SYM, 7
		);
}

void AppAuth(int y0, int x0, int height, int width, WindowType app_win, Action act){
	int name_len = 0, psswd_len = 0;
	string name, psswd;
	if( act.type == LoginActionType ){
		name = *act.payload.logact.name;
		psswd = *act.payload.logact.psswd;
		psswd_len = !psswd.empty() ? psswd.size() : 0;
		name_len = name.empty() ? 0 : name.size();
	}


	if( act.type == LoginActionType ){
		// Name
		mvwaddstr(
			stdscr, 
			y0 + (height - 1)/2 - 4, x0 + (width - strlen(ENTER_ACC_NAME))/2,
			ENTER_ACC_NAME
			);
		mvwhline(
			stdscr, 
			y0 + (height - 1)/2 - 2, x0 + (width - name_len - 1)/2,
			' ', name_len + 2
			);
		if( !act.payload.logact.cur ){
			attron(A_REVERSE);
			mvwaddstr(
				stdscr, 
				y0 + (height - 1)/2 - 2, x0 + (width - name_len)/2,
				name.c_str()
				);
			attroff(A_REVERSE);
		}
		else 
			mvwaddstr(
				stdscr, 
				y0 + (height - 1)/2 - 2, x0 + (width - name_len)/2,
				name.c_str()
				);

		// Password
		mvwaddstr(
			stdscr, 
			y0 + (height - 1)/2 + 2, x0 + (width - strlen(ENTER_ACC_PSWD))/2,
			ENTER_ACC_PSWD
			);
		mvwhline(
			stdscr, 
			y0 + (height - 1)/2 + 4, x0,
			' ', width
			);
		if( act.payload.logact.cur ){
			attron(A_REVERSE);
			mvwhline(
				stdscr, 
				y0 + (height - 1)/2 + 4, x0 + (width - psswd_len)/2,
				PSWD_SYM, psswd_len
				);
			attroff(A_REVERSE);
		}
		else 
			mvwhline(
				stdscr, 
				y0 + (height - 1)/2 + 4, x0 + (width - psswd_len)/2,
				PSWD_SYM, psswd_len
				);
	}else if( act.type == WrongCredsActionType ){
		mvwaddstr(
			stdscr, 
			y0 + (height - 1)/2 - 7, x0 + (width - strlen(WRONG_CRED))/2,
			WRONG_CRED
			);
	}else{
		wclear(stdscr);
		// Name
		mvwaddstr(
			stdscr, 
			y0 + (height - 1)/2 - 4, x0 + (width - strlen(ENTER_ACC_NAME))/2,
			ENTER_ACC_NAME
			);

		// Password
		mvwaddstr(
			stdscr, 
			y0 + (height - 1)/2 + 2, x0 + (width - strlen(ENTER_ACC_PSWD))/2,
			ENTER_ACC_PSWD
			);
	}

	wrefresh(stdscr);
}

// Transform to more templatable
void Greeter(int y0, int x0, int height, int width, WindowType app_win, Action act){
	wclear(stdscr);	

	mvwaddstr(
		stdscr, 
		y0 + (height - 1)/2, x0 + (width - strlen(GREET_MSG("Cirno")))/2,
		GREET_MSG("Cirno")
		);

	wrefresh(stdscr);
}

#endif