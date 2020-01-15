#pragma once
#include <utility>
#include <list>
#include <string>

class Mode
{
public:
	virtual std::list<std::pair<std::string , int>>distribute(std::list<std::string>& hardware, int numberOfImages) {}
};

