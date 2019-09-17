#pragma once

// parent class:

#include <SFML\Graphics.hpp>
#include <iostream>

class Block {
public:
	Block() {}

	virtual void drawTo(sf::RenderWindow &w) {}

	virtual void move(sf::Vector2f) {}

	virtual void changeUp() {}

	virtual void setHasChanged(bool) {}

	virtual bool intersects(sf::FloatRect) {return false;}

	virtual bool intersects(Block &b) { return false; }

	virtual void setFallen(bool) {}

	virtual bool getHasFallen() { return false; }

	virtual void setPosition(sf::Vector2f) {}

	~Block() {}
};

