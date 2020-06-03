#pragma once
#include <string>
#include <cstring>
#include <vector>
#include "Chat.h"
#include "Message.h"

enum WindowType {
	AppAuth,
	ChatLoginArea,
	SignArea,
	Default,
	Input,
	JoinArea,
	CreateArea,
	JoinChatArea,
	CreateChatArea,
	ChatListArea,
	ChatListChatBlockArea,
	ChatMainArea,
	ChatSignArea,
	Select
};

enum ActionTypes {
	LoginActionType,
	DispChMsgActionType,
	UpdMsgActionType,
	FocusActionType,
	UnfocusActionType,
	AddMsgActionType,
	ClearInputActionType,
	CrJoChActionType,
	UnfCrJoChActionType,
	AppAuthRegActionType,
	SignCharsActionType,
	SignStringActionType,
	SelectActionType
};

struct LoginAction {
	LoginAction(){}
	LoginAction(std::string name,	std::string pass,	int isUpper):
		pass(pass), name(name), isUpper(isUpper){}
	LoginAction( const LoginAction& la ):
		pass(la.pass), name(la.name), isUpper(la.isUpper) {}
	LoginAction& operator=( const LoginAction& la ){
		pass = la.pass;
		name = la.name;
		isUpper = la.isUpper;
		return *this;
	}

	std::string pass;
	std::string name;
	int isUpper;
};

struct FocAction {
	FocAction(){}
	FocAction(int num, std::vector<Chat> v, std::string txt):
		num(num), v(v), text(txt){}

	FocAction(const FocAction& fa): num(fa.num), v(fa.v), text(fa.text) {}

	int num;
	std::vector<Chat> v;
	std::string text;
};

union ActionsPayload {
	ActionsPayload(){}
	ActionsPayload(const ActionsPayload& act){memcpy(this, &act, sizeof(act));}
	ActionsPayload& operator=( const ActionsPayload& act ){
		memcpy(this, &act, sizeof(act));
		return *this;
	}
	
	ActionsPayload(const FocAction fa): ua(fa) {}
	ActionsPayload(const LoginAction la): logact(la) {}
	ActionsPayload(const std::string& s): text(s) {}
	ActionsPayload(const std::vector<Chat>& v): chats(v) {}

	LoginAction logact;
	std::vector<Chat> chats;
	std::string text;
	char* chars;
	FocAction ua;
	bool isCreate;

	~ActionsPayload(){}
};

struct Action {
	Action(){}
	Action(ActionTypes at): type(at) {}
	ActionsPayload payload;
	ActionTypes type;
};
