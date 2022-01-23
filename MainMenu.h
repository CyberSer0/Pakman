#pragma once
#include "Game.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#define MAX_MAINMENU_BUTTONS 5
#define FONT_SIZE 16

class MainMenu : public sf::Drawable
{
	// Private Sector
private:
	sf::Font font;
	sf::Text mainMenu[MAX_MAINMENU_BUTTONS];
	sf::Event event;
	sf::VideoMode videoMode; // Creating videoMode object (holds the dimensions and other variables of the displayed window)

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

	sf::View letterBox(sf::View view, float width, float height) const;

	void updateEvents(sf::RenderWindow& target);
	void update(sf::RenderWindow& target);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int MainMenuPressed();

	const bool isRunning() const;
};

