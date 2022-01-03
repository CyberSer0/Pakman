#include "Game.h"

/*
* Private Functions
*/
void Game::initVariables()
{
	this->gameState = true;
	this->window->setView(this->view);
	std::cout << this << "\tGame window:\t\t" << this->window << "\tView:\t" << &(this->view) << std::endl;
	/*std::cout << "Wpisz rozmiar mapy (16 - 64): ";
	std::cin >> this->size;
	if (this->size < 16)
	{
		std::cout << "Too small of a value, changing to 16" << std::endl;
		this->size = 16;
	}
	else if (this->size > 64)
	{
		std::cout << "Too big of a value, changing to 64" << std::endl;
		this->size = 64;
	}*/
	this->size = 16;

	this->level = new int[size * size];
	
	this->tileSize = sf::Vector2u(16, 16);
}

void Game::initMap()
{
	// 0 - blank | 1 - upperL corner | 2 - upperR corner | 3 - lowerL corner | 4 - lowerR corner
	// 5 - Ver. wall | 6 - Hor. wall | 7 - U-shape wall | 8 - n-shape wall | 9 - C-shape wall | 10 - >-shape wall
	for (unsigned int i = 0; i < size; ++i){
		for (unsigned int j = 0; j < size; ++j)
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

	/*for (unsigned int i = 2; i < size - 2; ++i)
		for (unsigned int j = 2; j < size - 2; ++j)
			if (rand() > (RAND_MAX / 2))
				level[i * size + j] = 11;
			else if (rand() > (RAND_MAX / 3) || rand() > (RAND_MAX / 4))
				level[i * size + j] = 0;*/
			

	this->map = new Tilemap();
	map->loadMap("Assets/tileset.png", this->tileSize, this->level, size, size);
	
}

void Game::initView()
{
	this->halfSize = (float)(this->tileSize.x * this->size) / 2;
	this->view.setCenter(this->halfSize, this->halfSize);
	//this->view.zoom((float)this->tileSize.y * (float)this->size / ((float)this->videoMode.height * 2));
	this->window->setView(this->letterBox(this->view, this->window->getSize().x, this->window->getSize().y));
}

sf::View Game::letterBox(sf::View view, int width, int height)
{
	float windowRatio = width / (float)height;
	float viewRatio = view.getSize().x / (float)view.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	if (windowRatio > viewRatio)
	{
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.f;
	}
	else
	{
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}

	view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
	return view;
}

void Game::initPlayer()
{
	this->player = new Player( "Assets/Player/pakman_right.png", ((int)tileSize.x / 2) * (int)size, ((int)tileSize.y / 2) * (int)size);
}

// De-/Constructors

Game::Game(sf::RenderWindow* window) : Scene{ window }
{
	this->initVariables();
	//this->initMap();
	this->initView();
	this->initPlayer();
}

Game::~Game()
{
	this->gameState = false;
	delete this->player;
	delete[] level;
}

// Accessors
const bool Game::gameRunning() const
{
	return gameState;
}

void Game::updateEvents()
{
	
	while (this->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->window->close();
	}

	// Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		if (this->level[(this->player->currentTile.y - 1) * this->size + this->player->currentTile.x] == 0)
			this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		if (this->level[this->player->currentTile.y * this->size + this->player->currentTile.x - 1] == 0)
			this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		if (this->level[(this->player->currentTile.y + 1) * this->size + this->player->currentTile.x] == 0)
			this->player->move(0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		if (this->level[this->player->currentTile.y * this->size + this->player->currentTile.x + 1] == 0)
			this->player->move(1.f, 0.f);
}
	

/*
* Private Functions
*/
void Game::update()
{
	// Backend logic, keystrokes
	this->updateEvents();
	player->update();
}

void Game::render()
{	
	this->window->clear();

	// Draw game objects
	this->window->draw(*map);
	this->player->render(*this->window);
	this->window->setView(this->letterBox(this->view, this->window->getSize().x, this->window->getSize().y));

	// Display the game
	this->window->display();
}
