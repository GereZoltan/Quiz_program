#include "Question.h"

using std::cin;
using std::cout;
using std::endl;

Question::Question()
{
}


Question::~Question()
{
}

istream& operator>> (istream &in, Question &questionInput) {
	char input[128];

	questionInput.question.clear();
	cout << "Enter question: ";
	cin.getline(input, sizeof(input));
	questionInput.question = input;
	cout << endl;

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

	/*
	for (int i = 1; i < 5; i++) {
		//answerInput.clear();
		cout << "Enter " << i << ". answer: ";
		cin.getline(input, sizeof(input));
		//answerInput = input;
		cout << endl;
		questionInput.answers.push_back(string(input));
	}
	*/

	do {
		cout << "Enter the number of correct answer: ";
		cin >> questionInput.correctAnswer;
		cout << endl;
		if ((questionInput.correctAnswer < 1) ||
			(questionInput.correctAnswer > questionInput.answers.size())) {
			cout << "No corresponding answer!" << endl;
		}
	} while ((questionInput.correctAnswer < 1) ||
		(questionInput.correctAnswer > questionInput.answers.size()));
	return in;
}

ostream& operator<< (ostream &out, Question &questionOutput) {
	cout << "  " << questionOutput.question << endl;
	for (string &s : questionOutput.answers) {
		cout << "\t" << s << endl;
	}
	cout << "Correct answer is: " << questionOutput.correctAnswer << endl;
	return out;
}