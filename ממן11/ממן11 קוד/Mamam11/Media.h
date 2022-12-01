#pragma once
#include <iostream>
class Media {
public:
		void virtual display() = 0;
		std::string virtual getMediaDescription() = 0 { return "media"; }
};
