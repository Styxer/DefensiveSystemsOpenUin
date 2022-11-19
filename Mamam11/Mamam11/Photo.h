#pragma once
#include "Media.h"
#include <iostream>
class Photos : public Media {
public:
	void display() {
	std::cout << "Photo\n";
	}

};
