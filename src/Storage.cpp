#include "Storage.h"
string& Storage::GetUser(string Nick)
{
	string* Ip = new string;
	cout << Nick << endl;
	return *Ip;
}
User& Storage::CreateUser(string Nick, string path_private_key)
{

	cout << "I have create a new user!" << endl;
	return;
}
Chat& Storage::CreateChat(int id_1, int id_2, string message)
{
	cout << "I have create a new chat!" << endl;
	return;
}
int Storage::GetUserId(string Nick)
{
	return 1;
}
Chat& Storage::GetChat(int id_1, int id_2)
{
	cout << "Get chat!" << endl;
	return;
}
int Storage::AddMessage(string message, int id_chat)
{
	cout << "Add a new message" <<	message << endl;
	return 1;
}
int Storage::UpdateUser(int id_user, string path_private_key)
{
	cout << "New IP is installed succesfully" << endl;
	return 1;
}