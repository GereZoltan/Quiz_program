/*
 * Quiz program
 * Written by Zoltan Gere
 *
 * 13-17.12.2018
 */

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "Question.h"
#include "QuestionNumberGenerator.h"

using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;

constexpr unsigned int ASKED_QUESTION_COUNT = 5;					// Numberof questions asked in quiz

static const char * QUESTION_FILE = "questions.txt";				// The file name where questions are saved

// Function to save the question list to file
void saveQuestionsToFile (const vector<Question> &outputQuestions) {
	ofstream outputFile(QUESTION_FILE);

	if (outputFile.fail()) {
		cout << "Error during file opening for write" << endl;
	}
	else {
		// Save questions to file
		for (const Question &q : outputQuestions) {
			outputFile << q;
		}
	}
	if (outputFile.is_open()) {
		outputFile.close();
	}
}

// Function to load the question list from file
void loadQuestionsFromFile (vector<Question> &inputQuestions) {
	ifstream inputFile(QUESTION_FILE);
	Question temp;

	if (inputFile.fail()) {
		cout << "Error during file opening for read" << endl;
	}
	else {
		// Load questions from file
		inputQuestions.clear();										// Clear current content, the list is replaced
		do {
			inputFile >> temp;
			if (inputFile.good()) {									// Only successfully read questions
				inputQuestions.push_back(temp);						// are saved. (Last new line starts
			}														// reading a question but fails.)
			
		} while (inputFile.good());
	}
	if (inputFile.is_open()) {
		inputFile.close();
	}
}

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
			if (!cin) {												// If invalid character in buffer
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
				if (questions.size() >= ASKED_QUESTION_COUNT)		// Check if there is sufficient number of questions
				{
					// Ask 5 random question, no duplicates
					// Question number generator (function object) provides the number of questions to ask
					// Question has Ask method -> return value is user's answer correct / incorrect

					QuestionNumberGenerator qng(questions.size());	// Provides the numbers, initialized with the nmber of questions
					int correctAnswers = 0;							// Hold the number of correct answers

					for (size_t i = 0; i < ASKED_QUESTION_COUNT; i++) {
						correctAnswers += questions[qng()].Ask();	// Ask the questions and gather the correct answer's count
					}

					// After the quiz print the final score
					cout << "You answered " << correctAnswers << " of " << ASKED_QUESTION_COUNT << " correctly." << endl;
				}
				else {												// Not enough questions in pool
					cout << "You need minimum " << ASKED_QUESTION_COUNT << " questions to run the quiz." << endl;
				}
				break;
			case 6:													// Print the questions to screen
				for (Question &q : questions) {
					cout << q;
				}
#ifdef _DEBUG
				cout << "DEBUG: Number of questions: " << questions.size() << endl;
#endif
				break;
			case 7:													// Quit
				// Nothing to do
				break;
			default:												// Anything else
				cout << "No such option!" << endl;
				break;
			}
		} while (choice != 7);

		//_CrtMemCheckpoint(&memory);
		//_CrtMemDumpStatistics(&memory);
	}

#ifdef _DEBUG
	if (!_CrtDumpMemoryLeaks()) {
		cout << "DEBUG: No memory leaks!" << endl;
	}
	_CrtDumpMemoryLeaks();
#endif

	return EXIT_SUCCESS;
}
