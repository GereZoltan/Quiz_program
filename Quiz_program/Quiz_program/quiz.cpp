/*
 * Quiz program
 * Written by Zoltan Gere
 *
 * 13.12.2018
 */

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "Question.h"

 // Include and using for QuestionNumberGenerator
#include <time.h>
#include <algorithm>
#include <random>
using std::shuffle;
using std::default_random_engine;

// Include and using for main()
using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;

constexpr unsigned int MAXIMUM_QUESTION = 1000;
constexpr unsigned int ASKED_QUESTION_COUNT = 5;

static const char * QUESTION_FILE = "questions.txt";

class QuestionNumberGenerator {
private:
	vector<size_t> numbers;
	size_t currentNumber;
public:
	QuestionNumberGenerator(size_t initNumber);
	size_t operator() ();
};

QuestionNumberGenerator::QuestionNumberGenerator(size_t initNumber) {
	if ((initNumber > 0) && (initNumber < MAXIMUM_QUESTION)) {
		numbers.reserve(initNumber);
		for (size_t i = 0; i < initNumber; i++) {
			numbers.push_back(i + 1);
		}
		shuffle(numbers.begin(), numbers.end(), default_random_engine(time(NULL)));
	}
	else {
#ifdef _DEBUG
		cout << "WARNING: Invalid initNumber in QuestionNumberGenerator!" << endl;
#endif
	}
	currentNumber = 0;
}

size_t QuestionNumberGenerator::operator() () {
	size_t returnValue;
	if (currentNumber < numbers.size()) {
		returnValue = numbers[currentNumber++];
	}
	else {
		returnValue = 0;
	}
	return returnValue;
}

void saveQuestionsToFile (vector<Question> &outputQuestions) {
	ofstream outputFile(QUESTION_FILE);

	if (outputFile.fail()) {
		cout << "Error during file opening for write" << endl;
	}
	else {
		// Save questions to file
		for (Question &q : outputQuestions) {
			outputFile << q;
		}

	}
	if (outputFile.is_open()) {
		outputFile.close();
	}
}

void loadQuestionsFromFile (vector<Question> &inputQuestions) {
	ifstream inputFile(QUESTION_FILE);
	Question temp;

	if (inputFile.fail()) {
		cout << "Error during file opening for read" << endl;
	}
	else {
		// Load questions from file
		do {
			inputFile >> temp;
			if (inputFile.good()) {
				inputQuestions.push_back(temp);
			}
			
		} while (inputFile.good());
	}
	if (inputFile.is_open()) {
		inputFile.close();
	}
}

#if 1

int main() {
	{
		//_CrtMemState memory; // C/C++ runtime memory management state storage
		vector<Question> questions;									// Store all questions in memory
		int choice;													// Store the menu choice

		do {
			cout << endl											// Print the menu
				<< "1 - Clear all questions" << endl
				<< "2 - Save questions to file" << endl
				<< "3 - Load questions from file" << endl
				<< "4 - Add new question" << endl
				<< "5 - Take the quiz" << endl
				<< "6 - List all questions" << endl
				<< "7 - Quit program" << endl
				<< "> ";
			cin >> choice;											// Read the choice
			if (!cin) {
				cin.clear(0);										// Clear error bits ...
				cin.ignore(256, '\n');								// ... and buffer
			}

			//cout << endl;
			system("cls");

			switch (choice) {										// Process menu selection
			case 1:													// Clear questions
				questions.clear();
				break;
			case 2:													// Save questions to file
				saveQuestionsToFile(questions);
				break;
			case 3:													// Load questions from file
				loadQuestionsFromFile(questions);
				break;
			case 4:													// Add new question
				questions.push_back(Question());
				cin >> *(questions.end() - 1);
				break;
			case 5:													// Take the quiz
				if (questions.size() >= ASKED_QUESTION_COUNT)
				{
					// Ask 5 random question, no duplicates
					// Question number generator
					// Question has Ask method -> return value is user's answer correct / incorrect
					QuestionNumberGenerator qng(questions.size());
					int correctAnswers = 0;

					for (size_t i = 0; i < ASKED_QUESTION_COUNT; i++) {
						// Answer alternatives displayed in random order
						// Two incorrect + correct presented
						// After each question program tells if answer was correct
						correctAnswers += questions[qng()].Ask();
					}

					// After the quiz print the final score
					cout << "You answered " << correctAnswers << " of " << ASKED_QUESTION_COUNT << " correctly." << endl;
				}
				else {
					cout << "You need minimum " << ASKED_QUESTION_COUNT << " questions to run the quiz." << endl;
				}
				break;
			case 6:													// Print the questions to screen
				for (Question &q : questions) {
					cout << q;
				}
				cout << "Number of questions: " << questions.size() << endl;
				break;
			case 7:													// Quit
				// Nothing to do
				break;
			default:
				cout << "No such option!" << endl;
				break;
			}
		} while (choice != 7);

		//_CrtMemCheckpoint(&memory);
		//_CrtMemDumpStatistics(&memory);
	}

	if (!_CrtDumpMemoryLeaks()) {
		cout << "No memory leaks!" << endl;
	}
	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}
#endif