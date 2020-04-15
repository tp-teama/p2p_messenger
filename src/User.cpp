#include "User.h"
	User& User::GetUser(unsigned int id)
{
	std::cout << id << endl;
	return;
}
int User::UpdateUser(unsigned int id_user, std::string path_private_key)
{
	std::cout << "New IP is installed succesfully" << endl;
	return 1;
}
User& User::CreateUser(std::string nickname)
{
	cout << "I have done user" <<endl;
	return;
}
User* User::GetUsersByNick(std::string nickname)
{
	cout << "Users with" << nickname << endl;
	return;
}