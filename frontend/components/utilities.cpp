#include <vector>
#include <map>
#include <ncurses.h>
#include "constants.cpp"

using namespace std;


// A bit too complicated, but ok
void whline( WINDOW* win, int y, int x1, int x2 ){
	wmove(win, y, x1);
	whline(win, HOR, x2 - x1 + 1);
}

void wvline( WINDOW* win, int x, int y1, int y2 ){
	wmove(win, y1, x);
	wvline(win, VER, y2 - y1 + 1);
}
