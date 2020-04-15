#include "Storage.h"
User& Storage::GetUser(unsigned int id)
{
	std :: cout << Nick << endl;
	return;
}
User& Storage::CreateUser(string Nick)
{

	std :: cout << "I have create a new user!" << endl;
	return;
}
User* Storage::GetUsersByNick(std::string)
{
	std :: cout << "I have create a new user!" << endl;
	return;
}
Chat& Storage::CreateChat(unsigned int id_1,unsigned int id_2,std::string message)
{
	std :: cout << "I have create a new chat!" << endl;
	return;
}
Chat& Storage::GetChat(unsigned int id_1)
{
	std :: cout << "Get chat!" << endl;
	return;
}
Chat* Storage::GetAllMyChats (unsigned int id_chat){
	return;
}
int Storage::DeleteChat(unsigned int id_chat){
	return;
}
Message& Storage::SendMessage(Message message)
{
	std :: cout << "Add a new message" <<  endl;
	return;
}
int Storage::UpdateUser(unsigned int id_user,std::string nickname)
{
	std :: cout << "New IP is installed succesfully" << endl;
	return 1;
}