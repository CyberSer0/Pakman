#include "MainMenu.h"
#include "Game.h"
#include <iostream>
#include <windows.h>


int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Pakman");
	
	// Delta time clock
	sf::Clock deltaClock;

	// Init Scenes
	MainMenu mainMenu;
	Game game;

	// Loop
	while (mainWindow.isOpen()) 
	{
		float delta = deltaClock.restart().asSeconds();

		// Main menu loop when main menu is running
		if (mainMenu.isRunning())
		{

			// Render graphics
			mainWindow.draw(mainMenu);

			// Update logic
			mainMenu.update(mainWindow);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				if (mainMenu.buttonSelected == 1)
				{
					mainMenu.menuState = false;
					game.resetGame();
					game.gameState = true;
				}
				else if (mainMenu.buttonSelected == 3)
				{
					mainWindow.close();
					return 0;
				}
		}

		// Game loop when game is running
		else if (game.gameRunning())
		{

			// Render graphics
			mainWindow.draw(game);
			
			// Update logic
			game.update(mainWindow, delta);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				mainMenu.menuState = true;
				game.gameState = false;
			}
		}

		mainWindow.setFramerateLimit(60);
		mainWindow.setVerticalSyncEnabled(true);
		mainWindow.display();
	}
}