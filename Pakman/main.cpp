#include "Game.h"
#include <windows.h>


int main() 
{
	// Init Game
	Game game;

	// Loop
	while (game.gameRunning())
	{
		// Update
		game.update();

		// Render
		game.render();
	}
}