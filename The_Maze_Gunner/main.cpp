#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <vector>
#include <string>
#include <Windows.h>					// to use sound functions 
#include <Mmsystem.h>
#include <iostream>

#include "RenderableObject.h"
#include "Player.h"
#include "Maze.h"						// note that some methods in this class are not ours
#include "Ghost.h"					// include the Ghost header
#include "QuestionOBJ.h"			// for the question boxes


#include <random>
                               
                        // for dialog box 
#include "stdafx.h" 
#include "dlgX.h" 
#include "Win32InputBox.h"

#include <stdio.h>
#include <sstream>
#include <fstream>
//#include <stdlib.h>

#include "MathQuestion.h"  // include actual maths question header 

#include "BackgroundSound.h"   // for the sound effects (not background music)
#include "Bullet.h"



#define TEXTURE_FILE "wall.bmp"
#define BACKGROUND_MUSIC  "bgSound.wav"
#define GUN_NOISE "Laser1.wav"    // laser beam
#define SCREAM "man-scream-01.wav"
#define GHOST_SCREAM "EnemyDeath.wav"
#define MATHS_QUESTIONS "math_questions.txt"
#define SCOREFILE "PlayerScores.txt"


#pragma warning(disable:4996)


using namespace std;

// Global variables
const float PI = 22.0 / 7.0;


int time_og = 0;		// for timing of gunshot or blast 
int t = 0;				// for blast 
Bullet * oneBullet;
bool gunTrigered = false;



// borrowed code  for texture
//--------------------------------------------------------------
//Variables for textures
const GLint TEXTURE_SIZE2 = 225;
const GLint TEXTURE_SIZE = 512;
const GLint MAX_APPERROR = 64;
const GLint WINDOW_MARGIN = 100;
const GLint BMP_HEADER_SIZE = 54;
//--------------------------------------------------------------




/*Global Camera variables */
float R = 0.01;		// used to align camera directly behind player 
float CamX;			// basically same as EyeX 
float CamY;
float CamZ;
int view = 0;


Player * pL;		// new pointer 
Maze m;				// instance of the Maze


BackgroundSound blast;		// for the sound effects  (gun)
BackgroundSound scream;		//  (screaming noise)   , when collides with ghost 

vector<RenderableObject *> ghosts;    // for all the ghosts  (vector of pointers)
vector<RenderableObject *> boxes;    // boxes , container for the question objects

/*for the random coordinates of the Question Box objects*/ 
vector<float> ranBoxXCos;     
vector<float> ranBoxZCos;

vector<float> ranGhostXCos;  // for the random coordinates of the Ghost objects (default coordinates) 
vector<float> ranGhostZCos; 

/*Variables that will be used for the questioning*/
MathQuestion mq;
int numQCorrect= 0; //  for the actual questions that will be asked  
int numQWrong = 0;    

int quesIndex=0;			// random index that will be used for the questions
string userAnswer;			// Actual answer that the user inputs will be stored in this string
bool wasCorrect = false;	// to check if the user's provided solution was corrrect

string name="Gsizz"; 



/*for the Maths Questions
to generate random number in a range*/
string getRandomQuestion() {    
	random_device rseed;
	mt19937 rng(rseed());
	uniform_int<int> dist(0, mq.getSize()-1);  // index values

	quesIndex = dist(rng);                    // get a random index withing the range
	return mq.getQuestion(quesIndex);         // return a random question in the list
}



void freeMemory();       // prototype function redefined , for the memory management

// display message at the end
void showCreditsDetails() {
	string message = "\nThis Game was developed for New West Secondary School.\nWe hope that the students enjoy playing this educational game :) \n\nThis game was developed by C0deine  ";
	const char * mwe = message.c_str();
	MessageBox(0, mwe, "-------MAZE_GUNNER-------      @G-sizz", MB_OK);
}




/*to check if the player finished the game*/  
void checkFinishGame() {
	if (pL->getLocation().x >= 75 && (pL->getLocation().z >= 56 && pL->getLocation().z <= 62)) {
		string msg = "You completed the Game with a Score of : " + to_string(pL->getScore());
		const char * mwe = msg.c_str();
		MessageBox(0,  mwe,"You Completed the maze !!!", MB_OK);
		showCreditsDetails();
		freeMemory();         // Deallocate the allocated memory for the Dynamic variables
		exit(0);
	}
}



