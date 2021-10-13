#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

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

	// Private functions
	void initVariables();
	void initWindow();

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

