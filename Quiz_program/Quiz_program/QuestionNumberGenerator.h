#pragma once

#include <vector>
#include <time.h>
#include <algorithm>
#include <random>
#include <iostream>

using std::vector;
using std::shuffle;
using std::default_random_engine;

constexpr unsigned int MAXIMUM_QUESTION = 1000;						// Maximum allowed numbers in the sequence

/*
 * QuestionNumberGenerator
 * Provide unique numbers in random order
 */
class QuestionNumberGenerator
{
private:
	vector<size_t> numbers;											// Contains the sequence of numbers
	size_t currentNumber;											// Position of the current number (to provide)
public:
	// Constructor - Init the sequence of shuffled unique numbers
	QuestionNumberGenerator(size_t initNumber);
	~QuestionNumberGenerator();
	// Provide the next number in the sequence or 0 if ended
	size_t operator() ();

};