//display dialog box and ask user to enter their name, then return their name
string getUserName() {
	string ask = "Please enter your name :";
	const char *myques = ask.c_str();
	char buf[100] = { 0 };

	CWin32InputBox::InputBox("Hi there ! :)", myques, buf, 100, false);
	string s = buf;
	return s;
}



/* function to display an input dialog box , will ask the user a maths question,
and user must provide the input*/
void displayInput(string question) {    // to display the input box
	const char *myques = question.c_str();
	char buf[100] = { 0 };

	CWin32InputBox::InputBox("Maths Question", myques, buf, 100, false);
	string s = buf;
	userAnswer = s;

	// must remove blank spaces from the input 
	if (mq.removeBlankSpaces(userAnswer) == mq.getAnswer(quesIndex)) {   
		printf("\nCorrect answer !");						// increment score 
		pL->incScore();										// increase players score by 10
		printf("%s %d", "score is : ", pL->getScore());
		wasCorrect = true;    
		MessageBox(0, "The answer you provided was correct !", "Well Done", MB_OK);
	}
	else if(mq.removeBlankSpaces(userAnswer) == mq.removeBlankSpaces("pass")){ // then no score will be added 
		printf("\nUser did not answer this question ");
	}
	else {
		// do nothing 
		printf("\nIncorrect answer !");
		string msg = "The correct answer is " + mq.getDisplayAnswer(quesIndex);
		const char * mwe = msg.c_str();
		MessageBox(0, mwe,"Incorrect !",   MB_OK);
	}
	gunTrigered = false;  // for debugging gun 
}



/*check if player collides with any question object */
void checkQuestionOBJCollide() {  // flop with this is that it needs to remove the coordinates
	for (int i = 0; i < boxes.size(); i++) {    
		if ((ranBoxXCos[i]== pL->getLocation().x) && (ranBoxZCos[i] == pL->getLocation().z)) {
			printf("%s","\nThe player collided with a Question object !");	
			displayInput(getRandomQuestion());								// call the dialog box

			// if the question is correct remove the object from the QuestionOBJ vector
			if (wasCorrect) {
				boxes.erase(boxes.begin() + i);             // remove this actual question object from the boxes vector
				ranBoxXCos.erase(ranBoxXCos.begin() + i);
				ranBoxZCos.erase(ranBoxZCos.begin() +i );   // remove these coordinates from the game 
				wasCorrect = false;
			}
		}
	}
	gunTrigered = false; // debug gun 
}



/*check if the player collides with any ghost*/ 
void checkGhostPlayerCollide() {
	for (int i = 0; i < ghosts.size(); i++) {
		// check if x and z coordinates within the range
		if (((pL->getLocation().x <= ghosts[i]->getLocation().x + 1) && (pL->getLocation().x >= ghosts[i]->getLocation().x - 1)) &&
			((pL->getLocation().z <= ghosts[i]->getLocation().z + 1) && (pL->getLocation().z >= ghosts[i]->getLocation().z - 1))  ) { // remember that Bullet has same coordinates as the player 

			scream.OpenSounds(SCREAM);
			scream.PlaySounds();

			if (pL->getScore() != 0) {   // score can only decrease if score above 0; 
				pL->decScore();
				printf("%s %d ", "\nPlayer score decreased :", pL->getScore());
			}
		}
	}
}



/*This function checks if the energy blast collided with a ghost,*/
void checkGhostBulletCollide() {
	for (int i = 0; i < ghosts.size(); i++) {
		// check if x and z coordinates within the range
		// bullet can only collide if gun was triggered
		if (((oneBullet->getLocation().x <= ghosts[i]->getLocation().x + 1) && (oneBullet->getLocation().x >= ghosts[i]->getLocation().x - 1)) &&
			((oneBullet->getLocation().z <= ghosts[i]->getLocation().z + 1) && (oneBullet->getLocation().z >= ghosts[i]->getLocation().z - 1)) &&
			 gunTrigered==true) { 

			printf("%s", "\nThe Bomb collided with a Ghost !"); // remove this ghost from the vector then 

			scream.OpenSounds(GHOST_SCREAM);
			scream.PlaySounds();

			// makes uses of the iterator for vectors
			ghosts.erase(ghosts.begin()+i);  // remove that specific ghost , cause he got shot 
		}
	}
}



