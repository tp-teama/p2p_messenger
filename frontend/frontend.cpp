#include <vector>
#include <stdlib.h>
#include "frontend.h"
#include "App.cpp"
#include "ncurscript.cpp"

// #include "../backend/include/Peer.h"
// #include "../backend/include/User.h"
// #include "../backend/include/Storage.h"

using namespace std;


void MessengerUI::Run(){
	initscr();
	curs_set(0);
	keypad(stdscr, TRUE);

	User usr(0);

	if( !selectFunction(usr) ){
		usr.goodbye();
		delwin(stdscr);
		endwin();
		return;
	}

	// Is not important, but usable for continuos extending
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


void MessengerUI::UpdateMsgs( int chat_id, vector<char> v ){
	;
}
