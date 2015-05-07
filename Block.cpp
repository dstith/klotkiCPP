/**
 * Block implementation file
 */
#include "Block.h"

Block::Block() {
	fillChar = NULL;
	rowSize = 2;
	colSize = 2;
	block = new char*[colSize];
	for (int i = 0; i < colSize; i++) {
		block[i] = new char[rowSize];
	}

	fillBlock();
}

Block::Block(char fillChar) {
	this->fillChar = fillChar;
	rowSize = 2;
	colSize = 2;
	block = new char*[colSize];
	for (int i = 0; i < colSize; i++) {
		block[i] = new char[rowSize];
	}

	fillBlock();
}

Block::Block(char fillChar, int rows, int cols) {
	this->fillChar = fillChar;
	rowSize = rows;
	colSize = cols;
	block = new char*[colSize];
	for (int i = 0; i < colSize; i++) {
		block[i] = new char[rowSize];
	}

	fillBlock();
}

Block::~Block() {
	for (int i = 0; i < colSize; i++) {
		delete[] block[i];
	}
	delete[] block;
}

void Block::setFill(char fillChar) {
	this->fillChar = fillChar;
}

char Block::getFill() {
	return fillChar;
}

void Block::fillBlock() {
	for (int i = 0; i < colSize; i++) {
		for (int j = 0; j < rowSize; j++) {
			block[i][j] = fillChar;
		}
	}
}

void Block::printBlock() {
	for (int i = 0; i < colSize; i++) {	
		for (int j = 0; j < rowSize; j++) {
			cout << block[i][j];
		}
		cout << endl;
	}
}

char** Block::getArray() {
	return block;
}
