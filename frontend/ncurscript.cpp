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
#define LEFT 4
#define RIGHT 5

#define PORT 1337

using namespace std;


bool login();
bool login_try(string& name, string& p455wd, Action& act);
bool chat_window();
void refocus(
	int& cur_sel, int& prev_sel, int& cur_chat, bool up, string text,
	vector<Chat> v, const int max_focus, Action login_act
	);
bool isempty(string s);
void ChatLogFunc(bool isCreate, vector<Chat>& chats_v);
bool tryAuth(string name, string pass, bool isCreate);
Chat makeChat(string name){
	Chat Ch; Ch.name = name; Ch.members = 1; return Ch;
}

bool login(){
	Action act;

	App(AppAuth, act);

	while( 1 ){
		string p455wd;
		string name;

		if( login_try(name, p455wd, act) )
			return 0;
		if( p455wd == "c1rn015b4k4" && name == "Cirno" ){
			act.payload.text = GREET_MSG("") + name ;
			App(SignArea, act);
			getch();
			return 0;
		}else{
			act.payload.text = WRONG_CRED;
			App(SignArea, act);
			getch();
			App(AppAuth, act);
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

		act.payload.logact.name = name;
		act.payload.logact.pass = p455wd;
		act.payload.logact.isUpper = cur;

		App(AppAuth, act);
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

	Action login_act(CrJoChActionType);
	login_act.payload = ActionsPayload(LoginAction("", "", 1));

	App(Default, msgs_act);

	msgs_act.type = AddMsgActionType;

	char ch;
	bool status = 0;
	int cur_sel = 0;
	int prev_sel = 0;
	int cur_chat = 0;
	Message msgObj;
	string msg = "";
	bool isLeft = 1;
	string name;
	string pass;

	// We're in library, so keep silence
	noecho();
	while( !status ){
		switch( ch = getch() ){
		case ENTER:
			if( cur_sel != cur_chat )
				continue;
			App(Input, Action(ClearInputActionType));
			if( !isempty(msg) ){
				msgObj.set(username, msg, time(NULL));
				chats_v[cur_chat].msgs.push_back(msgObj);
				chats_v[cur_chat].last_msg = msg;
				// sendmsg(...)
				msgs_act.payload = ActionsPayload(
					FocAction(cur_chat, chats_v, "")
					);
				App(ChatMainArea, msgs_act);
			}
			msg = "";
			break;
		case UP:
			refocus(
				cur_sel, prev_sel, cur_chat, 1, msg,
				chats_v, chats_v.size() + 2, login_act
				);
			break;
		case DOWN:
			refocus(
				cur_sel, prev_sel, cur_chat, 0, msg,
				chats_v, chats_v.size() + 2, login_act
				);
			break;
		case LEFT:
		case RIGHT:
			if( cur_sel != cur_chat )
				ChatLogFunc(cur_sel == chats_v.size() + 1, chats_v);
			break;
		case ESC:
			status = 1;
			break;
		case BACKSPACE:
			if( cur_sel != cur_chat )
				continue;
			if( msg.size() ){
				msg.pop_back();
				upd_act.payload.text = msg + " ";
				App(Input, upd_act);
			}
			break;
		default:
			if( cur_sel != cur_chat )
				continue;
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
		int& cur_sel, int& prev_sel, int& cur_chat, bool up, string text,
		vector<Chat> v, const int max_focus, Action login_act
		){
	prev_sel = cur_sel;
	if( up )
		cur_sel = (cur_sel - 1 < 0)? (max_focus - 1): (cur_sel - 1);
	else
		cur_sel = (cur_sel + 1) % max_focus;

	if( 0 <= cur_sel && cur_sel <= max_focus - 3 )
		cur_chat = cur_sel;

	Action act(UnfocusActionType);
	if( prev_sel == max_focus - 1 ){
		App(CreateChatArea, act);
	}else if( prev_sel == max_focus - 2 ){
		App(JoinChatArea, act);
	}else{
		act.payload = ActionsPayload(FocAction(prev_sel, v, text));
		App(ChatListArea, act);
	}

	act.type = FocusActionType;
	if( cur_sel == max_focus - 1 ){
		App(CreateChatArea, login_act);
	}else if( cur_sel == max_focus - 2 ){
		App(JoinChatArea, login_act);
	}else{
		act.payload = ActionsPayload(FocAction(cur_chat, v, text));
		App(ChatListChatBlockArea, act);
	}
}

bool isempty(string s){
	if( all_of(s.begin(), s.end(), [](char c){return isspace(c);}) )
		return 1;
	if( s.empty() )
		return 1;
	return 0;
}

void ChatLogFunc(bool isCreate, vector<Chat>& chats_v){
	Chat newchat = {
		"TEAMA Chat", "I hope, Ilya won't find us there", 4,
		{
			{
				"Misha", "I've created this chat to protect us from Ilya's jokes",
				1591060209
			},
			{
				"Misha", "So good not to hear his jokes every 5 sec", 1591060329
			},
			{
				"Natan", "Yeah, It's like heaven", 1591060389
			},
			{
				"Michail", "I hope, Ilya won't find us there", 1591060815
			}
		}
	};

	char ch;

	char* bad = WRONG_CHAT;
	char* ok = CHAT_ADDED;

	string name = "";
	string pass = "";
	bool isUpper = 1;
	Action login_act(CrJoChActionType);
	login_act.payload = ActionsPayload(LoginAction(name, pass, isUpper));

	Action chats_act(DispChMsgActionType);

	Action sg;
	sg.payload.text = "";

	Action focus(UnfocusActionType);
	if( isCreate )
		App(CreateArea, focus);
	else
		App(JoinArea, focus);

	while( 1 ){
		switch( ch = getch() ){
			case UP:
			case DOWN:
				login_act.payload.logact.isUpper = !login_act.payload.logact.isUpper;
				App(ChatLoginArea, login_act);
				break;
			case LEFT:
			case RIGHT:
			case ESC:
				login_act.type = UnfCrJoChActionType;
				App(ChatLoginArea, login_act);
				focus.type = FocusActionType;
				if( isCreate)
					App(CreateArea, focus);
				else
					App(JoinArea, focus);
				return;
			case BACKSPACE:
				if( login_act.payload.logact.isUpper ){
					if( name.size() )
						name.pop_back();
				}else{
					if( pass.size() )
						pass.pop_back();
				}

				login_act.payload = ActionsPayload(
					LoginAction(name, pass, login_act.payload.logact.isUpper)
					);
				App(ChatLoginArea, login_act);
				break;
			case ENTER:
			if( tryAuth(name, pass, isCreate) ){
					sg.payload.chars = ok;
					sg.type = SignCharsActionType;

					App(ChatSignArea, sg);

					if( !isCreate )
						chats_v.push_back(newchat);
					else
						chats_v.push_back(makeChat(name));

					chats_act.payload = ActionsPayload(chats_v);
					fprintf(stderr, "%s\n", "test");

					App(ChatListArea, chats_act);
					return;
				}else{
					if( isCreate )
						sg.payload.text = NO_CHAT_NAME;
					else
						sg.payload.text = WRONG_CHAT;
					App(ChatSignArea, sg);
				}
				break;
			default:
				if( login_act.payload.logact.isUpper )
					name.push_back(ch);
				else
					pass.push_back(ch);

				login_act.payload = ActionsPayload(
					LoginAction(name, pass, login_act.payload.logact.isUpper)
					);
				App(ChatLoginArea, login_act);
		}
	}
}

bool tryAuth(string name, string pass, bool isCreate){
	fprintf(stderr, "%s\n", "inside tA");
	if( isCreate ){
		if( isempty(name) )
			return 0;
		else
			return 1;
	}
	if( name == "TEAMA Chat" && pass == "deadbeef" )
		return 1;

	return 0;
}

#endif NCURSCRIPT
