// Daniel Burns
// Lab 4
// cell.cpp

#include "cell.h"
using namespace std;

// constructor
Cell::Cell(const int& value) : answer{value} {
	if (answer == 0) {
		for (int i{1}; i < 10; i++) {
			possibleAnswers.push_back(i);
		}
	}
}

// destructor
Cell::~Cell() {}

// function to set the answer
void Cell::setAnswer(const int& answer) {
	this->answer = answer;
	possibleAnswers.clear();
}

// function to get the answer
int Cell::getAnswer() const {
	return answer;
}

// function to add a possible answer
void Cell::addPossibleAnswer(const int& possibleAnswer) {
	possibleAnswers.push_back(possibleAnswer);
}

// function to remove a number from possible answers
void Cell::removePossibleAnswer(const int& numberToRemove) {
	 possibleAnswers.remove(numberToRemove);
}

// function to check if number is a possible answer
bool Cell::isNumberPossibleAnswer(const int& number) {
	for (auto it = possibleAnswers.begin(); it != possibleAnswers.end(); it++) {
		if (*it == number) {
			return true;
		}
	}
	return false;
}

// function to return how many possible answers are left
int Cell::getPossibleAnswersSize() const {
	return possibleAnswers.size();
}

// function to fill in answer if only 1 possible answer is left
void Cell::setPossibleAnswerToAnswer() {
	auto it = possibleAnswers.begin();
	answer = *it;
	possibleAnswers.clear();
}

// function to get a possible answer from the list possibleAnswers
int Cell::getPossibleAnswer(const int& element) {
	auto it = possibleAnswers.begin();
	for (int i{0}; i < element; i++) {
		it++;
	}
	return *it;
}
