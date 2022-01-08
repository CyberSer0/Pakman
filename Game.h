#pragma once
#include "Scene.h"
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"
#include "Tilemap.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <chrono>

/*
	Main Game class/Functionality wrapper
*/

class Game : Scene, public sf::Drawable
{
private:
	sf::Event event;

	size_t enemyAmount;

	// Map
	Tilemap map; // Tilemap object map for creating a game environment
	sf::Vector2u tileSize; // Dimensions of one single tile of the tilemap
	int* level; // Pointer to the array of tiles in the tilemap
	float halfSize; // Half of the game enviroment length (for view setting)
	std::vector<sf::FloatRect> mapCollisionArray;

	// Entities
	Player player; // Player object
	std::vector<std::unique_ptr<Enemy>> allEnemies; // Array of all enemies

	// Private Methods
	void initVariables(); // Method to initialize differrent variables
	void initView(); // Method to set and modify the camera view
	void initEnemies(); // Method initializing enemies
	sf::View letterBox(sf::View view, size_t width, int height) const; // Method to responsively adjust the scale and size of the game objects and view

public: 
	// Public Variables
	bool gameState;
	size_t size; // Size of the game environment (in nr of tiles)

	// View
	sf::View view; // Creating a view object to use as a camera
	
	/*
	* Constructor - used to initialize all Methods at the start of the game
	* Deconstor - deletes objects created in the constructor to prevent memory leaks
	*/
	Game(); // Constructor
	virtual ~Game(); // Deconstructor
	void initMap(); // Method to initialize and load the game environment map
	
	/*
	* Accessors - serve as bools to check certain game states
	*/
	const bool gameRunning() const; // true - game is running, false - game is not running

	// Methods
	void updateEvents(sf::RenderWindow& target, float delta); // Event Handler
	void update(sf::RenderWindow& target, float delta); // Logic and background updates
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Graphic updates
	void resetGame();
};

