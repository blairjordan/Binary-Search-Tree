/*! \file main.cpp
 *  \brief Entry point for ObjectGuess
 *
 * This program reads in a single text file containing questions
 * and answers. Questions and answers are read from the file and 
 * stored in a decision tree. The user is prompted to think of an
 * object and is queried with yes/ no questions derived from nodes.
 * When a leaf node is reached, the program outputs the node. If
 * the node contents matches the object that the user thought of,
 * the program wins- If the two objects do not match, the program
 * learns by asking the user to specify a yes/no question that 
 * distinguishes the users object from the leafs object
 *
 * \pre Correctly formed input file containing decision tree data exists.
 * \post The computer wins or loses, based on whether they guess the
 *       object correctly.
 * \post If the computer loses, an additional question and answer
 *       are added to the tree.
 * \post (optional) An output file containing updated decision tree.
 * \author B. Jordan
 * \date 21-MAY-2009
 *
 * Input/output: 
 * object - alphanumeric string, no delimiters (spaces):
 *    example: monkey hat textbook mountain
 * question - alphanumeric string, may include delimiters:
 *    example: Is it living?
 * yes/no prompts - a single character: y, Y, n or N
 *
 * Checks and Errors:
 * ----------------------------------------------------------------
 * Checked:
 *  - Incorrect file locations will raise an error and exit the program.
 *  - Incorrect input from yes/ no prompts will raise an error message
 *    and prompt the user for correct input.
 * Errors:
 *  - Input files must include a new line before the end of the file.
 *
 * Files
 * -----------------------------------------------------------------
 * Headers: 
 *  - binarytree.h
 *  - bsttype.h
 *  - qatree.h
 * Source:
 *  - main.cpp
 *  - qatree.cpp
 * Test:
 *  - BSTTest.cpp
 *  - QATreeTest.cpp
 */

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "qatree.h"

using namespace std;

bool SaveTreeToFile(string fname, QATree &tree);
bool LoadTreeFromFile(string fname, QATree &tree);
void PromptNewObject(QATree &qatree, string &alternateAnswer);
void PromptQuestion(QATree &qatree, string &question, string &input);
void PromptSave(QATree &qatree);

int main(int argc, char** argv) {

	QATree qatree;				 // Tree to store questions and answers

	string fname;				 // The input/ output file name
	string input;				 // Stores user input
	string question;			 // Tree question
	string answer;				 // Tree answer
	string newQuestion;			 // New question input
	string newAnswer;			 // New answer input

	bool finished = false;		 // Determines whether program has finished
	bool exit = false;			 // Determines whether user wishes to exit
	bool inputError = false;     // Input error flag

	cout << "Input file name: ";
	cin >> fname;

	if (!LoadTreeFromFile(fname, qatree)) {
		cout << endl
			 << "Error: Unable to locate input file" << endl;

		return (EXIT_FAILURE);
	}

	while (!exit)
	{
		cout << endl
			 << "You must think of a single object. Please answer the "
			 << "following questions about this object."
			 << endl << endl;

		/* Return the first question in the tree */
		if (!qatree.GetFirstQA(question))
		{
			cout << "Error: No root node defined. " << endl;
			return (EXIT_FAILURE);
		}

		while (!finished && !exit && !inputError) 
		{
			PromptQuestion(qatree, question, input);

			/* If an answer was proposed */
			if (qatree.IsAnswer(question)) 
			{
				/* If the user answers "yes", finish this round. */
				if (input == "y" || input == "Y") 
				{
					cout << "Notice the superior intellect of the computer!" 
						 << endl << endl;

					finished = true;
				} 
				/* Otherwise, no answer was found so obtain the correct answer. */
				else if (input == "n" || input == "N") 
				{
					PromptNewObject(qatree, question);

					finished = true;
				}
			}

			/* If no answer has been found yet, return the next question or answer */
			if (!finished) 
			{
				if (input == "y" || input == "Y") 
				{
					qatree.GetNextQA(question, answer, CORRECT_PATH);
					question = answer;
				} 
				else if (input == "n" || input == "N") 
				{
					qatree.GetNextQA(question, answer, INCORRECT_PATH);
					question = answer;
				}
			}
		}

		exit = false;
		inputError = false;

		cout << "Play again? (Y or N): ";
		cin >> input;

		if (input == "N" || input == "n") 
		{
			exit = true;
			inputError = false;

			PromptSave(qatree);
		} 
		else if (input == "Y" || input == "y")
			finished = false;
		else 
		{
			cout << endl << "INCORRECT RESPONSE - Please type Y or N" << endl;
			inputError = true;
		}
	}

	return (EXIT_SUCCESS);
}

void PromptSave(QATree &qatree)
{
	string input;
	string fname;
	bool inputError;

	do {
		inputError = false;
		cout << endl << "Would you like to save the current decision tree? (Y or N): ";
		cin >> input;

		if (   input != "n" && input != "N"
			&& input != "y" && input != "Y")
		{
			cout << endl << "INCORRECT RESPONSE - Please type Y or N" << endl;
			inputError = true;
		}

		if (input == "y" || input == "Y") 
		{
			cout << endl 
				 << "Enter the output path: ";
			
			cin >> fname;

			if (SaveTreeToFile(fname, qatree))
				cout << endl << "Decision tree saved to file." << endl;
			else
				cout << endl 
				<< "Unable to resolve output path. Decision tree not saved." 
				<< endl;
		}
	} while (inputError);
}

void PromptNewObject(QATree &qatree, string &alternateAnswer)
{
	string newAnswer;
	string newQuestion;

	cout << "What were you thinking of? ";
	cin >> newAnswer;

		cout << endl 
			<< "Please specify a question that has a yes answer for your object and a no answer for my guess: "
			<< endl;

	cin.ignore();
	getline(cin, newQuestion);

	qatree.CreateQuestionAnswer(newQuestion, newAnswer, alternateAnswer);

	cout << endl;
}

void PromptQuestion(QATree &qatree, string &question, string &input)
{
	bool inputError;
	
	do {
		inputError = false;

		if (qatree.IsAnswer(question))
			cout << "I guess that your object is a(n) " << question << "? (Y or N): ";
		else
			cout << question << " ";

		cin >> input;

		if (   input != "n" && input != "N"
			&& input != "y" && input != "Y")
		{
			cout << endl << "INCORRECT RESPONSE - Please type Y or N" << endl << endl;
			inputError = true;
		}

	} while (inputError);

	cout << endl;
}

bool SaveTreeToFile(string fname, QATree &tree) {

	ofstream ofile;
	ofile.open(fname.c_str());

	if (!ofile)
		return false;

	ofile << tree;
	ofile.close();

	return true;
}

bool LoadTreeFromFile(string fname, QATree &tree) {

	ifstream ifile(fname.c_str());

	if (!ifile)
		return false;

	while (ifile) {
		if (ifile.peek() != '\n' && !ifile.eof())
			ifile >> tree;
	}

	ifile.close();

	return true;
}
