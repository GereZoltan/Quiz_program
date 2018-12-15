#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using std::string;
using std::vector;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;

class Question
{
private:
	string question;
	vector<string> answers;
	size_t correctAnswer;

public:
	Question();
	~Question();

	unsigned int Ask();

	friend istream& operator>> (istream &in, Question &questionInput);
	friend ostream& operator<< (ostream &out, Question &questionOutput);

	friend ifstream& operator>> (ifstream &inputFile, Question &questionInput);
	friend ofstream& operator<< (ofstream &outputFile, Question &questionOutput);
};
