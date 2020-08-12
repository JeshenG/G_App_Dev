#pragma once

class Location
{
public:
	Location(float x, float y, float z);
	Location(const Location& l);
	virtual ~Location();
	// make these public for ease of use, but off course it is dangerous
	float x;
	float y;
	float z;

};

