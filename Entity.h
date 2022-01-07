#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Entity : public sf::Drawable
{
protected:
	// Protected variables
	sf::Texture texture; // Creating a texture object
	sf::Sprite sprite; // Creating a sprite object
	sf::FloatRect collisionBox; // Creating a collisionBox rectangle
	float scale; // Creating scale variable

	// Protected functions
	void initVariables(); // Initializes different variables
	void initTexture(const std::string& textureName); // Function to initialize the texture (to use in the sprite)
	void initSprite(int startTileX, int startTileY); // Function to initialize the sprite, arguments are the tile coordinates it should be created at

	/*
	* Constructor - used to initialize all functions at the instatiation of the object
	*/
	Entity();
	Entity(const std::string & textureName, int startTileX, int startTileY);
	/*
	* Deconstructor - deletes objects created in the constructor to prevent memory leaks
	*/
	virtual ~Entity();
public:
	void update(); // Function to update variables and logic
	void draw(sf::RenderTarget& target, sf::RenderStates states); // Function to update graphic variables and functionality
};

