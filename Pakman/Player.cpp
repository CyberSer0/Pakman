#include "Player.h"

using namespace sf;

// Private functions
void Player::initVariables()
{
	this->scale = sf::Vector2f(1, 1);
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

void Player::initSprite(int startTileX, int startTileY)
{
	// Setting the sprite to the set texture
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(8, 8);
	this->sprite.setScale(this->scale.x, this->scale.y);
	this->sprite.setPosition(startTileX, startTileY);
}

// Constructor
Player::Player(int startTileX, int startTileY)
{
	this->initVariables();
	this->initTexture();
	this->initSprite(startTileX, startTileY);
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
		this->sprite.setScale(this->scale.x, -this->scale.y);
	}
	else if(dirX == -1.f && dirY == 0.f)
	{
		this->sprite.setRotation(0.f);
		this->sprite.setScale(this->scale.x, this->scale.y);
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
	this->tileX = sprite.getPosition().x/16;
	this->tileY = sprite.getPosition().y/16;
	//std::cout << "(" << this->tileX << ", " << this->tileY << ")" << std::endl;
}

void Player::render(sf::RenderTarget& targetWindow)
{
	//this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
	this->collisionBox = this->sprite.getGlobalBounds();
	targetWindow.draw(this->sprite);
}
