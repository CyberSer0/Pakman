#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>

class Player : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget target, sf::RenderStates states) const;
};

int main() 
{
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Pakman");
	Player player;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(player);
		window.display();
	}
}