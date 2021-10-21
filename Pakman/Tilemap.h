#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Tilemap : public sf::Drawable, public sf::Transformable
{
private:
	// Private Variables
	sf::VertexArray vertices;
	sf::Texture tileset;
	sf::Vertex* quad;
	int tileNumber;
	int tu;
	int tv;

public:
	// Public functions
	bool loadMap(const std::string& tilemap, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

