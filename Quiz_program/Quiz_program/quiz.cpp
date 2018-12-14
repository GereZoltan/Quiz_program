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

using std::cin;
using std::cout;
using std::endl;
using std::unique_ptr;

int main() {
	{
		//_CrtMemState memory; // C/C++ runtime memory management state storage
		vector<unique_ptr<Question>> questions;
		//unique_ptr<Question> inputQuestion;
		int choice;

		do {
			cout << endl
				<< "1 - Clear all questions" << endl
				<< "2 - Save questions to file" << endl
				<< "3 - Load questions from file" << endl
				<< "4 - Add new question" << endl
				<< "5 - Take the quiz" << endl
				<< "6 - List all questions" << endl
				<< "7 - Quit program" << endl
				<< "> ";
			cin >> choice;
			cin.ignore(256, '\n');
			cout << endl;

			switch (choice) {
			case 1:
				questions.clear();
				break;
			case 4:
				questions.push_back(unique_ptr<Question>(new Question()));
				cin >> **((questions.end() - 1));
				break;
			case 6:
				for (unique_ptr<Question> &q : questions) {
					cout << *q;
				}
				break;
			default:
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
