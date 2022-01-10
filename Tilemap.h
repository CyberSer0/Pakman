#pragma once

#include <iostream>
#include <iomanip>
#include <SFML/Graphics.hpp>

#define TILESIZE sf::Vector2u(16, 16)

/*
* The Tilemap Class extents classes sf::Drawable and sf:Transformable to instantiate it in the Game class
*/
class Tilemap : public sf::Drawable, public sf::Transformable
{
private:
	// Private Variables
	sf::VertexArray vertices; // Vertex array for creation of the wall sprites and posiitons of them
	sf::Texture tileset; // Texture of the tiles
	sf::Vertex* quad; // Single vertex to be used in setting positions of the tilemap
	size_t tileNumber; // Number of tiles in the given tileset
	size_t tu; // ##################DOCUMENTATION NEEDED###################
	size_t tv; // ##################DOCUMENTATION NEEDED###################
	std::vector<sf::FloatRect> collisionArray;
public:
	// Public functions
	// Function to load the map, arguments: (tileset - name of tileset file, tileSize - dimensions of 1 tile, width, height - width and height of the generated map)
	bool loadMap(const std::string& tilemap, sf::Vector2u tileSize, std::vector<size_t> tiles, size_t width, size_t height);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::vector<sf::FloatRect> getMapCollisionArray() const;

	virtual ~Tilemap();
};

