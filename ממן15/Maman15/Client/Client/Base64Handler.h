#pragma once

#include <string>
#include <base64.h>

class base64_handler
{
public:
	static std::string encode(const std::string& str);
	static std::string decode(const std::string& str);
};
