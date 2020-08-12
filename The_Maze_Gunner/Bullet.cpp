#include "Bullet.h"
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include<math.h>

Bullet::Bullet(float id, Location & location) :
	RenderableObject(id, location, 1), c_loc(location)
{

}

void Bullet::drawBullet()
{
	glPushMatrix();
	// Draw Bullet
	glTranslatef(0.0, 0.95, 0.0);
	glColor3f(0, 255, 255);
	glutSolidSphere(0.25, 20, 20);
	glPopMatrix();
}

// increasing x 
void Bullet::update_linear()
{
	loc.x += 0.3;
}

// send energy blast back to players origin
void Bullet::goToOrigin()				// since only one blast will be used each time 
{   
	loc.x = c_loc.x;
	loc.z = c_loc.z;
}

void Bullet::changeXCoZco(float xco, float zco)
{
	loc.x = xco;
	loc.z = zco;
}

void Bullet::update()
{
	update_linear();
}

void Bullet::render()
{
	glPushMatrix();
	glTranslated(loc.x, loc.y, loc.z);		// move to this position
	drawBullet();							// will draw the bullet 
	glPopMatrix();
}
