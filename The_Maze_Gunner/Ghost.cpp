#include "Ghost.h"
#include "RenderableObject.h"
#include <Windows.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <cmath>


Ghost::Ghost(float id, Location & location)
	: RenderableObject(id, location, 1), c_loc(location)
{
	direction = 1;							// horizontally right

	this->speed = 2.0f;						//speed;  the ghosts speed
	this->p_radius = 10 ;					// p_radius;
	lut = glutGet(GLUT_ELAPSED_TIME);

	ph_limit = c_loc.z + 10.0f;				// where 10.0f is the parole radius 
	nh_limit = c_loc.z - 10.0f;

}


// update member function , just changes the ghosts ,z coordinate
void Ghost::update()
{
	update_linear();
}


// renders the ghost graphics
void Ghost::render()
{
	update();   // update the ghost's position  , then render 

	glPushMatrix();
	glTranslated(loc.x, loc.y, loc.z);
	drawGhost();
	glPopMatrix();
}

// draws the ghost
void Ghost::drawGhost()
{
	glPushMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glRotatef(90, 0, 1, 0);  // rotate the model 



									// draws the ghost with a cone body 
	glPushMatrix();
	glTranslatef(0.0, 0.3, 0.0);
	glRotatef(90, 1.0, 0.0, 1.0);
	glutSolidCone(0.75, 3, 20, 3);
	glPopMatrix();


							// Draws the ghosts head
	glTranslatef(0.0, 0.95, 0.0);
	glutSolidSphere(0.25, 20, 20);

							// Draws the ghosts eyes
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(0.1, 0.1, -0.2);
	glutSolidSphere(0.05, 10, 10);
	glTranslatef(-0.2, 0.0, 0.0);
	glutSolidSphere(0.05, 10, 10);
	glPopMatrix();

	glPopMatrix();
}

void Ghost::update_linear()						// updates the Ghost's linear position , that is X and Z coordinates 
{
	int time = glutGet(GLUT_ELAPSED_TIME);			// get the elapsed time in milliseconds since glutInit() was executed

	int t_elapsed = time - lut;
	float dist = speed * t_elapsed / 1000.0;

	// shift horizontally from current position,  negative or positive
	if (direction == 1) {							// postive
		float nz = loc.z + dist;

		// check if nx is greater than cx+radius
		if (nz > ph_limit) {
			direction = -1;							// change direction to negative
			loc.z = ph_limit;
		}
		else
			loc.z = nz;
	}
	else {											// negative
		float nz = loc.z - dist;
		if (nz < nh_limit) {
			direction = 1;								// change direction to postive
			loc.z = nh_limit;
		}
		else
			loc.z = nz;
	}
	lut = time;
}

