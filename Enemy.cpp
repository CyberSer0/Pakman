#include "Enemy.h"

void Enemy::initVariables()
{
	this->movementSpeed = 2.5f;
}

/*
*  PUBLIC FUNCTIONS
*/
// Constructor
Enemy::Enemy(const std::string& textureName, int startTileX, int startTileY) : Entity(textureName, startTileX, startTileY)
{
	this->initVariables();
}

// RandomWalk algorithm if player is not seen
void Enemy::randomWalk()
{

}

// Pathfinding A* to the players position if seen
void Enemy::pathfind()
{

}

// Movement function for enemy
void Enemy::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

// Update logic and functionality
void Enemy::update()
{
	this->currentTile = sf::Vector2i(this->sprite.getPosition().x / 16, this->sprite.getPosition().y / 16);

	switch (this->playerSeen)
	{
	case true:
		this->randomWalk();
	case false:
		this->pathfind();
	}
}

// Rendering graphics
void Enemy::render(sf::RenderTarget& targetWindow)
{

}