/*This function will use parameter passing by reference , pass in object container by reference ,
xCoordinate container and zCoordinate by reference// its a generic function*/ 
template <class OBJType>
void generateRandomCoordinatesAndObjects(vector<OBJType*> & objvector , vector<float> & xCoords , vector<float> & zCoords , int numObjects, int minRange, int maxRange, string objType) {
	// to generate random number in a range
	random_device rseed;
	mt19937 rng(rseed());
	uniform_int<int> dist(minRange, maxRange);    // z and x values 
	
	int objCount = 0;							// the number of renderable objects that should be created

	while (objCount != numObjects+10) {       // Added 10 ,to generate 10 extra coordinates incase of index issue
		float xCo = (float)(dist(rng));
		float zCo = (float)(dist(rng));

		bool valid = false;						// to check if a X and Z coordinate are valid

		if (objType == "Q") {					// for question obj
			if (m.pathOpen(xCo, xCo)) {			// note that question cannot collide with the maze but can be in the paths
				valid = true;					 // this a valid point 
			}
		}
		else if(objType == "G"){				 // for ghost obj , ghosts can be anywhere
			valid = true; 
		}  

		if (valid)  {					
			xCoords.push_back(xCo);
			zCoords.push_back(zCo);				 // push random coorinates into vectors , for the ghost objects, and question objects
			objCount += 1;
			valid = false;						// change valid back to false 
		}
	}

	
	for (int i = 0; i < numObjects ; i++) {							// create the questionOBJs/ ghosts objects and store them in the vector 
		Location loc = Location(xCoords[i], 0, zCoords[i]);

		if (objType =="Q") {										// put this pointer in the vector    (for question object)
			objvector.push_back(new QuestionOBJ(1, loc));
		}
		else if (objType == "G") {				                     // for ghost object
			loc = Location(xCoords[i], 0.8, zCoords[i]);			// ghosts should be slightly high
			objvector.push_back(new Ghost(1, loc));
		}
	}
}



/* Initialize OpenGL Graphics  & Other variables/ populate containers (vectors)*/
void init()
{
	 
	// Set "clearing" or background color
	glClearColor(0, 0, 0, 1);							//for  background 

	
	//---------------------------------------------------------------------------------------------------------------------------------------------
	glEnable(GL_DEPTH_TEST);							// turns on hidden surface removal so that objects behind other objects do not get displayed
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	//----------------------------------------------------------------------------------------------------------------------------------------------

	//string name = getUserName();  // returns a string
	Location loc = Location(-70, 0, 0);					//Create the player's original position
	pL = new Player(1,loc, name);

	loc.y -= 0.5;										// decrease the Y coordinate for the energy blast
	oneBullet = new Bullet(1, loc);				// should have same position as the player


	// generate and store random coordinates for the Question objects and the Ghost objects,(using Generic void function)
	generateRandomCoordinatesAndObjects<RenderableObject>(boxes, ranBoxXCos, ranBoxZCos, 40, -10, 70 , "Q");		// generate question objects
	generateRandomCoordinatesAndObjects<RenderableObject>(ghosts, ranGhostXCos, ranGhostZCos, 20, -10, 80, "G");	 // generate ghosts

	mq = MathQuestion(MATHS_QUESTIONS);
	mq.readTextFile();									// read in the text file 

	t = glutGet(GLUT_ELAPSED_TIME);						// used for the timing of the energy blast
}



// This sets the camera to first person view
void SetFPCamera()
{
	CamX = pL->getLocation().x ;
	CamY = pL->getLocation().y ;
	CamZ = pL->getLocation().z + R;

	gluLookAt(CamX, CamY, CamZ,									// eye position
		      pL->getLocation().x+1, pL->getLocation().y+0.01, pL->getLocation().z,     // position to look at        
		      0, 1, 0);
	
}



