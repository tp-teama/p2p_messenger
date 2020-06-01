#include <vector>
#include <stdlib.h>
#include "frontend.h"
#include "App.cpp"
#include "ncurscript.cpp"

using namespace std;


void MessengerUI::Run(){
	initscr();
	curs_set(0);
	keypad(stdscr, TRUE);

	// if( login() ){
	// 	delwin(stdscr);
	// 	endwin();
	// 	return;
	// }

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
