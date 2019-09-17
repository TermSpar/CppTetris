#include "Lblock.h"

Lblock::Lblock() {
	Limage.loadFromFile("resources/Lblock.png");
}

void Lblock::drawTo(sf::RenderWindow &window) {
	window.draw(Lsprite);
}

void Lblock::move(sf::Vector2f dist) {
	Lsprite.move(dist);
}

void Lblock::setTexture(std::string texture) {
	Ltexture.loadFromFile(texture);
	Lsprite.setTexture(Ltexture);
}

std::string Lblock::getBlockName() {
	return "Lblock";
}

void Lblock::changeUp() {
	if (!hasChanged) {
		if (appearance == 1) {
			// turn L on its side:
			appearance++;
			hasChanged = true;
		}
		else if (appearance == 2) {
			// turn L upsidedown:
			appearance++;
			hasChanged = true;
		}
		else if (appearance == 3) {
			// turn L back to original position and reset appearance:
			appearance = 1;
			hasChanged = true;
		}
	}
}

void Lblock::setHasChanged(bool change) {
	hasChanged = change;
}

void Lblock::setFallen(bool ToF) {
	hasFallen = ToF;
}

bool Lblock::getHasFallen() {
	return hasFallen;
}

bool Lblock::intersects(sf::FloatRect bounds) {
	if (Lsprite.getGlobalBounds().intersects(bounds)) {
		return true;
	}
	return false;
}

inline sf::IntRect Lblock::FToIRect(const sf::FloatRect& f) {
	return sf::IntRect((int)f.left, (int)f.top, (int)f.width, (int)f.height);
}

bool Lblock::PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b,
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

sf::Sprite Lblock::getSprite() {
	return Lsprite;
}

sf::Image Lblock::getImage() {
	return Limage;
}

void Lblock::setPosition(sf::Vector2f pos) {
	// make sure L block stays together as one thing:
	Lsprite.setPosition(pos);
}

Lblock::~Lblock() {
}
