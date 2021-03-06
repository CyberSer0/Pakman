#include "Entity.h"

//// Private Functions
// Variable Initialization
void Entity::initVariables()
{
	this->scale = 1;
}

// Texture Initialization
void Entity::initTexture(const std::string& textureName)
{
	if (!this->texture.loadFromFile(textureName))
	{
		std::cout << "[!] ERR::" << this << "::INITTEXTURE(): " << this << " texture couldn't be loaded\n" << std::endl;
	}
}

// Sprite Initialization
void Entity::initSprite(int startTileX, int startTileY)
{
	this->sprite.setTexture(this->texture); // Setting the texture given to the sprite 
	this->sprite.setOrigin(8, 8); // Setting Origin of the sprite at the middle of it (16x16 textures)
	this->sprite.setScale(this->scale, this->scale); // Setting the scale of the sprite
	this->sprite.setPosition(startTileX, startTileY); // Setting the position of the sprite at (startTileX, startTileY)
}

//// Public Functions
// Constructor with overload
Entity::Entity(const std::string& textureName, int startTileX, int startTileY)
{
	this->initVariables();
	this->initTexture(textureName); // Initializing texture with textureName
	this->initSprite(startTileX, startTileY); // Initializing sprite at (startTileX, startTileY)
}

// Deconstructor
Entity::~Entity()
{
	
}

// Update function
void Entity::update()
{
	this->currentTile = sf::Vector2i(sprite.getPosition().x / 16, sprite.getPosition().y / 16); // Updating the current Tile the sprite is at
}

// Render function
void Entity::render(sf::RenderTarget& targetWindow)
{
	this->collisionBox = this->sprite.getGlobalBounds(); // Setting the collision box to the global bounds of the sprite
	targetWindow.draw(this->sprite); // Drawing the sprite on the targetWindow
}