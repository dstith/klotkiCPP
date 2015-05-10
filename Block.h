/**
 * Block header file
 */
#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
using namespace std;

// Block class definition
class Block {
	private:
		char fillChar;
		char name;
		char** block;
		int rowSize;
		int colSize;
	public:
		Block();
		Block(char, char);
		Block(char, char, int, int);
		~Block();
		void setFill(char);
		void setName(char);
		char getFill();
		char getName();
		void fillBlock();
		void printBlock();
		char** getArray();
}; // End of Block class

#endif
