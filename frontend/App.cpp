// Add exceptions for EXXXTRA Small sizes such as less than basic titles or
//   less that much it's impossible to read(any: vert or horiz)
// Make it colored, maybe
// Create placeholder inside of input area
// Enable resizing
// Few key functions: UI update, input, msgs update cos of new msg
// Colors, maybe
// Adapt keyboard keys compatibility
// Perform in-place coordinate transform and any-func-aviability
// Change actions payload
// Make switch(){case} instead of ifs of app_win and act
// Make display chat auth & creation on buttons select
// Make temporary text storing
// Change word wrap to split every line if it's size more expected
#include "App.h"
#include <cstring>
#include <string>
#include <vector>
#include <ncurses.h>
#include "utilities.h"
#include "constants.h"
#include "lang/en.h"

using namespace std;


void App(WindowType app_win, Action act){
	// let height and width be the last block of each axis position
	int height = 0;
	int width = 0;
	getmaxyx(stdscr, height, width);
	height--;
	width--;


	switch( app_win ){
		case AppAuth:
			LoginWindow(0, 0, height, width, app_win, act);
			break;
		case SignArea:
			Sign(0, 0, height, width, app_win, act);
			break;
		case ChatMainArea:
		case Input:
		case ChatLoginArea:
		case ChatSignArea:
			ChatWindow(0, width/4 + 2, height, width - width/4 - 2, app_win, act);
			break;
		case JoinArea:
		case CreateArea:
		case ChatListArea:
			Panel(0, 0, height, width/4, app_win, act);
			break;
		case ChatListChatBlockArea:
		case CreateChatArea:
		case JoinChatArea:
			Panel(0, 0, height, width/4, app_win, act);
			ChatWindow(0, width/4 + 2, height, width - width/4 - 2, app_win, act);
			break;
		case Select:
			SelectWindow(0, 0, height, width, app_win, act);
			break;
		default:
			mvwvline(stdscr, 0, width/4 + 1, VER, height+1);

			Panel(0, 0, height, width/4, app_win, act);

			ChatWindow(0, width/4 + 2, height, width - width/4 - 2, app_win, act);
	}
	wrefresh(stdscr);
}

void Panel(
		int y0, int x0, int height, int width, WindowType app_win, Action act
		){
	switch( app_win ){
	case JoinArea:
	case JoinChatArea:
		JoinButton(height - 2, 0, 1, width, app_win, act);
		break;
	case CreateChatArea:
	case CreateArea:
		CreateChat(height, 0, 1, width, app_win, act);
		break;
	case ChatListArea:
	case ChatListChatBlockArea:
		ChatList(y0, x0, height, width, app_win, act);
		break;
	default:
		ChatList(y0, x0, height, width, app_win, act);

		mvwhline(stdscr, height - 3, 0, HOR, width+1);
		mvwaddch(stdscr, height - 3, width + 1, ACS_RTEE);

		JoinButton(height - 2, 0, 1, width, app_win, act);

		mvwhline(stdscr, height - 1, 0, HOR, width+1);
		mvwaddch(stdscr, height - 1, width + 1, ACS_RTEE);

		CreateChat(height, 0, 1, width, app_win, act);
	}
}

void ChatList(
		int y0, int x0, int height, int width, WindowType app_win, Action act
		){
	vector<Chat> chats;
	int prev, cur;
	switch( act.type ){
	case DispChMsgActionType:
		chats = act.payload.chats;
		if( chats.size() )
		if( chats.size() ){
			attron(A_REVERSE);
			mvwprintw(
				stdscr, 0, 1, trunc(chats[0].name, width).c_str()
				);
			mvwhline(stdscr, 1, 0, ' ', width);
			// mvwprintw(
				// stdscr, 1, 0, trunc(chats[0].last_msg,
				// width+1).c_str()
				// );
			attroff(A_REVERSE);
		}

		if( chats.size() > 1 ){
			mvwhline(stdscr, 2, 1, HOR_SEC, width - 1);

			int i;
			for(
					i = 1;
					i < (int)chats.size() - 1 && (i+1)*3 < height;
					++i
					){
				mvwprintw(stdscr, i*3, 1, trunc(chats[i].name, width).c_str());

				// mvwprintw(
				// 	stdscr, i*3+1, 0, trunc(chats[i].last_msg, width+1).c_str()
				// 	);
				mvwhline(stdscr, i*3+2, 1, HOR_SEC, width - 1);
			}

			mvwprintw(stdscr, i*3, 1, trunc(chats[i].name, width).c_str());

			// mvwprintw(
			// 	stdscr, i*3+1, 0, trunc(chats[i].last_msg, width+1).c_str()
			// 	);
		}
		break;
	case UnfocusActionType:
		prev = act.payload.ua.num;
		chats = act.payload.ua.v;

		mvwprintw(stdscr, prev*3, 1, trunc(chats[prev].name, width).c_str());

		mvwhline(stdscr, prev*3+1, 0, ' ', width );
		// mvwprintw(
		// 	stdscr, prev*3+1, 0, trunc(chats[prev].last_msg, width+1).c_str()
		// 	);
		break;
	case FocusActionType:
		cur = act.payload.ua.num;
		chats = act.payload.ua.v;

		attron(A_REVERSE);
		mvwprintw(stdscr, cur*3, 1, trunc(chats[cur].name, width).c_str());

		// mvwprintw(
		// 	stdscr, cur*3+1, 0, trunc(chats[cur].last_msg, width+1).c_str()
		// 	);
		attroff(A_REVERSE);
		break;
	}
}

