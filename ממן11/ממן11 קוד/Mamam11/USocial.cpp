#include "USocial.h"
#include "User.h"
#include "BusinessUser.h"
#include <format>

#pragma region Functions


/// <summary>
/// register user in the social network
/// </summary>
/// <param name="userName">the user name</param>
/// <param name="isBusinessAccount"> if the user is buiness account </param>
/// <returns>if isBusinessAccount is false returns a user, else returns a Business Account. sets its name, add it to the social network. </returns>
User* USocial::registerUser(std::string userName, bool isBusinessAccount)
{
	User* user = isBusinessAccount ? new BusinessUser() : new User();

	user->name = userName;
	user->us = this;
	users.insert(std::make_pair(user->id, user));//add a user(with a new id) to registred users

	return user;
}

/// <summary>
/// remover user from social netowkr
/// </summary>
/// <param name="user">remove user from the social network</param>
void USocial::removeUser(User* user)
{
	//if not users in the social netowrk
	if (users.empty())
	{
		std::cout << "  USocial has to users in it" << std::endl;		
	}

	//throw if send user is null
	else if (user == NULL)
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


/// <summary>
/// get user from the social network by its id
/// </summary>
/// <param name="userId">the user id that we want to look up</param>
/// <returns>a User if its found in the social network</returns>
User* USocial::getUserById(unsigned long userId)
{
	//if not users in the social netowrk
	if (users.empty())
	{
		std::cout << "  USocial has to users in it" << std::endl;
		return NULL;
	}

	User* user = users[userId];
	//if the user is not found
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

/// <summary>
/// override post defualt print
/// </summary>
/// <param name="stream">default stream</param>
/// <param name="USocial"></param>
/// <returns>a stream of formatted string USocial</returns>
std::ostream& operator<<(std::ostream& stream, const USocial& usocial)
{
	for (auto user : usocial.users)
	{
		stream << *user.second << std::endl;
	}
	return stream << std::endl;
}

#pragma endregion

