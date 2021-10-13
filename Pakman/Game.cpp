#include "Game.h"

// Private Functions
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 700;
	this->videoMode.width = 1280;

	this->window = new sf::RenderWindow(this->videoMode, "Pakman");
}

// De-/Constructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

// Accessors
const bool Game::gameRunning() const
{
	return this->window->isOpen();
}

void Game::updateEvents()
{
	// Event Monitoring
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

// Functions
void Game::update()
{
	// Backend logic, keystrokes
	this->updateEvents();
}

void Game::render()
{
	// Visual loop
	this->window->clear(sf::Color(0, 0, 0, 255));
	
	// Draw game objects

	// Display the game
	this->window->display();
}
