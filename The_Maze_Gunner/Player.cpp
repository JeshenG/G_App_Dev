#include "Player.h"
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include<math.h>
#include <cmath>
#include "Maze.h"

Player::Player(float id, Location & location, string fName)
	: RenderableObject(id, location, 1), c_loc(location) 
{
	playName = fName;
	score = 0;
	xPrev = c_loc.x;
	zPrev = c_loc.z;   // for the bounce back feature 
}

/*research with trial and error had to be done in order to draw the player object*/
void Player::drawPlayer()  // draw a player using openGL
{
	glPushMatrix();

	glScalef(0.6, 0.6, 0.6); 
	glRotatef(90, 0, 1, 0);

	glPushMatrix();
	glColor3ub(153, 76, 0);
	glTranslatef(0, 1.9, 0);					
	glutSolidSphere(0.6, 120, 120);				//head
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.1, 0); 
	glScalef(0.5, 1, 0.5);
	glutSolidCube(0.5);							 //neck
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 0, 0);						 // red
	glTranslatef(0, 0.104, 0);
	glScalef(4, 4.4, 2.5);					   
	glutSolidCube(0.5);							//body
	glPopMatrix();

	glPushMatrix();
	glColor3ub(153, 76, 0);
	glTranslatef(1.2, 0.5, 0);      
	glScalef(2.0, 0.5, 0.5);
	glutSolidCube(0.4);						 //right arm

	glTranslatef(0.2, -1, 0);
	glScalef(0.3, 4, 0.5);           
	glutSolidCube(0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, -1.8, 0);
	glScalef(0.5, 6.5, 0.5);             //leg
	glutSolidCube(0.5);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.5, -1.8, 0);
	glScalef(0.5, 6.5, 0.5);            //leg
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -1, 0);
	glutSolidCube(0.10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.2, 0.5, 0);        //left arm
	glScalef(2.0, 0.5, 0.5);
	glutSolidCube(0.4);

	glTranslatef(-0.2, -1, 0);
	glScalef(0.3, 4, 0.5);
	glutSolidCube(0.6);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.3, 0.0);
	glPopMatrix();
	
}



void Player::goUp() {						 // as you go up the x value increases
	float dist = 1.0;
	float nx = loc.x + dist;

	if (!collidesWithMaze()) {				  // if already in collision state go Back 
		xPrev = loc.x;
		zPrev = loc.z;
	}
	if (nx < 90   && (!collidesWithMaze())) {   
		loc.x = nx;
	}
	else {  // bounce back 
		loc.x -=1.0f;   // i put this here 
	}
	render();
}


void Player::goDown() {				  // as you go down the x value decrease
	float dist = 1.0;
	float nx = loc.x - dist;

	if (!collidesWithMaze()) {			// if already in collision state go Up
		xPrev = loc.x;
		zPrev = loc.z;
	}
	if (nx > -90 && (!collidesWithMaze())) {   // only if x value greater than -90 then you may move downwards
		loc.x = nx;
	}
	else {  // bounce back 
		loc.x += 1.0f;
	}
	render();
}
                 
             
void Player::turnLeft()  // as you go left , z value decreases
{
	// remember to make changes to this code 
	float dist = 1.0;
	float nz = loc.z - dist;

	if (!collidesWithMaze()) {   // if already in collision state go Right
		xPrev = loc.x;
		zPrev = loc.z;
	}
	if (nz > -90 && (!collidesWithMaze())) { // if x value less than 90 , dont move to the right 
		loc.z = nz;
	}

	else { // bounce back feature 
		loc.z += 1.0f;     // 
	}
	render();
}

void Player::turnRight()  //  if you go right , the z value increases
{
	float dist = 1.0;
	float nz = loc.z + dist;

	if (!collidesWithMaze()) {   // if already in collision state go Left
		xPrev = loc.x;
		zPrev = loc.z;
	}
	if (nz < 90  && (!collidesWithMaze())) {  // if z value less than 90 , dont move to the right
		loc.z = nz;
	}
	else {   // bounce back
		loc.z -= 1.0f; 
	}
	render();
}


void Player::render()
{
	if (collidesWithMaze()) { // if there is a collision then go back to previous coordinates
		loc.x = xPrev;
		loc.z = zPrev;  
	}

	// remember to update position before render (x and z position)
	glPushMatrix();
	glTranslated(loc.x, loc.y, loc.z); // move to this position
	drawPlayer();
	glPopMatrix();
	
}

bool Player::collidesWithMaze()
{
	Maze m;
	if (m.collide(loc.x , loc.z)) {    // check if the player collides with the maze 
		return true;
	}
	return false;
}


// other non graphics related member functions 
string Player::getFName() const
{
	return playName;
}

void Player::incScore()
{
	score+=10;
}

void Player::decScore()
{
	score--; 
}

int Player::getScore() const
{
	return score;
}




