#pragma once
#include <iostream>
#include <string>
#include "Media.h"

class Post {
private:
	std::string _text;
	Media* _media;

public:
#pragma region Constructor 
	Post(std::string text);
	Post(std::string text, Media* media);

#pragma endregion

#pragma region Getters
	std::string getText();
	Media* getMedia();
#pragma endregion

#pragma region Operators 	
	bool operator==(const Post& post);
	friend std::ostream& operator<<(std::ostream& stream, const Post& post);
#pragma endregion

	~Post();




};
