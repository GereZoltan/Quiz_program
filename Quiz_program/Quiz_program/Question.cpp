#include "Question.h"

using std::cin;
using std::cout;
using std::endl;

Question::Question() {
}


Question::~Question() {
}

unsigned int Question::Ask() {
	int choice;														// Store the menu choice
	// Ask the question
	// Answer alternatives displayed in random order
	// Two incorrect + correct presented
	// After each question program tells if answer was correct
	cout << question << endl;


	cin >> choice;													// Read the choice
	if (!cin) {
		cin.clear(0);												// Clear error bits ...
		cin.ignore(256, '\n');										// ... and buffer
	}

	return 0;
}

// Input overload - Read a complete quiz question
istream& operator>> (istream &in, Question &questionInput) {
	char input[128];												// Hold the text input

	questionInput.question.clear();									// Clear question container
	cin.ignore(256, '\n');											// Clear buffer
	cout << "Enter question: ";
	cin.getline(input, sizeof(input));
	questionInput.question = input;									// Read and store the question
	cout << endl;

	/*
	do {
		cout << "Enter an answer or ENTER to finish: ";
		cin.getline(input, sizeof(input));
		cout << endl;
		if (strlen(input) > 0) {
			questionInput.answers.push_back(string(input));
		}
		else {
			if (questionInput.answers.size() < 4) {
				cout << "At least 4 answer required!" << endl;
			}
		}
	} while (!((strlen(input) == 0) && (questionInput.answers.size() >= 4)));
	*/

	for (int i = 1; i < 5; i++) {									// Read 4 possible answers
		cout << "Enter " << i << ". answer: ";
		cin.getline(input, sizeof(input));
		cout << endl;
		questionInput.answers.push_back(string(input));
	}

	do {															// Read the number of the correct answer
		cout << "Enter the number of correct answer: ";
		cin >> questionInput.correctAnswer;
		if (!cin) {
			cin.clear(0);												// Clear error bits ...
			cin.ignore(256, '\n');										// ... and buffer
		}
		cout << endl;
		if ((questionInput.correctAnswer < 1) ||					// Correct answer's number is checked
			(questionInput.correctAnswer > questionInput.answers.size())) {	// Is answer with this serial number exist?
			cout << "No corresponding answer!" << endl;
		}
	} while ((questionInput.correctAnswer < 1) ||
		(questionInput.correctAnswer > questionInput.answers.size()));		// Exit loop if number is in range
	return in;
}

// Output overload - Print a complete quiz question
ostream& operator<< (ostream &out, Question &questionOutput) {
	cout << "  " << questionOutput.question << endl;				// Print question
	for (string &s : questionOutput.answers) {						// Print all the answers
		cout << "\t" << s << endl;
	}
#ifdef _DEBUG
	cout << "Correct answer is: " << questionOutput.correctAnswer << endl;	// Print correct answers number
#endif
	cout << endl;
	return out;
}

// Read one question from file
ifstream & operator>>(ifstream & inputFile, Question & questionInput)
{
	bool run = true;
	string inputString;

	questionInput.question.clear();
	questionInput.answers.clear();

	do {
		getline(inputFile, inputString);
		if (inputString.length() > 0) {
			switch (inputString[0]) {
			case 'Q':
				inputString.erase(0, 1);
				questionInput.question = inputString;
				break;
			case 'A':
				inputString.erase(0, 1);
				questionInput.answers.push_back(inputString);
				break;
			case 'C':
				inputString.erase(0, 1);
				questionInput.correctAnswer = std::stoul(inputString);
				run = false;
				break;
			default:
				break;
			}
		}
	} while (run && inputFile.good());

	return inputFile;
}

// Save one question to file
ofstream & operator<<(ofstream & outputFile, Question & questionOutput)
{
	outputFile << 'Q' << questionOutput.question << endl;
	for (string &s : questionOutput.answers) {
		outputFile << 'A' << s << endl;
	}
	outputFile << 'C' << std::to_string(questionOutput.correctAnswer) << endl;
	return outputFile;
}
