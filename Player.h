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
	sf::Texture textureLeft;
	sf::Texture textureRight;
	sf::Texture textureDown;
	sf::Texture textureUp;

	// Private functions
	void initVariables(); // Function to initialize and set values to all Variables
public:
	// De-/Constructor
	Player(const std::string& textureName, int startTileX, int startTileY);

	// Variables
	sf::Vector2i currentTile; // Vector of current Tile X and current Tile Y of the Entity

	// Functions
	void move(const float dirX, const float dirY); // Function to move the player object/sprite

	void update(); // Function to update variables and logic
	void render(sf::RenderTarget& targetWindow); // Function to update graphic variables and functionality
};

