#include "Tilemap.h"

using namespace sf;

// Public functions
bool Tilemap::loadMap(const std::string & tileset, sf::Vector2u tileSize, const int* tiles, size_t width, size_t height)
{
	// Loading tileset texture
	if (!this->tileset.loadFromFile(tileset))
		std::cout << "[!] ERR::" << this << "::LOADMAP(): " << this << " map couldn't be loaded" << std::endl;

	// Resizing the vertex array
	this->vertices.setPrimitiveType(sf::Quads);
	this->vertices.resize(width * height * 4);

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
			quad[0].texCoords = sf::Vector2f((float)(tu * tileSize.x), (float)(tv * tileSize.y));
			quad[1].texCoords = sf::Vector2f((float)((tu + 1) * tileSize.x), (float)(tv * tileSize.y));
			quad[2].texCoords = sf::Vector2f((float)((tu + 1) * tileSize.x), (float)((tv + 1) * tileSize.y));
			quad[3].texCoords = sf::Vector2f((float)(tu * tileSize.x), (float)((tv + 1) * tileSize.y));
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


sf::VertexArray Tilemap::getMapVertices() const
{
	return this->vertices;
}




