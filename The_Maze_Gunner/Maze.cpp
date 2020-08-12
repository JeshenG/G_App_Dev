#include "Maze.h"
#include "Location.h"
#include <vector> // to store the maze coordinates 

Maze::Maze()
{
	
}

// borrowed code
GLint((*(Maze::maze_innards()))[Z_SIZE])
{
	static int whole_maze[X_SIZE + 2][Z_SIZE + 2] = { NO_PATH };
	return (int(*)[Z_SIZE])(&whole_maze[0][1]);
}

//our code 
void Maze::drawCube(GLfloat x, GLfloat y, GLfloat z)
{
	glColor3ub(255, 223,0);

	glPushMatrix();

	// Top of cube
	glTexCoord2d(1.0, 1.0);
	glVertex3f(x + HALF_CUBE, HALF_CUBE, z - HALF_CUBE); // Top Right Of The Quad (Top)
	glTexCoord2d(0.0, 1.0);
	glVertex3f(x - HALF_CUBE, HALF_CUBE, z - HALF_CUBE); // Top Left Of The Quad (Top)
	glTexCoord2d(0.0, 0.0);
	glVertex3f(x - HALF_CUBE, HALF_CUBE, z + HALF_CUBE); // Bottom Left Of The Quad (Top)
	glTexCoord2d(1.0, 0.0);
	glVertex3f(x + HALF_CUBE, HALF_CUBE, z + HALF_CUBE); // Bottom Right Of The Quad (Top)

													 // Bottom
	glTexCoord2d(1.0, 1.0);
	glVertex3f(x + HALF_CUBE, -HALF_CUBE, z + HALF_CUBE); // Top Right Of The Quad (Bottom)
	glTexCoord2d(0.0, 1.0);
	glVertex3f(x - HALF_CUBE, -HALF_CUBE, z + HALF_CUBE); // Top Left Of The Quad (Bottom)
	glTexCoord2d(0.0, 0.0);
	glVertex3f(x - HALF_CUBE, -HALF_CUBE, z - HALF_CUBE); // Bottom Left Of The Quad (Bottom)
	glTexCoord2d(1.0, 0.0);
	glVertex3f(x + HALF_CUBE, -HALF_CUBE, z - HALF_CUBE); // Bottom Right Of The Quad (Bottom)
	
													  // Front
	glTexCoord2d(1.0, 1.0);
	glVertex3f(x + HALF_CUBE, HALF_CUBE, z + HALF_CUBE); // Top Right Of The Quad (Front)
	glTexCoord2d(0.0, 1.0);
	glVertex3f(x - HALF_CUBE, HALF_CUBE, z + HALF_CUBE); // Top Left Of The Quad (Front)
	glTexCoord2d(0.0, 0.0);
	glVertex3f(x - HALF_CUBE, -HALF_CUBE, z + HALF_CUBE); // Bottom Left Of The Quad (Front)
	glTexCoord2d(1.0, 0.0);
	glVertex3f(x + HALF_CUBE, -HALF_CUBE, z + HALF_CUBE); // Bottom Right Of The Quad (Front)


														// Back
	glTexCoord2d(1.0, 1.0);
	glVertex3f(x - HALF_CUBE, HALF_CUBE, z - HALF_CUBE); // Top Right Of The Quad (Back)
	glTexCoord2d(0.0, 1.0);
	glVertex3f(x + HALF_CUBE, HALF_CUBE, z - HALF_CUBE); // Top Left Of The Quad (Back)
	glTexCoord2d(0.0, 0.0);
	glVertex3f(x + HALF_CUBE, -HALF_CUBE, z - HALF_CUBE); // Bottom Left Of The Quad (Back)
	glTexCoord2d(1.0, 0.0);
	glVertex3f(x - HALF_CUBE, -HALF_CUBE, z - HALF_CUBE); // Bottom Right Of The Quad (Back)


													  // left of cube
	glTexCoord2d(1.0, 1.0);
	glVertex3f(x - HALF_CUBE, HALF_CUBE, z + HALF_CUBE); // Top Right Of The Quad (Left)
	glTexCoord2d(0.0, 1.0);
	glVertex3f(x - HALF_CUBE, HALF_CUBE, z - HALF_CUBE); // Top Left Of The Quad (Left)
	glTexCoord2d(0.0, 0.0);
	glVertex3f(x - HALF_CUBE, -HALF_CUBE, z - HALF_CUBE); // Bottom Left Of The Quad (Left)
	glTexCoord2d(1.0, 0.0);
	glVertex3f(x - HALF_CUBE, -HALF_CUBE, z + HALF_CUBE); // Bottom Right Of The Quad (Left)
			

														// Right of cube
	glTexCoord2d(1.0, 1.0);
	glVertex3f(x + HALF_CUBE, HALF_CUBE, z - HALF_CUBE); // Top Right Of The Quad (Right)
	glTexCoord2d(0.0, 1.0);
	glVertex3f(x + HALF_CUBE, HALF_CUBE, z + HALF_CUBE); // Top Left Of The Quad (Right)
	glTexCoord2d(0.0, 0.0);
	glVertex3f(x + HALF_CUBE, -HALF_CUBE, z + HALF_CUBE); // Bottom Left Of The Quad (Right)
	glTexCoord2d(1.0, 0.0);
	glVertex3f(x + HALF_CUBE, -HALF_CUBE, z - HALF_CUBE); // Bottom Right Of The Quad (Right)
	

	glPopMatrix();
}

