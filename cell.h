// Daniel Burns
// Lab 4
// cell.h

#ifndef CELL_H
#define CELL_H

#include <list>
using namespace std;

class Cell {
public:
	Cell(const int&); // constructor
	~Cell(); // destructor
	void setAnswer(const int&); // prototype to set the answer
	int getAnswer() const; // prototype to get answer
	void addPossibleAnswer(const int&); // prototype to add a possible answer
	void removePossibleAnswer(const int&); // prototype to remove a number from possible answers
	bool isNumberPossibleAnswer(const int&); // prototype to check if number is a possible answer
	int getPossibleAnswersSize() const; // prototype to return how many possible answers are left
	void setPossibleAnswerToAnswer(); // prototype to fill in answer if only 1 possible answer
	int getPossibleAnswer(const int&); // prototype to get a possible answer from list
private:
	int answer;
	list< int > possibleAnswers;
};

#endif
