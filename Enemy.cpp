#include "Enemy.h"

using namespace sf;

/*
* Private functions
*/
void Enemy::initVariables()
{
	this->movementSpeed = 210.f;
	this->textureLeft.loadFromFile("Assets/Enemy/enemy_left.png");
	this->textureRight.loadFromFile("Assets/Enemy/enemy_right.png");
}

/*
* Public functions
*/
// Constructor
Enemy::Enemy() : Entity("Assets/Enemy/enemy_right.png", 1, 1)
{
	this->initVariables();
}

Enemy::Enemy(size_t startTileX, size_t startTileY) : Entity("Assets/Enemy/enemy_right.png", startTileX, startTileY)
{
	this->initVariables();
}

// Functions
void Enemy::move(const float dirX, const float dirY)
{
	this->velocity = sf::Vector2f(dirX, dirY);
	if (dirX > 0.f)
	{
		this->sprite.setTexture(textureRight);
	}
	else if (dirX < 0.f)
	{
		this->sprite.setTexture(textureLeft);
	}
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Enemy::update()
{
	this->currentTile = sf::Vector2i((int)((float)(sprite.getPosition().x) / 16), (int)((float)(sprite.getPosition().y) / 16));
	//std::cout << "tileX: " << this->currentTile.x << ", tileY: " << this->currentTile.y << "\tX: " << this->getPos().x << ", Y: " << this->getPos().y << std::endl;
}


void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
