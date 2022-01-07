#include "Player.h"

using namespace sf;

/*
* Private functions
*/ 
void Player::initVariables()
{
	this->movementSpeed = 2.f;
	this->textureLeft.loadFromFile("Assets/Player/pakman_left.png");
	this->textureRight.loadFromFile("Assets/Player/pakman_right.png");
	this->textureDown.loadFromFile("Assets/Player/pakman_down.png");
	this->textureUp.loadFromFile("Assets/Player/pakman_up.png");
}

/*
* Public functions
*/ 
// Constructor
Player::Player()
{

}

Player::Player(const std::string& textureName, int startTileX, int startTileY) : Entity(textureName, startTileX, startTileY)
{
	this->initVariables();
}


// Functions
void Player::move(const float dirX, const float dirY)
{
	this->velocity = sf::Vector2f(dirX, dirY);
	if (dirX == 1.f && dirY == 0.f)
	{
		this->sprite.setTexture(textureRight);
	}
	else if(dirX == -1.f && dirY == 0.f)
	{
		this->sprite.setTexture(textureLeft);
	}
	else if (dirX == 0.f && dirY == 1.f)
	{
		this->sprite.setTexture(textureDown);
	}
	else if(dirX == 0.f && dirY == -1.f)
	{
		this->sprite.setTexture(textureUp);
	}
		this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

sf::Vector2f Player::getPos() const
{
	return sf::Vector2f(this->sprite.getPosition().x, this->sprite.getPosition().y);
}

sf::FloatRect Player::getCollisionBox() const
{
	return this->collisionBox;
}


void Player::update()
{
	this->currentTile = sf::Vector2i((int)((float)(sprite.getPosition().x) / 16), (int)((float)(sprite.getPosition().y) / 16));
	//std::cout << "tileX: " << this->currentTile.x << ", tileY: " << this->currentTile.y << "\tX: " << this->getPos().x << ", Y: " << this->getPos().y << std::endl;
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.draw(this->sprite);
}
