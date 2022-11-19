#pragma once
#include "Media.h"
#include <iostream>
class Audio : public Media {
public:
	void display() {
		std::cout << "audio\n";
	}
};
