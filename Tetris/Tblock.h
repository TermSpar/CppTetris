#pragma once

#include "Block.h"

class Tblock : public Block {
public:
	Tblock();

	virtual void drawTo(sf::RenderWindow &w);

	virtual void move(sf::Vector2f);

	// change T:
	virtual void changeUp();

	virtual void setHasChanged(bool);

	// check if this block has reached the ground:
	virtual void setFallen(bool);

	virtual bool getHasFallen();

	virtual bool intersects(sf::FloatRect);

	virtual bool intersects(Block &b);

	virtual void setPosition(sf::Vector2f);

	~Tblock();

private:
	// T shape:
	sf::RectangleShape T1; sf::RectangleShape T2;
	
	// keep track of which appearance T's on:
	int appearance = 1;
	bool hasChanged = false;

	// whether the block has reached ground:
	bool hasFallen = false;
};

