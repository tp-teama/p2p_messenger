#ifndef CONSTANTS
#define CONSTANTS

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


struct AuthAction{
	int len;
};

union ActionType {
	AuthAction auth;
};

#endif