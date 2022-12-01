#include "Message.h"

#pragma region Constructor
Message::Message()
{
	_text = "";
}

Message::Message(std::string str)
{
	_text = str;
}

Message::Message(const Message& message)
{
	_text = message._text;
}
#pragma endregion


#pragma region Getters
std::string Message::getText()
{
	return _text;
}

#pragma endregion

