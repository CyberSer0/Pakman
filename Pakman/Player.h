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

	float movementSpeed;
	
	// Private functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	// De-/Constructors
	Player();
	virtual ~Player();

	// Functions
	void move(const float dirX, const float dirY);

	void update();
	void render(sf::RenderTarget& targetWindow);
};

