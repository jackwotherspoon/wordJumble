/*
jumble.h

		Created: Nov 14, 2018
		Author: Jack Wotherspoon

*/
#pragma once 
#include <string>
using namespace std;

typedef char* charArrayPtr; //told to implement this in assignment handout

class BadJumbleException {
public:
	BadJumbleException(const string&);
	string what() const;
private:
	string message;
}; //end of exception class

class JumblePuzzle {
public:
	JumblePuzzle(); //default constructor
	JumblePuzzle(string hiddenWord,string difficulty); //two parameter constructor
	JumblePuzzle(const JumblePuzzle&); //copy constructor
	~JumblePuzzle(); //destructor
	JumblePuzzle& operator=(const JumblePuzzle& jp); //overloading assignment operator


	//accessors
	int getRowPos();
	int getColPos();
	int getSize();
	char getDirection();
	string getWord();
	string getDifficulty();
	charArrayPtr* getJumble(); //this is the double pointer to heap

private:
	//insert words for each direction
	bool hidden=false;
	bool insertNorth(int, int);
	bool insertSouth(int, int);
	bool insertEast(int, int);
	bool insertWest(int, int);
	void insertWord();
	
	string word;
	string difficulty;
	int rowPos;
	int colPos;
	int size;
	char direction;
	charArrayPtr* jumble;
};