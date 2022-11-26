#include "USocial.h"
#include "User.h"
#include "BusinessUser.h"
#include <format>

#pragma region Functions
User* USocial::registerUser(std::string userName, bool isBusinessAccount)
{
	User* user = isBusinessAccount ? new BusinessUser() : new User();

	user->name = userName;
	user->us = this;
	users.insert(std::make_pair(user->id, user));//add a user(with a new id) to registred users

	return user;
}

void USocial::removeUser(User* user)
{
	if (users.empty())
	{
		std::cout << "  USocial has to users in it" << std::endl;
		return;
	}

	//throw if send user i null
	if (user == NULL)
	{
		throw std::invalid_argument("user is null");
	}
	//throw if trying to remove non-existing user
	if (users.find(user->id) == users.end())
	{
		throw std::invalid_argument("User not found");
	}

	//user if found and remove it
	users.erase(user->id);

}

User* USocial::getUserById(unsigned long userId)
{

	if (users.empty())
	{
		std::cout << "  USocial has to users in it" << std::endl;
		return NULL;
	}

	User* user = users[userId];
	if (user == NULL)
	{
		char* errorMessage = new char[300];
		sprintf_s(errorMessage, 300, "user with %lu nott found", userId);
		throw std::invalid_argument(errorMessage);
	}


	return user;
}
#pragma endregion


#pragma region constructors
USocial::USocial() {}

USocial::USocial(const USocial& usocial)
{
	//clear exisitng users
	this->users.clear();

	//copy users
	for (auto user : usocial.users)
		users.insert(std::make_pair(user.first, user.second));}

#pragma endregion

#pragma region de-constructor
USocial::~USocial()
{
	// release all users
	for (auto  user : users)
		delete user.second;
}
#pragma endregion

#pragma region Overrides

//ovrride  "ToString"  method to make perttier printing
std::ostream& operator<<(std::ostream& stream, const USocial& usocial)
{
	for (auto user : usocial.users)
	{
		stream << *user.second << std::endl;
	}
	return stream << std::endl;
}

#pragma endregion

