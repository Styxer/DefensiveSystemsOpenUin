#pragma once
#include <string>
class Message {
private:
	std::string text;

public:
	std::string getText();
	Message();
	Message(std::string text);
	Message(const Message& message);
};