#include "Tilemap.h"

using namespace sf;

// Public functions
void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &this->tileset;
	target.draw(this->vertices, states);
}

bool Tilemap::loadMap(const std::string & tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
	// Loading tileset texture
	if (!this->tileset.loadFromFile(tileset))
			std::cout << "" << std::endl;

	// Resizing the vertex array
	this->vertices.setPrimitiveType(sf::Quads);
	this->vertices.resize(width * height * 4);

	// Populate vertex array with 1 quad/tile
	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{
			// Get current tyle number
			this->tileNumber = tiles[i + j * width];

			// Finding position in tileset texture
			this->tu = tileNumber % (this->tileset.getSize().x / tileSize.x);
			this->tv = tileNumber / (this->tileset.getSize().x / tileSize.x);
			
			// Getting a pointer to the current quad
			this->quad = &this->vertices[(i + j * width) * 4];

			// Defining the 4 corners of the level map
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// Defining 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
	}

	return true;
}



