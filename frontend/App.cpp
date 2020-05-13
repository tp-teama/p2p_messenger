// Add exceptions for EXXXTRA Small sizes such as less than basic titles or
// less that much it's impossible to read(any: vert or horiz)
// Make it colored
// Enable keyboard events 
// Create label inside of input area
// Enable resizing
// Code-style < 80 symbols
// Add chat line generator
// Add nice corners
// Refactor code to look pretty


#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <ncurses.h>

#define HOR ACS_HLINE
#define VER ACS_VLINE
#define BUFSIZE 1000

using namespace std;


char buffer[BUFSIZE];

string trunc(string s, int n){
	if( int(s.length()) <= n )
		return s;

	int j;
	for( j = n-4; s[j] == ' ' && j > 0; --j );
	s = s.substr(0, j+1) + "...";
	return s;
}



string msg_header(string name, int timestamp){
	string h(name);
	h += "   ";

	time_t temp = (uint32_t)timestamp;
	tm* t = gmtime(&temp);
	stringstream ss;
	ss << put_time(t, "%Y-%m-%d %I:%M:%S %p");

	return h + ss.str();;
}

struct Chat{
	string name;
	string last_msg;
	int members;
};
vector<Chat> chats = {
	{"Chat1", "Hey guys I want whole place search now", 4},
	{"Chat2", "Come here and fight!", 1},
	{"Chat3", "Where did you put Bertram's wooden snuff box?", 265}
};
int cur_chat = 0;

struct Message{
	string name;
	string text;
	int timestamp;
};
vector<Message> msgs = {
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


std::string wrap(const string text, size_t line_length = 72){
  std::istringstream words(text);
  std::ostringstream wrapped;
  std::string word;

  if (words >> word) {
    wrapped << word;
    size_t space_left = line_length - word.length();
    while (words >> word) {
      if (space_left < word.length() + 1) {
        wrapped << '\n' << word;
        space_left = line_length - word.length();
      } else {
        wrapped << ' ' << word;
        space_left -= word.length() + 1;
      }
    }
  }
  return wrapped.str();
}

std::vector<std::string> split(const std::string& s, char delimiter){
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
      tokens.push_back(token);
    
   return tokens;
}

std::vector<string> wrap_text(string inp, size_t line_length){
  std::vector<string> v;
  std::vector<string> lines = split(inp, '\n');
  std::vector<string> tmp;
  for( int i = 0; i < lines.size(); ++i ){
    tmp = split(wrap(lines[i], line_length), '\n');
    v.insert(v.end(), tmp.begin(), tmp.end());
  }

  return v;
}

void App();

void Panel(int y0, int x0, int height, int width);
void Chat(int y0, int x0, int height, int width);
void ChatList(int y0, int x0, int height, int width);
void JoinButton(int y0, int x0, int height, int width);
void CreateChat(int y0, int x0, int height, int width);
void ChatHeader(int y0, int x0, int height, int width);
void ChatBlock(int y0, int x0, int height, int width);
void InputField(int y0, int x0, int height, int width);

void App(){
	initscr();
	curs_set(0);

	// let height and width be the last block of each axis position
	int height = 0;
	int width = 0;
	getmaxyx(stdscr, height, width);
	height--;
	width--;
	
	Panel(0, 0, height, width/4);

	mvwvline(stdscr, 0, width/4 + 1, VER, height+1);

	Chat(0, width/4 + 2, height, width - width/4 - 2);
	
	wrefresh(stdscr);

	getch();

	endwin();
}

void Panel(int y0, int x0, int height, int width){
	ChatList(y0, x0, height, width);

	mvwhline(stdscr, height - 3, 0, HOR, width+1);

	JoinButton(height - 2, 0, 1, width);

	mvwhline(stdscr, height - 1, 0, HOR, width+1);

	CreateChat(height, 0, 1, width);
}

void ChatList(int y0, int x0, int height, int width){
	for( int i = 0; i < (int)chats.size() && (i+1)*3 < height; ++i ){
		mvwprintw(stdscr, i*3, 1, trunc(chats[i].name, width).c_str());

		mvwprintw(stdscr, i*3+1, 0, trunc(chats[i].last_msg, width+1).c_str());

		mvwhline(stdscr, i*3+2, 0, '-', width+1);
	}
}

void JoinButton(int y0, int x0, int height, int width){
	mvwaddstr(stdscr, y0, (width - 8)/2, "Join Chat");
}

void CreateChat(int y0, int x0, int height, int width){
	mvwaddstr(stdscr, y0, (width - 10)/2, "Create Chat");	
}

void Chat(int y0, int x0, int height, int width){
	ChatHeader(y0, x0, 1, width);

	mvwhline(stdscr, y0 + 1, x0, HOR, width + 1);

	ChatBlock(y0 + 2, x0, height - 4, width);

	mvwhline(stdscr, height - 1, x0, HOR, width + 1);

	InputField(height, x0, 1, width);
}

void ChatHeader(int y0, int x0, int height, int width){
	string chat_name = chats[cur_chat].name;
	int n_mem = chats[cur_chat].members;
	string members_str = ((n_mem % 1 == 0) && (n_mem % 100 != 11)) ? "member" : "members";
	string header = chat_name + "   " + to_string(n_mem) + " " + members_str;

	mvwaddstr(stdscr, y0, x0 + 1, header.c_str());
}

void InputField(int y0, int x0, int height, int width){
	mvwaddstr(stdscr, y0, x0, "Hello everyone, my name is|");	
}

void ChatBlock(int y0, int x0, int height, int width){
	string header;
	vector<string> lines;
	int y = y0 + height;
	cout << msgs.size() << endl;
	for( int m = msgs.size() - 1; y >= y0 && m >= 0; --m ){
		lines = wrap_text(msgs[m].text, width);
		for( int l = lines.size() - 1; y >= y0 && l >= 0; --l )
			mvwaddstr(stdscr, y--, x0, lines[l].c_str());
		if(y >= y0)
			mvwaddstr(
				stdscr, y--, x0 + 2, 
				msg_header(msgs[m].name, msgs[m].timestamp).c_str()
				);
		if(y >= y0)
			mvwhline(stdscr, y--, x0, '-', width + 1);
	}
}