void JoinButton(
		int y0, int x0, int height, int width, WindowType app_win, Action act
		){
	switch( act.type ){
	case FocusActionType:
	case CrJoChActionType:
		attron(A_REVERSE);
		mvwaddstr(stdscr, y0, (width - strlen(JOIN_CHAT))/2, JOIN_CHAT);
		attroff(A_REVERSE);
		break;
	case UnfocusActionType:
	default:
		mvwaddstr(stdscr, y0, (width - strlen(JOIN_CHAT))/2, JOIN_CHAT);
	}
}

void CreateChat(
		int y0, int x0, int height, int width, WindowType app_win, Action act
		){
	switch( act.type ){
	case CrJoChActionType:
	case FocusActionType:
		attron(A_REVERSE);
		mvwaddstr(stdscr, y0, (width - strlen(CREATE_CHAT))/2, CREATE_CHAT);
		attroff(A_REVERSE);
		break;
	case UnfocusActionType:
	default:
		mvwaddstr(stdscr, y0, (width - strlen(CREATE_CHAT))/2, CREATE_CHAT);
	}
}

void ChatWindow(
		int y0, int x0, int height, int width, WindowType app_win, Action act
		){
	switch( app_win ){
	case JoinChatArea:
	case CreateChatArea:
	case ChatLoginArea:
		mvwaddch(stdscr, y0 + 1, x0 - 1, ACS_VLINE);
		mvwaddch(stdscr, height - 1, x0 - 1, ACS_RTEE);
		LoginWindow(y0, x0, height + 1, width + 1, app_win, act);
		break;
	case Input:
		// Change it while text is more than 2 lines

		// mvwhline(stdscr, height - 1, x0, HOR, width + 1);
		InputField(height, x0, 1, width, app_win, act);
		break;
	case ChatMainArea:
		ChatBlock(y0 + 2, x0, height - 4, width, app_win, act);
		break;
	case ChatSignArea:
		Sign(y0, x0, height, width, app_win, act);
		break;
	default:
		ChatHeader(y0, x0, 1, width, app_win, act);

		mvwhline(stdscr, y0 + 1, x0, HOR, width + 1);
		mvwaddch(stdscr, y0 + 1, x0 - 1, ACS_LTEE);

		ChatBlock(y0 + 2, x0, height - 4, width, app_win, act);

		mvwhline(stdscr, height - 1, x0, HOR, width + 1);
		mvwaddch(stdscr, height - 1, x0-1, ACS_PLUS);

		mvwhline(stdscr, height, x0, ' ', width + 1);

		InputField(height, x0, 1, width, app_win, act);
	}
}

void ChatHeader(
		int y0, int x0, int height, int width, WindowType app_win, Action act
		){
	string chat_name;
	int n_mem = 0;
	if( act.type == FocusActionType ){
		WINDOW* win = newwin(1, width, y0, x0);
		wclear(win);
		wrefresh(win);
		delwin(win);

		if( act.payload.ua.v.size() ){
			chat_name = act.payload.ua.v[act.payload.ua.num].name;
			// n_mem = act.payload.ua.v[act.payload.ua.num].members;
		}
	}else{
		if( act.payload.chats.size() ){
			chat_name = act.payload.chats[0].name;
			// n_mem = act.payload.chats[0].members;
		}
	}
	string members_str = MEMBERS;

	if( act.payload.chats.size() ){
		// string header = chat_name + "   " + to_string(n_mem) + " " + members_str;
		string header = chat_name;

		mvwaddstr(stdscr, y0, x0 + 1, header.c_str());
	}
}

void InputField(
		int y0, int x0, int height, int width, WindowType app_win, Action act
		){
	switch( act.type ){
	case FocusActionType:
		mvwaddstr(stdscr, y0, x0, act.payload.ua.text.c_str());
		break;
	case UpdMsgActionType:
		mvwaddstr(stdscr, y0, x0, act.payload.text.c_str());
		break;
	case ClearInputActionType:
		mvwhline(stdscr, y0, x0, ' ', width + 1);
		break;
	default:
		mvwaddstr(stdscr, y0, x0, "");
	}
}

