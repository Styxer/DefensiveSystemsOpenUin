#include "User.h"
#include <algorithm>
#include <memory>
#include <stdio.h>

constexpr auto MAX_STR_LEN =  300;

unsigned long User::nextUserId = 1;

#pragma region Constructors

///
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
	//note: no need to do for-each with delete
	//becuase the each contains detructor will be call on each iteration 


	//clear all items from posts list
	posts.clear();

	//clear all items from message list

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

/// <summary>
/// add user to its friends list
/// </summary>
/// <param name="user">add user to current friends list</param>
void User::addFriend(User* user)
{
	if (user == NULL)
	{
		throw std::invalid_argument("incoming user paramaters is null");
	}

	if (user == this)
	{
		std::cout << " cannot add yourself as a friend" << std::endl;
	}

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

/// <summary>
/// remover user from current user friends
/// </summary>
/// <param name="user"></param>
void User::removeFriend(User* user)
{
	if (user == NULL)
	{
		throw std::invalid_argument("incoming user parameter is null");
	}

	if (user == this)
	{
		std::cout << "you cannot remove yourself from friends list" << std::endl;
	}

	if (!isFriend(user))
	{
		user->friends.remove(id);// remove this user from given user's friend list 
		friends.remove(user->id);// remove given user from this user's friend list
	}
	else
	{

		char* errorMessage = new char[MAX_STR_LEN];
		sprintf_s(errorMessage, MAX_STR_LEN, "user with id %lu and name %s is not a friend of a user with id %lu and %s", user->id, user->name.c_str(), id, name.c_str());
		throw std::invalid_argument(errorMessage);
	}
}

/// <summary>
/// view current user friends post
/// </summary>
void User::viewFriendsPosts()
{
	//if user have not friends
	if (friends.empty())
	{
		std::cout << *this << " has not friends" << std::endl;
		return;
	}

	std::cout << *this << "friends posts" << std::endl;

	//prints user friends post in nice formatted string
	for (auto friendId : friends)
	{
		User* usersFriend = us->getUserById(friendId);
		std::cout << "\t\t" << *usersFriend << ":";
		for (auto post : usersFriend->posts)
			std::cout << std::endl << "\t" << *post;
		std::cout << std::endl;
	}
}

/// <summary>
/// checks if user is friend with current user friend
/// </summary>
/// <param name="user">a suer</param>
/// <returns>true if user is friend of current user, else returns false</returns>
bool User::isFriend(User* user)
{
	for (auto friendId : friends)
	{
		if (friendId == user->id)
		{
			return true;
		}
		return false;
	}
}
#pragma endregion



#pragma region Posts related functions
void User::post(std::string text)
{
	posts.push_back(new Post(text));
}

void User::post(std::string text, Media* media)
{
	posts.push_back(new Post(text, media));
}
#pragma endregion


#pragma region Message related fucntions
void User::receiveMessage(Message* message)
{
	receivedMsgs.push_back(message);
}

/// <summary>
/// send message from user to current user
/// </summary>
/// <param name="user">a user</param>
/// <param name="message">the message the user wants to send</param>
void User::sendMessage(User* user, Message* message)
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

	if (!isFriend(user))
	{
		std::cout << *this << " cannot send message to " << *user << " " << std::endl;
		std::cout << "Only buisness user can send message to users which are not in thier freinds list" << std::endl;
		
	}
	else if (user == this)
	{
		std::cout << " cannot send message to yourself " << std::endl;
		
	}
	else 
	{
		user->receivedMsgs.push_back(new Message(message->getText()));
	}
}

/// <summary>
/// see all user recvied messages
/// </summary>
void User::viewReceivedMessages()
{
	if (receivedMsgs.empty())
	{
		std::cout << " you have no messages " << std::endl;
		return;
	}

	std::cout << *this << " messages are: " << std::endl;
	for (auto message : receivedMsgs)
	{
		std::cout << "\t\t" << message->getText() << std::endl;
	}
}

#pragma endregion




#pragma region Overrirdes

/// <summary>
/// override User defualt print
/// </summary>
/// <param name="stream">default stream</param>
/// <param name="User"></param>
/// <returns>a stream of formatted string User</returns>
std::ostream& operator<<(std::ostream& stream, const User& user)
{
	return stream << "User id:" << user.id 
		<< "\tname:" << user.name
		<< "\t network:" << user.us << std::endl;

}

/// <summary>
/// override user equality opreator
/// </summary>
/// <param name="user"></param>
/// <returns>returns true if user id equals current user id</returns>
bool User::operator==(const User& user)
{
	return id == user.id;
}
#pragma endregion





