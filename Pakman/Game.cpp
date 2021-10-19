#include "Game.h"

// Private Functions
void Game::initVariables()
{
	std::cout << "Wpisz rozmiar mapy: ";
	std::cin >> this->size;
	this->level = new int[size * size];

	// WiP
	std::cout << "Wpisz seed mapy (lub zostaw puste i potiwerdz dla losowego)" << "\nSeed mapy jest rowny (dlugosci rozmiaru mapy - 2) do kwadratu: ";
	std::cin >> this->seed;

	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 700;
	this->videoMode.width = 1280;

	this->window = new sf::RenderWindow(this->videoMode, "Pakman");
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initMap()
{
	// 0 - blank | 1 - upperL corner | 2 - upperR corner | 3 - lowerL corner | 4 - lowerR corner
	// 5 - Ver. wall | 6 - Hor. wall | 7 - U-shape wall | 8 - n-shape wall | 9 - C-shape wall | 10 - >-shape wall
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (j == 0 && i == 0)
			{
				level[i * size + j] = 1;
			}
			else if (j == size - 1 && i == 0)
			{
				level[i * size + j] = 2;
			}
			else if (j == 0 && i == size - 1)
			{
				level[i * size + j] = 3;
			}
			else if (j == size - 1 && i == size - 1)
			{
				level[i * size + j] = 4;
			}
			else if (j == 0 || j == size - 1)
			{
				level[i * size + j] = 5;
			}
			else if (i == 0 || i == size - 1)
			{
				level[i * size + j] = 6;
			}
			else
			{
				level[i * size + j] = 0;
			}
			std::cout << level[i * size + j] << " ";
		}
		std::cout << std::endl;
	}
	this->map = new Tilemap();
	this->tileSize = sf::Vector2u(16, 16);
	map->loadMap("Assets/tileset.png", this->tileSize, this->level, size, size);

}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::collideUp(Player* player, Tilemap* tilemap)
{

}

void Game::collideDown(Player* player, Tilemap* tilemap)
{
}

void Game::collideLeft(Player* player, Tilemap* tilemap)
{
}

void Game::collideRight(Player* player, Tilemap* tilemap)
{
}

// De-/Constructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initMap();
	this->initPlayer();
}

Game::~Game()
{
	delete this->player;
	delete[] level;
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

	// Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->player->move(0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->player->move(1.f, 0.f);
}

// Public Functions
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
	this->window->draw(*map);
	this->player->render(*this->window);

	// Display the game
	this->window->display();
}
