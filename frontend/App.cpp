// Add exceptions for EXXXTRA Small sizes such as less than basic titles or
//   less that much it's impossible to read(any: vert or horiz)
// Make it colored
// Enable keyboard events 
// Create label inside of input area
// Enable resizing
// Add chat line generator
// Add nice corners
// Some functions(as utilies as elements) work unefficient

#include <string>
#include <vector>
#include <ncurses.h>
#include "utilities.cpp"
#include "App.h"

#define HOR ACS_HLINE
#define VER ACS_VLINE
#define HOR_SEC '-'
#define PSWD_SYM '*'

using namespace std;


void App(){
	initscr();
	curs_set(0);

	// let height and width be the last block of each axis position
	int height = 0;
	int width = 0;
	getmaxyx(stdscr, height, width);
	height--;
	width--;

	if( 0 ){
		AppAuth(0, 0, height, width);
	} else {
		Panel(0, 0, height, width/4);

		mvwvline(stdscr, 0, width/4 + 1, VER, height+1);

		Chat(0, width/4 + 2, height, width - width/4 - 2);
	}
	
	wrefresh(stdscr);

	getch();

	endwin();
}

void Panel(int y0, int x0, int height, int width){
	ChatList(y0, x0, height, width);

	mvwhline(stdscr, height - 3, 0, HOR, width+1);

	JoinButton(height - 2, 0, 1, width);

	mvwhline(stdscr, height - 1, 0, HOR, width+1);

	CreateChat(height, 0, 1, width);
}

void ChatList(int y0, int x0, int height, int width){
	for( int i = 0; i < (int)chats.size() && (i+1)*3 < height; ++i ){
		mvwprintw(stdscr, i*3, 1, trunc(chats[i].name, width).c_str());

		mvwprintw(
			stdscr, i*3+1, 0, trunc(chats[i].last_msg, width+1).c_str()
			);

		mvwhline(stdscr, i*3+2, 0, HOR_SEC, width+1);
	}
}

void JoinButton(int y0, int x0, int height, int width){
	mvwaddstr(stdscr, y0, (width - 8)/2, "Join Chat");
}

void CreateChat(int y0, int x0, int height, int width){
	mvwaddstr(stdscr, y0, (width - 10)/2, "Create Chat");	
}

void Chat(int y0, int x0, int height, int width){
	if( 0 ){
		ChatAuth(y0, x0, height, width);
	} else {
		ChatHeader(y0, x0, 1, width);

		mvwhline(stdscr, y0 + 1, x0, HOR, width + 1);

		ChatBlock(y0 + 2, x0, height - 4, width);

		mvwhline(stdscr, height - 1, x0, HOR, width + 1);

		InputField(height, x0, 1, width);
	}
}

void ChatHeader(int y0, int x0, int height, int width){
	string chat_name = chats[cur_chat].name;
	int n_mem = chats[cur_chat].members;
	string members_str = 
		((n_mem % 1 == 0) && (n_mem % 100 != 11)) ? "member" : "members";
		
	string header = chat_name + "   " + to_string(n_mem) + " " + members_str;

	mvwaddstr(stdscr, y0, x0 + 1, header.c_str());
}

void InputField(int y0, int x0, int height, int width){
	mvwaddstr(stdscr, y0, x0, "Hello everyone, my name is|");	
}

void ChatBlock(int y0, int x0, int height, int width){
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

void ChatAuth(int y0, int x0, int height, int width){
	mvwaddstr(
		stdscr, 
		y0 + (height - 1)/2 - 1, x0 + (width - 19)/2,
		"Enter chat password"
		);

	mvwhline(
		stdscr, 
		y0 + (height - 1)/2 + 1, x0 + (width - 7)/2,
		PSWD_SYM, 7
		);
}

void AppAuth(int y0, int x0, int height, int width){
	mvwaddstr(
		stdscr, 
		y0 + (height - 1)/2 - 1, x0 + (width - 22)/2,
		"Enter account password"
		);

	mvwhline(
		stdscr, 
		y0 + (height - 1)/2 + 1, x0 + (width - 7)/2,
		PSWD_SYM, 7
		);
}