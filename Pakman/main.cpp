#include "Game.h"
#include <windows.h>


int main() 
{
	// Hide console window
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);

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