#include "Location.h"

Location::Location(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Location::Location(const Location& l) {
	this->x = l.x;
	this->y = l.y;
	this->z = l.z;
}

Location::~Location()
{
	//dtor
}