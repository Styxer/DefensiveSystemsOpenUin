#include "BusinessUser.h"

void BusinessUser::sendMessage(User* user, Message* message)
{
	user->sendMessage(user, message);
}