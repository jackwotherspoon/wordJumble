/*
jumble.cpp

		Created: Nov 14, 2018
		Author: Jack Wotherspoon

*/
#include"jumble.h"
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

typedef char* charArrayPtr;
BadJumbleException::BadJumbleException(const string& message){
	this->message = message;
}; 
string BadJumbleException::what() const { return message; }

//Jumble Class Accessors
char JumblePuzzle::getDirection(){
	return direction;
}
int JumblePuzzle::getColPos() {
	return colPos;
}
int JumblePuzzle::getRowPos() {
	return rowPos;
}
int JumblePuzzle::getSize() {
	return size;
}
string JumblePuzzle::getDifficulty() {
	return difficulty;
}
string JumblePuzzle::getWord() {
	return word;
}
charArrayPtr* JumblePuzzle::getJumble() {
	return jumble;
}

//JumblePuzzle constructors
JumblePuzzle::JumblePuzzle() {}; //default constructor
JumblePuzzle::JumblePuzzle( string hiddenWord,  string difficulty) {
	word = hiddenWord;
	this->difficulty = difficulty; 
	if (word.length() < 3 || word.length() > 10)
		throw BadJumbleException("Invalid word, please make it between 3 and 10 characters in length!");
	if (difficulty == "hard")
		size = 4 * word.length();
	else if (difficulty == "medium")
		size = 3 * word.length();
	else if (difficulty == "easy")
		size = 2 * word.length();
	else 
		throw BadJumbleException("Invalid difficulty, must input easy, medium or hard");

	srand(time(nullptr));
	//generate table of random lowercase characters
	jumble = new char*[size];
	for (int i = 0; i < size; i++) {
		jumble[i] = new char[size];
		for (int j = 0; j < size; j++) {
			jumble[i][j] = 'a' + rand() % 26;
		}
	}
	insertWord();
}
//create copy puzzle
JumblePuzzle::JumblePuzzle(const JumblePuzzle& jp) {
	rowPos = jp.rowPos;
	colPos = jp.colPos;
	direction = jp.direction;
	difficulty = jp.difficulty;
	//copy from original puzzle
	jumble = new charArrayPtr[jp.size];
	for (int j = 0; j < jp.size; j++)
		jumble[j] = new char[jp.size];
	for (int y = 0; y < jp.size; y++) {
		for (int x = 0; x < jp.size + 1; x++) {
			jumble[y][x] = jp.jumble[y][x];
		}
	}
	size = jp.size;
}
//print word in array bottom to top
bool JumblePuzzle::insertNorth(int x, int y) {
	for (int i = 0; i < word.length(); i++) {
		if (y < 0) { // if y becomes an invalid index
			return false;
		}
		else {
			jumble[y][x] = word[i];
			y--;
		}
	}
	return true;
}
//print word in array top to bottom
bool JumblePuzzle::insertSouth(int x, int y) {
	for (int i = 0; i < word.length(); i++) {
		if (y > (size-1)) { // if y becomes an invalid index
			return false;
		}
		else {
			jumble[y][x] = word[i];
			y++;
		}
	}
	return true;
}
// print word in array left to right
bool JumblePuzzle::insertEast(int x, int y) {
	for (int i = 0; i < word.length(); i++) {
		if (x > (size-1)) { // if x becomes an invalid index
			return false;
		}
		else {
			jumble[y][x] = word[i];
			x++;
		}
	}
	return true;
}
//print word in array right to left
bool JumblePuzzle::insertWest(int x, int y) {
	for (int i = 0; i < word.length(); i++) {
		if (x < 0) { // if x becomes an invalid index
			return false;
		}
		else {
			jumble[y][x] = word[i];
			x--;
		}
	}
	return true;
}
void JumblePuzzle::insertWord() {
	//insert word into the array
		// picking orientation that word will be placed in
	int dir = rand() % 3; // generate number between 0-3 NSEW
	// keep trying until entire word has been added to grid
	while (true) {
		if (hidden == false) {
			// coordinates of starting point
			int x = rand() % size;
			int y = rand() % size;
			if (dir == 0) {
				hidden = insertNorth(x, y);
				direction = 'n';
			}
			if (dir == 1) {
				hidden = insertSouth(x, y);
				direction = 's';
			}
			if (dir == 2) {
				hidden = insertEast(x, y);
				direction = 'e';
			}
			if (dir == 3) {
				hidden = insertWest(x, y);
				direction = 'w';
			}
			rowPos = y;
			colPos = x;
		}
		else {
			break;
		}
	}
}
//Overloading Assignment Operator
JumblePuzzle& JumblePuzzle::operator =(const JumblePuzzle& rhs) {
	if (this == &rhs)
		return *this;

	//since jumble is stored on the heap, it must be deleted before it is reassigned
	for (int i = 0; i < this->size; i++) {
		delete[] jumble[i];
		jumble[i] = nullptr;
	}
	delete[] jumble;
	jumble = nullptr;

	this->colPos = rhs.colPos;
	this->rowPos = rhs.rowPos;
	this->direction = rhs.direction;
	this->difficulty = rhs.difficulty;
	this->size = rhs.size;

	jumble = new charArrayPtr[rhs.size];
	for (int j = 0; j < rhs.size; j++)
		jumble[j] = new char[rhs.size];
	for (int y = 0; y < rhs.size; y++) {
		for (int x = 0; x < rhs.size + 1; x++) {
			jumble[y][x] = rhs.jumble[y][x];
		}
	}

	return *this;
}
//destructor for puzzle
JumblePuzzle::~JumblePuzzle() {
	for (int i = 0; i < size; ++i) {
		delete[] jumble[i];
		jumble[i] = nullptr;
	}
	delete[] jumble;
	jumble = nullptr;
}