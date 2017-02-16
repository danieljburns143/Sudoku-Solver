// Daniel Burns
// Lab 4
// cell.h

#ifndef CELL_H
#define CELL_H


#include <iostream>
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
	void printPossibleAnswers(); // prototype to print all possible answers for cell
private:
	int answer;
	list< int > possibleAnswers;
};

#endif