// This function positions the camera above the maze 
// Provides a birds eye view of the game
void upCamera()
{
	CamX = pL->getLocation().x - 30;
	CamY = pL->getLocation().y + 1;
	CamZ = pL->getLocation().z + R;

	gluLookAt(CamX, 60, CamZ,									// eye position
			  pL->getLocation().x, 0, pL->getLocation().z,     // position to look at        
	        	0, 1, 0);										// up vector
}



void setCamera();					// prototype


void rotateCam_Left() {				//rotates the camera left
	if (R<7)
	{
		R += 0.5;
		setCamera();
	}
}

void rotateCam_Right() {			// rotates the camera right
	if (R >-7)
	{
		R -= 0.5;
		setCamera();
	}
}



// for the normal 3rd person camera 
void setCamera() {
	CamX = pL->getLocation().x - 4;
	CamY = pL->getLocation().y + 1.2;
	CamZ = pL->getLocation().z + R;

	gluLookAt(CamX, CamY, CamZ, pL->getLocation().x, pL->getLocation().y, pL->getLocation().z, 0, 1, 0);

}



// Prototype functions for the borrowed code 
//------------------------------------------------------------------------------------------------------
void app_assert_success(const char* szz);
GLuint maketex(const char* tfile, GLint xSize, GLint ySize);				//returns tex. no.
//------------------------------------------------------------------------------------------------------



// draws text to the screen (borrowed code)
void drawText(const char *text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[24];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);

}


void drawGround() {
	glColor3ub(75, 189, 67);					// light green
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, -2.0f, -100.0f);		  // y is the height 
	glVertex3f(-100.0f, -2.0f, 100.0f);
	glVertex3f(100.0f, -2.0f, 100.0f);
	glVertex3f(100.0f, -2.0f, -100.0f);
	glEnd();
}



void render()
{
	string text2 = "	PLAYER:	"+ name;
	string text = "	CURRENT SCORE: " + to_string(pL->getScore());
	string text3 = "THE MAZE GUNNER";

	// GL_DEPTH_BUFFER_BIT - resets the depth test values for hidden surface removal
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//to switch between cameras 
	if (view ==0) { // working
		setCamera();
	}
	else if (view ==1) {
		upCamera();
	}
	else if (view == 2) {
		SetFPCamera();
	}

	//-------------------------------------------------------------------
	static bool init = 0;
	static GLuint mesh; /*Texture for the cube*/
	static GLuint grass; /*Texture for the sky*/
	if (!init)
	{
		init = 1;
		mesh = maketex(TEXTURE_FILE, TEXTURE_SIZE, TEXTURE_SIZE);
		//grass = maketex(GROUND_FILE, TEXTURE_SIZE, TEXTURE_SIZE);
	}
	//----------------------------------------------------------------------


	// Draw ground 
	drawGround();
	pL->render();   // render the player

	// renders all the questionOBJs 
	for (int i = 0; i < boxes.size(); i++) {
		boxes[i]->render();
	}

	// render all the ghosts
	for (int i = 0; i < ghosts.size(); i++) {
		ghosts[i]->render();
	}


	//-------------------------------------------------------
	glBindTexture(GL_TEXTURE_2D, mesh);

	glBegin(GL_QUADS);
	m.printMaze();					// calling from other class
	glEnd();
	//---------------------------------------------------------


	// for the movement of the  energy blast
	if (gunTrigered) {
		oneBullet->update();	
	}
	oneBullet->render();

	// draws the text to the screen
	glColor3f(252,252,252);
	drawText(text.data(), text.size(), 2, 560);
	drawText(text2.data(), text2.size(), 2, 580);
	drawText(text3.data(), text3.size(), 500, 580);

	glFlush();   // ******** DO NOT FORGET THIS **********
}


/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
void display()
{
	//update(); // no need to update all done in render
	render();
}



