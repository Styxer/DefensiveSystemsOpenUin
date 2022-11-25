#pragma once
#include "Media.h"
#include <iostream>
class Photo : public Media {
public:
	void display() 
	{
		std::cout << "Photo" << std::endl;
	}
	std::string getMediaDescription() { return "Photo"; }

};
