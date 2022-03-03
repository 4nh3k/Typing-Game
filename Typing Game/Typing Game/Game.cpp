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
	if(hasStart==true)
	{
		Player.Update(deltaTime);
		updateBackground();
		updateObstacle();
		updateText();
	}
}

void Game::render()
{
	this->window->clear(Color(253, 239, 244));
	
	//Draw game objects here
	this->window->draw(Player);
	renderBackground();
	renderText();
	renderObstacles();
	this->window->display();
}

#pragma endregion

#pragma region Initialization

void Game::initVariables()
{
	hasStart = false;
	health = 5;
	points = 0;
	WINDOW_HEIGHT = 700;
	WINDOW_WIDTH = 1400;
	SPEED = 350; 
	player.loadFromFile("../Data/run.png");
	background.loadFromFile("../Data/background.png");
	b1 = Background(background, SPEED, Vector2f(0, 500));
	b2 = Background(background, SPEED, Vector2f(background.getSize().x, 500));
	Player = Animation(player, Vector2i(3, 1), Vector2f(5.f, 430.f), 0.1);
	maxObs = 6;
	spawnObTimer = 0;
	spawnObTimerMax = 90;
	timerMax = 100;
	timerMin = 80;
	window = nullptr;
}

void Game::initWindow()
{
	window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Typing Corona", Style::Close | Style::Titlebar);
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
			if(sz(cur) > 2) texts.push_back(cur);
			cur = "";
		}
		else cur += s[i];
	}
	numOfTexts = sz(texts);
	fi.close();

	this->uiText.setFont(this->font);
	this->uiText.setFillColor(Color(82, 74, 78));
	this->uiText.setCharacterSize(24);
	this->uiText.setPosition(470.f, 300.f);
	this->uiText.setString("PRESS ENTER TO START");
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
			if (event.key.code == Keyboard::Escape)
				this->window->close();
			else if (event.key.code == Keyboard::Enter)
			{
				hasStart = true;
				textbox.setSelected(true); 
			}
			break;
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
	if (hasStart)
	{
		uiText.setPosition(2.f, 5.f);
		stringstream ss;
		ss << "Point: " << points << '\n'
			<< "Health: " << health << '\n';
		this->uiText.setString(ss.str());
	}
}

void Game::setDeltaTime(float deltaTime)
{
	this->deltaTime = deltaTime;
}

void Game::spawnOb()
{
	/// <summary>
	/// vui thì code giùm cái random hình đi :< 
	/// hình có trong Data hết rồi á 
	/// </summary>
	human.loadFromFile("../Data/pp1.png");
	string cur = texts[Rand(0, numOfTexts - 1)];
	ob = Obstacle(human, SPEED, Vector2f(1390.f, 430.f), (String)cur, font);
	obs.push_back(ob);
}

void Game::updateBackground()
{
	b1.Update(deltaTime);
	b2.Update(deltaTime);
}

void Game::updateObstacle()
{
	if (textbox.isDone == true)
	{
		if (obs.front().text.getString() == textbox.getText())
		{
			obs.pop_front();
			points += 1;
		}
	}

	/// <summary>
	/// Chỉnh cho kim biến mất lúc gặp corona ở đây nè
	/// </summary>
	for (auto o : obs)
	{
		FloatRect playerBox = Player.getGlobalBounds();
		FloatRect objectBox = o.getGlobalBounds();
		if ((o.getPosition().x <= 0)||playerBox.intersects(objectBox))
		{
			obs.pop_front(), health -= 1; 
			if (health == 0)
			{
				isEnd = true;
				return;
			}
		}
	}


	if (sz(obs) < maxObs)
	{
		if (spawnObTimer == spawnObTimerMax)
		{
			spawnOb();
			/// <summary>
			/// đống này để nhanh dần thoi
			/// </summary>
			if (timerMin > 35) timerMin--;
			else if (timerMax > 55) timerMax--;

			spawnObTimer = 0;
			spawnObTimerMax = Rand(timerMin, timerMax);
		}
		else spawnObTimer += 1;
	}
}

#pragma endregion

#pragma region Render

void Game::renderText()
{
	textbox.renderText(*this->window);
	window->draw(uiText);
}

void Game::renderBackground()
{
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



