#include "Game.h"

Game::Game() {
	ground.setSize({ 900, 50 });
	ground.setFillColor(sf::Color::Blue);
	ground.setPosition({ 0, 850 });
}

Game::Game(sf::Vector2f size) {
	ground.setSize(size);
	ground.setFillColor(sf::Color::Blue);
	ground.setPosition({ 0, 900 - size.y });
}

// return block vector:
std::vector<Block*>* Game::getBlocks() {
	return &blockVec;
}

// main game logic:
void Game::start() {
	// make sure only one block is created at a time:
	if (gameHasStarted) {

		// if current block hasn't reached the ground:
		if (!blockVec[currentBlock]->getHasFallen()) {

			if (!isCreated) {
				// generate random x position:
				float xPos = rand() % 800 + 1;
				blockVec[currentBlock]->setPosition({ xPos, 20 });
				isCreated = true;
			}

			// make block fall until ground or another block:
			for (int i = 0; i < blockVec.size(); i++) {
				// check if block hits another block:
				if (i != currentBlock && blockVec[currentBlock]->intersects(*blockVec[i])) {
					// if another block is hit, stop falling:
					blockIsFallen();
				}
			}
			// check if block hits ground:
			if (!blockVec[currentBlock]->intersects(ground.getGlobalBounds())) {
				blockVec[currentBlock]->move({ 0, blockSpeed });
			}
			else {
				// when ground reached, stop falling:
				blockIsFallen();
			}
		}
	}
	else {
		addRandomBlock();
		gameHasStarted = true;
	}
}

// get random block:
void Game::addRandomBlock() {
	// generate random block num:
	int rndBlock = rand() % 2 + 1;

	// make Tblock:
	if (rndBlock == 1) {
		// add new Tblock:
		blockVec.push_back(new Tblock());
	}
	else if (rndBlock == 2) {
		// add new Lblock:
		blockVec.push_back(new Lblock());
	}
}

void Game::blockIsFallen() {
	// set fallen to true:
	blockVec[currentBlock]->setFallen(true);
	// add random block to vector and move on:
	addRandomBlock();
	currentBlock++;
	isCreated = false;
}

void Game::drawTo(sf::RenderWindow &window) {
	window.draw(ground);

	// draw blocks:
	for (int i = 0; i < blockVec.size(); i++) {
		blockVec[i]->drawTo(window);
	}
}

Game::~Game() {
}
