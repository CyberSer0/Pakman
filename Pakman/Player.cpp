#include "Player.h"

using namespace sf;

/*
* Private functions
*/ 
void Player::initVariables()
{
	this->movementSpeed = 5.f;
}

/*
* Public functions
*/ 
// Constructor
Player::Player(const std::string& textureName, int startTileX, int startTileY) : Entity(textureName, startTileX, startTileY)
{
	this->initVariables();
}

void Player::move(const float dirX, const float dirY)
{
	if (dirX == 1.f && dirY == 0.f)
	{
		this->sprite.setRotation(180.f);
		this->sprite.setScale(this->scale, -this->scale);
	}
	else if(dirX == -1.f && dirY == 0.f)
	{
		this->sprite.setRotation(0.f);
		this->sprite.setPosition(sprite.getPosition().x - 16, sprite.getPosition().y - 16);
		this->sprite.setScale(this->scale, this->scale);
	}
	else if (dirX == 0.f && dirY == 1.f)
	{
		this->sprite.setRotation(-90.f);
		this->sprite.setPosition(sprite.getPosition().x + 16, sprite.getPosition().y + 16);
	}
	else if(dirX == 0.f && dirY == -1.f)
	{
		this->sprite.setRotation(90.f);
	}
		this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

// Functions
void Player::update()
{
	this->currentTile = sf::Vector2i(sprite.getPosition().x/16, sprite.getPosition().y / 16);
}

void Player::render(sf::RenderTarget& targetWindow)
{
	this->collisionBox = this->sprite.getGlobalBounds();
	
	targetWindow.draw(this->sprite);
}
