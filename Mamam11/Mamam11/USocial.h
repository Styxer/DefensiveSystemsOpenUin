#pragma once
#include <map>
#include "User.h"


class User;

class USocial {
private:
	friend class User;
	std::map<unsigned long, User*> users;

	

public:
#pragma region Methods
	User* registerUser(std::string userName, bool isBusinessAccount = false);
	void removeUser(User* user);
	User* getUserById(unsigned long userId);
#pragma endregion

//#pragma region Operators
	friend std::ostream& operator<<(std::ostream& stream, const USocial& usocial);	
//	USocial& operator=(const USocial& usocial);
//
//#pragma endregion

#pragma region Constructor
	USocial();
	USocial(const USocial& usocial);
#pragma endregion

	~USocial();



		

};