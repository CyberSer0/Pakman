#pragma once

#include "Entity.h"
#include "Player.h"

#include <iostream>
#include <future>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define MOVE_SPEED 80.f
#define RUN_SPEED 160.f

struct pathNode
{
	size_t G;
	size_t H;
	size_t F;
	pathNode* nextPathNode;
};

class Enemy : public Entity
{
private:
	// Variables
	float movementSpeed; // Creating a movement speed variable
	sf::Vector2f velocity;
	sf::Texture textureLeft;
	sf::Texture textureRight;
	Player* seenPlayer;
	std::vector<pathNode> pathLevel;
	void pathfind(Player player, std::vector<pathNode> level, float delta);

	// Private functions
	void initVariables(); // Function to initialize and set values to all Variables
	void initPathLevel(std::vector<size_t> level);
	bool randomWalk(float delta);
public:
	// De-/Constructor
	Enemy();
	Enemy(sf::Vector2u startTile, std::vector<size_t> level);

	// Variables
	sf::Vector2i currentTile; // Vector of current Tile X and current Tile Y of the Entity

	// Functions
	void move(const float dirX, const float dirY); // Function to move the player object/sprite

	void update(float delta); // Function to update variables and logic
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Function to update graphic variables and functionality

	void setPlayerDetected(Player& player);
	void clearPlayerDetected();
};

