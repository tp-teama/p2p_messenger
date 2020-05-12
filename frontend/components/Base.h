#include <ncurses.h>
#include "constants.cpp"

using namespace std;


class Base{
protected:
	int x, y, height, width;
	WINDOW* win;
public:
	explicit Base(void);
	explicit Base(int x0, int y0, int sx, int sy);
	virtual int do_something() = 0;
	virtual ReturnCode render() = 0;
	virtual ReturnCode redraw(int el) = 0;
	~Base();
	void print();
};