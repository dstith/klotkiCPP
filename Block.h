/**
 * Block header file
 */
#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp> // For shapes
#include <SFML/Graphics/Image.hpp> // For image files
#include <iostream>
using namespace std;

// Block class definition
class Block {
	private:
		char fillChar;
		sf::Texture blockTexture;
		sf::Sprite fillSprite;
		float sprScale;
		char name;
		int *ptr;
	public:
		Block();
		Block(char, char, float);
		Block(char, char, int, int, int, int, float);
		Block(const Block &); // Copy constructor
		~Block();
		void setFill(char);
		void setName(char);
		char getFill();
		sf::Sprite getSprite();
		char getName();
		void printBlock();
}; // End of Block class

#endif
