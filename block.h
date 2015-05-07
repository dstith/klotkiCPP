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
		char** block;
		int rowSize;
		int colSize;
	public:
		Block();
		Block(char);
		Block(char, int, int);
		~Block();
		void setFill(char);
		char getFill();
		void fillBlock();
		void printBlock();
		char** getArray();
}; // End of Block class

#endif
