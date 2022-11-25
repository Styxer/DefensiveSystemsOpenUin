#include "User.h"
#include <algorithm>
#include <memory>
#include <stdio.h>

constexpr auto MAX_STR_LEN =  300;;

unsigned long User::nextUserId = 1;

#pragma region Constructors
/// <summary>
/// 
/// </summary>
User::User()
{
	char* defaultUserName = new char[MAX_STR_LEN];
	sprintf_s(defaultUserName, MAX_STR_LEN, "user %lu", nextUserId);

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
	for (auto message : user.receivedMsgs)
		receivedMsgs.push_back(new Message(*message));

	//copy posts list
	for (auto post : user.posts)
		posts.push_back(new Post(*post));

	//copy friends list
	for (auto friendId : user.friends)
		friends.push_back(friendId);
}
#pragma endregion




#pragma region destructor
User::~User()
{
	//clear all items from posts list
	//std::for_each(posts.begin(), posts.end(), std::default_delete<Post*>());

	std::for_each(posts.begin(), posts.end(), [&](const decltype(posts)::reference& v) {
		posts.remove(v);
		});

	//clear all items from message list
	/*std::for_each(receivedMsgs.begin(), receivedMsgs.end(), ~Message);*/

	receivedMsgs.clear();

	//clear all items from friends list
	friends.clear();

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
		char* errorMessage = new char[MAX_STR_LEN];
		sprintf_s(errorMessage, MAX_STR_LEN, "user with id %lu and name %s is already a friend of a user with id %lu and %s", user->id, user->name.c_str(), id, name.c_str());
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

	char* errorMessage = new char[MAX_STR_LEN];
	sprintf_s(errorMessage, MAX_STR_LEN, "user with id %lu and name %s is not a friend of a user with id %lu and %s", user->id, user->name.c_str(), id, name.c_str());
	throw std::invalid_argument(errorMessage);
}

#pragma region Posts related functions
void User::post(std::string text)
{
	posts.push_back(new Post(text));
}

void User::post(std::string text, Media* media)
{
	posts.push_back(new Post(text, media));
}

void User::viewFriendsPosts()
{
	if (friends.empty())
	{
		std::cout << *this << " has not friends" << std::endl;
		return;
	}
}

#pragma endregion



#pragma region Overrirdes

std::ostream& operator<<(std::ostream& stream, const User& user)
{
	return stream << "User " << user.id << user.name << user.us <<  std::endl;
}
#pragma endregion





