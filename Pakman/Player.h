#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player
{
private:
	// Variables
	sf::Texture texture;
	sf::Sprite sprite;
	float scaleX;
	float scaleY;
	sf::FloatRect collisionBox;

	float movementSpeed;

	// Private functions
	void initVariables();
	void initTexture();
	void initSprite(int startTileX, int startTileY);

public:
	// De-/Constructors
	Player(int startTileX, int startTileY);
	virtual ~Player();

	// Variables
	int tileX;
	int tileY;

	// Functions
	void move(const float dirX, const float dirY);

	void update();
	void render(sf::RenderTarget& targetWindow);
};

