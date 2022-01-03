#pragma once

#include "Entity.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Enemy : protected Entity
{
private:
	// Variables
	float movementSpeed; // Creating a movement speed variable
	bool playerSeen = false; // Bool of if it has seen player

	// Private functions
	void initVariables(); // Function to initialize and set values to all Variables
public:
	// De-/Constructor
	Enemy(const std::string& textureName, int startTileX, int startTileY);

	// Variables
	sf::Vector2i currentTile; // Vector of current Tile X and current Tile Y of the Entity

	// Functions
	void pathfind();
	void randomWalk();
	void move(const float dirX, const float dirY); // Function to move the enemy object/sprite

	void update(); // Function to update variables and logic
	void render(sf::RenderTarget& targetWindow); // Function to update graphic variables and functionality
};

