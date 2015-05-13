/**
 * Block implementation file
 */
#include "Block.h"

Block::Block() { // Default constructor
	fillChar = NULL;
	sprScale = 0.5;
	if (!blockTexture.loadFromFile("gems.png")) {
		exit(1);
	}
	fillSprite.setTexture(blockTexture);
	fillSprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
	fillSprite.setScale(sprScale, sprScale);
	name = NULL;
}

Block::Block(char fillChar, char name, float scale) {
	this->fillChar = fillChar;
	sprScale = scale;
	if (!blockTexture.loadFromFile("gems.png")) {
		exit(1);
	}
	fillSprite.setTexture(blockTexture);
	fillSprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
	fillSprite.setScale(sprScale, sprScale);
	this->name = name;
}

Block::Block(char fillChar, char name, int imgX, int imgY, int imgWidth, int imgHeight, float scale) {
	this->fillChar = fillChar;
	sprScale = scale;
	if (!blockTexture.loadFromFile("gems.png")) {
		exit(1);
	}
	fillSprite.setTexture(blockTexture);
	fillSprite.setTextureRect(sf::IntRect(imgX, imgY, imgWidth, imgHeight));
	fillSprite.setScale(sprScale, sprScale);
	this->name = name;
}

Block::Block(const Block &obj) { // Copy constructor
	ptr = new int;
	*ptr = *obj.ptr;
}

Block::~Block() {
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

sf::Sprite Block::getSprite() {
	return fillSprite;
}

char Block::getName() {
	return name;
}
