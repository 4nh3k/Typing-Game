#include "Game.h"
#include "TextBox.h"

#pragma region Public Functions
TextBox textbox;

Game::Game()
{
	initVariables();
	initWindow();
	//initFontandText();
}

Game::~Game()
{
	delete window;
}

const bool Game::isRunning() const
{
	return window->isOpen();
}

const bool Game::endGame() const
{
	return isEnd;
}

void Game::update()
{
	pollEvents();
	updateMousePos();
}

void Game::render()
{
	this->window->clear(Color::Black);

	//Draw game objects here
	renderText();

	this->window->display();
}

#pragma endregion

#pragma region Initialization

void Game::initVariables()
{
	window = nullptr;
}

void Game::initWindow()
{
	window = new RenderWindow(VideoMode(800, 800), "Typing racing", Style::Close | Style::Titlebar);
	window->setFramerateLimit(60);
}

void Game::initFontandText()
{
	
}

#pragma endregion

#pragma region Update

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case Event::Closed:
			this->window->close(); break;
		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape) this->window->close();
			else if (event.key.code == Keyboard::Enter) textbox.setSelected(true);  break;
		case Event::TextEntered: textbox.updateText(event); break;
		}
	}
}

void Game::updateMousePos()
{
	mousePosWindow = Mouse::getPosition();
	mousePosView = this->window->mapPixelToCoords(mousePosWindow);
}

void Game::updateText()
{
	textbox.updateText(event);
}

#pragma endregion

#pragma region Render

void Game::renderText()
{
	textbox.renderText(*this->window);
}
#pragma endregion



