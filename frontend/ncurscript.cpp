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
	int cur_chanj;

	while( !status ){
		cur_chanj = 0;
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
			cur_chanj = 1;
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
		act.payload.logact.cur_chanj = cur_chanj;
	
		App(0, 0, Auth, act);
	}

	echo();
}

#endif NCURSCRIPT