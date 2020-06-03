#pragma once
#include <vector>
#include "User.h"

#define NCURSES_NOMACROS

class MessengerUI {
private:
	int curr_win;
	int curr_chat;
public:
	void UpdateMsgs(int chat_id, std::vector<char>); // Updates messages in chat
	void Run(); // Does rest of the work: input, window switching, etc
};
