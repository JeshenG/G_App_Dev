#include "MathQuestion.h"
#include <algorithm>   // used for blank space removal  

MathQuestion::MathQuestion()
{
}

MathQuestion::MathQuestion(string fname)
{
	fileName = fname;
}

void MathQuestion::readTextFile()
{
	string line;
	int delimIndex;
	ifstream myFile(fileName);

	if (myFile)
	{
		cout << "\n Maths Text File exists" << endl;
		if (myFile.is_open())
		{
			while (getline(myFile, line))
			{
				delimIndex = line.find("#");
				questions.push_back(line.substr(0, delimIndex));
				answers.push_back(line.substr(delimIndex + 1, line.length()));
				if (size != 0)
				{
					size = size + 1;
				}

			}
		}
	}
	else
	{
		cout << "\n Maths Text File does not exist" << endl;
	}
}

int MathQuestion::getSize()
{
	return questions.size();
}


string MathQuestion::getQuestion(int indx)
{
	return questions[indx];
}

string MathQuestion::getAnswer(int indx)   // will return the answer without blank spaces 
{
	return removeBlankSpaces(answers[indx]);
}

string MathQuestion::getDisplayAnswer(int index)
{
	return answers[index];
}

string MathQuestion::removeBlankSpaces(string ans) // should remove blank whites spaces from the string
{
	ans.erase(std::remove(ans.begin(), ans.end(), ' '), ans.end());
	return ans;
}
