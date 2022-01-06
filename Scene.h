#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Scene
{
// Protected Sector (Extended can access; Outsider can't)
protected:
	// Window
	sf::RenderWindow* window; // Creating window object
	sf::VideoMode videoMode; // Creating videoMode object (holds the dimensions and other variables of the displayed window)

	void initVariables();
	void initWindow(); // Function to initialize the window and all it's functionality
	void initWindow(sf::RenderWindow* window); // Function to initialize the window and all it's functionality

// Public sector (Everyone can access)
public:
	Scene();
	Scene(sf::RenderWindow* window);
	virtual ~Scene();

	sf::RenderWindow* getWindow();
};

