#include "Block.h"

Block::Block(std::string nameOfBlock) {
	if (nameOfBlock == "Tblock") {
		blockImage.loadFromFile("resources/Tblock.png");
	}
	else if (nameOfBlock == "Lblock") {
		blockImage.loadFromFile("resources/Lblock.png");
	}
	else if (nameOfBlock == "Sblock") {
		blockImage.loadFromFile("resources/Sblock.png");
	}
	else if (nameOfBlock == "SQblock") {
		blockImage.loadFromFile("resources/SQblock.png");
	}
	else if (nameOfBlock == "Zblock") {
		blockImage.loadFromFile("resources/Zblock.png");
	}
}

void Block::drawTo(sf::RenderWindow &window) {
	window.draw(blockSprite);
}

void Block::move(sf::Vector2f dist) {
	blockSprite.move(dist);
}

void Block::setTexture(std::string texture) {
	blockTexture.loadFromFile(texture);
	blockSprite.setTexture(blockTexture);
}

void Block::changeUp() {
	if (!hasChanged) {
		if (appearance == 1) {
			// turn on its side:
			blockSprite.setTextureRect(sf::IntRect(blockSprite.getLocalBounds().width, 0, -blockSprite.getLocalBounds().width, 
				blockSprite.getLocalBounds().height));
			// flip image as well
			blockImage.flipHorizontally();
			appearance++;
			hasChanged = true;
		}
		else if (appearance == 2) {
			// turn upsidedown:
			blockSprite.setTextureRect(sf::IntRect(0, blockSprite.getLocalBounds().height, blockSprite.getLocalBounds().width,
				-blockSprite.getLocalBounds().height));
			// flip image as well
			blockImage.flipVertically();
			appearance++;
			hasChanged = true;
		}
		else if (appearance == 3) {
			// turn back to original position and reset appearance:
			blockSprite.setTextureRect(sf::IntRect(0, 0, blockSprite.getLocalBounds().width, blockSprite.getLocalBounds().height));
			blockImage.flipHorizontally();
			blockImage.flipVertically();
			appearance = 1;
			hasChanged = true;
		}
	}
}

void Block::setHasChanged(bool change) {
	hasChanged = change;
}

void Block::setFallen(bool ToF) {
	hasFallen = ToF;
}

bool Block::getHasFallen() {
	return hasFallen;
}

bool Block::intersects(sf::FloatRect bounds) {
	if (blockSprite.getGlobalBounds().intersects(bounds)) {
		return true;
	}
	return false;
}

// FToIRect and PixelPerfectCollision functuions from https://gist.github.com/ernestoalejo/3033095:

inline sf::IntRect Block::FToIRect(const sf::FloatRect& f) {
	return sf::IntRect((int)f.left, (int)f.top, (int)f.width, (int)f.height);
}

bool Block::PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b,
	const sf::Image& imgA, const sf::Image& imgB) {
	sf::IntRect boundsA(FToIRect(a.getGlobalBounds()));
	sf::IntRect boundsB(FToIRect(b.getGlobalBounds()));
	sf::IntRect intersection;

	if (boundsA.intersects(boundsB, intersection)) {
		const sf::Transform& inverseA(a.getInverseTransform());
		const sf::Transform& inverseB(b.getInverseTransform());

		const sf::Vector2u& sizeA(imgA.getSize());
		const sf::Vector2u& sizeB(imgB.getSize());

		const sf::Uint8* pixA = imgA.getPixelsPtr();
		const sf::Uint8* pixB = imgB.getPixelsPtr();

		sf::Vector2f vecA, vecB;
		int xMax = intersection.left + intersection.width;
		int yMax = intersection.top + intersection.height;

		for (int x = intersection.left; x < xMax; x++)
			for (int y = intersection.top; y < yMax; y++) {
				vecA = inverseA.transformPoint(x, y);
				vecB = inverseB.transformPoint(x, y);

				int idxA = ((int)vecA.x + ((int)vecA.y)*sizeA.x) * 4 + 3;
				int idxB = ((int)vecB.x + ((int)vecB.y)*sizeB.x) * 4 + 3;

				if (vecA.x > 0 && vecA.y > 0 &&
					vecB.x > 0 && vecB.y > 0 &&
					vecA.x < sizeA.x && vecA.y < sizeA.y &&
					vecB.x < sizeB.x && vecB.y < sizeB.y &&
					pixA[idxA] > 0 &&
					pixB[idxB] > 0) {
					return true;
				}
			}
	}

	return false;
}

sf::Sprite Block::getSprite() {
	return blockSprite;
}

sf::Image Block::getImage() {
	return blockImage;
}

void Block::setPosition(sf::Vector2f pos) {
	// make sure block stays together as one thing:
	blockSprite.setPosition(pos);
}

Block::~Block() {
}
