// Tetris by Ben Bollinger

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Block.h"
#include "Tblock.h"
#include "Lblock.h"

#include "Game.h"

int main() {
	sf::RenderWindow window;

	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

	window.create(sf::VideoMode(900, 900), "C++ Tetris", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);

	// main game:
	Game game;

	float moveSpeed = 0.1;
	
	//Main Loop:
	while (window.isOpen()) {

		sf::Event Event;

		// key events:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			// change currently falling block:
			for (int i = 0; i < game.getBlocks()->size(); i++) {
				Block *current = game.getBlocks()->at(i);
				if (!current->getHasFallen()) {
					current->changeUp();
				}
			}
		} 
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			// move currently falling block right:
			for (int i = 0; i < game.getBlocks()->size(); i++) {
				Block *current = game.getBlocks()->at(i);
				if (!current->getHasFallen()) {
					current->move({ moveSpeed, 0 });
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			// move currently falling block left:
			for (int i = 0; i < game.getBlocks()->size(); i++) {
				Block *current = game.getBlocks()->at(i);
				if (!current->getHasFallen()) {
					current->move({ -moveSpeed, 0 });
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			// placeholder
		}

		//Event Loop:
		while (window.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				window.close();
			case sf::Event::KeyReleased:
				if (Event.key.code == sf::Keyboard::Up) {
					// only change the currently falling block:
					for (int i = 0; i < game.getBlocks()->size(); i++) {
						Block *current = game.getBlocks()->at(i);
						if (!current->getHasFallen()) {
							current->setHasChanged(false);
						}
					}
				}
			}
		}
		// start game:
		game.start();

		// draw things:
		window.clear();
		game.drawTo(window);
		window.display();
	}
}