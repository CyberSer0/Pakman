#pragma once
#include "Scene.h"
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"
#include "Tilemap.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <random>

/*
	Main Game class/functionality wrapper
*/

class Game : protected Scene
{
private:
	sf::Event event;


	// Map
	Tilemap* map; // Creating a ptr to the tilemap object map for creating a game environment
	sf::Vector2u tileSize; // Dimensions of one single tile of the tilemap
	int* level; // Pointer to the array of tiles in the tilemap
	float halfSize; // Half of the game enviroment length (for view setting)

	// Entities
	Player* player; // Creating a pointer to a player object
	Enemy* enemy; // Creating an enemy

	// Private functions
	void initVariables(); // Function to initialize differrent variables
	void initView(); // Function to set and modify the camera view
	sf::View letterBox(sf::View view, int width, int height); // Function to responsively adjust the scale and size of the game objects and view
	void initPlayer(); // Function to initialize the player object and it's functionality

public: 
	// Public Variables
	bool gameState;
	unsigned int size; // Size of the game environment (in nr of tiles)

	// View
	sf::View view; // Creating a view object to use as a camera
	
	/*
	* Constructor - used to initialize all functions at the start of the game
	* Deconstor - deletes objects created in the constructor to prevent memory leaks
	*/
	Game(sf::RenderWindow* window); // Constructor
	virtual ~Game(); // Deconstructor
	void initMap(); // Function to initialize and load the game environment map
	
	/*
	* Accessors - serve as bools to check certain game states
	*/
	const bool gameRunning() const; // true - game is running, false - game is not running

	// Functions
	void updateEvents(); // Event Handler
	void update(); // Logic and background updates
	void render(); // Graphic updates
};

