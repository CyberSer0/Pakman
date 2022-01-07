#include "Game.h"

/*
* Private Functions
*/
void Game::initVariables()
{
	this->gameState = true;
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
		}
	}

	/*for (size_t i = 2; i < size - 2; ++i)
		for (size_t j = 2; j < size - 2; ++j)
			if (rand() > (RAND_MAX / 1.25))
				level[i * size + j] = 11;
			else if (rand() > (RAND_MAX / 3))
				level[i * size + j] = 0;*/
			

	this->map.loadMap("Assets/tileset.png", this->tileSize, this->level, size, size);
	
}

void Game::initView()
{
	this->halfSize = (float)(this->tileSize.x * this->size) / 2;
	this->view.setCenter(this->halfSize, this->halfSize);
	this->view.zoom(0.3f);
}

sf::View Game::letterBox(sf::View view, size_t width, int height) const
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
	this->player = Player( "Assets/Player/pakman_right.png", ((int)tileSize.x / 2) * (int)size, ((int)tileSize.y / 2) * (int)size);
}

// De-/Constructors

Game::Game()
{
	this->initVariables();
	this->initMap();
	this->initView();
	this->initPlayer();
}

Game::~Game()
{
	this->gameState = false;
	delete[] this->level;
}

// Accessors
const bool Game::gameRunning() const
{
	return gameState;
}

void Game::updateEvents(sf::RenderWindow& target)
{
	
	while (target.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			target.close();
	}

	// Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		if (this->level[((size_t)this->player.currentTile.y - 1) * this->size + this->player.currentTile.x] == 0)
			this->player.move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		if (this->level[this->player.currentTile.y * this->size + this->player.currentTile.x - 1] == 0)
			this->player.move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		if (this->level[((size_t)this->player.currentTile.y + 1) * this->size + this->player.currentTile.x] == 0)
			this->player.move(0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		if (this->level[this->player.currentTile.y * this->size + this->player.currentTile.x + 1] == 0)
			this->player.move(1.f, 0.f);
}
	

/*
* Public Functions
*/
void Game::update(sf::RenderWindow& target)
{
	// Logic, ecent handler
	this->updateEvents(target);
	this->player.update();
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.clear(sf::Color::Black);
	target.setView(this->letterBox(this->view, target.getSize().x, target.getSize().y));

	// Draw game objects
	target.draw(this->player);
	target.draw(this->map);
}

