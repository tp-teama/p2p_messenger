#include "User.h"
std::string& User::GetUser(std::string Nick)
{
	std::string* Ip = new std::string;
	std::cout << Nick << endl;
	return Storage::GetUser(Nick);
}
int User::UpdateUser(int id_user, std::string path_private_key)
{
	std::cout << "New IP is installed succesfully" << endl;
	return 1;
}