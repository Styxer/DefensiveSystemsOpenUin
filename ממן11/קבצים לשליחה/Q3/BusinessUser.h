#pragma once
#include "User.h"

class BusinessUser : public User {
	virtual void sendMessage(User* user, Message* message);
};
