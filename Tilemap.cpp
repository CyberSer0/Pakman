#include "Tilemap.h"

using namespace sf;

// Public functions
bool Tilemap::loadMap(const std::string & tileset, sf::Vector2u tileSize, const int* tiles, int width, int height)
{
	this->collisionArray.clear();
	// Loading tileset texture
	if (!this->tileset.loadFromFile(tileset))
	{
		std::cout << "[!] ERR::" << this << "::LOADMAP(): " << this << " map couldn't be loaded" << std::endl;
		return false;
	}

	// Resizing the vertex array
	this->vertices.setPrimitiveType(sf::Quads);
	this->vertices.resize(width * height * 4);

	system("CLS");

	// Populate vertex array with 1 quad/tile
	for (size_t i = 0; i < width; ++i)
	{
		for (size_t j = 0; j < height; ++j)
		{
			// Get current tile number
			this->tileNumber = tiles[i + j * width];

			// Finding position in tileset texture
			this->tu = tileNumber % (this->tileset.getSize().x / tileSize.x);
			this->tv = tileNumber / (this->tileset.getSize().x / tileSize.x);
			
			// Getting a pointer to the current quad
			this->quad = &this->vertices[(unsigned)((i + j * width) * 4)];

			// Defining the 4 corners of the level map
			quad[0].position = sf::Vector2f((float)(i * tileSize.x), (float)(j * tileSize.y));
			quad[1].position = sf::Vector2f((float)((i + 1) * tileSize.x), (float)(j * tileSize.y));
			quad[2].position = sf::Vector2f((float)((i + 1) * tileSize.x), (float)((j + 1) * tileSize.y));
			quad[3].position = sf::Vector2f((float)(i * tileSize.x), (float)((j + 1) * tileSize.y));

			// Defining 4 texture coordinates
			quad[0].texCoords = sf::Vector2f((float)(this->tu * tileSize.x), (float)(this->tv * tileSize.y));
			quad[1].texCoords = sf::Vector2f((float)((this->tu + 1) * tileSize.x), (float)(this->tv * tileSize.y));
			quad[2].texCoords = sf::Vector2f((float)((this->tu + 1) * tileSize.x), (float)((this->tv + 1) * tileSize.y));
			quad[3].texCoords = sf::Vector2f((float)(this->tu * tileSize.x), (float)((this->tv + 1) * tileSize.y));
			
			// Pushing the collision rect to the collisionArray
			if (tiles[i + j * width] != 0)
				this->collisionArray.push_back(sf::FloatRect(quad[0].position, sf::Vector2f(tileSize.x, tileSize.y)));
			else
				this->collisionArray.push_back(sf::FloatRect());
			
			std::cout << std::setw(3) << tiles[i * width + j];
		}
		std::cout << std::endl;
	}
	return true;
}


void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &this->tileset;
	target.draw(this->vertices, states);
}


std::vector<sf::FloatRect> Tilemap::getMapCollisionArray() const
{
	return this->collisionArray; 
}



