#pragma once
#include "RenderableObject.h"
#include "Location.h"

class QuestionOBJ : public  RenderableObject {   // QuestionOBJ extends RenderableObject

private:
	Location c_loc;                  // initial location of this object
	void drawQuestionOBJ();

public :
	QuestionOBJ(float id, Location & location); // default constructor 
	void render(); // renders the question object 
};
