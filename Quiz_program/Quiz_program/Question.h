#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <random>

using std::string;
using std::vector;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;

class Question
{
private:
	string question;												// Question
	vector<string> answers;											// List of answers
	size_t correctAnswer;											// Number of correct answer

public:
	// Constructor
	Question();
	// Destructor
	~Question();

	// Method to ask the quiz question, return value is 1 for correct answer, 0 for incorrect
	unsigned int Ask() const;

	// Input overload - Read a complete quiz question
	friend istream& operator>> (istream &in, Question &questionInput);
	// Output overload - Print a complete quiz question
	friend ostream& operator<< (ostream &out, const Question &questionOutput);
	// Stream input overload - Read one question from file
	friend ifstream& operator>> (ifstream &inputFile, Question &questionInput);
	// Stream input overload - Write one question to file
	friend ofstream& operator<< (ofstream &outputFile, const Question &questionOutput);
};
