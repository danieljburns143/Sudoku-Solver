// Daniel Burns
// Lab 4
// main.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include "cell.h"
using namespace std;

bool checkWin(const vector< vector< Cell > >&); // prototype to check if board is solved
void printPuzzle(const vector< vector< Cell > >&); // prototype to print the board
void initializePuzzle(vector< vector< Cell > >&); // prototype to initialize board

int main() {
	vector< vector< Cell > > puzzle;
	initializePuzzle(puzzle);
	printPuzzle(puzzle);
}


// function to check if board is solved
bool checkWin(const vector< vector< Cell > >& puzzle) {
	for (int row{0}; row < 9; row++) {
		for (int column{0}; column < 9; column++) {
			if (puzzle[row][column].getAnswer() == 0) {
				return false;
			}
		}
	}
	return true;
}

// function to print the board
void printPuzzle(const vector< vector< Cell > >& puzzle) {
	cout << " __________________" << endl;
	for (int row{0}; row < 9; row++) {
		cout << "|";
		for (int column{0}; column < 9; column++) {
			if (puzzle[row][column].getAnswer() == 0) {
				cout << " " << " ";
			}
			else {
				cout << puzzle[row][column].getAnswer() << " ";
			}
		}
		cout << "|" << endl;
	}
	cout << " ------------------" << endl;
}

// function to initialize board
void initializePuzzle(vector< vector< Cell > >& puzzle) {
	ifstream ifs;
	ifs.open("input.txt");
	vector< Cell > puzzleRow;
	for (int row{0}; row < 9; row++) {
		for (int column{0}; column < 9; column++) {
				int tempInput;
				ifs >> tempInput;
				puzzleRow.push_back(Cell(tempInput));
		}
		puzzle.push_back(puzzleRow);
		puzzleRow.clear();
	}
}
