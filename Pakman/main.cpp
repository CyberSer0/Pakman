#include "MainMenu.h"
#include "Game.h"
#include <windows.h>


int main()
{
	// Init Game
	MainMenu mainMenu;
	Game game = Game(mainMenu.getWindow());

	// Loop
	do {
		// Main menu loop when main menu is running
		if (mainMenu.isRunning())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				if (mainMenu.buttonSelected == 1)
				{
					mainMenu.menuState = false;
					game.gameState = true;
					game.initMap();
				}
				else if (mainMenu.buttonSelected == 4)
				{
					return 0;
				}

			// Update logic
			mainMenu.update();

			// Render graphics
			mainMenu.render();
		}

		// Game loop when game is running
		else if (game.gameRunning())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				mainMenu.~MainMenu();
				game.~Game();
				return 0;
				/*game.gameState = false;
				mainMenu.menuState = true;*/
			}

			// Update logic
			game.update();

			// Render graphics
			game.render();
		}
		else 
		{
			break;
		}
	} while (1);
}
