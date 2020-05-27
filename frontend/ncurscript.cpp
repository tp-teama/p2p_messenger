#ifndef NCURSCRIPT
#define NCURSCRIPT

#include "constants.cpp"
#include "App.cpp"

#define BACKSPACE 127
#define ENTER 10
#define UP 65
#define DOWN 66
#define TAB 9
#define ESC 27

using namespace std;

bool login();
bool login_try(string& name, string& p455wd, Action& act);

bool login(){
	Action act;

	act.type = NoneActionType;
	App(0, 0, WindowType::Auth, act);

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
			App(0, 0, Welcome, act);
			getch();
			return 0;
		} else {
			act.type = WrongCredsActionType;
			App(0, 0, Auth, act);
			getch();
			act.type = NoneActionType;
			App(0, 0, WindowType::Auth, act);
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

		App(0, 0, Auth, act);
	}

	echo();
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
		{"Chat1", "Hey guys I want whole place search now", 4, msgs},
		{"Chat2", "Come here and fight!", 1, msgs},
		{"Chat3", "Where did you put Bertram's wooden snuff box?", 265, msgs}
	};

	int cur_chat = 0;
	Action act;
	act.type = ChatMsgsActionType;
	ActionsPayload ap;
	ap.chats = ChatsMsgs(chats_v, cur_chat);
	act.payload = ap;

	App(0, 0, Default, act);
	getch();
	return 0;
}


#endif NCURSCRIPT
