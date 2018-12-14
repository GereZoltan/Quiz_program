#pragma once

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::istream;
using std::ostream;

class Question
{
private:
	string question;
	vector<string> answers;
	size_t correctAnswer;

public:
	Question();
	~Question();

	friend istream& operator>> (istream &in, Question &questionInput);
	friend ostream& operator<< (ostream &out, Question &questionOutput);
};

