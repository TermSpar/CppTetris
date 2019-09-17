#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

#include "Tblock.h"
#include "Lblock.h"

class Game {
public:
	Game();

	Game(sf::Vector2f);

	// return block vector:
	std::vector<Block*>* getBlocks();

	// main game logic:
	void start();

	void drawTo(sf::RenderWindow &w);

	~Game();

private:
	sf::RectangleShape ground;

	// keep track of block vector:
	std::vector<Block*> blockVec;
	int currentBlock = 0;

	// check if it's the first loop:
	bool gameHasStarted = false;

	// check if current block has been created:
	bool isCreated = false;

	// generate random block:
	void addRandomBlock();

	// when block has fallen:
	void blockIsFallen();

	// block move speed:
	float blockSpeed = 0.1;
};

