#include "MainMenu.h"

//Private Methods
void MainMenu::initFont()
{
	if (!font.loadFromFile("Assets/Fonts/PressStart2P-Regular.ttf"))
	{
		std::cout << "[!] ERR::" << this << "::INITFONT(): " << this << " font couldn't be loaded\n" << std::endl;
	}
}

void MainMenu::initVariables()
{
	//std::cout << this << "\tMain Menu window:\t" << this->window << "\tView:\t" << &(this->window->getView()) << std::endl;
	this->buttonSelected = 1;
	this->selectionRect.setFillColor(sf::Color(0, 0, 0, 0));
	this->selectionRect.setOutlineColor(sf::Color::White);
	this->selectionRect.setOutlineThickness(2);
}

void MainMenu::initView()
{
	this->view.setCenter((float)this->videoMode.width / 2, (float)this->videoMode.height / 2);
	this->view.zoom(0.5f);
}

void MainMenu::initButtons()
{
	// Pakman Logo
	this->mainMenu[0].setFont(this->font);
	this->mainMenu[0].setFillColor(sf::Color::White);
	this->mainMenu[0].setString("PAKMAN");
	this->mainMenu[0].setCharacterSize(FONT_SIZE + 20);
	this->mainMenu[0].setPosition((float)this->videoMode.width / 2, (float)this->videoMode.height / 2 - 200);
	this->mainMenu[0].setOrigin(mainMenu[0].getCharacterSize() * (float)mainMenu[0].getString().getSize() / 2, (float)mainMenu[0].getCharacterSize() / 2);

	// Play Button
	this->mainMenu[1].setFont(this->font);
	this->mainMenu[1].setFillColor(sf::Color::White);
	this->mainMenu[1].setString("Play");
	this->mainMenu[1].setCharacterSize(FONT_SIZE);
	this->mainMenu[1].setPosition((float)this->videoMode.width / 2, (float)this->videoMode.height / 2 - 40);
	this->mainMenu[1].setOrigin(FONT_SIZE * (float)mainMenu[1].getString().getSize() / 2, FONT_SIZE / 2);

	// Editor Button
	this->mainMenu[2].setFont(this->font);
	this->mainMenu[2].setFillColor(sf::Color::White);
	this->mainMenu[2].setString("Editor");
	this->mainMenu[2].setCharacterSize(FONT_SIZE);
	this->mainMenu[2].setPosition((float)this->videoMode.width / 2, (float)this->videoMode.height / 2 + 40);
	this->mainMenu[2].setOrigin(FONT_SIZE * (float)mainMenu[2].getString().getSize() / 2, FONT_SIZE / 2);

	// Exit Button
	this->mainMenu[3].setFont(this->font);
	this->mainMenu[3].setFillColor(sf::Color::White);
	this->mainMenu[3].setString("Exit");
	this->mainMenu[3].setCharacterSize(FONT_SIZE);
	this->mainMenu[3].setPosition((float)this->videoMode.width / 2, (float)this->videoMode.height / 2 + 120);
	this->mainMenu[3].setOrigin(FONT_SIZE * (float)mainMenu[3].getString().getSize() / 2, FONT_SIZE / 2);
}

void MainMenu::SelectUp()
{
	if (this->buttonSelected > 1)
		this->buttonSelected--;
}

void MainMenu::SelectDown()
{
	if (this->buttonSelected < MAX_MAINMENU_BUTTONS - 1)
		this->buttonSelected++;
}

// Public Methods
MainMenu::MainMenu()
{
	this->menuState = true;
	initFont();
	initVariables();
	initView();
	initButtons();
}

MainMenu::~MainMenu()
{
	this->menuState = false;
}

sf::View MainMenu::letterBox(sf::View view, float width, float height) const
{
	float windowRatio = width / height;
	float viewRatio = view.getSize().x / view.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	if (windowRatio > viewRatio)
	{
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.f;
	}
	else
	{
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}

	view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
	return view;
}

void MainMenu::updateEvents(sf::RenderWindow& target)
{
	while (target.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			target.close();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			SelectUp();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			SelectDown();
	}
}

void MainMenu::update(sf::RenderWindow& target)
{
	this->updateEvents(target);
	this->selectionRect.setPosition(this->mainMenu[buttonSelected].getPosition().x - 1, this->mainMenu[buttonSelected].getPosition().y + 12.5f);
	this->selectionRect.setSize(sf::Vector2f(FONT_SIZE * (float)mainMenu[buttonSelected].getString().getSize() + 10, FONT_SIZE + 10));
	this->selectionRect.setOrigin(selectionRect.getSize().x / 2, selectionRect.getSize().y);
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.clear(sf::Color::Black);
	
	for (int i = 0; i < MAX_MAINMENU_BUTTONS; ++i)
		target.draw(this->mainMenu[i], states);
	
	target.setView(this->letterBox(this->view, (float)target.getSize().x, (float)target.getSize().y));
	target.draw(this->selectionRect, states);
}

int MainMenu::MainMenuPressed()
{
	return this->buttonSelected;
}

const bool MainMenu::isRunning() const
{
	return this->menuState;
}
