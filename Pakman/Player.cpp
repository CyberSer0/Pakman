#include "Player.h"

using namespace sf;

// Private functions
void Player::initVariables()
{
	this->scaleX = 4;
	this->scaleY = 4;
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
	//this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
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
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

// Functions
void Player::update()
{

}

void Player::render(sf::RenderTarget& targetWindow)
{
	targetWindow.draw(this->sprite);
}
