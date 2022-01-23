#include "Editor.h"

void Editor::initVariables()
{
	if (!this->selectionTexture.loadFromFile("Assets/selection_texture.png"))
	{
		std::cout << "[!] ERR::" << this << "::EDITOR_SELECTIONTEXTURE(): " << this << " texture couldn't be loaded" << std::endl;
	}
	this->selectionSprite.setTexture(this->selectionTexture);
	this->selectionMoveable = true;
	this->selectedTile = sf::Vector3<size_t>(0, 0, 12);
	this->mapSize = 16;
}

void Editor::initView()
{
	this->view.setCenter((float)this->videoMode.width / 2 + TILESIZE.x / 2 * this->mapSize, (float)this->videoMode.height / 2 + TILESIZE.y / 2 * (this->mapSize - 1) + 8);
	this->view.zoom(0.3f);
}

void Editor::initGrid()
{
	this->level.clear();
	for (size_t i = 0; i < this->mapSize; ++i)
	{
		for (size_t j = 0; j < this->mapSize; ++j)
		{
			this->level.emplace_back(12);
		}
	}
	this->tilemap.loadMap("Assets/tileset.png", TILESIZE, this->level, this->mapSize, this->mapSize);
}

void Editor::updateGrid(sf::Vector2<size_t> changedTile, size_t value)
{
	for (size_t i = 0; i < this->mapSize; ++i)
	{
		for (size_t j = 0; j < this->mapSize; ++j)
		{
			if (changedTile.x == j && changedTile.y == i && value != 0)
				std::swap(this->level[changedTile.x + changedTile.y * this->mapSize], value);
		}
	}
	this->tilemap.loadMap("Assets/tileset.png", TILESIZE, this->level, this->mapSize, this->mapSize);
}

void Editor::saveMap()
{
	for (size_t i = 0; i < this->mapSize * this->mapSize; ++i) if (this->level[i] == 12) this->level[i] = 0;

	this->outputFile.open("Saves/SavedTileset" + std::to_string((unsigned  int)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()) + ".paksave");

	for (size_t i = 0; i < this->mapSize; ++i)
	{
		for (size_t j = 0; j < this->mapSize; ++j)
		{
			this->outputFile << std::setw(3) << this->level[j + i * this->mapSize];
		}
		this->outputFile << std::endl;
	}
	this->outputFile.close();
}

Editor::Editor()
{
	this->outputFile.open("");
	this->initVariables();
	this->initView();
	this->initGrid();
}

Editor::~Editor()
{
}

sf::View Editor::letterBox(sf::View view, float width, float height) const
{
	float windowRatio = width / height;
	float viewRatio = view.getSize().x / view.getSize().y;
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

bool Editor::isRunning() const
{
	return this->editorState;
}

void Editor::resetEditor()
{
	this->selectionSprite.setPosition(0, 0);
	this->initVariables();
	this->initGrid();
}

void Editor::update(sf::RenderWindow& target)
{
	while (target.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			target.close();
	
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && this->selectedTile.y > 0)
		{
			this->selectionSprite.setPosition(this->selectionSprite.getPosition().x, this->selectionSprite.getPosition().y - TILESIZE.y);
			this->selectedTile.y--;
			this->selectionMoveable = false;
			std::cout << "W pressed; ";
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && this->selectedTile.y < this->mapSize - 1)
		{
			this->selectionSprite.setPosition(this->selectionSprite.getPosition().x, this->selectionSprite.getPosition().y + TILESIZE.y);
			this->selectedTile.y++;
			this->selectionMoveable = false;
			std::cout << "S pressed; ";
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && this->selectedTile.x < this->mapSize - 1)
		{
			this->selectionSprite.setPosition(this->selectionSprite.getPosition().x + TILESIZE.x, this->selectionSprite.getPosition().y);
			this->selectedTile.x++;
			this->selectionMoveable = false;
			std::cout << "D pressed; ";
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && this->selectedTile.x > 0) 
		{
			this->selectionSprite.setPosition(this->selectionSprite.getPosition().x - TILESIZE.x, this->selectionSprite.getPosition().y);
			this->selectedTile.x--;
			this->selectionMoveable = false;
			std::cout << "A pressed; ";
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) || !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) this->selectionMoveable = true;
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) || !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) this->selectionMoveable = true;
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) || !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) this->selectionMoveable = true;
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) || !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) this->selectionMoveable = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) this->saveMap();
		//std::cout << "X: " << selectedTile.x << "\tY: " << selectedTile.y << "\tValue: " << selectedTile.z << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) this->updateGrid(sf::Vector2<size_t>(this->selectedTile.x, this->selectedTile.y), 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) this->updateGrid(sf::Vector2<size_t>(this->selectedTile.x, this->selectedTile.y), 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) this->updateGrid(sf::Vector2<size_t>(this->selectedTile.x, this->selectedTile.y), 3);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) this->updateGrid(sf::Vector2<size_t>(this->selectedTile.x, this->selectedTile.y), 4);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) this->updateGrid(sf::Vector2<size_t>(this->selectedTile.x, this->selectedTile.y), 5);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) this->updateGrid(sf::Vector2<size_t>(this->selectedTile.x, this->selectedTile.y), 6);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) this->updateGrid(sf::Vector2<size_t>(this->selectedTile.x, this->selectedTile.y), 7);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) this->updateGrid(sf::Vector2<size_t>(this->selectedTile.x, this->selectedTile.y), 8);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) this->updateGrid(sf::Vector2<size_t>(this->selectedTile.x, this->selectedTile.y), 9);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) this->updateGrid(sf::Vector2<size_t>(this->selectedTile.x, this->selectedTile.y), 10);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) this->updateGrid(sf::Vector2<size_t>(this->selectedTile.x, this->selectedTile.y), 12);

}

void Editor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.clear(sf::Color::Black);
	target.setView(this->letterBox(this->view, (float)target.getSize().x, (float)target.getSize().y));
	target.draw(this->tilemap);
	target.draw(this->selectionSprite);
}
