#include "QuestionOBJ.h"

#include <Windows.h>

#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>


// note all questions will be based on Mathematics 

QuestionOBJ::QuestionOBJ(float id, Location & location)    //  a question will just have an ID and a Location 
	: RenderableObject(id, location, 1), c_loc(location)  // c_loc is central location of that particular question object 
{

}


void QuestionOBJ::drawQuestionOBJ()  // will draw the question object 
{
	glPushMatrix();                      // will draw the question box 
	glColor3ub(0, 100, 0);
	glTranslatef(0, -1.8, 0);//head
	//glTranslatef(0, 0, 0); // 
	//glutSolidCube(0.90);
	glutSolidSphere(0.30, 20, 20);
	glPopMatrix();

}


void QuestionOBJ::render()
{
	glPushMatrix();
	glTranslated(loc.x, loc.y, loc.z); // move to this position
	drawQuestionOBJ();
	glPopMatrix();

}

