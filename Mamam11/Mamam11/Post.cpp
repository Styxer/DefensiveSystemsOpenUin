#include "Post.h"

#pragma region Constructors
//Post::Post(std::string text)
//{
//	this->_text = text;
//	this->_media = nullptr;
//}

Post::Post(std::string text) : _text(text), _media(NULL) {}

Post::Post(std::string text) : _text(text), _media(_media) {}

#pragma endregion

#pragma region Getters
std::string Post::getText()
{
	return _text;
}

Media* Post::getMedia() {
	return _media;
}
#pragma endregion

Post& Post::operator=(const Post& post)
{
	if (&post != this) 
	{
		Post::Post(post);
	}
	return *this;
}

bool Post::operator==(const Post& post)
{
	return _text == post._text
		&& _media == post._media;
}

Post::~Post() 
{
	if (_media != NULL) {

		delete _media;
		_media = NULL;
	}
}
