#pragma once
#include "Location.h"

class RenderableObject
{
public:
	RenderableObject(float id, const Location& location, float radius);
	virtual ~RenderableObject();
	Location getLocation() { return loc; }
	float getId() { return id; }
	virtual void render() = 0; // =0 make this pure virtual and the class abstract
	//virtual void update() = 0;
	
protected:
	Location loc;     // actual location of the object
	float radius;     // some objects have a radius
	float id;        // unique id for this entity, not really needed
};