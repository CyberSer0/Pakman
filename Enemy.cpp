#include "Enemy.h"

using namespace sf;

/*
* Private functions
*/
void Enemy::pathfind(sf::Vector2f targetPos, std::vector<pathNode> pathLevel, float delta)
{
	std::vector<std::reference_wrapper<pathNode>> openPathNodes;
	std::vector<std::reference_wrapper<pathNode>> closedPathNodes;
	pathNode* currentNode;
	size_t minF = 999;

	for (auto node : pathLevel)
		if (node.selfPos == sf::Vector2<size_t>((unsigned int)this->currentTile.x * TILESIZE.x + 8, (unsigned int)this->currentTile.y * TILESIZE.y + 8))
			currentNode = &node;

	while (true)
	{
		for (pathNode &node : openPathNodes)
		{
			if (node.F < minF)
			{
				currentNode = &node;
				minF = node.F;
			}
		}
		minF = 999;
		break;
	}
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
	size_t mapSize = 16;
	for (size_t y = 0; y < mapSize; ++y)
		for (size_t x = 0; x < mapSize; ++x)
		{
		currentNode.selfPos = sf::Vector2<size_t>(x * TILESIZE.x + 8, y * TILESIZE.y + 8);
		if (level[y * mapSize + x] != 0)
		{
			currentNode.G = 999;
			currentNode.H = 999;
		}
		else
		{
			currentNode.G = std::sqrt(abs(this->getPos().x - currentNode.selfPos.x) * abs(this->getPos().x - currentNode.selfPos.x) + abs(this->getPos().y - currentNode.selfPos.y) * abs(this->getPos().y - currentNode.selfPos.y));
			currentNode.H = 0;
		}
		currentNode.F = currentNode.G + currentNode.H;
		this->pathLevel.push_back(currentNode);
		}

	for (size_t y = 1; y < mapSize - 1; ++y)
		for (size_t x = 1; x < mapSize - 1; ++x)
		{
			// Adding 4 neighbours
			// Left neighbour
			std::reference_wrapper<pathNode> neighbour = this->pathLevel[y * mapSize + x - 1];
			this->pathLevel[y * mapSize + x].neighbours.push_back(neighbour);
			// Top neighbour
			neighbour = this->pathLevel[(y - 1) * mapSize + x];
			this->pathLevel[y * mapSize + x].neighbours.push_back(neighbour);
			// Right neighbour
			neighbour = this->pathLevel[y * mapSize + x + 1];
			this->pathLevel[y * mapSize + x].neighbours.push_back(neighbour);
			// Bottom neighbour
			neighbour = this->pathLevel[(y + 1) * mapSize + x];
			this->pathLevel[y * mapSize + x].neighbours.push_back(neighbour);
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
	if (dirX > 0.f) this->sprite.setTexture(textureRight);
	else if (dirX < 0.f) this->sprite.setTexture(textureLeft);
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Enemy::update(float delta)
{
	this->currentTile = sf::Vector2i((int)((float)(sprite.getPosition().x) / 16), (int)((float)(sprite.getPosition().y) / 16));
	std::cout << "tileX: " << this->currentTile.x << ", tileY: " << this->currentTile.y << "\tX: " << this->getPos().x << ", Y: " << this->getPos().y << std::endl;
	if (seenPlayer != nullptr)
	{
		this->movementSpeed = RUN_SPEED;
		this->pathfind(seenPlayer->getPos() , this->pathLevel, delta);
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
