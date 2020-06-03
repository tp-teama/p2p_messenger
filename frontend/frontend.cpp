#include <vector>
#include <stdlib.h>
#include "frontend.h"
#include <ncurses.h>
#include "App.h"
#include "ncurscript.h"

// #include "../backend/include/Peer.h"
// #include "../backend/include/User.h"
// #include "../backend/include/Storage.h"

using namespace std;


void MessengerUI::Run(){
	initscr();
	curs_set(0);
	keypad(stdscr, TRUE);

	// User usr(0);

	if( !selectFunction() ){
		delwin(stdscr);
		endwin();
		return;
	}

	if( chat_window() ){
		delwin(stdscr);
		endwin();
		return;
	}

	delwin(stdscr);
	endwin();
}


void MessengerUI::UpdateMsgs( int chat_id, vector<char> v ){}
