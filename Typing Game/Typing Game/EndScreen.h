#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;

class EndScreen
{
public:
	RenderWindow* window;
	EndScreen(int p = 0) : points(p) { init(); }
	~EndScreen() 
	{
		delete window;
	}

	const bool isRunning() const
	{
		return window->isOpen();
	}

	bool update()
	{
		return pollEvents();
	}

	void render()
	{
		window->clear(Color(253, 239, 244));
		window->draw(text[0]);
		window->draw(text[1]);
		window->draw(_again);
		window->display();
	}

private:
	int points;
	Font font;
	Text text[2];
	Event event;
	Texture again;
	Sprite _again;
	void init()
	{
		font.loadFromFile("../Data/font.ttf");
		for (int i = 0; i <= 1; ++i)
		{
			text[i].setFont(font);
			text[i].setFillColor(Color(82, 74, 78));
		}
		text[0].setCharacterSize(20);
		text[1].setCharacterSize(18);

		text[0].setString("GAME OVER");
		stringstream ss;
		ss << "YOUR POINTS IS: " << points;
		text[1].setString(ss.str());

		text[0].setOrigin(text[0].getLocalBounds().width / 2, text[0].getLocalBounds().height / 2);
		text[1].setOrigin(text[1].getLocalBounds().width / 2, text[1].getLocalBounds().height / 2);

		text[0].setPosition(250,200);
		text[1].setPosition(250, 250);

		window = new RenderWindow(VideoMode(500, 500), "Typing Corona", Style::Close | Style::Titlebar);
		window->setFramerateLimit(60);

		again.loadFromFile("../Data/back.png");
		_again = Sprite(again);
		_again.setOrigin(_again.getLocalBounds().width / 2, _again.getLocalBounds().height / 2);
		_again.setPosition(250, 350);
	}

	bool pollEvents()
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
			case Event::MouseButtonPressed:
				if (event.key.code == Mouse::Left)
				{
					Vector2i mousePosWindow = Mouse::getPosition(*window);
					Vector2f mousePosView = window->mapPixelToCoords(mousePosWindow);
					if (_again.getGlobalBounds().contains(mousePosView))
						return true;
				} break;
			}
		}
		return false;
	}

};