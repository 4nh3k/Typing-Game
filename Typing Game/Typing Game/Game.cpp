#include "Game.h"

#pragma region Public Functions

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
	updateText();
}

void Game::render()
{
	this->window->clear(Color::Black);

	//Draw game objects here


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
			if (event.key.code == Keyboard::Escape) this->window->close(); break;
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

}

#pragma endregion

#pragma region Render

void Game::renderText()
{

}
#pragma endregion



