/**
 * Program Name: cis27Spring2015Klotski.c
 * Discussion:   
 * Written By:   D Stith
 * Date:         2015/05/09
 */

#include <iostream>
#include <iomanip>
#include "Block.h"

using namespace std;

void searchAry(char, Block**, int, int, int*, int*);
void runBoardGame(void);

int main() {
	runBoardGame();
	return 0;
}

void runBoardGame() {
	char blockToMove = NULL;
	char moveDirection = NULL;
	int xPos = NULL; // Poisition of the block found after search
	int yPos = NULL;
	const int rows = 7; // Size of the board that contains the objects
	const int cols = 6;
	char boardDisplay[10][8];
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

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 8; j++) {
			boardDisplay[i][j] = 'X';
		}
	}
	
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

	/*
	
	A  BC  D
	E  FG  H
	
	I  JK  L
	M  N O P

	Q '''' R

	2x2: N,O,Q,R

	4x2: AE, DH, IM, LP
	
	2x4: JK
	
	4x4: BCFG
	
	*/

	// Run the puzzle
	do {
		// TODO
		// print board
		// input piece to move
		// input direction
		// q to quit

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				boardDisplay[i][j] = myBoard[1][1].getFill();
				boardDisplay[i][j + 2] = myBoard[1][2].getFill();
				boardDisplay[i][j + 4] = myBoard[1][3].getFill();
				boardDisplay[i][j + 6] = myBoard[1][4].getFill();

				boardDisplay[i + 2][j] = myBoard[2][1].getFill();
				boardDisplay[i + 2][j + 2] = myBoard[2][2].getFill();
				boardDisplay[i + 2][j + 4] = myBoard[2][3].getFill();
				boardDisplay[i + 2][j + 6] = myBoard[2][4].getFill();

				boardDisplay[i + 4][j] = myBoard[3][1].getFill();
				boardDisplay[i + 4][j + 2] = myBoard[3][2].getFill();
				boardDisplay[i + 4][j + 4] = myBoard[3][3].getFill();
				boardDisplay[i + 4][j + 6] = myBoard[3][4].getFill();

				boardDisplay[i + 6][j] = myBoard[4][1].getFill();
				boardDisplay[i + 6][j + 2] = myBoard[4][2].getFill();
				boardDisplay[i + 6][j + 4] = myBoard[4][3].getFill();
				boardDisplay[i + 6][j + 6] = myBoard[4][4].getFill();

				boardDisplay[i + 8][j] = myBoard[5][1].getFill();
				boardDisplay[i + 8][j + 2] = myBoard[5][2].getFill();
				boardDisplay[i + 8][j + 4] = myBoard[5][3].getFill();
				boardDisplay[i + 8][j + 6] = myBoard[5][4].getFill();
			}
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 8; j++) {
				cout << boardDisplay[i][j];
			}
			cout << endl;
		}


		cout << "Enter direction (Q to quit): ";
		cin >> moveDirection;
		if (toupper(moveDirection) != 'Q') {
			do {
				cout << "Enter piece to move: ";
				cin >> blockToMove;
			} while (toupper(blockToMove) < 'A' || toupper(blockToMove) > 'R');
		
			// Search the board for the block and store xPos and yPos
			searchAry(blockToMove, myBoard, rows, cols, &xPos, &yPos);
			cout << "\nX position: " << xPos << "\nY position: " << yPos << endl << endl;
		}
		//cout << "xpos = " << xPos << " ypos = " << yPos << endl;
		switch (toupper(moveDirection)) {
			case 'Q':
				break;
			case 'W':
				switch (toupper(blockToMove)) {
					case 'N':
					case 'O':
					case 'Q':
					case 'R':
						// Check if move is legal
						if (myBoard[xPos - 1][yPos].getFill() == ' ') {
							// swap
							tempBlock.setFill(myBoard[xPos][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos] = myBoard[xPos - 1][yPos];
							myBoard[xPos - 1][yPos] = tempBlock;
						}
						break;
					case 'J': // JK horizontal block
						// Check if move is legal
						if (myBoard[xPos - 1][yPos].getFill() == ' ' &&
							myBoard[xPos - 1][yPos + 1].getFill() == ' ') {
								// swap
								tempBlock.setFill(myBoard[xPos][yPos].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos] = myBoard[xPos - 1][yPos];
								myBoard[xPos - 1][yPos] = tempBlock;

								tempBlock.setFill(myBoard[xPos][yPos + 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos + 1] = myBoard[xPos - 1][yPos + 1];
								myBoard[xPos - 1][yPos + 1] = tempBlock;
						}
						break;
					case 'A': // vertical blocks A/E, D/H, I/M, L/P
					case 'D':
					case 'I':
					case 'L':
						// Check if move is legal
						if (myBoard[xPos - 1][yPos].getFill() == ' ') {
							// swap
							tempBlock.setFill(myBoard[xPos][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos] = myBoard[xPos - 1][yPos];
							myBoard[xPos - 1][yPos] = tempBlock;

							tempBlock.setFill(myBoard[xPos + 1][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 1][yPos] = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = tempBlock;
						}
						break;
					case 'B': // BC/FG
						// Check if move is legal
						if (myBoard[xPos - 1][yPos].getFill() == ' ' &&
							myBoard[xPos - 1][yPos + 1].getFill() == ' ') {
								// swap
								tempBlock.setFill(myBoard[xPos][yPos].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos] = myBoard[xPos - 1][yPos];
								myBoard[xPos - 1][yPos] = tempBlock;

								tempBlock.setFill(myBoard[xPos][yPos + 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos + 1] = myBoard[xPos - 1][yPos + 1];
								myBoard[xPos - 1][yPos + 1] = tempBlock;

								tempBlock.setFill(myBoard[xPos + 1][yPos].getFill());
								tempBlock.fillBlock();
								myBoard[xPos + 1][yPos] = myBoard[xPos][yPos];
								myBoard[xPos][yPos] = tempBlock;

								tempBlock.setFill(myBoard[xPos + 1][yPos + 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos + 1][yPos + 1] = myBoard[xPos][yPos + 1];
								myBoard[xPos][yPos + 1] = tempBlock;
						}
						break;
				}
				break;
			case 'A': 
				// Check if move is legal
				switch (toupper(blockToMove)) {
					case 'N':
					case 'O':
					case 'Q':
					case 'R':
						// Check if move is legal
						if (myBoard[xPos][yPos - 1].getFill() == ' ') {
							// swap
							tempBlock.setFill(myBoard[xPos][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos] = myBoard[xPos][yPos - 1];
							myBoard[xPos][yPos - 1] = tempBlock;
						}
						break;
					case 'J': // JK horizontal block
						// Check if move is legal
						if (myBoard[xPos][yPos - 1].getFill() == ' ') {
								// swap
								tempBlock.setFill(myBoard[xPos][yPos - 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos - 1] = myBoard[xPos][yPos];
								myBoard[xPos][yPos] = myBoard[xPos][yPos + 1];
								myBoard[xPos][yPos + 1] = tempBlock;
						}
						break;
					case 'A': // vertical blocks A/E, D/H, I/M, L/P
					case 'D':
					case 'I':
					case 'L':
						// Check if move is legal
						if (myBoard[xPos][yPos - 1].getFill() == ' ' && 
							myBoard[xPos + 1][yPos - 1].getFill() == ' ') {
							// swap
							tempBlock.setFill(myBoard[xPos][yPos - 1].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos - 1] = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = tempBlock;

							tempBlock.setFill(myBoard[xPos + 1][yPos - 1].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 1][yPos - 1] = myBoard[xPos + 1][yPos];
							myBoard[xPos + 1][yPos] = tempBlock;
						}
						break;
					case 'B': // BC/FG
						// Check if move is legal
						if (myBoard[xPos][yPos - 1].getFill() == ' ' &&
							myBoard[xPos + 1][yPos - 1].getFill() == ' ') {
								// swap
								tempBlock.setFill(myBoard[xPos][yPos - 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos - 1] = myBoard[xPos][yPos];
								myBoard[xPos][yPos] = tempBlock;

								tempBlock.setFill(myBoard[xPos + 1][yPos - 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos + 1][yPos - 1] = myBoard[xPos + 1][yPos];
								myBoard[xPos + 1][yPos] = tempBlock;

								tempBlock.setFill(myBoard[xPos][yPos].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos] = myBoard[xPos][yPos + 1];
								myBoard[xPos][yPos + 1] = tempBlock;

								tempBlock.setFill(myBoard[xPos + 1][yPos].getFill());
								tempBlock.fillBlock();
								myBoard[xPos + 1][yPos] = myBoard[xPos + 1][yPos + 1];
								myBoard[xPos + 1][yPos + 1] = tempBlock;
						}
						break;
				}
				break;
			case 'S': // Move block down
				switch (toupper(blockToMove)) {
					case 'N':
					case 'O':
					case 'Q':
					case 'R':
						// Check if move is legal
						if (myBoard[xPos + 1][yPos].getFill() == ' ') {
							// swap
							tempBlock.setFill(myBoard[xPos][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos] = myBoard[xPos + 1][yPos];
							myBoard[xPos + 1][yPos] = tempBlock;
						}
						break;
					case 'J': // JK horizontal block
						// Check if move is legal
						if (myBoard[xPos + 1][yPos].getFill() == ' ' &&
							myBoard[xPos + 1][yPos + 1].getFill() == ' ') {
								// swap
								tempBlock.setFill(myBoard[xPos][yPos].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos] = myBoard[xPos + 1][yPos];
								myBoard[xPos + 1][yPos] = tempBlock;

								tempBlock.setFill(myBoard[xPos][yPos + 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos + 1] = myBoard[xPos + 1][yPos + 1];
								myBoard[xPos + 1][yPos + 1] = tempBlock;
						}
						break;
					case 'A': // vertical blocks A/E, D/H, I/M, L/P
					case 'D':
					case 'I':
					case 'L':
						// Check if move is legal
						if (myBoard[xPos + 2][yPos].getFill() == ' ') {
							// swap
							tempBlock.setFill(myBoard[xPos + 2][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 2][yPos] = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = tempBlock;

							tempBlock.setFill(myBoard[xPos + 1][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 1][yPos] = myBoard[xPos + 2][yPos];
							myBoard[xPos + 2][yPos] = tempBlock;
						}
						break;
					case 'B': // BC/FG
						// Check if move is legal
						if (myBoard[xPos + 2][yPos].getFill() == ' ' &&
							myBoard[xPos + 2][yPos + 1].getFill() == ' ') {
							// swap
							tempBlock.setFill(myBoard[xPos + 2][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 2][yPos] = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = tempBlock;

							tempBlock.setFill(myBoard[xPos + 2][yPos + 1].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 2][yPos + 1] = myBoard[xPos][yPos + 1];
							myBoard[xPos][yPos + 1] = tempBlock;

							tempBlock.setFill(myBoard[xPos + 2][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 2][yPos] = myBoard[xPos + 1][yPos];
							myBoard[xPos + 1][yPos] = tempBlock;

							tempBlock.setFill(myBoard[xPos + 2][yPos + 1].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 2][yPos + 1] = myBoard[xPos + 1][yPos + 1];
							myBoard[xPos + 1][yPos + 1] = tempBlock;
						}
						break;
				}
				break;
			case 'D': // Move block right
				switch (toupper(blockToMove)) {
					case 'N':
					case 'O':
					case 'Q':
					case 'R':
						// Check if move is legal
						if (myBoard[xPos][yPos + 1].getFill() == ' ') {
							// swap
							tempBlock = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = myBoard[xPos][yPos + 1];
							myBoard[xPos][yPos + 1] = tempBlock;
						}
						break;
					case 'J': // JK horizontal block
						// Check if move is legal
						if (myBoard[xPos][yPos + 2].getFill() == ' ') {
								// swap
								tempBlock.setFill(myBoard[xPos][yPos].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos] = myBoard[xPos][yPos + 2];
								myBoard[xPos][yPos + 2] = tempBlock;

								tempBlock.setFill(myBoard[xPos][yPos + 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos + 1] = myBoard[xPos][yPos + 2];
								myBoard[xPos][yPos + 2] = tempBlock;
						}
						break;
					case 'A': // vertical blocks A/E, D/H, I/M, L/P
					case 'D':
					case 'I':
					case 'L': 
						// Check if move is legal
						if (myBoard[xPos][yPos + 1].getFill() == ' ' &&
							myBoard[xPos + 1][yPos + 1].getFill() == ' ') {
							// swap
							tempBlock.setFill(myBoard[xPos][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos] = myBoard[xPos][yPos + 1];
							myBoard[xPos][yPos + 1] = tempBlock;

							tempBlock.setFill(myBoard[xPos + 1][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 1][yPos] = myBoard[xPos + 1][yPos + 1];
							myBoard[xPos + 1][yPos + 1] = tempBlock;
						}
						break;
					case 'B': // BC/FG
						// Check if move is legal
						if (myBoard[xPos][yPos + 2].getFill() == ' ' &&
							myBoard[xPos + 1][yPos + 2].getFill() == ' ') {
							// swap
							tempBlock.setFill(myBoard[xPos][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos] = myBoard[xPos][yPos + 2];
							myBoard[xPos][yPos + 2] = tempBlock;

							tempBlock.setFill(myBoard[xPos + 1][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 1][yPos] = myBoard[xPos + 1][yPos + 2];
							myBoard[xPos + 1][yPos + 2] = tempBlock;

							tempBlock.setFill(myBoard[xPos][yPos + 1].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos + 1] = myBoard[xPos][yPos + 2];
							myBoard[xPos][yPos + 2] = tempBlock;

							tempBlock.setFill(myBoard[xPos + 1][yPos + 1].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 1][yPos + 1] = myBoard[xPos + 1][yPos + 2];
							myBoard[xPos + 1][yPos + 2] = tempBlock;
						}
						break;
				}
				break;
			default:
				cout << "\nInvalid direction.\n";
				break;
		}
	} while (toupper(moveDirection) != ']');
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
