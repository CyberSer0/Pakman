#include "Enemy.h"

using namespace sf;

/*
* Private functions
*/
void Enemy::pathfind(Player player, std::vector<pathNode> pathLevel, float delta)
{
	std::vector<pathNode> openPathNodes;
	std::vector<pathNode> closedPathNodes;
}

void Enemy::initVariables()
{
	this->movementSpeed = MOVE_SPEED;
	if(!this->textureLeft.loadFromFile("Assets/Enemy/enemy_left.png")) std::cout << "[ERR] LEFT texture of Enemy not found" << std::endl;
	if (!this->textureRight.loadFromFile("Assets/Enemy/enemy_right.png")) std::cout << "[ERR] RIGHT texture of Enemy not found" << std::endl;
	this->seenPlayer = nullptr;
}

void Enemy::initPathLevel(std::vector<size_t> level)
{
	this->pathLevel.clear();
	pathNode currentNode;
	for (auto i : level)
		if (i != 0)
		{
			currentNode.G = 999;
			currentNode.H = 999;
			currentNode.F = currentNode.G + currentNode.H;
			currentNode.nextPathNode = nullptr;
			this->pathLevel.push_back(currentNode);
		}
		else
		{
			currentNode.G = 0;
			currentNode.H = 0;
			currentNode.F = currentNode.G + currentNode.H;
			currentNode.nextPathNode = nullptr;
			this->pathLevel.push_back(currentNode);
		}
}

bool Enemy::randomWalk(float delta)
{
	int randomDir = rand() % 100;
	if (randomDir < 25 && this->currentTile.x - 2 != 0) this->move(-1 * delta, 0);
	else if (randomDir >= 25 && randomDir < 50 && this->currentTile.x + 2 != 15) this->move(1 * delta, 0);
	else if (randomDir >= 50 && randomDir < 75 && this->currentTile.y - 2 != 0) this->move(0, -1 * delta);
	else if (randomDir >= 75 && randomDir < 100 && this->currentTile.x + 2 != 15) this->move(0, 1 * delta);
	
	return true;
}

/*
* Public functions
*/
// Constructor
Enemy::Enemy() : Entity("Assets/Enemy/enemy_right.png", 1, 1)
{
	this->initVariables();
}

Enemy::Enemy(sf::Vector2u startTile, std::vector<size_t> level) : Entity("Assets/Enemy/enemy_right.png", startTile.x, startTile.y)
{
	this->initVariables();
	this->initPathLevel(level);
}

// Functions
void Enemy::move(const float dirX, const float dirY)
{
	//this->velocity = sf::Vector2f(dirX, dirY);
	if (dirX > 0.f)
	{
		this->sprite.setTexture(textureRight);
	}
	else if (dirX < 0.f)
	{
		this->sprite.setTexture(textureLeft);
	}
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Enemy::update(float delta)
{
	this->currentTile = sf::Vector2i((int)((float)(sprite.getPosition().x) / 16), (int)((float)(sprite.getPosition().y) / 16));
	std::cout << "tileX: " << this->currentTile.x << ", tileY: " << this->currentTile.y << "\tX: " << this->getPos().x << ", Y: " << this->getPos().y << std::endl;
	if (seenPlayer != nullptr)
	{
		this->movementSpeed = RUN_SPEED;
		this->pathfind(*seenPlayer, this->pathLevel, delta);
	}
	else
	{
		this->movementSpeed = MOVE_SPEED;
		this->randomWalk(delta);
	}
}


void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}

void Enemy::setPlayerDetected(Player& player)
{
	this->seenPlayer = &player;
}

void Enemy::clearPlayerDetected()
{
	this->seenPlayer = nullptr;
}
