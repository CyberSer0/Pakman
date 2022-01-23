#pragma once

#include "Entity.h"
#include "Player.h"

#include <iostream>
#include <future>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define MOVE_SPEED 80.f
#define RUN_SPEED 160.f

/*
* Structure created for pathfinding to some locations
*/
struct pathNode
{
	sf::Vector2<size_t> selfPos; // size_t position sf::Vector2 of the pathNode
	size_t G; // Distance from this
	size_t H; // Distance from the target
	size_t F; // Sum of the distances from this and from the target
	std::vector<std::reference_wrapper<pathNode>> neighbours; // Left, top, right, bottom neighbour pathNodes
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
	void pathfind(sf::Vector2f targetPos, std::vector<pathNode> level, float delta);

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