// since update always being called , the ghost collision check should be done in here 
// basically will stop the rendering of the energy blast 
void update(int value)
{
	time_og = glutGet(GLUT_ELAPSED_TIME); // get the elapsed time in milliseconds since glutInit() was executed
	
	checkGhostBulletCollide(); // within the 5 seconds check if there is a collision

	if ((time_og - t) / 1000 == 5) {   // if time afer energy blast is equal to 5 seconds , go back to the player's location
		gunTrigered = false;
		oneBullet->changeXCoZco(pL->getLocation().x, pL->getLocation().z);
		t = time_og;
	}

	glutTimerFunc(0, update, 0);
}



/* Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height */
void reshape(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)	h = 1;

	GLfloat ratio = 1.0f * (GLfloat)w / (GLfloat)h;

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the clipping volume
	gluPerspective(45, ratio, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}



void processNormalKeys(unsigned char key, int xCo, int yCo) {
	typedef unsigned char uchar;			// using type def 	
	switch (key) {
	
	case 32:								// space bar for shooting
		blast.OpenSounds(GUN_NOISE);		// open sound 

		if (gunTrigered == false) {			// can only press this once gun is triggered
			gunTrigered = true;	
			blast.PlaySounds();
		}
		break;

	case 27: printf("\n %s ", "Clicked on esc ");
			 exit(0); 
		     break;						// esc
					   
	case (uchar)120:				//	X on keyboard   , moving camera backwards
		view = 0;					 // normal view 
		break;

	case (uchar)97:				//A on keyboard,  move camera to the left
		printf("\n %s ", "Clicked on A");
		rotateCam_Left();
		break;

	case (uchar)100:					//D on keyboard,   move camera to the right
		printf("\n %s", "Clicked on D");
		rotateCam_Right();
		break;

	case (uchar)119:						// W on keyboard,  w is to switch to top/ birds eye view
		printf("\n %s", "Clicked on W");
		view = 1;    // top view 
		break;

	case (uchar)102:						// F on keyboard switches to First Person View
		printf("\n %s", "Clicked on F");
		view = 2;    // top view 
		break;
	}
	glutPostRedisplay();
}


/*this function checks if the blast was fired, checks if the player walked into a ghost , or if
the player walked into a question object*/
void checkCollisionAndBlast() {
	if (!gunTrigered) {						// if gun not triggered then move the bullet along with the player
		oneBullet->changeXCoZco(pL->getLocation().x, pL->getLocation().z);
	}
	checkQuestionOBJCollide();				// check if player collides with a question object
	checkGhostPlayerCollide();				// checks if the player collided with a ghost
}



// special key controls 
// flop , when anyone of these keys are pressed the bullet stops rendering 
// player should be stationary when blasting bomb
void inputKey(int key, int ix, int iy) {
	switch (key) {
	case GLUT_KEY_LEFT:
		pL->turnLeft();					// move the player to the left
		checkCollisionAndBlast();
		break;

	case GLUT_KEY_RIGHT:
		pL->turnRight();                 // move the player to the right
		checkCollisionAndBlast();
		break;

	case GLUT_KEY_UP:
		pL->goUp();                      // move the player forward
		checkCollisionAndBlast();
		checkFinishGame();               // check if the player completed the maze 
		break;

	case GLUT_KEY_DOWN:
		pL->goDown();                     // move the player backwards
		checkCollisionAndBlast();           
		break;
	}
	glutPostRedisplay();
}


void idle() {
	glutPostRedisplay(); // called when there is now other event
}


/*Deallocate the memory after use*/
void freeMemory() {
	for (int i = 0; i < ghosts.size();  i++) {   // delete all the ghost objects
		delete ghosts[i];
	}
	for (int i = 0; i < boxes.size(); i++) {     // delete all the question objects
		delete boxes[i];
	}
	delete oneBullet;                // delete the energy blast
	delete pL;                       // delete the player 

	printf("%s", "deletion of objects was successful");
}


