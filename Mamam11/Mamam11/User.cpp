#include "User.h"
#include <algorithm>
#include <memory>

unsigned long User::nextUserId = 1;

#pragma region Construcrs
User::User()
{
	char* defaultUserName = new char[300];
	sprintf(defaultUserName, "user %lu", nextUserId);

	id = nextUserId++;
	name = defaultUserName;
	us = NULL;
}


User::User(const User& user)
{
	id = nextUserId++;
	name = user.name;
	us = user.us;

	//copy the message list
	for (auto  message : user.receivedMsgs)
		receivedMsgs.push_back(new Message(*message));

	//copy posts list
	for (auto  post : user.posts)
		posts.push_back(new Post(*post));

	//copy friends list
	for (auto  friendId : user.friends)
		friends.push_back(friendId);
}
#pragma endregon



#pragma region destructor
User::~User()
{
	//clear all items from posts list
	std::for_each(posts.begin(), posts.end(), std::default_delete<Post*>());

	//clear all items from message list
	std::for_each(receivedMsgs.begin(), receivedMsgs.end(), std::default_delete<Message*>());

	//clear all items from friends list
	std::for_each(friends.begin(), friends.end(), std::default_delete<unsigned long>());
}
#pragma endregion

#pragma region Getters
unsigned long User::getId()
{
	return id;
}

std::string User::getName()
{
	return name;
}

std::list<Post*> User::getPosts()
{
	return posts;
}
#pragma endregion

#pragma region Friend related functions

void User::addFriend(User* user)
{
	//throw exception is user is already a friend of this user
	if (isFriend(user))	
	{
		char* errorMessage = new char[300];
		sprintf(errorMessage, "user with id %lu and name %s is already a friend of a user with id %lu and %s", user->id, user->name, id, name);
		throw std::invalid_argument(errorMessage);
	}

	user->friends.push_back(id);// add this user to given user's friend list 
	friends.push_back(user->id);// add  user to this user's friend list 

}
#pragma endregion
void User::removeFriend(User* user)
{
	if (!isFriend(user))
	{
		user->friends.remove(id);// remove this user from given user's friend list 
		friends.remove(user->id);// remove given user from this user's friend list
	}

	char* errorMessage = new char[300];
	sprintf(errorMessage, "user with id %lu and name %s is not a friend of a user with id %lu and %s", user->id, user->name, id, name);
	throw std::invalid_argument(errorMessage);
}


#pragma region Overrirdes

std::ostream& operator<<(std::ostream& stream, const User& user)
{
	return stream << "User " << user.id << user.name << user.us <<  std::endl;
}
#pragma endregion





