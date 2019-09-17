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
				// set right texture:
				if (nameOfBlock == "Tblock") {
					blockVec[currentBlock]->setTexture("resources/Tblock.png");
				}
				else if (nameOfBlock == "Lblock") {
					blockVec[currentBlock]->setTexture("resources/Lblock.png");
				}
				else if (nameOfBlock == "Sblock") {
					blockVec[currentBlock]->setTexture("resources/Sblock.png");
				}
				else if (nameOfBlock == "SQblock") {
					blockVec[currentBlock]->setTexture("resources/SQblock.png");
				}
				else if (nameOfBlock == "Zblock") {
					blockVec[currentBlock]->setTexture("resources/Zblock.png");
				}
				isCreated = true;
			}

			// make block fall until ground or another block:
			for (int i = 0; i < blockVec.size(); i++) {
				// check if block hits another block:
				if (i != currentBlock) {
					for (int j = 0; j < blockVec.size(); j++) {
						// so the current block doesn't collide with itself:
						if (j != currentBlock) {
							// if another block is hit:
							if (blockVec[i]->PixelPerfectCollision(blockVec[currentBlock]->getSprite(), blockVec[j]->getSprite(),
								blockVec[currentBlock]->getImage(), blockVec[j]->getImage())) {
								// stop falling:
								blockIsFallen();
							}
						}
					}
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
	int rndBlock = rand() % 5 + 1;

	// make Tblock:
	if (rndBlock == 1) {
		// add new Tblock:
		nameOfBlock = "Tblock";
		blockVec.push_back(new Block("Tblock"));
	}
	else if (rndBlock == 2) {
		// add new Lblock:
		nameOfBlock = "Lblock";
		blockVec.push_back(new Block("Lblock"));
	}
	else if (rndBlock == 3) {
		// add new Sblock:
		nameOfBlock = "Sblock";
		blockVec.push_back(new Block("Sblock"));
	}
	else if (rndBlock == 4) {
		// add new SQblock:
		nameOfBlock = "SQblock";
		blockVec.push_back(new Block("SQblock"));
	}
	else if (rndBlock == 5) {
		// add new Zblock:
		nameOfBlock = "Zblock";
		blockVec.push_back(new Block("Zblock"));
	}
}

// call this everytime a block has reached the ground:
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
