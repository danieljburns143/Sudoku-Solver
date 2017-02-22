// Daniel Burns
// Lab 4
// main.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include "cell.h"
using namespace std;

void singletonUtility(vector< vector< Cell > >&, const int&, const int&, int&); // utility prototype to assist singleton function
void singleton(vector< vector< Cell > >&, int&); // prototype to implement singleton algorithm
void singlePossibility(vector< vector< Cell > >&, int&); // prototype to set answer if only one possible answer is left
void reducePossibleAnswersByMiniGrid(vector< vector< Cell > >&); // prototype to remove possible answers
void reducePossibleAnswersByRowAndColumn(vector< vector< Cell > >&); // prototype to reduce possible answers
bool checkWin(const int&); // prototype to check if board is solved
void printPuzzle(const vector< vector< Cell > >&); // prototype to print the board
void initializePuzzle(vector< vector< Cell > >&, char*, int&); // prototype to initialize board

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Please try again and enter name of input file as command line argument..." << endl;
		return 1;
	}
	int cellsPlaced{81}; // this is used in checkWin() function to decide if puzzle as been solved
	vector< vector< Cell > > puzzle;
	initializePuzzle(puzzle, argv[1], cellsPlaced);
	reducePossibleAnswersByRowAndColumn(puzzle); // reduces possibilities by checking rows, columns, and minigrids
	reducePossibleAnswersByMiniGrid(puzzle);
	while (checkWin(cellsPlaced) == false) {
		singlePossibility(puzzle, cellsPlaced); // utilizes SINGLE POSSIBILITY algorithm
		singleton(puzzle, cellsPlaced); // utilizes SINGLETON algorithm
	}
	printPuzzle(puzzle);
}

// function to assist singleton function and make it easier to read
void singletonUtility(vector< vector< Cell > >& puzzle, const int& startingRow, const int& startingColumn, int& cellsPlaced) {
	for (int row{startingRow}; row < startingRow + 3; row++) {
		for (int column{startingColumn}; column < startingColumn + 3; column++) {
			for (int element{0}; element < puzzle[row][column].getPossibleAnswersSize(); element++) {
				bool onlyElementInMiniGrid{true};
				for (int m{startingRow}; m < startingRow + 3; m++) {
					for (int n{startingColumn}; n < startingColumn + 3; n++) {
						if ((m != row || n != column) && puzzle[m][n].isNumberPossibleAnswer(puzzle[row][column].getPossibleAnswer(element))) {
							onlyElementInMiniGrid = false;
						}
					}
				}
				if (onlyElementInMiniGrid == true) {
					puzzle[row][column].setAnswer(puzzle[row][column].getPossibleAnswer(element));
					cellsPlaced--;
					reducePossibleAnswersByRowAndColumn(puzzle);
					reducePossibleAnswersByMiniGrid(puzzle);
					break;
				}
			}
		}
	}
}

// function to implement singleton algorithm
void singleton(vector< vector< Cell > >& puzzle, int& cellsPlaced) {
	for (int row{0}; row < 9; row++) {
		for (int column{0}; column < 9; column++) {
			for (int element{0}; element < puzzle[row][column].getPossibleAnswersSize(); element++) {
				bool onlyElementInColumn{true}, onlyElementInRow{true};
				for (int m{0}; m < 9; m++) {
					// check down column and row
					if (m != row && puzzle[m][column].isNumberPossibleAnswer(puzzle[row][column].getPossibleAnswer(element))) {
						onlyElementInColumn = false;
					}
					if (m != column && puzzle[row][m].isNumberPossibleAnswer(puzzle[row][column].getPossibleAnswer(element))) {
						onlyElementInRow = false;
					}
				}
				if (onlyElementInRow == true || onlyElementInColumn == true) {
					puzzle[row][column].setAnswer(puzzle[row][column].getPossibleAnswer(element));
					cellsPlaced--;
					reducePossibleAnswersByRowAndColumn(puzzle);
					reducePossibleAnswersByMiniGrid(puzzle);
					break;
				}
			}
		}
	}
	for (int i{0}; i <= 6; i += 3) {
		for (int k{0}; k <= 6; k += 3) {
			singletonUtility(puzzle, i, k, cellsPlaced); // call to singleton utility function to implement algorithm
		}
	}
}

