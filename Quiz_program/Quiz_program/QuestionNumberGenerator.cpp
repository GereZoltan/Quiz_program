#include "QuestionNumberGenerator.h"

using std::cout;
using std::endl;

// Constructor - Init the sequence of shuffled unique numbers
QuestionNumberGenerator::QuestionNumberGenerator(size_t initNumber) {
	if ((initNumber > 0) && (initNumber < MAXIMUM_QUESTION)) {		// If the number of numbers is valid
		numbers.reserve(initNumber);
		for (size_t i = 0; i < initNumber; i++) {					// Place the unique numbers into the container...
			numbers.push_back(i);
		}
		shuffle(numbers.begin(), numbers.end(), default_random_engine(time(NULL)));	// ...and shuffle them
	}
	else {
#ifdef _DEBUG
		cout << "DEBUG: WARNING: Invalid initNumber in QuestionNumberGenerator!" << endl;
#endif
	}
	currentNumber = 0;												// Set position to first element
}

QuestionNumberGenerator::~QuestionNumberGenerator()
{
}

// Provide the next number in the sequence or 0 if ended
size_t QuestionNumberGenerator::operator() () {
	size_t returnValue;
	if (currentNumber < numbers.size()) {							// If still reading the sequence...
		returnValue = numbers[currentNumber++];						// ...return the next value
	}
	else {
		returnValue = 0;											// Otherwise return 0.
	}
	return returnValue;
}