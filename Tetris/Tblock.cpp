#include "Tblock.h"

Tblock::Tblock() {
	Timage.loadFromFile("resources/Tblock.png");
}

void Tblock::drawTo(sf::RenderWindow &window) {
	window.draw(Tsprite);
}

void Tblock::move(sf::Vector2f dist) {
	Tsprite.move(dist);
}

void Tblock::setTexture(std::string texture) {
	Ttexture.loadFromFile(texture);
	Tsprite.setTexture(Ttexture);
}

std::string Tblock::getBlockName() {
	return "Tblock";
}

void Tblock::changeUp() {
	if (!hasChanged) {
		if (appearance == 1) {
			// turn T on its side:
			appearance++;
			hasChanged = true;
		}
		else if (appearance == 2) {
			// turn T upsidedown:
			appearance++;
			hasChanged = true;
		}
		else if (appearance == 3) {
			// turn T back to original position and reset appearance:
			appearance = 1;
			hasChanged = true;
		}
	}
}

void Tblock::setHasChanged(bool change) {
	hasChanged = change;
}

void Tblock::setFallen(bool ToF) {
	hasFallen = ToF;
}

bool Tblock::getHasFallen() {
	return hasFallen;
}

bool Tblock::intersects(sf::FloatRect bounds) {
	if (Tsprite.getGlobalBounds().intersects(bounds)) {
		return true;
	}
	return false;
}

inline sf::IntRect Tblock::FToIRect(const sf::FloatRect& f) {
	return sf::IntRect((int)f.left, (int)f.top, (int)f.width, (int)f.height);
}

bool Tblock::PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b,
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

sf::Sprite Tblock::getSprite() {
	return Tsprite;
}

sf::Image Tblock::getImage() {
	return Timage;
}

void Tblock::setPosition(sf::Vector2f pos) {
	// make sure T block stays together as one thing:
	Tsprite.setPosition(pos);
	//T2.setPosition({ pos.x + 23, pos.y - 20 });
}

Tblock::~Tblock() {
}
