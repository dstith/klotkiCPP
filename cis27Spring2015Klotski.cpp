/**
 * Program Name: cis27Spring2015Klotski.c
 * Discussion:   
 * Written By:   D Stith
 * Date:         2015/05/13
 */

#include <SFML/Graphics.hpp> // For shapes
#include <SFML/Graphics/Image.hpp> // For image files
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
	sf::RenderWindow window(sf::VideoMode(520, 640), "Klotski");
	sf::Texture bTexture;
	sf::Sprite bImage;
	sf::Sprite boardDisp[10][8];
	const float sprScale = 0.5;
	const int sprSize = 128;
	char blockToMove = NULL;
	char moveDirection = NULL;
	int xPos = NULL; // Poisition of the block found after search
	int yPos = NULL;
	const int rows = 7; // Size of the board that contains the objects
	const int cols = 6;
	char boardDisplay[10][8];

	if (!bTexture.loadFromFile("background.jpg")) {
		cout << "Error could not load background image.";
	}
	
 	bImage.setTexture(bTexture);

	Block **myBoard = new Block *[rows]; // Dynamically allocate memory to board containing objects
	for (int i = 0; i < rows; i++) {
		myBoard[i] = new Block[cols];
	}

	// Declare and define objects of 2x2 Block objects
	Block block1('A', 'A', 0, 0, sprSize, sprSize, sprScale);
	Block block2('B', 'B', sprSize, 0, sprSize, sprSize, sprScale);
	Block block3('B', 'K', sprSize, 0, sprSize, sprSize, sprScale);
	Block block4('C', 'C', 0, sprSize, sprSize, sprSize, sprScale);
	Block block5('A', 'L', 0, 0, sprSize, sprSize, sprScale);
	Block block6('B', 'M', sprSize, 0, sprSize, sprSize, sprScale);
	Block block7('B', 'N', sprSize, 0, sprSize, sprSize, sprScale);
	Block block8('C', 'O', 0, sprSize, sprSize, sprSize, sprScale);
	Block block9('D', 'D', sprSize, sprSize, sprSize, sprSize, sprScale);
	Block block10('E', 'E', 0,  sprSize * 3, sprSize, sprSize, sprScale);
	Block block11('E', 'P', 0, sprSize * 3, sprSize, sprSize, sprScale);
	Block block12('F', 'F', sprSize * 2, sprSize * 3, sprSize, sprSize, sprScale);
	Block block13('D', 'Q', sprSize, sprSize, sprSize, sprSize, sprScale);
	Block block14('G', 'G', sprSize * 2, sprSize, sprSize, sprSize, sprScale);
	Block block15('H', 'H', sprSize * 3, sprSize, sprSize, sprSize, sprScale);
	Block block16('F', 'R', sprSize * 2, sprSize * 3, sprSize, sprSize, sprScale);
	Block block17('I', 'I', sprSize * 2, 0, sprSize, sprSize, sprScale);
	Block block18('J', 'J', sprSize * 3, 0, sprSize, sprSize, sprScale);
	Block block19(' ', ' ', sprScale);
	Block block20(' ', ' ', sprScale);
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
	
	while (window.isOpen()) // Run game loop
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
			}
        }

		// Begin puzzle code block
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				boardDisplay[i][j] = myBoard[1][1].getFill();		
				boardDisplay[i][j + 2] = myBoard[1][2].getFill();
				boardDisplay[i][j + 4] = myBoard[1][3].getFill();
				boardDisplay[i][j + 6] = myBoard[1][4].getFill();

				boardDisp[i][j] = myBoard[1][1].getSprite();
				boardDisp[i][j + 2] = myBoard[1][2].getSprite();
				boardDisp[i][j + 4] = myBoard[1][3].getSprite();
				boardDisp[i][j + 6] = myBoard[1][4].getSprite();

				boardDisplay[i + 2][j] = myBoard[2][1].getFill();
				boardDisplay[i + 2][j + 2] = myBoard[2][2].getFill();
				boardDisplay[i + 2][j + 4] = myBoard[2][3].getFill();
				boardDisplay[i + 2][j + 6] = myBoard[2][4].getFill();

				boardDisp[i + 2][j] = myBoard[2][1].getSprite();
				boardDisp[i + 2][j + 2] = myBoard[2][2].getSprite();
				boardDisp[i + 2][j + 4] = myBoard[2][3].getSprite();
				boardDisp[i + 2][j + 6] = myBoard[2][4].getSprite();

				boardDisplay[i + 4][j] = myBoard[3][1].getFill();
				boardDisplay[i + 4][j + 2] = myBoard[3][2].getFill();
				boardDisplay[i + 4][j + 4] = myBoard[3][3].getFill();
				boardDisplay[i + 4][j + 6] = myBoard[3][4].getFill();

				boardDisp[i + 4][j] = myBoard[3][1].getSprite();
				boardDisp[i + 4][j + 2] = myBoard[3][2].getSprite();
				boardDisp[i + 4][j + 4] = myBoard[3][3].getSprite();
				boardDisp[i + 4][j + 6] = myBoard[3][4].getSprite();

				boardDisplay[i + 6][j] = myBoard[4][1].getFill();
				boardDisplay[i + 6][j + 2] = myBoard[4][2].getFill();
				boardDisplay[i + 6][j + 4] = myBoard[4][3].getFill();
				boardDisplay[i + 6][j + 6] = myBoard[4][4].getFill();

				boardDisp[i + 6][j] = myBoard[4][1].getSprite();
				boardDisp[i + 6][j + 2] = myBoard[4][2].getSprite();
				boardDisp[i + 6][j + 4] = myBoard[4][3].getSprite();
				boardDisp[i + 6][j + 6] = myBoard[4][4].getSprite();

				boardDisplay[i + 8][j] = myBoard[5][1].getFill();
				boardDisplay[i + 8][j + 2] = myBoard[5][2].getFill();
				boardDisplay[i + 8][j + 4] = myBoard[5][3].getFill();
				boardDisplay[i + 8][j + 6] = myBoard[5][4].getFill();

				boardDisp[i + 8][j] = myBoard[5][1].getSprite();
				boardDisp[i + 8][j + 2] = myBoard[5][2].getSprite();
				boardDisp[i + 8][j + 4] = myBoard[5][3].getSprite();
				boardDisp[i + 8][j + 6] = myBoard[5][4].getSprite();
			}
		}

		// Clear the screen in console
		if (toupper(moveDirection) != 'Q' && toupper(blockToMove) != 'Q') {
			cout << setfill('\n') << setw(50) << ' ' << '\b';
		}

		window.draw(bImage); // Display the background image

		// Display the board in console and window
		for (int i = 0; i < 10; i++) {
			cout << setfill(' ') << setw(36) << ' '; // Set board position to middle of console
			for (int j = 0; j < 8; j++) { // Display all board blocks
				cout << boardDisplay[i][j]; // Display to console
					
				boardDisp[i][j].setPosition(j * sprSize * sprScale, i * sprSize * sprScale); // Display to window
				window.draw(boardDisp[i][j]);
			}
			cout << endl;
		}
		window.display();
		window.clear();


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
				return;
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
							tempBlock = myBoard[xPos][yPos]; // Uses copy constructor
							myBoard[xPos][yPos] = myBoard[xPos - 1][yPos];
							myBoard[xPos - 1][yPos] = tempBlock;
						}
						break;
					case 'E': // JK horizontal block
						// Check if move is legal
						if (myBoard[xPos - 1][yPos].getName() == ' ' &&
							myBoard[xPos - 1][yPos + 1].getName() == ' ') {
								// swap
								tempBlock = myBoard[xPos][yPos];
								myBoard[xPos][yPos] = myBoard[xPos - 1][yPos];
								myBoard[xPos - 1][yPos] = tempBlock;

								tempBlock = myBoard[xPos][yPos + 1];
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
							tempBlock = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = myBoard[xPos - 1][yPos];
							myBoard[xPos - 1][yPos] = tempBlock;

							tempBlock = myBoard[xPos + 1][yPos];
							myBoard[xPos + 1][yPos] = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = tempBlock;
						}
						break;
					case 'B': // BC/FG
						// Check if move is legal
						if (myBoard[xPos - 1][yPos].getName() == ' ' &&
							myBoard[xPos - 1][yPos + 1].getName() == ' ') {
								// swap
								tempBlock = myBoard[xPos][yPos];
								myBoard[xPos][yPos] = myBoard[xPos - 1][yPos];
								myBoard[xPos - 1][yPos] = tempBlock;

								tempBlock = myBoard[xPos][yPos + 1];
								myBoard[xPos][yPos + 1] = myBoard[xPos - 1][yPos + 1];
								myBoard[xPos - 1][yPos + 1] = tempBlock;

								tempBlock = myBoard[xPos + 1][yPos];
								myBoard[xPos + 1][yPos] = myBoard[xPos][yPos];
								myBoard[xPos][yPos] = tempBlock;

								tempBlock = myBoard[xPos + 1][yPos + 1];
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
							tempBlock = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = myBoard[xPos][yPos - 1];
							myBoard[xPos][yPos - 1] = tempBlock;
						}
						break;
					case 'E': // JK horizontal block
						// Check if move is legal
						if (myBoard[xPos][yPos - 1].getName() == ' ') {
								// swap
								tempBlock = myBoard[xPos][yPos - 1];
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
							tempBlock = myBoard[xPos][yPos - 1];
							myBoard[xPos][yPos - 1] = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = tempBlock;

							tempBlock= myBoard[xPos + 1][yPos - 1];
							myBoard[xPos + 1][yPos - 1] = myBoard[xPos + 1][yPos];
							myBoard[xPos + 1][yPos] = tempBlock;
						}
						break;
					case 'B': // BC/FG
						// Check if move is legal
						if (myBoard[xPos][yPos - 1].getName() == ' ' &&
							myBoard[xPos + 1][yPos - 1].getName() == ' ') {
								// swap
								tempBlock = myBoard[xPos][yPos - 1];
								myBoard[xPos][yPos - 1] = myBoard[xPos][yPos];
								myBoard[xPos][yPos] = tempBlock;

								tempBlock = myBoard[xPos + 1][yPos - 1];
								myBoard[xPos + 1][yPos - 1] = myBoard[xPos + 1][yPos];
								myBoard[xPos + 1][yPos] = tempBlock;

								tempBlock = myBoard[xPos][yPos];
								myBoard[xPos][yPos] = myBoard[xPos][yPos + 1];
								myBoard[xPos][yPos + 1] = tempBlock;

								tempBlock = myBoard[xPos + 1][yPos];
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
							tempBlock = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = myBoard[xPos + 1][yPos];
							myBoard[xPos + 1][yPos] = tempBlock;
						}
						break;
					case 'E': // JK horizontal block
						// Check if move is legal
						if (myBoard[xPos + 1][yPos].getName() == ' ' &&
							myBoard[xPos + 1][yPos + 1].getName() == ' ') {
								// swap
								tempBlock = myBoard[xPos][yPos];
								myBoard[xPos][yPos] = myBoard[xPos + 1][yPos];
								myBoard[xPos + 1][yPos] = tempBlock;

								tempBlock = myBoard[xPos][yPos + 1];
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
							tempBlock = myBoard[xPos + 2][yPos];
							myBoard[xPos + 2][yPos] = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = tempBlock;

							tempBlock = myBoard[xPos + 1][yPos];
							myBoard[xPos + 1][yPos] = myBoard[xPos + 2][yPos];
							myBoard[xPos + 2][yPos] = tempBlock;
						}
						break;
					case 'B': // BC/FG
						// Check if move is legal
						if (myBoard[xPos + 2][yPos].getName() == ' ' &&
							myBoard[xPos + 2][yPos + 1].getName() == ' ') {
							// swap
							tempBlock = myBoard[xPos + 2][yPos];
							myBoard[xPos + 2][yPos] = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = tempBlock;

							tempBlock = myBoard[xPos + 2][yPos + 1];
							myBoard[xPos + 2][yPos + 1] = myBoard[xPos][yPos + 1];
							myBoard[xPos][yPos + 1] = tempBlock;

							tempBlock = myBoard[xPos + 2][yPos];
							myBoard[xPos + 2][yPos] = myBoard[xPos + 1][yPos];
							myBoard[xPos + 1][yPos] = tempBlock;

							tempBlock = myBoard[xPos + 2][yPos + 1];
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
							tempBlock = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = myBoard[xPos][yPos + 1];
							myBoard[xPos][yPos + 1] = tempBlock;
						}
						break;
					case 'E': // JK horizontal block
						// Check if move is legal
						if (myBoard[xPos][yPos + 2].getName() == ' ') {
								// swap
								tempBlock = myBoard[xPos][yPos];
								myBoard[xPos][yPos] = myBoard[xPos][yPos + 2];
								myBoard[xPos][yPos + 2] = tempBlock;

								tempBlock = myBoard[xPos][yPos + 1];
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
							tempBlock = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = myBoard[xPos][yPos + 1];
							myBoard[xPos][yPos + 1] = tempBlock;

							tempBlock = myBoard[xPos + 1][yPos];
							myBoard[xPos + 1][yPos] = myBoard[xPos + 1][yPos + 1];
							myBoard[xPos + 1][yPos + 1] = tempBlock;
						}
						break;
					case 'B': // BC/FG
						// Check if move is legal
						if (myBoard[xPos][yPos + 2].getName() == ' ' &&
							myBoard[xPos + 1][yPos + 2].getName() == ' ') {
							// swap
							tempBlock = myBoard[xPos][yPos];
							myBoard[xPos][yPos] = myBoard[xPos][yPos + 2];
							myBoard[xPos][yPos + 2] = tempBlock;

							tempBlock = myBoard[xPos + 1][yPos];
							myBoard[xPos + 1][yPos] = myBoard[xPos + 1][yPos + 2];
							myBoard[xPos + 1][yPos + 2] = tempBlock;

							tempBlock = myBoard[xPos][yPos + 1];
							myBoard[xPos][yPos + 1] = myBoard[xPos][yPos + 2];
							myBoard[xPos][yPos + 2] = tempBlock;

							tempBlock = myBoard[xPos + 1][yPos + 1];
							myBoard[xPos + 1][yPos + 1] = myBoard[xPos + 1][yPos + 2];
							myBoard[xPos + 1][yPos + 2] = tempBlock;
						}
						break;
				}
				break;
			default:
				break;
		} // End of puzzle code block
	}
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
/* COMMENT
Credits:
Image of gems (Original file name: gems2.png crc32: 6DF21FAC) by: Ville Seppanen

TODO:
- Fix Klotski (Not Responding) due to the game loop running indefinitely while waiting for input
- Fix output position of the board in the window (minor issue)
- Take events inside of the window instead of in console
- Use mouse cursor position and mouse click and release events to drag tiles
- Add animation to pieces sliding in the window
- Remove console window and all console output from within the source code
- Add buttons to the game for setting board back to initial state (reset)
- Add move counter and display
- Change image size references to variables with the number stored inside
- Add win state with congratulations picture
- Add sound to tiles after a tile is moved
*/

/* OUTPUT FROM CONSOLE












                                    AABBBBCC
                                    AABBBBCC
                                    AABBBBCC
                                    AABBBBCC
                                    DDEEEEFF
                                    DDEEEEFF
                                    DDGGHHFF
                                    DDGGHHFF
                                    II    JJ
                                    II    JJ

W = Up, S = Down, A = Left, D = Right (Q to quit)
Enter direction:
*/


