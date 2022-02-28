#include "HomeScreen.h"

HomeScreen::HomeScreen()
{
	initWindow();
	initFont();
	initText();
}

void HomeScreen::renderEndScreen(int points)
{
	stringstream ss;
	uiText[0].setString("GAME OVER!");
	uiText[0].setPosition(190.f, 125.f);

	ss << "Your point is: " << points;
	uiText[1].setString(ss.str());
	uiText[1].setCharacterSize(20);
	uiText[1].setPosition(193.f, 175.f);

	uiText[2].setString("                  If you want to play again,\nplease exit this and restart the program again :D");
	uiText[2].setCharacterSize(13);
	uiText[2].setPosition(107.f, 225.f);

	this->window->clear(Color(234, 153, 213));
	for (int i = 0; i < 3; ++i) window->draw(uiText[i]);
	window->display();
}

void HomeScreen::pollEvent()
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
		}
	}
}

const bool HomeScreen::running() const
{
	return window->isOpen();
}