// function to set answer if only one possible answer is left
void singlePossibility(vector< vector< Cell > >& puzzle, int& cellsPlaced) {
	for (int row{0}; row < 9; row++) {
		for (int column{0}; column < 9; column++) {
			if (puzzle[row][column].getPossibleAnswersSize() == 1) {
				puzzle[row][column].setPossibleAnswerToAnswer();
				cellsPlaced--;
				reducePossibleAnswersByRowAndColumn(puzzle);
				reducePossibleAnswersByMiniGrid(puzzle);
			}
		}
	}
}

// function to assist the reduction of answers by the mini grid
void reducePossibleAnswersByMiniGrid(vector< vector< Cell > >& puzzle) {
	for (int startingRow{0}; startingRow <= 6; startingRow += 3) {
		for (int startingColumn{0}; startingColumn <= 6; startingColumn += 3) {
			for (int row{startingRow}; row < startingRow + 3; row++) {
				for (int column{startingColumn}; column < startingColumn + 3; column++) {
					if (puzzle[row][column].getAnswer() != 0) {
						for (int m{startingRow}; m < startingRow + 3; m++) {
							for (int n{startingColumn}; n < startingColumn + 3; n++) {
								puzzle[m][n].removePossibleAnswer(puzzle[row][column].getAnswer());
							}
						}
					}
				}
			}
		}
	}
}

// function to reduce possible answers by checking rows and columns
void reducePossibleAnswersByRowAndColumn(vector< vector< Cell > >& puzzle) {
	for (int row{0}; row < 9; row++) {
		for (int column{0}; column < 9; column++) {
			if (puzzle[row][column].getAnswer() != 0) {
				for (int m{0}; m < 9; m++) {
					puzzle[m][column].removePossibleAnswer(puzzle[row][column].getAnswer());
					puzzle[row][m].removePossibleAnswer(puzzle[row][column].getAnswer());
				}
			}
		}
	}
}

// function to check if board is solved
// CHECKWIN FUNCTION
bool checkWin(const int& cellsPlaced) {
	return (cellsPlaced == 0) ? true : false;
}

// function to print the board
void printPuzzle(const vector< vector< Cell > >& puzzle) {
	int rowCtr{0}, columnCtr{0};
	cout << "_______________________" << endl;
	for (int row{0}; row < 9; row++) {
		if (rowCtr == 3 || rowCtr == 6) {
			cout << "|---------------------|" << endl;
		}
		cout << "|";
		for (int column{0}; column < 9; column++) {
			if (columnCtr == 3 || columnCtr == 6) {
				cout << "| ";
			}
			if (puzzle[row][column].getAnswer() == 0) {
				cout << " " << " ";
			}
			else {
				(column < 8) ? cout << puzzle[row][column].getAnswer() << " " : cout << puzzle[row][column].getAnswer();
			}
			columnCtr++;
		}
		columnCtr = 0;
		cout << "|" << endl;
		rowCtr++;
	}
	cout << "-----------------------" << endl;
}

// function to initialize board
void initializePuzzle(vector< vector< Cell > >& puzzle, char* file, int& cellsPlaced) {
	ifstream ifs;
	ifs.open(file); // open up file of user's choosing
	vector< Cell > puzzleRow;
	for (int row{0}; row < 9; row++) {
		for (int column{0}; column < 9; column++) {
				int tempInput;
				ifs >> tempInput; // reads in each value from input file
				if (tempInput != 0) { cellsPlaced--; }
				puzzleRow.push_back(Cell(tempInput));
		}
		puzzle.push_back(puzzleRow);
		puzzleRow.clear();
	}
}
