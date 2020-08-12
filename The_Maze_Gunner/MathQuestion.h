#pragma once

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std;
//int qIndex = 0;


class MathQuestion
{
private:
	string fileName;
	vector<string> questions;
	vector<string> answers;
	int size = 0;


public:

	MathQuestion();
	MathQuestion(string fname);
	void readTextFile();
	int getSize();
	string getQuestion(int indx) ;			 // returns the math question in the questions vector
	string getAnswer(int indx);				 // will return the answer to that question at the specific index
	string getDisplayAnswer(int index);			// will return the answer to the question, as it appears in the text file
	string removeBlankSpaces(string ans);      // removes blank spaces from any string
};


