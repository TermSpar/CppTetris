#pragma once

#include "Block.h"

class Lblock : public Block {
public:
	Lblock();

	virtual void drawTo(sf::RenderWindow &w);

	virtual void move(sf::Vector2f);

	virtual void setTexture(std::string);

	virtual std::string getBlockName();

	// change L:
	virtual void changeUp();

	virtual void setHasChanged(bool);

	// check if this block has reached the ground:
	virtual void setFallen(bool);

	virtual bool getHasFallen();

	virtual bool intersects(sf::FloatRect bounds);

	virtual bool PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b,
		const sf::Image& imgA, const sf::Image& imgB);

	virtual inline sf::IntRect FToIRect(const sf::FloatRect& f);

	virtual sf::Sprite getSprite();

	virtual sf::Image getImage();

	virtual void setPosition(sf::Vector2f);

	~Lblock();

private:
	// L shape:
	sf::Texture Ltexture;
	sf::Sprite Lsprite;
	sf::Image Limage;

	// keep track of which appearance L's on:
	int appearance = 1;
	bool hasChanged = false;

	// whether the block has reached ground:
	bool hasFallen = false;
};

