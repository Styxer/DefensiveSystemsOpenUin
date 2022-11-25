#pragma once
#include "Media.h"
#include <iostream>
class Audio : public Media {
public:
	void display() 
	{
		std::cout << "audio " << std::endl;	
	}
	std::string getMediaDescription() { return "Audio"; }
};
