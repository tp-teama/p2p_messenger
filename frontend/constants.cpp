#ifndef CONSTANTS
#define CONSTANTS

#include <string>
#include <cstring>

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

struct LoginAction {
	std::string* psswd;
	std::string* name;
	int cur;
	int cur_chanj;
};

enum ActionTypes {
	NoneActionType,
	LoginActionType,
	WelcomeActionType,
	WrongCredsActionType,
};

union ActionsPayload {
	ActionsPayload(){}
	ActionsPayload(const ActionsPayload& act){memcpy(this, &act, sizeof(act));}
	ActionsPayload& operator=( const ActionsPayload& act ){ 
		memcpy(this, &act, sizeof(act)); return *this; 
	}

	LoginAction logact;
	std::string name;

	~ActionsPayload(){}
};

struct Action {
	Action(): type(NoneActionType) {}
	ActionsPayload payload;
	ActionTypes type;
};

#endif