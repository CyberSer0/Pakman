#include "MainMenu.h"
#include "Game.h"
#include <windows.h>


int main()
{
	sf::RenderWindow* mainWindow = new sf::RenderWindow(sf::VideoMode(640, 480), "Pakman");

	// Init Game
	MainMenu mainMenu(mainWindow);
	Game game(mainWindow);

	// Loop
	while (mainWindow->isOpen()) 
	{
		// Main menu loop when main menu is running
		if (mainMenu.isRunning())
		{
			// Update logic
			mainMenu.update();

			// Render graphics
			mainMenu.render();


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				if (mainMenu.buttonSelected == 1)
				{
					game = Game(mainWindow);
				}
				else if (mainMenu.buttonSelected == 4)
				{
					mainWindow->close();
					return 0;
				}
		}

		// Game loop when game is running
		else if (game.gameRunning())
		{
			// Update logic
			game.update();

			// Render graphics
			game.render();
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				mainMenu = MainMenu(mainWindow);
				//game.~Game();
			}
		}
	}
}
