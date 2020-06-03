#include <vector>
#include <stdlib.h>
#include "frontend.h"
#include <ncurses.h>
#include "App.h"
#include "ncurscript.h"

using namespace std;


void MessengerUI::Run(){
	initscr();
	curs_set(0);
	keypad(stdscr, TRUE);

	User usr(0);

	if( !selectFunction(usr) ){
		delwin(stdscr);
		endwin();
		return;
	}

	if( chat_window(usr) ){
		usr.goodbye();
		delwin(stdscr);
		endwin();
		return;
	}

	usr.goodbye();
	delwin(stdscr);
	endwin();
}


void MessengerUI::UpdateMsgs( int chat_id, vector<char> v ){}
