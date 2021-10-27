#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

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
	int tileNumber; // Number of tiles in the given tileset
	int tu; // ##################DOCUMENTATION NEEDED###################
	int tv; // ##################DOCUMENTATION NEEDED###################

public:
	// Public functions
	// Function to load the map, arguments: (tileset - name of tileset file, tileSize - dimensions of 1 tile, width, height - width and height of the generated map)
	bool loadMap(const std::string& tilemap, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // 
};

