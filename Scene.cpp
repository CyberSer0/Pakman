#include "Scene.h"

// Private Methods
void Scene::initVariables()
{
	//this->window = nullptr;
}

void Scene::initWindow()
{
	this->videoMode.height = 480;
	this->videoMode.width = 640;

	this->window = new sf::RenderWindow(this->videoMode, "Pakman");
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(true);
}

void Scene::initWindow(sf::RenderWindow* window)
{
	this->videoMode.height = 480;
	this->videoMode.width = 640;

	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);
}

// Public Methods
Scene::Scene()
{
	std::cout << "Default constructor" << std::endl;
	initVariables();
	initWindow();
}

Scene::Scene(sf::RenderWindow* window)
{
	std::cout << "Parameter constructor" << std::endl;
	initWindow(window);
	this->window = window;
}

Scene::~Scene()
{
	
}

sf::RenderWindow* Scene::getWindow()
{
	return this->window;
}