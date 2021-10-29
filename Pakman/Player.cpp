#include "Player.h"

using namespace sf;

/*
* Private functions
*/ 
void Player::initVariables()
{
	this->movementSpeed = 4.f;
	this->textureLeft.loadFromFile("Assets/Player/pakman_left.png");
	this->textureRight.loadFromFile("Assets/Player/pakman_right.png");
	this->textureDown.loadFromFile("Assets/Player/pakman_down.png");
	this->textureUp.loadFromFile("Assets/Player/pakman_up.png");
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
		//this->sprite.setRotation(180.f);
		//this->sprite.setScale(this->scale, -this->scale);
		this->sprite.setTexture(textureRight);
	}
	else if(dirX == -1.f && dirY == 0.f)
	{
		//this->sprite.setRotation(0.f);
		//this->sprite.setScale(this->scale, this->scale);
		this->sprite.setTexture(textureLeft);
	}
	else if (dirX == 0.f && dirY == 1.f)
	{
		//this->sprite.setRotation(-90.f);
		this->sprite.setTexture(textureDown);
	}
	else if(dirX == 0.f && dirY == -1.f)
	{
		//this->sprite.setRotation(90.f);
		this->sprite.setTexture(textureUp);
	}
		this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

// Functions
void Player::update()
{
	this->currentTile = sf::Vector2i((sprite.getPosition().x + 8) / 16, (sprite.getPosition().y + 8) / 16);
	std::cout << this->currentTile.x << ", " << this->currentTile.y << "\t" << this->sprite.getPosition().x << ", " << this->sprite.getPosition().y << std::endl;
}

void Player::render(sf::RenderTarget& targetWindow)
{
	this->collisionBox = this->sprite.getGlobalBounds();
	
	targetWindow.draw(this->sprite);
}
