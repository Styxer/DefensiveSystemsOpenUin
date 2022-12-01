#include "Post.h"

#pragma region Constructors
Post::Post(std::string text) : _text(text), _media(NULL) {}

Post::Post(std::string text, Media* media) : _text(text), _media(_media) {}
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

#pragma region Opreators
/// <summary>
/// override == opreator
/// </summary>
/// <param name="post"></param>
/// <returns>return true if text and media are equals else returns false</returns>
bool Post::operator==(const Post& post)
{
	return _text == post._text
		&& _media == post._media;
}

/// <summary>
/// override post defualt print
/// </summary>
/// <param name="stream">default stream</param>
/// <param name="post"></param>
/// <returns>a stream of formatted string post</returns>
std::ostream& operator<<(std::ostream& stream, const Post& post)
{
	stream << "Post-->{Text |" << post._text << "|";
	if (post._media != NULL)
	{
		stream << "Media: " << post._media->getMediaDescription();
	}
	stream << "}";
	return stream << std::endl;
}

#pragma endregion

/// <summary>
/// clears post pointers
/// </summary>
#pragma region Destructor
Post::~Post()
{
	if (_media != NULL) {

		delete _media;
		_media = NULL;
	}
}
#pragma endregion




