#ifndef NCURSCRIPT
#define NCURSCRIPT

#include "constants.cpp"
#include "App.cpp"

#define BACKSPACE 127
#define ENTER 10

using namespace std;


bool login(){
	noecho();

	ActionType act;
	AuthAction data;
	act.auth = data;
	char ch;
	bool status = 0;
	string p455wd;

	while( !status ){
		switch( ch = getch() ){
		case BACKSPACE:
			if( !p455wd.empty() )
			    p455wd.pop_back();
			break;
		case ENTER:
			status = 1;
			break;
		default:
			p455wd += ch;
		}
		act.auth.len = (p455wd.empty()) ? 0 : p455wd.size();
		App(0, 0, Auth, act);
	}

	if( p455wd == "c1rn015b4k4" ){
		fprintf(stderr, "%s\n", "I'm in...");
	}

	getch();
	echo();

	return 0;
}

#endif NCURSCRIPT