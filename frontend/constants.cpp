#ifndef CONSTANTS
#define CONSTANTS

#include <string>
#include <cstring>
#include <vector>

struct Message {
	Message& set(std::string name, std::string text, int timestamp){
		name = name;
		text = text;
		timestamp = timestamp;
	}

	std::string name;
	std::string text;
	int timestamp;
};

struct Chat {
	std::string name;
	std::string last_msg;
	int members;
	std::vector<Message> msgs;
};

enum WindowType {
	Auth,
	ChatLogin,
	Welcome,
	Default,
	Input,
	JoinArea,
	CreateArea,
	ChatListArea,
	ChatListChatBlockArea,
	ChatMainArea
};

enum ActionTypes {
	NoneActionType,
	LoginActionType,
	WelcomeActionType,
	WrongCredsActionType,
	DispChMsgActionType,
	UpdMsgActionType,
	FocusActionType,
	UnfocusActionType,
	AddMsgActionType,
	ClearInputActionType
};

struct LoginAction {
	std::string* psswd;
	std::string* name;
	int cur;
};

struct FocAction {
	FocAction(){}
	FocAction(int num, std::vector<Chat> v): num(num), v(v){}
	FocAction(const FocAction& fa): num(fa.num), v(fa.v) {}

	int num;
	std::vector<Chat> v;
};

union ActionsPayload {
	ActionsPayload(){}
	ActionsPayload(const ActionsPayload& act){memcpy(this, &act, sizeof(act));}
	ActionsPayload& operator=( const ActionsPayload& act ){
		memcpy(this, &act, sizeof(act));
		return *this;
	}
	ActionsPayload(const FocAction fa): ua(fa) {}
	ActionsPayload(const std::string& s): text(s) {}

	LoginAction logact;
	std::string name;
	std::vector<Chat> chats;
	std::string text;
	FocAction ua;

	~ActionsPayload(){}
};

struct Action {
	Action(): type(NoneActionType) {}
	Action(ActionTypes at): type(at) {}
	ActionsPayload payload;
	ActionTypes type;
};

#endif
