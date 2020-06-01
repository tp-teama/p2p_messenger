#ifndef NCURSCRIPT
#define NCURSCRIPT

#include "constants.cpp"
#include "App.cpp"

#define BACKSPACE 127
#define ENTER 10
#define TAB 9
#define ESC 27
#define I_KEY 105
#define K_KEY 107

#define PORT 1337

using namespace std;


bool login();
bool login_try(string& name, string& p455wd, Action& act);
bool chat_window();
void sendmsg(const string msg){}
void refocus(
	int& cur, int& prev, bool up, vector<Chat> v, const int max_focus
	);

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
	int cur_chat = 0;
	string msg = "";

	Action init_act(DispChMsgActionType);
	init_act.payload.chats = chats_v;

	Action upd_act(UpdMsgActionType);

	App(Default, init_act);

	char ch;
	bool status = 0;
	int sel_chat = 0;
	int prev_sel = 0;
	int max_focus = chats_v.size() + 2;

	// We're in library, so keep silence
	noecho();
	while( !status ){
		switch( ch = getch() ){
		case BACKSPACE:
			if( !msg.size() ){
				msg.pop_back();
				upd_act.payload.text = msg;
				App(Default, upd_act);
			}
			break;
		case ENTER:
			sendmsg(msg);
			msg = "";
			upd_act.payload.text = msg;
			App(Input, Action(AddMsgActionType));
			break;
		case I_KEY:
			refocus(sel_chat, prev_sel, 1, chats_v, max_focus);
			break;
		case K_KEY:
			refocus(sel_chat, prev_sel, 0, chats_v, max_focus);
			break;
		case ESC:
			return 1;
		default:
			msg += ch;
			upd_act.payload = ActionsPayload(msg);
			App(Input, upd_act);
			break;
		}
	}
	echo();

	return 0;
}

void refocus(
		int& cur, int& prev, bool up,
		vector<Chat> v, const int max_focus
		){
	prev = cur;
	if( up )
		cur = (cur - 1 < 0 )? (max_focus - 1): cur-1;
	else
		cur = (cur + 1) % max_focus;

	Action act(UnfocusActionType);
	if( prev == max_focus - 1 ){
		App(CreateArea, act);
	}else if( prev == max_focus - 2 ){
		App(JoinArea, act);
	}else{
		act.payload = ActionsPayload(FocAction(prev, v));
		App(ChatListArea, act);
	}

	act.type = FocusActionType;
	if( cur == max_focus - 1 ){
		App(CreateArea, act);
	}else if( cur == max_focus - 2 ){
		App(JoinArea, act);
	}else{
		act.payload = ActionsPayload(FocAction(cur, v));
		App(ChatListChatBlockArea, act);
	}
}


#endif NCURSCRIPT
