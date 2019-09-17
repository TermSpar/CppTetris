#pragma once

// parent class:

#include <SFML\Graphics.hpp>
#include <iostream>

class Block {
public:
	Block() {}

	virtual void drawTo(sf::RenderWindow &w) {}

	virtual void move(sf::Vector2f) {}

	virtual void setTexture(std::string) {}

	virtual std::string getBlockName() { return ""; }

	virtual void changeUp() {}

	virtual void setHasChanged(bool) {}

	virtual bool PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b,
		const sf::Image& imgA, const sf::Image& imgB) {return false;}

	virtual inline sf::IntRect FToIRect(const sf::FloatRect& f) { sf::IntRect i; return i; }

	virtual sf::Sprite getSprite() { sf::Sprite s; return s; }

	virtual sf::Image getImage() { sf::Image i; return i; }

	virtual bool intersects(sf::FloatRect) { return false; }

	virtual void setFallen(bool) {}

	virtual bool getHasFallen() { return false; }

	virtual void setPosition(sf::Vector2f) {}

	~Block() {}
};

