#include <exception>
#include <iostream>
#include "User.h"
#include "Audio.h"
#include "Photo.h"
#include "Video.h"

int main()
{
	USocial us;
#pragma region Usocial Tests
	User* u1 = us.registerUser("Liron");
	User* u2 = us.registerUser("Yahav");
	User* u3 = us.registerUser("Shachaf");
	User* u4 = us.registerUser("Tsur", true);
	User* u5 = us.registerUser("Elit");
	User* u6 = us.registerUser("avi");
	User* u7 = us.registerUser("sofer", true);

	us.removeUser(u6);
	us.removeUser(u7);
#pragma endregion


#pragma region Post Tests
	u1->post("Hello world!");
	u2->post("I'm having a great time here :)", new Audio());
	u3->post("This is awesome!", new Photo());
	u4->post("What is love?", new Video());
#pragma endregion

	
#pragma region Test post viewing
	u5->addFriend(u5);//should raise error
	u5->addFriend(u2);
	u5->viewFriendsPosts(); // should see only u1, u2 s' posts
	u4->sendMessage(u5, new Message("Buy Falafel!"));
	u5->viewReceivedMessages();
	try
	{
		u3->sendMessage(u5, new Message("All your base are belong to us"));
	}
	catch (const std::exception& e)
	{
		std::cout << "error: " << e.what() << std::endl;
	}
	u5->viewReceivedMessages();
	u3->addFriend(u5);
	u3->sendMessage(u5, new Message("All your base are belong to us"));
	u5->viewReceivedMessages();
	u4->viewReceivedMessages();
	return 0;
#pragma endregion

}


