#include "Player.h"

using namespace sf;

/*
* Private functions
*/ 
void Player::initVariables()
{
	this->movementSpeed = 150.f;
	this->textureLeft.loadFromFile("Assets/Player/pakman_left.png");
	this->textureRight.loadFromFile("Assets/Player/pakman_right.png");
	this->textureDown.loadFromFile("Assets/Player/pakman_down.png");
	this->textureUp.loadFromFile("Assets/Player/pakman_up.png");
}

/*
* Public functions
*/ 
// Constructor
Player::Player(): Entity("Assets/Player/pakman_right.png", 1, 1)
{
	this->initVariables();
}

Player::Player(int startTileX, int startTileY) : Entity("Assets/Player/pakman_right.png", startTileX, startTileY)
{
	this->initVariables();
}


// Functions
void Player::move(const float dirX, const float dirY)
{
	this->velocity = sf::Vector2f(dirX, dirY);
	if (dirX > 0.f && dirY == 0.f)
	{
		this->sprite.setTexture(textureRight);
	}
	else if(dirX < 0.f && dirY == 0.f)
	{
		this->sprite.setTexture(textureLeft);
	}
	else if (dirX == 0.f && dirY > 0.f)
	{
		this->sprite.setTexture(textureDown);
	}
	else if(dirX == 0.f && dirY < 0.f)
	{
		this->sprite.setTexture(textureUp);
	}
		this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::update()
{
	this->currentTile = sf::Vector2u((int)((float)(this->sprite.getPosition().x) / 16), (int)((float)(this->sprite.getPosition().y) / 16));
	//std::cout << "tileX: " << this->currentTile.x << ", tileY: " << this->currentTile.y << "\tX: " << this->getPos().x << ", Y: " << this->getPos().y << std::endl;
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.draw(this->sprite);
}
