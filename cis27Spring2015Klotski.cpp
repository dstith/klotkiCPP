/**
 * Program Name: cis27Spring2015Klotski.c
 * Discussion:   
 * Written By:   xxxxxxxxxxxx
 * Date:         2015/04/30
 */

#include <iostream>
#include <iomanip>
#include "Block.h"

using namespace std;

void searchAry(char, Block**, int, int, int*, int*);

int main() {
	char blockToMove = NULL;
	char moveDirection = NULL;
	int xPos = NULL; // Poisition of the block found after search
	int yPos = NULL;
	const int rows = 7; // Size of the board that contains the objects
	const int cols = 6;
	// char** fillAry; // Pointer that stores address of a 2D array containing chars

	//Block myBoard[rows][cols];
	Block **myBoard = new Block *[rows]; // Dynamically allocate memory to board containing objects
	for (int i = 0; i < rows; i++) {
		myBoard[i] = new Block[cols];
	}
	
	// Declare and define objects of 2x2 Block objects
	Block block1('A');
	Block block2('B');
	Block block3('C');
	Block block4('D');
	Block block5('E');
	Block block6('F');
	Block block7('G');
	Block block8('H');
	Block block9('I');
	Block block10('J');
	Block block11('K');
	Block block12('L');
	Block block13('M');
	Block block14('N');
	Block block15('O');
	Block block16('P');
	Block block17('Q');
	Block block18('R');
	Block block19(' ');
	Block block20(' ');
	Block tempBlock;
	
	// Put the block objects in the board
	myBoard[1][1] = block1;
	myBoard[1][2] = block2;
	myBoard[1][3] = block3;
	myBoard[1][4] = block4;
	myBoard[2][1] = block5;
	myBoard[2][2] = block6;
	myBoard[2][3] = block7;
	myBoard[2][4] = block8;
	myBoard[3][1] = block9;
	myBoard[3][2] = block10;
	myBoard[3][3] = block11;
	myBoard[3][4] = block12;
	myBoard[4][1] = block13;
	myBoard[4][2] = block14;
	myBoard[4][3] = block15;
	myBoard[4][4] = block16;
	myBoard[5][1] = block17;
	myBoard[5][4] = block18;
	myBoard[5][2] = block19;
	myBoard[5][3] = block20;
	
	/*
	// Display a board Block object
	fillAry = myBoard[5][2].getArray();
	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << fillAry[i][j];
		}
		cout << endl;
	}
	*/

	// Run the puzzle
	do {
		// TODO
		// print board
		// input piece to move
		// input direction
		// q to quit
		cout << "Enter direction: ";
		cin >> moveDirection;
		if (toupper(moveDirection) != 'Q') {
			do {
				cout << "Enter piece to move: ";
				cin >> blockToMove;
			} while (toupper(blockToMove) < 'A' || toupper(blockToMove) > 'R');
		
			// Search the board for the block and store xPos and yPos
			searchAry(blockToMove, myBoard, rows, cols, &xPos, &yPos);
		}
		//cout << "xpos = " << xPos << " ypos = " << yPos << endl;
		switch (toupper(moveDirection)) {
			case 'Q':
				break;
			case 'W':
				// Check if move is legal
				if (myBoard[xPos][yPos - 1].getFill() == ' ') {
					// swap
					tempBlock.setFill(myBoard[xPos][yPos].getFill());
					tempBlock.fillBlock();
					myBoard[xPos][yPos] = myBoard[xPos][yPos - 1];
					myBoard[xPos][yPos - 1] = tempBlock;
				}
				break;
			case 'A':
				// Check if move is legal
				if (myBoard[xPos - 1][yPos].getFill() == ' ') {
					// swap
					tempBlock.setFill(myBoard[xPos][yPos].getFill());
					tempBlock.fillBlock();
					myBoard[xPos][yPos] = myBoard[xPos - 1][yPos];
					myBoard[xPos - 1][yPos] = tempBlock;
				}
				// Move the block
				break;
			case 'S':
				// Check if move is legal
				if (myBoard[xPos][yPos + 1].getFill() == ' ') {
					// swap
					tempBlock.setFill(myBoard[xPos][yPos].getFill());
					tempBlock.fillBlock();
					myBoard[xPos][yPos] = myBoard[xPos][yPos + 1];
					myBoard[xPos][yPos + 1] = tempBlock;
				}
				break;
			case 'D':
				// Check if move is legal
				if (myBoard[xPos + 1][yPos].getFill() == ' ') {
					// swap
					tempBlock.setFill(myBoard[xPos][yPos].getFill());
					tempBlock.fillBlock();
					myBoard[xPos][yPos] = myBoard[xPos + 1][yPos];
					myBoard[xPos + 1][yPos] = tempBlock;
				}
				break;
			default:
				cout << "\nInvalid direction.\n";
				break;
		}
	} while (toupper(moveDirection) != 'Q');
	/*
	// Declare and define objects of various sizes
	// This block of code is an example but probably won't be used
	// since I am going to put blocks together somehow when moving
	// blocks that are larger than the default size
	Block myBlock1('A', 2, 4);
	Block myBlock2('B', 2, 4);
	Block myBlock3('C', 2, 4);
	Block myBlock4('D', 2, 4);
	Block myBlock5('E');
	Block myBlock6('F');
	Block myBlock7('G');
	Block myBlock8('H');
	Block myBlock9('I', 4, 2);
	Block myBlock10('J', 4, 4);
	Block myBlockBlank1(' ');
	Block myBlockBlank2(' ');
	
	// Print the blocks
	myBlock1.printBlock();
	cout << endl;
	myBlock2.printBlock();
	cout << endl;
	myBlock3.printBlock();
	cout << endl;
	myBlock4.printBlock();
	cout << endl;
	myBlock5.printBlock();
	cout << endl;
	myBlock6.printBlock();
	cout << endl;
	myBlock7.printBlock();
	cout << endl;
	myBlock8.printBlock();
	cout << endl;
	myBlock9.printBlock();
	cout << endl;
	myBlock10.printBlock();
	*/
	return 0;
}

void searchAry(char blockToMove, Block** boardAry, int rows, int cols, int *xPos, int *yPos) {
	int sentinel = 0;

	for (int i = 0; sentinel == 0 && i < rows; i++) {
		for (int j = 0; sentinel == 0 && j < cols; j++) {
			if (sentinel == 0 && boardAry[i][j].getFill() == toupper(blockToMove)) {
				sentinel = 1;
				*xPos = i;
				*yPos = j;
			}
		}
	}
}