// this function should show the controls for Maze_Gunner
void showGameControls() {
	string controls = "UP ARROW KEY \t-> MOVE PLAYER FORWARD \n\nDOWN ARROW KEY \t-> MOVE PLAYER BACKWARDS \n\nLEFT ARROW KEY \t-> MOVE PLAYER TO THE LEFT \n\nRIGHT ARROW KEY \t-> MOVE PLAYER TO THE RIGHT \n\nW \t\t-> SWITCH TO TOP VIEW \n\nX \t\t-> SWITCH TO NORMAL VIEW \n\nF \t\t-> SWITCH TO FIRST PERSON VIEW \n\nA \t\t-> LOOK TO THE LEFT \n\nD \t\t-> LOOK TO THE RIGHT \n\nSPACE BAR \t-> SHOOT ENERGY BLAST";

	const char * mwe = controls.c_str();
	MessageBox(0, mwe, "-------CONTROLS FOR MAZE GUNNER-------", MB_OK);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);							//initialize GLUT
	glutInitWindowSize(1900, 1060);					//Sets width and Height of our GLUT window
	glutInitWindowPosition(0, 0);					//Sets the position of the GLUT window on our screen
	glutCreateWindow("The Maze_Gunner");			//Set title for window
	

	init();											// Our own OpenGL initialization

	glutDisplayFunc(display);			// Register callback handler for window re-paint event
	glutReshapeFunc(reshape);			// Register callback handler for window re-size event

	
	glutKeyboardFunc(processNormalKeys);		// will be for camera controls
	glutSpecialFunc(inputKey);

	glutIdleFunc(idle);

	glutTimerFunc(0, update, 0);			 // used for gun animation

	name = getUserName();   // get the username
	showGameControls();


	m.createPaths();     // for the maze 
	m.complicateMaze();

	// to play background music 
	PlaySound(BACKGROUND_MUSIC, NULL , SND_ASYNC | SND_FILENAME |  SND_NOSTOP|SND_LOOP );
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}



// note that functions after the main method were borrowed code ****

// code by reference in isolated area
//--------------------------------------------------------------------------------------------------------------------------------------
void app_assert_success(const char* szz)
{
	if (GLint xerr = glGetError())
	{
		char szerr[MAX_APPERROR];
		sprintf_s(szerr, "%s , %d", szz, xerr);
		fprintf_s(stderr, "%s", szerr);
		exit(1);
	}
}

//Loads a texture from a text file and returns its integer OpenGL handle
GLuint maketex(const char* tfile, GLint xSize, GLint ySize) //returns tex. no.
{
	GLuint rmesh;
	FILE * file;
	unsigned char * texdata = (unsigned char*)malloc(xSize * ySize * 3); //3 is {R,G,B}

	file = fopen(tfile, "rb");
	fseek(file, BMP_HEADER_SIZE, SEEK_CUR);
	fread(texdata, xSize * ySize * 3, 1, file);
	fclose(file);
	glEnable(GL_TEXTURE_2D);

	char* colorbits = new char[xSize * ySize * 3];

	for (GLint a = 0; a<xSize * ySize * 3; ++a) colorbits[a] = 0xFF;

	glGenTextures(1, &rmesh);
	glBindTexture(GL_TEXTURE_2D, rmesh);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, xSize,
		ySize, 0, GL_RGB, GL_UNSIGNED_BYTE, colorbits);

	app_assert_success("post0_image");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	app_assert_success("pre_getview");

	//Save viewport and set up new one
	GLint viewport[4]; //4 is {X,Y,Width,Height}
	glGetIntegerv(GL_VIEWPORT, (GLint*)viewport);

	app_assert_success("pre_view");
	glViewport(0, 0, xSize, ySize);
	app_assert_success("post0_view");

	//Clear target and depth buffers
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glPushMatrix(); //Duplicates MODELVIEW stack top
	glLoadIdentity(); //Replace new top with {1}

	app_assert_success("ogl_mvx");

	glDrawPixels(xSize, ySize, GL_BGR, GL_UNSIGNED_BYTE, texdata);

	app_assert_success("pre_copytext");
	glPopMatrix();
	app_assert_success("copytext2");
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		0, 0, xSize, ySize, 0);
	app_assert_success("post_copy");

	//Restore viewport
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]); //{X,Y,Width,Height}
	app_assert_success("ogl_mm1");
	delete[] colorbits;
	free(texdata);
	return rmesh;

}
//-------------------------------------------------------------------------------------------------------------------------------------


