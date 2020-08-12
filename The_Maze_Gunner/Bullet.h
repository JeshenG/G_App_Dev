#pragma once
#include <iostream>
#include "RenderableObject.h"

class Bullet : public RenderableObject { // extends renderable object

private:
	Location c_loc; // central position
	void drawBullet();
	void update_linear();

public:
	Bullet(float id, Location& location);

	void goToOrigin();
	void changeXCoZco(float xco, float zco);
	void update();
	void render();
};