// borowed code
/*This member function cuts out the paths in the cube to create the maze*/
void Maze::createPaths() // 
{
	int path_leg_length = 3;
	int DIFFICULTY = /*6*/ 2;

	//Temporary position and direction variables
	int x = 0, z = 0;
	int d = EAST;

	bool facing_east_west = true;

	//Start at a random row at column 0
	z = rand() % Z_SIZE;

	//Build correct path column by column
	while (x<X_SIZE)
	{
		//March forward designated leg length in current direction
		while (path_leg_length-- && x<(X_SIZE))
		{
			switch (d)
			{
			case EAST:
				(maze_innards())[x++][z] = SOLUTION_PATH;
				break;

			case SOUTH:
				(maze_innards())[x][z++] = SOLUTION_PATH;
				break;

			case WEST:
				(maze_innards())[x--][z] = SOLUTION_PATH;
				break;

			case NORTH:
				(maze_innards())[x][z--] = SOLUTION_PATH;
				break;
			}
		}

		int tempx, tempy;

		do
		{
			tempx = x;
			tempy = z;
			if (facing_east_west) //Time for a turn... e/w -> n/s ; n/s -> east
			{
				d = (rand() % 2) ? NORTH : SOUTH;
			}
			else {
				d = EAST;
			}

			//Close to end; just complete the path
			if (X_SIZE - x<3)
			{
				d = EAST;
				path_leg_length = X_SIZE - x;
			}

			/*Don't require travel to West... a compromise
			that simplifies things. In practice, the user
			in the heat of battle will perceive a series of
			left and right turns w/o noticing absolute
			direction. Also, the user will inevitably
			deviate from the correct path, possibly requiring
			travel to the west. */

			//Set path_leg_length... must be at least 3 or we will make
			// "rooms," which would defy the design criteria stating that
			// there ought only to be one correct path through the maze.
			if (facing_east_west)
			{
				path_leg_length = ((rand() % (X_SIZE / DIFFICULTY) + 2));
			}
			else {
				path_leg_length = ((rand() % (Z_SIZE / DIFFICULTY) + 2));
			}

			switch (d)
			{
			case EAST:
				tempx += path_leg_length;
				break;
			case SOUTH:
				tempy += path_leg_length;
				break;
			case WEST:
				tempx -= path_leg_length;
				break;
			case NORTH:
				tempy -= path_leg_length;
				break;
			}
			//check here for overflow condition - JBW
		} while (tempx<0 || tempy<0 || tempy >= Z_SIZE);

		// Decided on a new direction... if prior direction
		// was vertical, new direction is horizontal and vice-versa
		facing_east_west = !facing_east_west;
	}

}

//not our code 
/*This function makes sure that there is only one path out of maze*/
bool Maze::isComplex(int x, int z)
{
	//Check ranges
	if (x <= 0) return false;
	if (z<0) return false;
	if (x >= X_SIZE - 1) return false;
	if (z >= Z_SIZE) return false;

	//Already part of the open paths
	if ((maze_innards())[x][z]) return false;

	//It's a valid point of obfuscation iff exactly one of the adjacent
	// points is open. If 2+ such points are open, then we're potentially
	// creating a "shortcut," which would result in a 2nd path between
	// start and finish. If 0 such points are open, we're potentially
	// creating an orphan.
	int ret = 0;

	if ((maze_innards())[x + 1][z]) ++ret;
	if (x - 1 >= 0 && (maze_innards())[x - 1][z]) ++ret;
	if (z + 1<Z_SIZE && (maze_innards())[x][z + 1]) ++ret;
	if (z - 1 >= 0 && (maze_innards())[x][z - 1]) ++ret;

	if (ret == 1)return true;
	else return false;
	
}

