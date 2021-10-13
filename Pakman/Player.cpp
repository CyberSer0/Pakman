#include "Player.h"

using namespace sf;

// Private functions
void Player::initVariables()
{
	this->texture.loadFromFile("Pakman.png");
	this->sprite.setTexture(texture);
	this->sprite.setPosition(100, 100);
	this->sprite.setScale(Vector2f(2, 2));
}

// Constructor
Player::Player()
{
}

// Deconstructor
Player::~Player()
{
	//delete this;
}

// Functions
void Player::update()
{

}

void Player::render()
{

}
