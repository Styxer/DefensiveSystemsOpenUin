#pragma once
#include "Media.h"
#include <iostream>
class Video : public Media {
public:
	void display() {
		std::cout << "video\n";
	}
};
