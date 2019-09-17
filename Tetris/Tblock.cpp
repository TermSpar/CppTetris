#include "Tblock.h"

Tblock::Tblock() {
	T1.setFillColor(sf::Color::White);
	T1.setSize({ 70, 20 });
	T2.setFillColor(sf::Color::White);
	T2.setSize({ 25, 20 });
}

void Tblock::drawTo(sf::RenderWindow &window) {
	window.draw(T1);
	window.draw(T2);
}

void Tblock::move(sf::Vector2f dist) {
	T1.move(dist); T2.move(dist);
}

void Tblock::changeUp() {
	if (!hasChanged) {
		if (appearance == 1) {
			// turn T on its side:
			T1.setSize({ 20, 70 });
			T2.setSize({ 20, 25 });
			T2.setPosition({ T1.getPosition().x + 20, T1.getPosition().y + 22 });
			appearance++;
			hasChanged = true;
		}
		else if (appearance == 2) {
			// turn T upsidedown:
			T1.setSize({ 70, 20 });
			T2.setSize({ 25, 20 });
			T2.setPosition({ T1.getPosition().x + 23, T1.getPosition().y + 20 });
			appearance++;
			hasChanged = true;
		}
		else if (appearance == 3) {
			// turn T back to original position and reset appearance:
			T2.setPosition({ T1.getPosition().x + 23, T1.getPosition().y - 20 });
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

bool Tblock::intersects(sf::FloatRect globalBounds) {
	// check if either part of the T block is intersecting:
	if (T1.getGlobalBounds().intersects(globalBounds) || T2.getGlobalBounds().intersects(globalBounds))
		return true;
	else
		return false;
}

bool Tblock::intersects(Block &block) {
	if (block.intersects(T1.getGlobalBounds()) || block.intersects(T2.getGlobalBounds()))
		return true;
	else
		return false;
}

void Tblock::setPosition(sf::Vector2f pos) {
	// make sure T block stays together as one thing:
	T1.setPosition(pos);
	T2.setPosition({ pos.x + 23, pos.y - 20 });
}

Tblock::~Tblock() {
}
