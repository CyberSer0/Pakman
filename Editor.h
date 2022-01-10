#pragma once
#include "Tilemap.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <stdio.h>
#include <chrono>

#define MAX_EDITOR_BUTTONS 4

class Editor : public sf::Drawable
{
private:
	std::ofstream outputFile;
	size_t mapSize;
	Tilemap tilemap;
	std::vector<size_t> level;
	sf::Event event;

	sf::Font font;
	sf::Text editorOptions[MAX_EDITOR_BUTTONS];
	sf::VideoMode videoMode;

	sf::Texture selectionTexture;
	sf::Sprite selectionSprite;
	sf::Vector3<size_t> selectedTile;
	bool selectionMoveable;

	void initVariables();
	void initView();
	void initGrid();
	void updateGrid(sf::Vector2<size_t> changedTile, size_t value);
	void saveMap();
public:
	bool editorState;
	Editor();
	virtual ~Editor();

	sf::View view;
	sf::View letterBox(sf::View view, float width, float height) const;

	bool isRunning() const;
	void resetEditor();

	void update(sf::RenderWindow& target);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

