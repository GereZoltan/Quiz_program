#include "Question.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::find;
using std::shuffle;
using std::default_random_engine;

Question::Question() {
}

Question::~Question() {
}

// Method to ask the quiz question, return value is 1 for correct answer, 0 for incorrect
unsigned int Question::Ask() const {
	size_t choice;													// Store the menu choice
	size_t randomNum;												// Strore the random generated number
	vector<size_t> answerAlternatives;								// Store the indices of the offered answers
	size_t j = 1;													// First store index values of answers and then
																	// 1 if answer is correct

	answerAlternatives.push_back(correctAnswer);					// Correct answer to pool
	for (size_t i = 0; i < 2; i++) {								// 2 another random number to pool
		do {
			randomNum = rand() % answers.size() + 1;
		} while (find(answerAlternatives.begin(), answerAlternatives.end(), randomNum) != answerAlternatives.end());
		answerAlternatives.push_back(randomNum);
	}
	shuffle(answerAlternatives.begin(), answerAlternatives.end(), default_random_engine(time(NULL)));	// Shuffle numbers

	//cout << "DEBUG: Offered answers: " << answerAlternatives[0] << "  " << answerAlternatives[1] << "  " << answerAlternatives[2] << endl;
	// Ask the question
	// Answer alternatives displayed in random order
	// Two incorrect + correct presented
	// After each question program tells if answer was correct

	cout << question << endl;										// Ask the question
	for (size_t i : answerAlternatives) {
		cout << j++ << " - " << answers[i-1] << endl;				// Print the answer alternatives
	}

	do {
		cout << "Enter your answer: ";

		cin >> choice;												// Read the choice
		if (!cin) {													// If invalid character in buffer
			cin.clear(0);											// Clear error bits ...
			cin.ignore(256, '\n');									// ... and buffer
		}
		if ((choice < 1) || (choice > 3)) {							// Check if answer is correct
			cout << "No answer corresponding to input!" << endl;
		}
	} while ((choice < 1) || (choice > 3));							// Keep asking for number if incorrect

	if (answerAlternatives[choice-1] == correctAnswer) {			// If correct answer
		cout << endl << "Your answer is correct." << endl << endl;
		j = 1;
	}
	else {															// If incorrect answer
		cout << endl << "Your answer is incorrect." << endl << endl;
		j = 0;
	}

	return j;
}

// Input overload - Read a complete quiz question
istream& operator>> (istream &in, Question &questionInput) {
	string input;												// Hold the text input

	questionInput.question.clear();									// Clear question container
	cin.ignore(256, '\n');											// Clear buffer
	cout << "Enter question: ";
	getline(cin, input);
	questionInput.question = input;									// Read and store the question
	cout << endl;

	/*
	// This is an alternate code where the number of questions is not fixed.
	// Minimum 4 answers neccessary, but it can be more.
	do {
		cout << "Enter an answer or ENTER to finish: ";
		getline(cin, input);
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
		getline(cin, input);
		cout << endl;
		questionInput.answers.push_back(string(input));
	}

	cout << "Recorded question: " << endl << questionInput.question << endl;
	cout << "Recorded answers: " << endl;
	for (string &s : questionInput.answers) {
		cout << s << endl;
	}
	cout << endl;

	do {															// Read the number of the correct answer
		cout << "Enter the number of correct answer: ";
		cin >> questionInput.correctAnswer;
		if (!cin) {													// If invalid character in buffer
			cin.clear(0);											// Clear error bits ...
			cin.ignore(256, '\n');									// ... and buffer
		}
		cout << endl;
		if ((questionInput.correctAnswer < 1) ||					// Correct answer's number is checked
			(questionInput.correctAnswer > questionInput.answers.size())) {	// Is answer with this index exist?
			cout << "No corresponding answer!" << endl;
		}
	} while ((questionInput.correctAnswer < 1) ||
		(questionInput.correctAnswer > questionInput.answers.size()));		// Exit loop if number is in range
	return in;
}

// Output overload - Print a complete quiz question
ostream& operator<< (ostream &out, const Question &questionOutput) {
	cout << "  " << questionOutput.question << endl;				// Print question

#ifdef _DEBUG
	for (const string &s : questionOutput.answers) {						// Print all the answers
		cout << "\t" << s << endl;
	}
	cout << "DEBUG: Correct answer is: " << questionOutput.correctAnswer << endl;	// Print correct answers number
#endif

	//cout << endl;
	return out;
}

// Stream input overload - Read one question from file
ifstream & operator>>(ifstream & inputFile, Question & questionInput)
{
	bool run = true;												// Exit signal, set when correct answer's number read
	string inputString;												// Line read into this string

	questionInput.question.clear();
	questionInput.answers.clear();

	do {
		getline(inputFile, inputString);							// Read one line from file
		if (inputString.length() > 0) {								// If not empty line
			switch (inputString[0]) {
			case 'Q':												// Reading question
				inputString.erase(0, 1);
				questionInput.question = inputString;
				break;
			case 'A':												// Reading answer
				inputString.erase(0, 1);
				questionInput.answers.push_back(inputString);
				break;
			case 'C':												// Reading correct answer's number
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

// Stream output overload - Write one question to file
ofstream & operator<<(ofstream & outputFile, const Question & questionOutput)
{
	outputFile << 'Q' << questionOutput.question << endl;			// Write question
	for (const string &s : questionOutput.answers) {						// Write answers
		outputFile << 'A' << s << endl;
	}
	outputFile << 'C' << std::to_string(questionOutput.correctAnswer) << endl;	// Write correct answer's number
	return outputFile;
}
