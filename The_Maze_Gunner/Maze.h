#pragma once
#include <iostream>
#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h> 
#include <cmath>
#include <windows.h>

using namespace std;

/*Note that we had to do research on how to draw and render a basic maze , the code provided was
redesigned and implemented */
class Maze {
private:
	const static GLint X_SIZE = 10; 
	const static GLint Z_SIZE = 10; 

	const GLint COMPLEXITY_LOOP_RUNS = (X_SIZE * Z_SIZE * 20 );  // howmany times to attempt to add a "flase path" coordinate

	// logic constants for map contents
	const static GLint SOLUTION_PATH = 2;
	const static GLint FALSE_PATH = 1;
	const static GLint NO_PATH = 0;

	enum Direction {EAST, SOUTH , WEST , NORTH};

	const GLfloat MAZE_EXTREME_LEFT = -5.0f ;     // this affects the collision
	const GLfloat MAZE_EXTREME_TOP = -9.0f ;      // this affects the collision 
	const GLfloat HALF_CUBE = 4.0f ;
	const GLfloat FULL_CUBE = HALF_CUBE + HALF_CUBE;
	const GLfloat START_X_AT = -10.0f ;
	const GLfloat START_Z_AT = 0.0f;     

	const GLfloat LEFTMOST_CUBE_CENTER = MAZE_EXTREME_LEFT + HALF_CUBE;

	const GLfloat COLLIDE_MARGIN =  0.15625  ;  //To keep from looking inside the cubes

public :

	 Maze();

	 GLint((*(maze_innards()))[Z_SIZE]); //Returns a pointer to the variable portion of the  maze, in 2D format.

	 void drawCube(GLfloat x, GLfloat y, GLfloat z); //Draws a cube centered at (x,y,z)
	 void createPaths();
	 bool isComplex(int x, int y); 
	 void complicateMaze();
	 void printMaze();
	 bool collide(float x_at , float y_at); //Is player in a state of collision? with the maze 
	 bool pathOpen(float x_at, float z_at);      
};
