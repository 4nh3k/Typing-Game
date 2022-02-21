#include "Game.h"
#include "TextBox.h"
#include "Background.h"
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
	spawnOb();
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
	maxObs = 1;
	spawnObTimer = 0;
	spawnObTimerMax = 100;
	window = nullptr;
}

void Game::initWindow()
{
	window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Typing racing", Style::Close | Style::Titlebar);
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

void Game::setDeltaTime(float deltaTime)
{
	this->deltaTime = deltaTime;
}

void Game::spawnOb()
{
	Obstacle ob;
	Font f;
	f.loadFromFile("../Data/font.ttf");
	human.loadFromFile("../Data/pp1.png");
	ob = Obstacle(human, 300, Vector2f(1350.f, 470.f), String("test"), font);
	if (spawnObTimer < spawnObTimerMax) spawnObTimer++;
	else if (sz(obs) < maxObs)
	{
		spawnObTimer = 0;
		obs.push_back(ob);
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
	for (auto o : obs)
	{
		//cout << "?????\n";
		o.Update(deltaTime);
	}
	for (auto o : obs) o.render(window);
}

#pragma endregion



