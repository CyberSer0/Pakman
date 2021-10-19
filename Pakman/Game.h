#pragma once
#include "Player.h"
#include "Tilemap.h"

/*
	Main Game class/functionality wrapper
*/

class Game
{
private:
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	// Map
	Tilemap* map;
	unsigned int size;
	sf::Vector2u tileSize;
	int* level;
	std::string seed;

	// Player
	Player* player;

	// Private functions
	void initVariables();
	void initWindow();
	void initMap();
	void initPlayer();
	void collideUp(Player* player, Tilemap* tilemap);
	void collideDown(Player* player, Tilemap* tilemap);
	void collideLeft(Player* player, Tilemap* tilemap);
	void collideRight(Player* player, Tilemap* tilemap);

public: 

	// De-/Constructors
	Game();
	virtual ~Game();
	
	// Accessors
	const bool gameRunning() const;

	// Functions
	void updateEvents();
	void update();
	void render();
};

