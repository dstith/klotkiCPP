/**
 * Program Name: cis27Spring2015Klotski.c
 * Discussion:   
 * Written By:   D Stith
 * Date:         2015/05/10
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
	Block block1('A', 'A');
	Block block2('B', 'B');
	Block block3('B', 'K');
	Block block4('C', 'C');
	Block block5('A', 'L');
	Block block6('B', 'M');
	Block block7('B', 'N');
	Block block8('C', 'O');
	Block block9('D', 'D');
	Block block10('E', 'E');
	Block block11('E', 'P');
	Block block12('F', 'F');
	Block block13('D', 'Q');
	Block block14('G', 'G');
	Block block15('H', 'H');
	Block block16('F', 'R');
	Block block17('I', 'I');
	Block block18('J', 'J');
	Block block19(' ', ' ');
	Block block20(' ', ' ');
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

		// Clear the screen
		if (toupper(moveDirection) != 'Q' && toupper(blockToMove) != 'Q') {
			cout << setfill('\n') << setw(50) << ' ' << '\b';
		}

		for (int i = 0; i < 10; i++) {
			cout << setfill(' ') << setw(36) << ' ';
			for (int j = 0; j < 8; j++) {
				cout << boardDisplay[i][j];
			}
			cout << endl;
		}

		do {
			cout << "\nW = Up, S = Down, A = Left, D = Right (Q to quit)" \
				"\nEnter direction: ";
			cin >> moveDirection;
		} while (toupper(moveDirection) != 'W' && toupper(moveDirection) != 'A' &&
			toupper(moveDirection) != 'S' && toupper(moveDirection) != 'D' &&
			toupper(moveDirection) != 'Q');

		if (toupper(moveDirection) != 'Q') {
			cout << "Enter piece to move [A thru J] or (Q to quit): ";
			cin >> blockToMove;

			cout << endl;

			// Search the board for the block and store xPos and yPos
			searchAry(blockToMove, myBoard, rows, cols, &xPos, &yPos);
		}

		switch (toupper(moveDirection)) {
			case 'Q':
				break;
			case 'W':
				switch (toupper(blockToMove)) {
					case 'G':
					case 'H':
					case 'I':
					case 'J':
						// Check if move is legal
						if (myBoard[xPos - 1][yPos].getName() == ' ') {
							// swap
							tempBlock.setName(myBoard[xPos][yPos].getName());
							tempBlock.setFill(myBoard[xPos][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos] = myBoard[xPos - 1][yPos];
							myBoard[xPos - 1][yPos] = tempBlock;
						}
						break;
					case 'E': // JK horizontal block
						// Check if move is legal
						if (myBoard[xPos - 1][yPos].getName() == ' ' &&
							myBoard[xPos - 1][yPos + 1].getName() == ' ') {
								// swap
								tempBlock.setName(myBoard[xPos][yPos].getName());
								tempBlock.setFill(myBoard[xPos][yPos].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos] = myBoard[xPos - 1][yPos];
								myBoard[xPos - 1][yPos] = tempBlock;

								tempBlock.setName(myBoard[xPos][yPos + 1].getName());
								tempBlock.setFill(myBoard[xPos][yPos + 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos + 1] = myBoard[xPos - 1][yPos + 1];
								myBoard[xPos - 1][yPos + 1] = tempBlock;
						}
						break;
					case 'A': // vertical blocks A/E, D/H, I/M, L/P
					case 'C':
					case 'D':
					case 'F':
						// Check if move is legal
						if (myBoard[xPos - 1][yPos].getName() == ' ') {
							// swap
							tempBlock.setName(myBoard[xPos][yPos].getName());
							tempBlock.setFill(myBoard[xPos][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos] = myBoard[xPos - 1][yPos];
							myBoard[xPos - 1][yPos] = tempBlock;

							tempBlock.setName(myBoard[xPos + 1][yPos].getName());
							tempBlock.setFill(myBoard[xPos + 1][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 1][yPos] = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = tempBlock;
						}
						break;
					case 'B': // BC/FG
						// Check if move is legal
						if (myBoard[xPos - 1][yPos].getName() == ' ' &&
							myBoard[xPos - 1][yPos + 1].getName() == ' ') {
								// swap
								tempBlock.setName(myBoard[xPos][yPos].getName());
								tempBlock.setFill(myBoard[xPos][yPos].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos] = myBoard[xPos - 1][yPos];
								myBoard[xPos - 1][yPos] = tempBlock;

								tempBlock.setName(myBoard[xPos][yPos + 1].getName());
								tempBlock.setFill(myBoard[xPos][yPos + 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos + 1] = myBoard[xPos - 1][yPos + 1];
								myBoard[xPos - 1][yPos + 1] = tempBlock;

								tempBlock.setName(myBoard[xPos + 1][yPos].getName());
								tempBlock.setFill(myBoard[xPos + 1][yPos].getFill());
								tempBlock.fillBlock();
								myBoard[xPos + 1][yPos] = myBoard[xPos][yPos];
								myBoard[xPos][yPos] = tempBlock;

								tempBlock.setName(myBoard[xPos + 1][yPos + 1].getName());
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
					case 'G':
					case 'H':
					case 'I':
					case 'J':
						// Check if move is legal
						if (myBoard[xPos][yPos - 1].getName() == ' ') {
							// swap
							tempBlock.setName(myBoard[xPos][yPos].getName());
							tempBlock.setFill(myBoard[xPos][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos] = myBoard[xPos][yPos - 1];
							myBoard[xPos][yPos - 1] = tempBlock;
						}
						break;
					case 'E': // JK horizontal block
						// Check if move is legal
						if (myBoard[xPos][yPos - 1].getName() == ' ') {
								// swap
								tempBlock.setName(myBoard[xPos][yPos - 1].getName());
								tempBlock.setFill(myBoard[xPos][yPos - 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos - 1] = myBoard[xPos][yPos];
								myBoard[xPos][yPos] = myBoard[xPos][yPos + 1];
								myBoard[xPos][yPos + 1] = tempBlock;
						}
						break;
					case 'A': // vertical blocks A/E, D/H, I/M, L/P
					case 'C':
					case 'D':
					case 'F':
						// Check if move is legal
						if (myBoard[xPos][yPos - 1].getName() == ' ' && 
							myBoard[xPos + 1][yPos - 1].getName() == ' ') {
							// swap
							tempBlock.setName(myBoard[xPos][yPos - 1].getName());
							tempBlock.setFill(myBoard[xPos][yPos - 1].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos - 1] = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = tempBlock;

							tempBlock.setName(myBoard[xPos + 1][yPos - 1].getName());
							tempBlock.fillBlock();
							myBoard[xPos + 1][yPos - 1] = myBoard[xPos + 1][yPos];
							myBoard[xPos + 1][yPos] = tempBlock;
						}
						break;
					case 'B': // BC/FG
						// Check if move is legal
						if (myBoard[xPos][yPos - 1].getName() == ' ' &&
							myBoard[xPos + 1][yPos - 1].getName() == ' ') {
								// swap
								tempBlock.setName(myBoard[xPos][yPos - 1].getName());
								tempBlock.setFill(myBoard[xPos][yPos - 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos - 1] = myBoard[xPos][yPos];
								myBoard[xPos][yPos] = tempBlock;

								tempBlock.setName(myBoard[xPos + 1][yPos - 1].getName());
								tempBlock.setFill(myBoard[xPos + 1][yPos - 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos + 1][yPos - 1] = myBoard[xPos + 1][yPos];
								myBoard[xPos + 1][yPos] = tempBlock;

								tempBlock.setName(myBoard[xPos][yPos].getName());
								tempBlock.setFill(myBoard[xPos][yPos].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos] = myBoard[xPos][yPos + 1];
								myBoard[xPos][yPos + 1] = tempBlock;

								tempBlock.setName(myBoard[xPos + 1][yPos].getName());
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
					case 'G':
					case 'H':
					case 'I':
					case 'J':
						// Check if move is legal
						if (myBoard[xPos + 1][yPos].getName() == ' ') {
							// swap
							tempBlock.setName(myBoard[xPos][yPos].getName());
							tempBlock.setFill(myBoard[xPos][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos] = myBoard[xPos + 1][yPos];
							myBoard[xPos + 1][yPos] = tempBlock;
						}
						break;
					case 'E': // JK horizontal block
						// Check if move is legal
						if (myBoard[xPos + 1][yPos].getName() == ' ' &&
							myBoard[xPos + 1][yPos + 1].getName() == ' ') {
								// swap
								tempBlock.setName(myBoard[xPos][yPos].getName());
								tempBlock.setFill(myBoard[xPos][yPos].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos] = myBoard[xPos + 1][yPos];
								myBoard[xPos + 1][yPos] = tempBlock;

								tempBlock.setName(myBoard[xPos][yPos + 1].getName());
								tempBlock.setFill(myBoard[xPos][yPos + 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos + 1] = myBoard[xPos + 1][yPos + 1];
								myBoard[xPos + 1][yPos + 1] = tempBlock;
						}
						break;
					case 'A': // vertical blocks A/E, D/H, I/M, L/P
					case 'C':
					case 'D':
					case 'F':
						// Check if move is legal
						if (myBoard[xPos + 2][yPos].getName() == ' ') {
							// swap
							tempBlock.setName(myBoard[xPos + 2][yPos].getName());
							tempBlock.setFill(myBoard[xPos + 2][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 2][yPos] = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = tempBlock;

							tempBlock.setName(myBoard[xPos + 1][yPos].getName());
							tempBlock.setFill(myBoard[xPos + 1][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 1][yPos] = myBoard[xPos + 2][yPos];
							myBoard[xPos + 2][yPos] = tempBlock;
						}
						break;
					case 'B': // BC/FG
						// Check if move is legal
						if (myBoard[xPos + 2][yPos].getName() == ' ' &&
							myBoard[xPos + 2][yPos + 1].getName() == ' ') {
							// swap
							tempBlock.setName(myBoard[xPos + 2][yPos].getName());
							tempBlock.setFill(myBoard[xPos + 2][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 2][yPos] = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = tempBlock;

							tempBlock.setName(myBoard[xPos + 2][yPos + 1].getName());
							tempBlock.setFill(myBoard[xPos + 2][yPos + 1].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 2][yPos + 1] = myBoard[xPos][yPos + 1];
							myBoard[xPos][yPos + 1] = tempBlock;

							tempBlock.setName(myBoard[xPos + 2][yPos].getName());
							tempBlock.setFill(myBoard[xPos + 2][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 2][yPos] = myBoard[xPos + 1][yPos];
							myBoard[xPos + 1][yPos] = tempBlock;

							tempBlock.setName(myBoard[xPos + 2][yPos + 1].getName());
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
					case 'G':
					case 'H':
					case 'I':
					case 'J':
						// Check if move is legal
						if (myBoard[xPos][yPos + 1].getName() == ' ') {
							// swap
							//tempBlock = myBoard[xPos][yPos];
							tempBlock.setName(myBoard[xPos][yPos].getName());
							tempBlock.setFill(myBoard[xPos][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos] = myBoard[xPos][yPos + 1];
							myBoard[xPos][yPos + 1] = tempBlock;
						}
						break;
					case 'E': // JK horizontal block
						// Check if move is legal
						if (myBoard[xPos][yPos + 2].getName() == ' ') {
								// swap
								tempBlock.setName(myBoard[xPos][yPos].getName());
								tempBlock.setFill(myBoard[xPos][yPos].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos] = myBoard[xPos][yPos + 2];
								myBoard[xPos][yPos + 2] = tempBlock;

								tempBlock.setName(myBoard[xPos][yPos + 1].getName());
								tempBlock.setFill(myBoard[xPos][yPos + 1].getFill());
								tempBlock.fillBlock();
								myBoard[xPos][yPos + 1] = myBoard[xPos][yPos + 2];
								myBoard[xPos][yPos + 2] = tempBlock;
						}
						break;
					case 'A': // vertical blocks A/E, D/H, I/M, L/P
					case 'C':
					case 'D':
					case 'F': 
						// Check if move is legal
						if (myBoard[xPos][yPos + 1].getName() == ' ' &&
							myBoard[xPos + 1][yPos + 1].getName() == ' ') {
							// swap
							tempBlock.setName(myBoard[xPos][yPos].getName());
							tempBlock.setFill(myBoard[xPos][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos] = myBoard[xPos][yPos + 1];
							myBoard[xPos][yPos + 1] = tempBlock;

							tempBlock.setName(myBoard[xPos + 1][yPos].getName());
							tempBlock.setFill(myBoard[xPos + 1][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 1][yPos] = myBoard[xPos + 1][yPos + 1];
							myBoard[xPos + 1][yPos + 1] = tempBlock;
						}
						break;
					case 'B': // BC/FG
						// Check if move is legal
						if (myBoard[xPos][yPos + 2].getName() == ' ' &&
							myBoard[xPos + 1][yPos + 2].getName() == ' ') {
							// swap
							tempBlock.setName(myBoard[xPos][yPos].getName());
							tempBlock.setFill(myBoard[xPos][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos] = myBoard[xPos][yPos + 2];
							myBoard[xPos][yPos + 2] = tempBlock;

							tempBlock.setName(myBoard[xPos + 1][yPos].getName());
							tempBlock.setFill(myBoard[xPos + 1][yPos].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 1][yPos] = myBoard[xPos + 1][yPos + 2];
							myBoard[xPos + 1][yPos + 2] = tempBlock;

							tempBlock.setName(myBoard[xPos][yPos + 1].getName());
							tempBlock.setFill(myBoard[xPos][yPos + 1].getFill());
							tempBlock.fillBlock();
							myBoard[xPos][yPos + 1] = myBoard[xPos][yPos + 2];
							myBoard[xPos][yPos + 2] = tempBlock;

							tempBlock.setName(myBoard[xPos + 1][yPos + 1].getName());
							tempBlock.setFill(myBoard[xPos + 1][yPos + 1].getFill());
							tempBlock.fillBlock();
							myBoard[xPos + 1][yPos + 1] = myBoard[xPos + 1][yPos + 2];
							myBoard[xPos + 1][yPos + 2] = tempBlock;
						}
						break;
				}
				break;
			default:
				break;
		}
	} while (toupper(moveDirection) != 'Q' && toupper(blockToMove) != 'Q');
}

void searchAry(char blockToMove, Block** boardAry, int rows, int cols, int *xPos, int *yPos) {
	int sentinel = 0;

	for (int i = 0; sentinel == 0 && i < rows; i++) {
		for (int j = 0; sentinel == 0 && j < cols; j++) {
			if (sentinel == 0 && boardAry[i][j].getName() == toupper(blockToMove)) {
				sentinel = 1;
				*xPos = i;
				*yPos = j;
			}
		}
	}
}
