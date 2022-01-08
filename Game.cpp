#include "Game.h"

/*
* Private Functions
*/
void Game::initVariables()
{
	this->gameState = true;
	this->size = 16;
	this->level = new int[this->size * this->size];
	this->tileSize = sf::Vector2u(16, 16);
}

void Game::initMap()
{
	// 0 - blank | 1 - upperL corner | 2 - upperR corner | 3 - lowerL corner | 4 - lowerR corner
	// 5 - Ver. wall | 6 - Hor. wall | 7 - U-shape wall | 8 - n-shape wall | 9 - C-shape wall | 10 - >-shape wall
	for (unsigned int i = 0; i < this->size; ++i){
		for (unsigned int j = 0; j < this->size; ++j)
		{
			if (j == 0 && i == 0)
			{
				level[i * this->size + j] = 1;
			}
			else if (j == this->size - 1 && i == 0)
			{
				level[i * this->size + j] = 2;
			}
			else if (j == 0 && i == this->size - 1)
			{
				level[i * this->size + j] = 3;
			}
			else if (j == this->size - 1 && i == this->size - 1)
			{
				level[i * this->size + j] = 4;
			}
			else if (j == 0 || j == this->size - 1)
			{
				level[i * this->size + j] = 5;
			}
			else if (i == 0 || i == this->size - 1)
			{
				level[i * this->size + j] = 6;
			}
			else
			{
				level[i * this->size + j] = 0;
			}
		}
	}

	for (size_t i = 2; i < this->size - 2; ++i)
		for (size_t j = 2; j < this->size - 2; ++j)
			if (rand() > (RAND_MAX / 1.25))
				level[i * this->size + j] = 11;
			else if (rand() > (RAND_MAX / 3))
				level[i * this->size + j] = 0;
			

	this->map.loadMap("Assets/tileset.png", this->tileSize, this->level, this->size, this->size);
	this->mapCollisionArray.clear();
	this->mapCollisionArray = this->map.getMapCollisionArray();
}

void Game::initView()
{
	this->halfSize = (float)(this->tileSize.x * this->size) / 2;
	this->view.setCenter(this->halfSize, this->halfSize);
	this->view.zoom(0.3f);
}

void Game::initEnemies()
{
	this->allEnemies.clear();
	this->enemyAmount = this->size / 4;
	for (size_t i = 0; i < enemyAmount; ++i)
	{
		Enemy enemy((rand() % (this->size - 4) + 2), (rand() % (this->size - 4) + 2));
		this->allEnemies.push_back(enemy);
	}
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

/*
* Public Functions
*/

// Constructor
Game::Game() 
{
	this->initVariables();
	this->initMap();
	this->initView();
}

// Deconstructor
Game::~Game()
{
	delete[] this->level;
}

// Accessors
const bool Game::gameRunning() const
{
	return this->gameState;
}

void Game::updateEvents(sf::RenderWindow& target, float delta)
{
	
	while (target.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			target.close();
	}

	// Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		if (!this->player.getCollisionBox().intersects(this->mapCollisionArray[(this->player.currentTile.y - 1) * this->size + this->player.currentTile.x]))
			this->player.move(0.f * delta, -1.f * delta);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		if (!this->player.getCollisionBox().intersects(this->mapCollisionArray[(this->player.currentTile.y) * this->size + this->player.currentTile.x - 1]))
			this->player.move(-1.f * delta, 0.f * delta);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		if (this->level[((size_t)this->player.currentTile.y + 1) * this->size + this->player.currentTile.x] == 0)
			this->player.move(0.f * delta, 1.f * delta);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		if (this->level[this->player.currentTile.y * this->size + this->player.currentTile.x + 1] == 0)
			this->player.move(1.f * delta, 0.f * delta);
}
	

void Game::update(sf::RenderWindow& target, float delta)
{
	// Logic, ecent handler
	this->updateEvents(target, delta);
	for (Enemy i : this->allEnemies) i.update();
	this->player.update();
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.clear(sf::Color::Black);
	target.setView(this->letterBox(this->view, target.getSize().x, target.getSize().y));

	// Draw game objects
	for(Enemy i : this->allEnemies) target.draw(i);
	target.draw(this->player);
	target.draw(this->map);
}

void Game::resetGame()
{
	srand((unsigned  int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	this->initVariables();
	this->initMap();
	this->initEnemies();
	this->player.setPos(this->tileSize.x, this->tileSize.y);
}