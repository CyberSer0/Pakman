#include "Game.h"
#include <Windows.h>
#include <shobjidl.h>

int WINAPI loadMapFromFile(Game& game, MainMenu& mainMenu, Editor& editor);

int main()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Pakman");
	
	// Delta time clock
	sf::Clock deltaClock;

	// Init Scenes
	MainMenu mainMenu;
	Game game;
//	if (argv != nullptr)
//		game.loadMap(*argv);
	Editor editor;

	// Loop
	while (mainWindow.isOpen())
	{
		if (mainWindow.hasFocus())
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
						editor.editorState = false;
						game.resetGame();
						game.gameState = true;
					}
					else if (mainMenu.buttonSelected == 2)
					{
						loadMapFromFile(game, mainMenu, editor);
					}
					else if (mainMenu.buttonSelected == 3)
					{
						mainMenu.menuState = false;
						game.gameState = false;
						editor.resetEditor();
						editor.editorState = true;
					}
					else if (mainMenu.buttonSelected == 4)
					{
						mainWindow.close();
						return 0;
					}
			}

			// Game loop when game is running
			else if (game.isRunning())
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
			else if (editor.isRunning())
			{
				// Render graphics
				mainWindow.draw(editor);

				// Update logic
				editor.update(mainWindow);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					mainMenu.menuState = true;
					editor.editorState = false;
				}
			}

			mainWindow.setFramerateLimit(60);
			mainWindow.setVerticalSyncEnabled(true);
			mainWindow.display();
		}
	}
	return 0;
}

int WINAPI loadMapFromFile(Game& game, MainMenu& mainMenu, Editor& editor)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			// Show the Open dialog box.
			hr = pFileOpen->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						mainMenu.menuState = false;
						editor.editorState = false;
						game.loadGameWithMap(pszFilePath);
						game.gameState = true;
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
	return 0;
}