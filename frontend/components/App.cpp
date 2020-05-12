#include <iostream>
#include "App.h"


int A::do_something() {
	return height/2 + width/2;
}

ReturnCode A::render(){
	box(win, 0, 0);
	refresh();
	wrefresh(win);
	return SmallSize;
}

ReturnCode A::redraw(int el){
	return SmallSize;
}
