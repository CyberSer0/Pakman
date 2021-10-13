#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:
	// Variables
	sf::Texture texture;
	sf::Sprite sprite;

	// Private functions
	void initVariables();
public:
	// De-/Constructors
	Player();
	virtual ~Player();

	// Functions
	void update();
	void render();
};

