/**
 * Program Name: cis27Spring2015Klotski.c
 * Discussion:   
 * Written By:   Dennis Stith
 * Date:         2015/05/18
 *
 * Setup:
 * Make sure the folder containing the executable has the following
 * dynamic link library files included or that they are in the system
 * path:
 *
 * msvcp110d.dll
 * msvcr110d.dll
 * openal32.dll
 * sfml-audio-2.dll
 * sfml-audio-d-2.dll
 * sfml-graphics-2.dll
 * sfml-graphics-d-2.dll
 * sfml-network-2.dll
 * sfml-network-d-2.dll
 * sfml-system-2.dll
 * sfml-system-d.dll
 * sfml-window-2.dll
 * sfml-window-d-2.dll
 *
 * Run cis27Spring2015DennisStithKlotskiWin32.exe
 * Graphics and keyboard commands will be displayed.
 *
 * Instructions:
 * Use arrow keys Arrow Up, Arrow Down, Arrow Left, and Arrow Right
 * to input the movement.  Use keyboard qwerty keys A-J for the
 * block to move.  After both inputs are read in any order
 * (either direction then block or block then direction), the 
 * block with the name corresponding to the key pressed will
 * move.
 */

#include <SFML/Graphics.hpp> // For shapes
#include <SFML/Graphics/Image.hpp> // For image files
#include <iostream>
#include <string>
#include "Block.h"

using namespace std;

// Function prototypes
void searchAryDS(char, Block**, int, int, int*, int*);
void runBoardGameDS(void);

int main() {
	runBoardGameDS();
	return 0;
}

