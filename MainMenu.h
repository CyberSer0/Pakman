#pragma once
#include "Scene.h"
#include "Game.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#define MAX_MAINMENU_BUTTONS 5
#define FONT_SIZE 16

class MainMenu : protected Scene
{
	// Private Sector
private:

	sf::Font font;
	sf::Text mainMenu[MAX_MAINMENU_BUTTONS];
	sf::Event event;

	sf::RectangleShape selectionRect;

	void initFont();
	void initVariables();
	void initView();
	void initButtons();

	void SelectUp();
	void SelectDown();

	// Public Sector
public:
	bool menuState;
	int buttonSelected;

	sf::View view;

	MainMenu();
	virtual ~MainMenu();

	sf::View letterBox(sf::View view, float width, float height);

	void updateEvents();
	void update();
	void render();

	int MainMenuPressed();

	const bool isRunning() const;
	sf::RenderWindow* getWindow();
};

