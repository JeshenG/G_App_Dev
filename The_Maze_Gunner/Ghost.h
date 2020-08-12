#pragma once
#include "RenderableObject.h"
#include "Location.h"

// basically the ghosts can fly through the maze , if a Player collides with the Ghost , then his score is deducted 

class Ghost : public RenderableObject { // class Ghost extends RenderableObject

private:
	Location c_loc;

	float p_radius; // patrol distance
	float speed;
	
	int lut;      // last update time
	int direction;

	float ph_limit; // the positive coord limit
	float nh_limit;  // the negative coord limit

	void drawGhost();
	void update_linear();

public:

	Ghost(float id, Location & location);
	void update();
	void render(); 
};



