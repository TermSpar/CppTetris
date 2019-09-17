#include "Lblock.h"

Lblock::Lblock() {
	L1.setFillColor(sf::Color::Magenta);
	L1.setSize({ 20, 70 });
	L2.setFillColor(sf::Color::Magenta);
	L2.setSize({ 30, 20 });
}

void Lblock::drawTo(sf::RenderWindow &window) {
	window.draw(L1);
	window.draw(L2);
}

void Lblock::move(sf::Vector2f dist) {
	L1.move(dist); L2.move(dist);
}

void Lblock::changeUp() {
	if (!hasChanged) {
		if (appearance == 1) {
			// turn L on its side:
			L1.setSize({ 70, 20 });
			L2.setSize({ 20, 30 });
			L2.setPosition({ L1.getPosition().x + 50, L1.getPosition().y - 30 });
			appearance++;
			hasChanged = true;
		}
		else if (appearance == 2) {
			// turn L upsidedown:
			L1.setSize({ 70, 20 });
			L2.setSize({ 20, 30 });
			L2.setPosition({ L1.getPosition().x + 50, L1.getPosition().y + 20 });
			appearance++;
			hasChanged = true;
		}
		else if (appearance == 3) {
			// turn L back to original position and reset appearance:
			L1.setSize({ 20, 70 });
			L2.setSize({ 30, 20 });
			L2.setPosition({ L1.getPosition().x + 20, L1.getPosition().y + 50 });
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

bool Lblock::intersects(sf::FloatRect globalBounds) {
	// check if either part of the L block is intersecting:
	if (L1.getGlobalBounds().intersects(globalBounds) || L2.getGlobalBounds().intersects(globalBounds))
		return true;
	else
		return false;
}

bool Lblock::intersects(Block &block) {
	if (block.intersects(L1.getGlobalBounds()) || block.intersects(L2.getGlobalBounds()))
		return true;
	else
		return false;
}

void Lblock::setPosition(sf::Vector2f pos) {
	// make sure L block stays together as one thing:
	L1.setPosition(pos);
	L2.setPosition({ pos.x + 20, pos.y + 50 });
}

Lblock::~Lblock() {
}
