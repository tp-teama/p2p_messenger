#ifndef CONSTANTS
#define CONSTANTS

#include <string>
#include <cstring>
#include <vector>

struct Message{
	std::string name;
	std::string text;
	int timestamp;
};

struct Chat{
	std::string name;
	std::string last_msg;
	int members;
	std::vector<Message> msgs;
};

enum WindowType {
	Auth,
	ChatLogin,
	Welcome,
	Default
};

enum PanelType {
	Chats,
	Messages,
	ChatCreation,
	ChatJoin
};

enum ActionTypes {
	NoneActionType,
	LoginActionType,
	WelcomeActionType,
	WrongCredsActionType,
	ChatMsgsActionType
};

struct LoginAction {
	std::string* psswd;
	std::string* name;
	int cur;
} logact;

struct ChatsMsgs{
	ChatsMsgs(){}
	ChatsMsgs(std::vector<Chat> v, int c): chat_v(v), cur_chat(c) {}

	std::vector<Chat> chat_v;
	int cur_chat;
} chats;

union ActionsPayload {
	ActionsPayload(){}
	ActionsPayload(const ActionsPayload& act){memcpy(this, &act, sizeof(act));}
	ActionsPayload& operator=( const ActionsPayload& act ){ 
		memcpy(this, &act, sizeof(act));
		return *this; 
	}

	LoginAction logact;
	std::string name;
	ChatsMsgs chats;
	~ActionsPayload(){}
};

struct Action {
	Action(): type(NoneActionType) {}
	ActionsPayload payload;
	ActionTypes type;
};

#endif