#include "Player.h"

using namespace sf;

// Private functions
void Player::initVariables()
{
	this->scaleX = 1;
	this->scaleY = 1;
	this->movementSpeed = 5.f;
}

void Player::initTexture()
{
	// Loading texure from file
	if (!this->texture.loadFromFile("Assets/pakman.png"))
	{
		std::cout << "[!] ERR::PLAYER::INITTEXTURE(): Player texture couldn't be loaded\n" << std::endl;
	}
}

void Player::initSprite()
{
	// Setting the sprite to the set texture
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(8, 8);
}

// Constructor
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

// Deconstructor
Player::~Player()
{
	
}


void Player::move(const float dirX, const float dirY)
{
	if (dirX == 1.f && dirY == 0.f)
	{
		this->sprite.setRotation(180.f);
		this->sprite.setScale(this->scaleX, -this->scaleY);
	}
	else if(dirX == -1.f && dirY == 0.f)
	{
		this->sprite.setRotation(0.f);
		this->sprite.setScale(this->scaleX, this->scaleY);
	}
	else if(dirX == 0.f && dirY == 1.f)
		this->sprite.setRotation(-90.f);
	else if(dirX == 0.f && dirY == -1.f)
		this->sprite.setRotation(90.f);
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

// Functions
void Player::update()
{

}

void Player::render(sf::RenderTarget& targetWindow)
{
	//this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
	this->collisionBox = this->sprite.getGlobalBounds();
	targetWindow.draw(this->sprite);
}
