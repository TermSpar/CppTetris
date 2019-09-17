#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Block {
public:
	Block(std::string);

	void drawTo(sf::RenderWindow &w);

	void move(sf::Vector2f);

	void setTexture(std::string);

	// change L:
	void changeUp();

	void setHasChanged(bool);

	// check if this block has reached the ground:
	void setFallen(bool);

	bool getHasFallen();

	bool intersects(sf::FloatRect bounds);

	bool PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b,
		const sf::Image& imgA, const sf::Image& imgB);

	inline sf::IntRect FToIRect(const sf::FloatRect& f);

	sf::Sprite getSprite();

	sf::Image getImage();

	void setPosition(sf::Vector2f);

	~Block();

private:
	// block stuff:
	sf::Texture blockTexture;
	sf::Sprite blockSprite;
	sf::Image blockImage;

	// keep track of which appearance L's on:
	int appearance = 1;
	bool hasChanged = false;

	// whether the block has reached ground:
	bool hasFallen = false;
};

