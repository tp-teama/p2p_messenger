#include <vector>
#include <stdlib.h>
#include "frontend.h"
#include "App.cpp"
#include "ncurscript.cpp"

// #include "Peer.h"
// #include "User.h"
// #include "Storage.h"

using namespace std;


void MessengerUI::Run(){
	initscr();
	curs_set(0);
	keypad(stdscr, TRUE);

	// User usr(0);

	if( !login() ){
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


void MessengerUI::UpdateMsgs( int chat_id, vector<char> v ){
	;
}
