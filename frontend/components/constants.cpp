#ifndef APP_UI_CONST
#define APP_UI_CONST

enum ReturnCode {
	Ok,
	SmallSize,
};

enum Area {
	Screen,
	Panel,
	Chat
};

struct VertBorder {
	int x, y1, y2;
	Area ar;
};

struct HorizBorder {
	int y, x1, x2;
	Area ar;	
};

char16_t HOR = U'|';
char16_t VER = U'─';

enum BoxSym {
	Up = U'┴',
	Left = U'┤',
	Down = U'┬',
	Right = U'├',
	Quatre = U'┼',
};

struct Coord{
	int x;
	int y;
	Coord(int coord_x, int coord_y): x(coord_x), y(coord_y) {}

	bool operator<(const Coord& b) const {
        return this->x + this->y < b.x + b.y;
    }
};


#endif