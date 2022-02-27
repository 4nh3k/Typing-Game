#include "Game.h"
#include "TextBox.h"
#include "Background.h"
#include <fstream>
#define _CRT_SECURE_NO_DEPRECATE

#pragma region Public Functions
TextBox textbox;

Game::Game()
{
	initVariables();
	initFontandText();
	initWindow();
}

Game::~Game()
{
	delete window;
}

int Game::Rand(int l, int r)
{
	return rand() % (r - l + 1) + l;
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
	updateObstacle();
}

void Game::render()
{
	this->window->clear(Color::White);
	
	//Draw game objects here
	renderBackground();
	renderText();
	renderObstacles();
	this->window->display();
}

#pragma endregion

#pragma region Initialization

void Game::initVariables()
{
	WINDOW_HEIGHT = 700;
	WINDOW_WIDTH = 1400;
	background.loadFromFile("../Data/background.png");
	b1 = Background(background, 300, Vector2f(0, 500));
	b2 = Background(background, 300, Vector2f(background.getSize().x, 500));
	maxObs = 4;
	spawnObTimer = 0;
	spawnObTimerMax = 30;
	timerMax = 150;
	timerMin = 100;
	window = nullptr;
}

void Game::initWindow()
{
	window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Typing racing", Style::Close | Style::Titlebar);
	window->setFramerateLimit(60);
}

void Game::initFontandText()
{
	font.loadFromFile("../Data/font.ttf");
	ifstream fi ("texts.txt");
	string s, cur = "";
	fi >> s;
	for (int i = 0; i < sz(s); ++i)
	{
		if (s[i] == '|')
		{
			texts.push_back(cur);
			cur = "";
		}
		else cur += s[i];
	}
	numOfTexts = sz(texts);
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

void Game::setDeltaTime(float deltaTime)
{
	this->deltaTime = deltaTime;
}

void Game::spawnOb()
{
	human.loadFromFile("../Data/pp1.png");
	string cur = texts[Rand(0, numOfTexts - 1)];
	ob = Obstacle(human, 300, Vector2f(1390.f, 430.f), (String)cur, font);
	obs.push_back(ob);
}

void Game::updateObstacle()
{
	for (auto o : obs)
		if (o.getPosition().x <= 0) obs.pop_front();
	if (sz(obs) < maxObs)
	{
		if (spawnObTimer == spawnObTimerMax)
		{
			spawnOb();
			if (timerMin > 70) timerMin--;
			else if (timerMax > 90) timerMax--;
			spawnObTimer = 0;
			spawnObTimerMax = Rand(timerMin, timerMax);
			cout << timerMax << " " << timerMin << " " << spawnObTimerMax << '\n';
		}
		else spawnObTimer += 1;
	}
}

#pragma endregion

#pragma region Render

void Game::renderText()
{
	textbox.renderText(*this->window);
}

void Game::renderBackground()
{
	b1.Update(deltaTime);
	b2.Update(deltaTime);
	this->window->draw(b1);
	this->window->draw(b2);
}
void Game::renderObstacles()
{
	for (auto &o : obs)
	{
		o.Update(deltaTime);
	}
	for (auto o : obs) o.render(window);
}

#pragma endregion



