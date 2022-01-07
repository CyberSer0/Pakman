#include "MainMenu.h"
#include "Game.h"
#include <windows.h>


int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(640, 480), "Pakman");

	// Init Game
	MainMenu mainMenu;
	Game game;

	// Loop
	while (mainWindow.isOpen()) 
	{
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
					game = Game();
					game.gameState = true;
				}
				else if (mainMenu.buttonSelected == 4)
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
			game.update(mainWindow);

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