// Function that runs the game
void runBoardGameDS() {
	sf::RenderWindow window(sf::VideoMode(820, 640), "Klotski");
	sf::Texture bgTexture;
	sf::Texture mvTexture;
	sf::Sprite bgImage;
	sf::Sprite mvImage;
	sf::Sprite boardDisp[10][8];
	sf::Font mvFont;
	sf::Text uText;
	sf::Text dText;
	sf::Text lText;
	sf::Text rText;
	sf::Text controlText;
	string uString;
	string dString;
	string lString;
	string rString;
	string control; // Declare string variable to store text of blocks to move
	const float sprScale = 0.5;
	const int sprSize = 128;
	char blockToMove = NULL;
	char moveDirection = NULL;
	int xPos = NULL; // Position of the block found after search
	int yPos = NULL;
	const int rows = 7; // Size of the board that contains the objects
	const int cols = 6;

	uString = "  Move With\nArrow Keys\n\t\tUp";
	dString = "Down";
	lString = "Left";
	rString = "Right";
	control = "\t\tSelect Block" \
		"\n\t\t\tWith Keys" \
		"\nPurple Square = A" \
		"\nGreen Circle = B" \
		"\nPink Gem = C" \
		"\nBlack Square = D" \
		"\nPurple Gem = E" \
		"\nLight Blue Gem = F" \
		"\nTriangle = G" \
		"\nBlue Spikey = H" \
		"\nOrange Gem = I" \
		"\nStar = J";

	if (!bgTexture.loadFromFile("background.jpg")) {
		cout << "Error could not load background image.";
	}

	if (!mvTexture.loadFromFile("gems.png")) {
		cout << "Error could not load moves image.";
	}

	if (!mvFont.loadFromFile("COOPBL.TTF")) {
		cout << "Error could not load font.";
	}
	
 	bgImage.setTexture(bgTexture); // Set background display image texture

	mvImage.setTexture(mvTexture); // Set moves display image texture
	mvImage.setTextureRect(sf::IntRect(sprSize * 2, sprSize * 2, sprSize, sprSize));
	mvImage.setPosition(sprSize * 4.5, sprSize * 3);
	
	// Set control and movement display text
	controlText.setString(control);
	controlText.setFont(mvFont);
	controlText.setCharacterSize(20);
	controlText.setColor(sf::Color(255, 255, 255));
	controlText.setPosition(sprSize * 4.2f, static_cast<float>(sprSize));
	controlText.setPosition(sprSize * 4.2f, 0);
	
	uText.setString(uString);
	uText.setFont(mvFont);
	uText.setCharacterSize(20);
	uText.setColor(sf::Color(255, 255, 255));
	uText.setPosition(sprSize * 4.55f, sprSize * 2.7f);

	uText.setString(uString);
	uText.setFont(mvFont);
	uText.setCharacterSize(20);
	uText.setColor(sf::Color(255, 255, 255));
	uText.setPosition(sprSize * 4.55f, sprSize * 2.5f);
	
	dText.setString(dString);
	dText.setFont(mvFont);
	dText.setCharacterSize(20);
	uText.setColor(sf::Color(255, 255, 255));
	dText.setPosition(sprSize * 4.73f, sprSize * 3.9f);

	lText.setString(lString);
	lText.setFont(mvFont);
	lText.setCharacterSize(20);
	lText.setColor(sf::Color(255, 255, 255));
	lText.setPosition(sprSize * 4.2f, sprSize * 3.4f);

	rText.setString(rString);
	rText.setFont(mvFont);
	rText.setCharacterSize(20);
	rText.setColor(sf::Color(255, 255, 255));
	rText.setPosition(sprSize * 5.45f, sprSize * 3.4f);

	// Dynamically allocate memory to board containing objects
	Block **myBoard = new Block *[rows]; 
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
	
	// Run game loop
	while (window.isOpen()) { 
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				// Get keyboard event and store its corresponding key into the moveDirection
				// and blockToMove for the block movement swith case
				case sf::Event::KeyPressed:
					switch (event.key.code) {
						case sf::Keyboard::Up:
							moveDirection = 'W';
							break;
						case sf::Keyboard::Down:
							moveDirection = 'S';
							break;
						case sf::Keyboard::Left:
							moveDirection = 'A';
							break;
						case sf::Keyboard::Right:
							moveDirection = 'D';
							break;
						case sf::Keyboard::A:
							blockToMove = 'A';
							break;
						case sf::Keyboard::B:
							blockToMove = 'B';
							break;
						case sf::Keyboard::C:
							blockToMove = 'C';
							break;
						case sf::Keyboard::D:
							blockToMove = 'D';
							break;
						case sf::Keyboard::E:
							blockToMove = 'E';
							break;
						case sf::Keyboard::F:
							blockToMove = 'F';
							break;
						case sf::Keyboard::G:
							blockToMove = 'G';
							break;
						case sf::Keyboard::H:
							blockToMove = 'H';
							break;
						case sf::Keyboard::I:
							blockToMove = 'I';
							break;
						case sf::Keyboard::J:
							blockToMove = 'J';
							break;
						default:
							break;
					}
			}
		}
        
		// Begin puzzle code block
		for (int i = 0; i < 2; i++) { // Assign sprites to the board to output to window
			for (int j = 0; j < 2; j++) {
				boardDisp[i][j] = myBoard[1][1].getSprite();
				boardDisp[i][j + 2] = myBoard[1][2].getSprite();
				boardDisp[i][j + 4] = myBoard[1][3].getSprite();
				boardDisp[i][j + 6] = myBoard[1][4].getSprite();

				boardDisp[i + 2][j] = myBoard[2][1].getSprite();
				boardDisp[i + 2][j + 2] = myBoard[2][2].getSprite();
				boardDisp[i + 2][j + 4] = myBoard[2][3].getSprite();
				boardDisp[i + 2][j + 6] = myBoard[2][4].getSprite();

				boardDisp[i + 4][j] = myBoard[3][1].getSprite();
				boardDisp[i + 4][j + 2] = myBoard[3][2].getSprite();
				boardDisp[i + 4][j + 4] = myBoard[3][3].getSprite();
				boardDisp[i + 4][j + 6] = myBoard[3][4].getSprite();

				boardDisp[i + 6][j] = myBoard[4][1].getSprite();
				boardDisp[i + 6][j + 2] = myBoard[4][2].getSprite();
				boardDisp[i + 6][j + 4] = myBoard[4][3].getSprite();
				boardDisp[i + 6][j + 6] = myBoard[4][4].getSprite();

				boardDisp[i + 8][j] = myBoard[5][1].getSprite();
				boardDisp[i + 8][j + 2] = myBoard[5][2].getSprite();
				boardDisp[i + 8][j + 4] = myBoard[5][3].getSprite();
				boardDisp[i + 8][j + 6] = myBoard[5][4].getSprite();
			}
		}
			
		window.draw(bgImage); // Display the background image

		// Draw all blocks in the board to the window
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 8; j++) { 
				boardDisp[i][j].setPosition(j * sprSize * sprScale, i * sprSize * sprScale);
				window.draw(boardDisp[i][j]);
			}
		}

		// Draw controls
		window.draw(controlText);
		window.draw(mvImage);
		window.draw(uText);
		window.draw(dText);
		window.draw(lText);
		window.draw(rText);

		// Display the graphics to the window
		window.display();
		window.clear();
			
		// Search the board for the block and store xPos and yPos
		searchAryDS(blockToMove, myBoard, rows, cols, &xPos, &yPos);

		// Movement logic.  This uses the moveDirection and blockToMove stored 
		// from keyboard events earlier in the program game loop
		if (moveDirection && blockToMove) {
			switch (toupper(moveDirection)) {
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

			// Clear the moveDirection and blockToMove
			moveDirection = NULL;
			blockToMove = NULL;

			window.draw(bgImage); // Display the background image

			// Draw all of the board pieces to the window
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 8; j++) {
					boardDisp[i][j].setPosition(j * sprSize * sprScale, i * sprSize * sprScale);
					window.draw(boardDisp[i][j]);
				}
			}

			// Draw controls
			window.draw(controlText);
			window.draw(mvImage);
			window.draw(uText);
			window.draw(dText);
			window.draw(lText);
			window.draw(rText);

			// Display graphics to window
			window.display();
			window.clear();
		} // End of if statement for inputs
	} // End of game loop
}

// Function for searching the game board array for the position of the block to move and passes
// by reference the *xPos and *yPos values back to the function that called it.
void searchAryDS(char blockToMove, Block** boardAry, int rows, int cols, int *xPos, int *yPos) {
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
- Make this program work in Release mode (right now it only compiles in Debug mode
- Add blocks to the moves list instead of text if still using keys for input
- Highlight block that is being moved for keyboard if still suing keys for input
- Use mouse cursor position and mouse click and release events to drag tiles
- Add animation to pieces sliding in the window
- Add buttons to the game for setting board back to initial state (reset)
- Add move counter and display
- Add win state with congratulations picture
- Add sound to tiles after a tile is moved
*/

/* OUTPUT
No console output.
*/


