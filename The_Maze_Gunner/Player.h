#pragma once
#include "RenderableObject.h"
#include "Location.h"
#include <string>


using namespace std;

class Player : public RenderableObject {  // Players extends RendarableObject
private:
	string playName;
	//string networkID; // might not use (for multiplayer )
	int score;
	Location c_loc;                      //initial location of player
	bool collided = false;
	void drawPlayer();
	float xPrev;
	float zPrev;   // when a collision occurs , sent player back to old position 

public :

	Player(float id, Location& location,  string fName);
	string getFName() const;
	void incScore();
	void decScore();
	int getScore() const; 
	                    // changes to display 
	void turnLeft();    // should be goLeft
	void turnRight();    // rename these functions
	void goUp();
	void goDown();
	void render();
	bool collidesWithMaze();
};
