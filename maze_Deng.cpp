// David Deng
// maze problem
// Note: Use the mazefile name as the first argument of the executable.
// Note: Use make command to compile
// fixme: find the optimum path and show it.

#include <iostream>
#include <fstream>
#include <cstring>
#include "conio.h"
#include <chrono>
#include <thread>

const int MAXCHAR = 20;
const char EXIT = 'E';
const char VISITED = '-';
const char WALL = '#';
const char DEADEND = 'x';
const char PASS = 'v';
const int MAZESIZE = 10;
const int DELAY = 200; // in milliseconds

using namespace std;

void printMaze(const char maze[][MAZESIZE]);
void printColoredMaze(const char maze[][MAZESIZE]);
void copyMatrix(char targetmaze[][MAZESIZE], const char sourcemaze[][MAZESIZE]);
void getStart(int& row, int& col);
bool solution( int row, int col, char scratchMaze[][MAZESIZE]);

int main(int argc, char** argv)
{
	// define variables
	int startCol, startRow;
	char matrix[MAZESIZE][MAZESIZE];
	char masterMatrix[MAZESIZE][MAZESIZE];

	// read the file name from parameter
	char fileName[MAXCHAR] = "";
	if (argc == 1)
		strcpy(fileName, "maze1.txt");
	else
		strcpy(fileName, argv[1]);

	// read the file
	ifstream mazestream;
	mazestream.open(fileName);
	for(int row=0; row<MAZESIZE; row++) {
		for(int col=0; col<MAZESIZE; col++) { 
			mazestream.get(masterMatrix[row][col]);
		}
		mazestream.get(); // dispose the new-line char
    }

	// asking the starting point and start animation
	printMaze(masterMatrix);
	getStart(startRow, startCol);
	while(cin)
	{
		copyMatrix(matrix,masterMatrix);
		if(solution(startRow,startCol,matrix)) {
			cout << "Happy day" << endl;
		} else {
			cout << "Less happy day" << endl;
		}
		printColoredMaze(matrix);
		getStart(startRow, startCol);
	}

	return 0;
}

bool solution(int row, int col, char matrix[][MAZESIZE] )
{
	if ( row<0 || row>MAZESIZE-1 || col<0 || row>MAZESIZE-1 ) return false;
	else if ( matrix[row][col] == WALL ) return false;
	else if ( matrix[row][col] == DEADEND ) return false;
	else if ( matrix[row][col] == VISITED ) return false;
	else if( matrix[row][col] == EXIT ) return true;

	matrix[row][col] = VISITED;
	printColoredMaze(matrix);
	this_thread::sleep_for(chrono::milliseconds(DELAY));

	if( solution(row-1, col, matrix) || 
		solution(row+1, col, matrix) || 
		solution(row, col-1, matrix) || 
		solution(row, col+1, matrix) )
	{
		matrix[row][col] = PASS;
		return true;
	}
	else
	{
		matrix[row][col] = DEADEND;
		return false;
	}
}

/*
   How to read in the matrix
char newline;
for(int row=0; row<10; row++) {
    for(int col ... ) }
 	mazeFile.get(matrix[row][col]);
    }
    mazeFile.get(newline);
}
*/

void printMaze(const char maze[][MAZESIZE]) {
	cout << "  ";
	for (int i=0; i<MAZESIZE; i++)
		cout << i << " ";
	cout << endl;

	for (int row=0; row<MAZESIZE; row++) {
		cout << row << " ";
		for(int col=0; col<MAZESIZE; col++) 
			cout << maze[row][col] << " ";
		cout << endl;
	}
}

void printColoredMaze(const char maze[][MAZESIZE]) {
	cout << "  ";
	for (int i=0; i<MAZESIZE; i++)
		cout << i << " ";
	cout << endl;

	for (int row=0; row<MAZESIZE; row++) {
		cout << row << " ";
		for(int col=0; col<MAZESIZE; col++) 
		{
			// set the colors
			switch (maze[row][col]) {
				case DEADEND:
					cout << conio::bgColor(conio::RED);
					break;
				case VISITED:
					cout << conio::bgColor(conio::YELLOW);
					break;
				case PASS:
					cout << conio::bgColor(conio::GREEN);
					break;
			}
			cout << maze[row][col] << " ";
			cout << conio::resetAll();
		}
		cout << endl;
	}
}

void copyMatrix(char targetmaze[][MAZESIZE], const char sourcemaze[][MAZESIZE]) {
	for (int row=0; row<MAZESIZE; row++) {
		for(int col=0; col<MAZESIZE; col++) 
			targetmaze[row][col] = sourcemaze[row][col];
	}
}
void getStart(int& row, int& col) {
	cout << "Enter the row number => ";
	cin >> row;
	cout << "Enter the col number => ";
	cin >> col;
	cout << "Row: " << row << endl;
	cout << "Col: " << col << endl;
}
