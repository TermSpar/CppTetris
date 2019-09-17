#pragma once

#include "Block.h"

class Lblock : public Block {
public:
	Lblock();

	virtual void drawTo(sf::RenderWindow &w);

	virtual void move(sf::Vector2f);

	// change L:
	virtual void changeUp();

	virtual void setHasChanged(bool);

	// check if this block has reached the ground:
	virtual void setFallen(bool);

	virtual bool getHasFallen();

	virtual bool intersects(sf::FloatRect);

	virtual bool intersects(Block &b);

	virtual void setPosition(sf::Vector2f);

	~Lblock();

private:
	// T shape:
	sf::RectangleShape L1; sf::RectangleShape L2;

	// keep track of which appearance L's on:
	int appearance = 1;
	bool hasChanged = false;

	// whether the block has reached ground:
	bool hasFallen = false;
};

