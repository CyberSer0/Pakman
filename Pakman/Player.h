#pragma once

#include "Entity.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player : protected Entity
{
private:
	// Variables
	float movementSpeed; // Creating a movement speed variable

	// Private functions
	void initVariables(); // Function to initialize and set values to all Variables
public:
	// De-/Constructor
	Player(const std::string& textureName, int startTileX, int startTileY);

	// Functions
	void move(const float dirX, const float dirY); // Function to move the player object/sprite

	void update(); // Function to update variables and logic
	void render(sf::RenderTarget& targetWindow); // Function to update graphic variables and functionality
};

