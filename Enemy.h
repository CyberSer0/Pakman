#pragma once

#include "Entity.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Enemy : public Entity
{
private:
	// Variables
	float movementSpeed; // Creating a movement speed variable
	sf::Vector2f velocity;
	sf::Texture textureLeft;
	sf::Texture textureRight;

	// Private functions
	void initVariables(); // Function to initialize and set values to all Variables
public:
	// De-/Constructor
	Enemy();
	Enemy(sf::Vector2u startTile);

	// Variables
	sf::Vector2i currentTile; // Vector of current Tile X and current Tile Y of the Entity

	// Functions
	void move(const float dirX, const float dirY); // Function to move the player object/sprite

	void update(); // Function to update variables and logic
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Function to update graphic variables and functionality
};

