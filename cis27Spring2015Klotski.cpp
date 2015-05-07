/**
 * Program Name: cis27Spring2015Klotski.c
 * Discussion:   
 * Written By:   xxxxxxxxxxxx
 * Date:         2015/05/07
 */

#include <iostream>
#include "Block.h" // Class header file for block objects

using namespace std;

int main() {
  // Declare and define constant variables to store a 2D array
  // that has a border around where the blocks will be
  // This block of code is for 2x2 blocks only
	const int rows = 6;
	const int cols = 5;
	char** fillAry; // Declare a double pointer variable to store 2D matrix

	Block myBoard[rows][cols];

	Block block1('E');
	Block block2('R');
	Block block3('T');
	Block block4('Y');
	Block block5('U');
	Block block6('I');
	Block block7('L');
	Block block8('P');
	Block block9('F');
	Block block10('G');
	Block block11('H');
	Block block12('J');
	Block block13('K');
	Block block14('M');
	Block block15('N');
	Block block16('O');
	Block block17('Q');
	Block block18('Z');

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
	
	// Display the Block contained at [1][1] in the myBoard array
	fillAry = myBoard[1][1].getArray();
	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << fillAry[i][j];
		}
		cout << endl;
	}
	/*
	// This commented out block of code is for blocks of
	// sizes 2x4, 2x2, and 4x4.  There also is two 2x2
	// blocks of NULL character (default constructor).
	
	// Create block pieces (objects)
	Block myBlock1('E', 2, 4);
	Block myBlock2('T', 2, 4);
	Block myBlock3('Y', 2, 4);
	Block myBlock4('I', 2, 4);
	Block myBlock5('F');
	Block myBlock6('G');
	Block myBlock7('L');
	Block myBlock8('P');
	Block myBlock9('U', 4, 2);
	Block myBlock10('R', 4, 4);
	Block myBlockNULL1();
	Block myBlockNULL2();
	// Display all of the block pieces (objects)
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
