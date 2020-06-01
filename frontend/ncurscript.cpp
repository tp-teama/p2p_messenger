#ifndef NCURSCRIPT
#define NCURSCRIPT

#include "constants.cpp"
#include "App.cpp"
#include <algorithm>

#define BACKSPACE 7
#define ENTER 10
#define TAB 9
#define ESC 27
#define UP 3
#define DOWN 2

#define PORT 1337

using namespace std;


bool login();
bool login_try(string& name, string& p455wd, Action& act);
bool chat_window();
void sendmsg(const Message msgObj, vector<Chat>& v, int cur);
void refocus(
	int& cur_sel, int& prev_sel, int& cur_chat, bool up,
	vector<Chat> v, const int max_focus
	);
bool isempty(string s);


bool login(){
	Action act;

	act.type = NoneActionType;
	App(WindowType::Auth, act);

	while( 1 ){
		string p455wd;
		string name;

		if( login_try(name, p455wd, act) )
			return 0;
		if( p455wd == "c1rn015b4k4" && name == "Cirno" ){
			act.type = WelcomeActionType;
			ActionsPayload ap;
			ap.name = "Cirno";
			act.payload = ap;
			App(Welcome, act);
			getch();
			return 0;
		} else {
			act.type = WrongCredsActionType;
			App(Auth, act);
			getch();
			act.type = NoneActionType;
			App(WindowType::Auth, act);
		}
	}

	return 0;
}

bool login_try(string& name, string& p455wd, Action& act){
	noecho();

	act.type = LoginActionType;

	char ch;
	bool status = 0;


	int cur = 0; // 0 for name, 1 for passwd

	while( !status ){
		switch( ch = getch() ){
		case BACKSPACE:
			if( !name.empty() && !cur )
				name.pop_back();
			else if( !p455wd.empty() && cur )
			    p455wd.pop_back();
			break;
		case ENTER:
			status = 1;
			continue;
		case TAB:
			cur = !cur;
			break;
		case ESC:
			return 1;
		default:
			if( !cur ) name += ch;
			else p455wd += ch;
		}

		act.payload.logact.name = &name;
		act.payload.logact.psswd = &p455wd;
		act.payload.logact.cur = cur;

		App(Auth, act);
	}

	echo();

	return 0;
}

bool chat_window(){
	vector<struct Message> msgs = {
		{"Ilya", "I'm going to create interface", 1589284088},
		{"Misha", "Natan and me will set up networking", 1589296970},
		{
			"Michail",
			{
				"Have you ever though about something big? It gets heavier when "
				"I pull it up. Sometimes I train so hard I rip the skin!"
			},
			1589297462
		},
		{
			"Natan",
			{
				"I suddenly smeared the weekday map\n"
				"splashing paint from a glass;\n"
				"On a plate of aspic\n"
				"I revealed\n"
				"the ocean's slanted cheek.\n"
				"On the scales of a tin fish\n"
			},
			1589297762
		},
		{"Ilya", "I think, these B&W terminal blocks isn't Qt", 1589301142},
	};
	vector<struct Chat> chats_v = {
		{"Chat1", "I think, these B&W terminal blocks isn't Qt", 4, {msgs}},
		{"Chat2", "Come here and fight!", 1, {}},
		{"Chat3", "Where did you put Bertram's wooden snuff box?", 265, {}}
	};
	string username = "Ilya";

	Action msgs_act(DispChMsgActionType);
	msgs_act.payload.chats = chats_v;

	Action upd_act(UpdMsgActionType);

	App(Default, msgs_act);

	msgs_act.type = AddMsgActionType;

	char ch;
	bool status = 0;
	int cur_sel = 0;
	int prev_sel = 0;
	int cur_chat = 0;
	Message msgObj;
	string msg = "";

	// We're in library, so keep silence
	noecho();
	while( !status ){
		switch( ch = getch() ){
		case ENTER:
			App(Input, Action(ClearInputActionType));
			if( !isempty(msg) ){
				msgObj.set(username, msg, time(NULL));
				sendmsg( msgObj, chats_v, cur_chat);
				msgs_act.payload = ActionsPayload(
					FocAction(cur_chat, chats_v)
					);
				App(ChatMainArea, msgs_act);
			}
			msg = "";
			break;
		case UP:
			refocus(cur_sel, prev_sel, cur_chat, 1, chats_v, chats_v.size() + 2);
			break;
		case DOWN:
			refocus(cur_sel, prev_sel, cur_chat, 0, chats_v, chats_v.size() + 2);
			break;
		case ESC:
			status = 1;
			break;
		case BACKSPACE:
			if( msg.size() ){
				msg.pop_back();
				upd_act.payload.text = msg + " ";
				App(Input, upd_act);
			}
			break;
		default:
			msg += ch;
			// msg += to_string(sel_chat);
			upd_act.payload = ActionsPayload(msg);
			App(Input, upd_act);
			break;
		}
	}
	echo();

	return 0;
}

void refocus(
		int& cur_sel, int& prev_sel, int& cur_chat, bool up,
		vector<Chat> v, const int max_focus
		){
	prev_sel = cur_sel;
	if( up )
		cur_sel = (cur_sel - 1 < 0)? (max_focus - 1): (cur_sel - 1);
	else
		cur_sel = (cur_sel + 1) % max_focus;

	if( 0 <= cur_sel && cur_sel <= max_focus - 3 ){
		cur_chat = cur_sel;
	}

	Action act(UnfocusActionType);
	if( prev_sel == max_focus - 1 ){
		App(CreateArea, act);
	}else if( prev_sel == max_focus - 2 ){
		App(JoinArea, act);
	}else{
		act.payload = ActionsPayload(FocAction(prev_sel, v));
		App(ChatListArea, act);
	}

	act.type = FocusActionType;
	if( cur_sel == max_focus - 1 ){
		App(CreateArea, act);
	}else if( cur_sel == max_focus - 2 ){
		App(JoinArea, act);
	}else{
		act.payload = ActionsPayload(FocAction(cur_chat, v));
		App(ChatListChatBlockArea, act);
	}
}

void sendmsg(const Message msgObj, vector<Chat>& v, int cur){

	v[cur].msgs.push_back(msgObj);

}

bool isempty(string s){
	if( all_of(s.begin(), s.end(), [](char c){return isspace(c);}) )
		return 1;
	if( s.empty() )
		return 1;
	return 0;
}

#endif NCURSCRIPT
