#include "Entity.h"

//// Private Functions
// Variable Initialization
void Entity::initVariables()
{
	this->scale = 1.f;
}

// Texture Initialization
void Entity::initTexture(const std::string& textureName)
{
	if (!this->texture.loadFromFile(textureName))
	{
		std::cout << "[!] ERR::" << this << "::INITTEXTURE(): " << this << " texture couldn't be loaded\n" << std::endl;
	}
	this->texture.loadFromFile(textureName);
}

// Sprite Initialization
void Entity::initSprite(int startTileX, int startTileY)
{
	this->sprite.setTexture(this->texture); // Setting the texture given to the sprite 
	this->sprite.setOrigin(8, 8); // Setting Origin of the sprite at the middle of it (16x16 textures)
	this->sprite.setPosition((float)startTileX*16 + this->sprite.getOrigin().x, (float)startTileY*16 + this->sprite.getOrigin().y); // Setting the position of the sprite at (startTileX, startTileY)
}

// Default constructor
Entity::Entity()
{
	this->initVariables();
}

// Constructor with overload
Entity::Entity(const std::string& textureName, size_t startTileX, size_t startTileY)
{
	this->initVariables();
	this->initTexture(textureName); // Initializing texture with textureName
	this->initSprite(startTileX, startTileY); // Initializing sprite at (startTileX, startTileY)
}

// Deconstructor
Entity::~Entity()
{

}

//// Public Functions

void Entity::setPos(size_t x, size_t y)
{
	this->sprite.setPosition(x + this->sprite.getOrigin().x, y + this->sprite.getOrigin().y);
}

sf::Vector2f Entity::getPos() const
{
	return sf::Vector2f(this->sprite.getPosition().x, this->sprite.getPosition().y);
}

sf::FloatRect Entity::getCollisionBox() const
{
	return this->sprite.getGlobalBounds();
}

// Render function
void Entity::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(this->sprite); // Drawing the sprite on the targetWindow
}

