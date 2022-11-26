#pragma once
#include <String>
#include <List>
#include "Post.h"
#include "USocial.h"
#include "Message.h"

class USocial;

class User {

private:
	friend class USocial;
	static unsigned long nextUserId;

protected:
#pragma region Members
	USocial* us;
	unsigned long id;
	std::string name;
	std::list<unsigned long> friends;
	std::list<Post*> posts;
	std::list<Message*> receivedMsgs;
#pragma endregion

#pragma region constructors
	User();
	User(const User& user);
#pragma endregion

	~User();

#pragma region Methods
	bool isFriend(User* user);
#pragma endregion

public:
#pragma region Getters
	unsigned long getId();
	std::string getName();
	std::list<Post*> getPosts();
#pragma endregion
	
#pragma region Friend Methods
	void addFriend(User* user);
	void removeFriend(User* user);
	void viewFriendsPosts();
#pragma endregion


#pragma region Post Methods
	void post(std::string text);
	void post(std::string text, Media* media);
#pragma endregion

	
#pragma region Message Methods
	void receiveMessage(Message* message);
	virtual void sendMessage(User* user, Message* message);
	void viewReceivedMessages();
#pragma endregion

	//User& operator=(const User& post);
	bool operator==(const User& post);
	friend std::ostream& operator<<(std::ostream& stream, const User& user);

	






};