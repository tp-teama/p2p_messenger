#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;


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

vector<struct Chat> chats = {
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


string wrap(const string text, size_t line_length = 72){
  istringstream words(text);
  ostringstream wrapped;
  string word;

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


vector<string> split(const string& s, char delimiter){
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream, token, delimiter))
      tokens.push_back(token);
    
   return tokens;
}


vector<string> wrap_text(string inp, size_t line_length){
  vector<string> v;
  vector<string> lines = split(inp, '\n');
  vector<string> tmp;
  for( int i = 0; i < lines.size(); ++i ){
    tmp = split(wrap(lines[i], line_length), '\n');
    v.insert(v.end(), tmp.begin(), tmp.end());
  }

  return v;
}