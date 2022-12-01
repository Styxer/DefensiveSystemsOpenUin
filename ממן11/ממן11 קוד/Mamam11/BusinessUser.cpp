#include "BusinessUser.h"

constexpr auto MAX_STR_LEN = 300;

void BusinessUser::sendMessage(User* user, Message* message)
{
	if (user == NULL)
	{
		char* errorMessage = new char[MAX_STR_LEN];
		sprintf_s(errorMessage, MAX_STR_LEN, "user is null");
		throw std::invalid_argument(errorMessage);
	}

	if (message == NULL)
	{
		char* errorMessage = new char[MAX_STR_LEN];
		sprintf_s(errorMessage, MAX_STR_LEN, "message is null");
		throw std::invalid_argument(errorMessage);
	}

	if (user == this)
	{
		std::cout << "you cannot remove yourself from friends list" << std::endl;
	}

	user->sendMessage(user, message);
}