// our code 
void Maze::complicateMaze()
{
	int x, z;
	int c = 0;

	for (int ob = 0; ob < COMPLEXITY_LOOP_RUNS; ++ob)
	{
		x = rand() % X_SIZE;
		z = rand() % Z_SIZE;

		if (isComplex(x, z))
		{
			c++;
			(maze_innards())[x][z] = FALSE_PATH;
		}
	}
}


void Maze::printMaze()
{
	int x, z;
	for (x = 0; x<X_SIZE; ++x) //Print a border
	{
		drawCube(MAZE_EXTREME_LEFT + HALF_CUBE + ((GLfloat)x*FULL_CUBE),
			0.0,
			MAZE_EXTREME_TOP + HALF_CUBE);

		drawCube(MAZE_EXTREME_LEFT + HALF_CUBE + ((GLfloat)x*FULL_CUBE),
			0.0,
			MAZE_EXTREME_TOP + HALF_CUBE + FULL_CUBE + (Z_SIZE*(FULL_CUBE)));	
	}

	for (z = 0; z<Z_SIZE; ++z) //Maze proper
	{
		for (x = 0; x<X_SIZE; ++x)
		{
			if ((maze_innards())[x][z] == NO_PATH)
			{
				drawCube(LEFTMOST_CUBE_CENTER + ((GLfloat)x*FULL_CUBE),
					0.0,
					MAZE_EXTREME_TOP + HALF_CUBE + FULL_CUBE + ((GLfloat)z*FULL_CUBE));
			}
		}
	}
}


// note side collision is not working properly 
bool Maze::collide(float x_at, float z_at)  // players coordinates passed 
{
	int x, z;

	//Walls...     (am assuming this works )
	
	if (x_at >= MAZE_EXTREME_LEFT - COLLIDE_MARGIN &&
		x_at <= MAZE_EXTREME_LEFT + X_SIZE*FULL_CUBE +  COLLIDE_MARGIN)
	{
		if (z_at <= (MAZE_EXTREME_TOP + FULL_CUBE) + COLLIDE_MARGIN &&
			z_at >= MAZE_EXTREME_TOP - COLLIDE_MARGIN )
		{
			return 1;
		}

		if (z_at <= (MAZE_EXTREME_TOP + FULL_CUBE) + FULL_CUBE + (Z_SIZE*FULL_CUBE) + COLLIDE_MARGIN &&
			z_at >= MAZE_EXTREME_TOP + FULL_CUBE + (Z_SIZE*FULL_CUBE) - COLLIDE_MARGIN)
		{
			return 1;
		}
	}
	
	
	//Maze proper     (there is an error here , code is not allowing player to go through path properly )
	                                 // im assuming i need to make a change to COLLIDE_MARGIN
	for (z = 0; z<Z_SIZE; ++z)
	{
		for (x = 0; x<X_SIZE; ++x)
		{
			if ((maze_innards())[x][z] == NO_PATH)
			{

				// where x_at is the users x position 
				// collide margin isnt really that important 

				if (x_at >= MAZE_EXTREME_LEFT + x*FULL_CUBE - COLLIDE_MARGIN  &&
					x_at <= MAZE_EXTREME_LEFT + FULL_CUBE + x*FULL_CUBE + COLLIDE_MARGIN   &&

					z_at >= MAZE_EXTREME_TOP + (z + 1)*FULL_CUBE - COLLIDE_MARGIN &&    // z position
					z_at <= MAZE_EXTREME_TOP + (z + 2)*FULL_CUBE + COLLIDE_MARGIN    )   // z position
				{
					return 1;

				}	
			}
		}
	}
	
   return 0;
}



// our code 
/*This function will return true if a point is within an open path of the maze */
bool Maze::pathOpen(float x_at, float z_at) {
	for (int z = 0; z < Z_SIZE; ++z)
	{
		for (int x = 0; x < X_SIZE; ++x)
		{
			if ((maze_innards())[x][z] == SOLUTION_PATH)
			{
				// where x_at is the users x position 
				if (x_at >= MAZE_EXTREME_LEFT + x*FULL_CUBE - COLLIDE_MARGIN  &&
					x_at <= MAZE_EXTREME_LEFT + FULL_CUBE + x*FULL_CUBE + COLLIDE_MARGIN   &&

					z_at >= MAZE_EXTREME_TOP + (z + 1)*FULL_CUBE - COLLIDE_MARGIN &&    // z position
					z_at <= MAZE_EXTREME_TOP + (z + 2)*FULL_CUBE + COLLIDE_MARGIN)   // z position
				{
					return 1;
				}
			}
		}
	}

}







