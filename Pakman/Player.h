#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player
{
private:
	// Variables
	sf::Texture texture; // Creating a texture object
	sf::Sprite sprite; // Creating a sprite object
	sf::FloatRect collisionBox; // Creating a collisionBox rectangle
	sf::Vector2f scale; // Creating scale vector
	float movementSpeed; // Creating a movement speed variable

	// Private functions
	void initVariables(); // Function to initialize and set values to all Variables
	void initTexture(); // Function to initialize the texture (to use in the sprite)
	void initSprite(int startTileX, int startTileY); // Function to initialize the sprite, arguments are the tile coordinates it should be created at

public:
	/*
	* Constructor - used to initialize all functions at the instatiation of the object
	* Deconstor - deletes objects created in the constructor to prevent memory leaks
	*/
	Player(int startTileX, int startTileY); // Constructor with the possibility to overload the constructor to use in initSprite(startTileX, startTileY)
	virtual ~Player(); // Deconstructor

	// Variables
	int tileX; // Current tile X position the player object is in
	int tileY; // Current tile Y position the plater object is in

	// Functions
	void move(const float dirX, const float dirY); // Function to move the player object/sprite

	void update(); // Function to update variables and logic
	void render(sf::RenderTarget& targetWindow); // Function to update graphic variables and functionality
};

