#include <iostream>
#include <math.h>
#include <ncurses.h>
#include "Base.h"

using namespace std;


int Base::do_something(){
	return 0;
}

Base::Base(void){
	initscr();
	refresh();
	cout << "test\n";
	cout << "test\n";
	x = y = 0;
	getmaxyx(stdscr, height, width);
	win = newwin(height, width, y, x);
}

Base::Base(int x0, int y0, int sx, int sy){
	initscr();
	refresh();
	x = x0, y = y0, height = sy, width = sx;
	win = newwin(height, width, y, x);
}

ReturnCode Base::render(){
	return Ok;
}

ReturnCode Base::redraw(int el){
	return Ok;
}

Base::~Base(){
	delwin(win);
	endwin();
}