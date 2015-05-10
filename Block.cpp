/**
 * Block implementation file
 */
#include "Block.h"

Block::Block() {
	fillChar = NULL;
	name = NULL;
	rowSize = 2;
	colSize = 2;
	block = new char*[colSize];
	for (int i = 0; i < colSize; i++) {
		block[i] = new char[rowSize];
	}

	fillBlock();
}

Block::Block(char fillChar, char name) {
	this->fillChar = fillChar;
	this->name = name;
	rowSize = 2;
	colSize = 2;
	block = new char*[colSize];
	for (int i = 0; i < colSize; i++) {
		block[i] = new char[rowSize];
	}

	fillBlock();
}

Block::Block(char fillChar, char name, int rows, int cols) {
	this->fillChar = fillChar;
	this->name = name;
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

void Block::setName(char name) {
	this->name = name;
}

char Block::getFill() {
	return fillChar;
}

char Block::getName() {
	return name;
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