void ChatBlock(
		int y0, int x0, int height, int width, WindowType app_win, Action act
		){
	vector<Message> msgs;
	if( act.type == FocusActionType || act.type == AddMsgActionType ){
		msgs = act.payload.ua.v[act.payload.ua.num].messages;

		WINDOW* win = newwin(height + 1, width + 1, y0, x0);
		wclear(win);
		wrefresh(win);
		delwin(win);
	}else{
		if( act.payload.chats.size() )
			msgs = act.payload.chats[0].messages;
	}

	string header;
	vector<string> lines;
	int y = y0 + height;
	for( int m = msgs.size() - 1; y >= y0 && m >= 1; --m ){
		lines = wrap_text(msgs[m].mes, width);
		for( int l = lines.size() - 1; y >= y0 && l >= 0; --l )
			mvwaddstr(stdscr, y--, x0, lines[l].c_str());
		if(y >= y0)
			mvwaddstr(
				stdscr, y--, x0 + 2,
				msg_header(msgs[m].name_sender, msgs[m].timestamp).c_str()
				);
		if(y >= y0)
			mvwhline(stdscr, y--, x0 + 1, HOR_SEC, width - 1);
	}
	// the first one message, that should be bordered above
	if( y >= y0 && msgs.size() > 0 ){
		lines = wrap_text(msgs[0].mes, width);
		for( int l = lines.size() - 1; y >= y0 && l >= 0; --l )
			mvwaddstr(stdscr, y--, x0, lines[l].c_str());
		if(y >= y0)
			mvwaddstr(
				stdscr, y--, x0 + 2,
				msg_header(msgs[0].name_sender, msgs[0].timestamp).c_str()
				);
	}
}

void LoginWindow(
		int y0, int x0, int height, int width, WindowType app_win, Action act
		){
	WINDOW* win = newwin(height, width, y0, x0);
	wclear(win);
	wrefresh(win);
	delwin(win);

	if( act.type == UnfocusActionType )
		return;

	string upper, lower;
	switch( act.type ){
		case UnfCrJoChActionType:
		case CrJoChActionType:
			upper = ENTER_CHAT_NAME;
			lower = ENTER_CHAT_PASS;
			break;
		case AppAuthRegActionType:
			upper = ENTER_ACC_NAME;
			lower = ENTER_ACC_PASS;
			break;
	}

	string name = act.payload.logact.name;
	string pass = act.payload.logact.pass;

	// Upper text
	mvwaddstr(
		stdscr,
		y0 + (height - 1)/2 - 4, x0 + (width - upper.size())/2,
		upper.c_str()
		);
	mvwhline(
		stdscr,
		y0 + (height - 1)/2 - 2, x0,
		' ', width
		);

	// Lower text
	mvwaddstr(
		stdscr,
		y0 + (height - 1)/2 + 2, x0 + (width - lower.size())/2,
		lower.c_str()
		);
	mvwhline(
		stdscr,
		y0 + (height - 1)/2 + 4, x0,
		' ', width
		);

	if( act.type == UnfCrJoChActionType )
		return;

	if( act.payload.logact.isUpper ){
		attron(A_REVERSE);
		mvwaddstr(
			stdscr,
			y0 + (height - 1)/2 - 2, x0 + (width - name.size())/2,
			name.c_str()
			);
		attroff(A_REVERSE);

		mvwaddstr(
			stdscr,
			y0 + (height - 1)/2 + 4, x0 + (width - pass.size())/2,
			pass.c_str()
			);
	}else{
		mvwaddstr(
			stdscr,
			y0 + (height - 1)/2 - 2, x0 + (width - name.size())/2,
			name.c_str()
			);
		attron(A_REVERSE);
		mvwaddstr(
			stdscr,
			y0 + (height - 1)/2 + 4, x0 + (width - pass.size())/2,
			pass.c_str()
			);
		attroff(A_REVERSE);
	}
}

// Transform to more templatable
void Sign(
		int y0, int x0, int height, int width, WindowType app_win, Action act
		){
	WINDOW* win = newwin(height, width, y0, x0);

	wclear(win);
	wrefresh(win);

	if( act.type == SignCharsActionType )
		mvwaddstr(
			stdscr,
			y0 + (height - 1)/2, x0 + (width - strlen(act.payload.chars))/2,
			act.payload.chars
			);
	else
		mvwaddstr(
			stdscr,
			y0 + (height - 1)/2, x0 + (width - act.payload.text.size())/2,
			act.payload.text.c_str()
			);
	getch();

	wclear(win);
	wrefresh(win);

	delwin(win);
}

void SelectWindow(
		int y0, int x0, int height, int width, WindowType app_win, Action act
		){
	wclear(stdscr);
	if( act.payload.isCreate ){
		attron(A_REVERSE);
		mvwaddstr(
			stdscr,
			y0 + height/2 - 2, x0 + (width - strlen(REG_USER))/2,
			REG_USER
		);
		attroff(A_REVERSE);

		mvwaddstr(
			stdscr,
			y0 + height/2 + 2, x0 + (width - strlen(REG_USER))/2,
			AUTH_USER
		);
	}else{
		mvwaddstr(
			stdscr,
			y0 + height/2 - 2, x0 + (width - strlen(REG_USER))/2,
			REG_USER
			);

		attron(A_REVERSE);
		mvwaddstr(
			stdscr,
			y0 + height/2 + 2, x0 + (width - strlen(AUTH_USER))/2,
			AUTH_USER
			);
		attroff(A_REVERSE);
	}
}
