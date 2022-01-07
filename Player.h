#pragma once

#include "Entity.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player : public Entity
{
private:
	// Variables
	float movementSpeed; // Creating a movement speed variable
	sf::Vector2f velocity;
	sf::Texture textureLeft;
	sf::Texture textureRight;
	sf::Texture textureDown;
	sf::Texture textureUp;

	// Private functions
	void initVariables(); // Function to initialize and set values to all Variables
public:
	// De-/Constructor
	Player();
	Player(const std::string& textureName, int startTileX, int startTileY);

	// Variables
	sf::Vector2i currentTile; // Vector of current Tile X and current Tile Y of the Entity

	// Functions
	void move(const float dirX, const float dirY); // Function to move the player object/sprite
	sf::Vector2f getPos() const;
	sf::FloatRect getCollisionBox() const;

	void update(); // Function to update variables and logic
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Function to update graphic variables and functionality
};

