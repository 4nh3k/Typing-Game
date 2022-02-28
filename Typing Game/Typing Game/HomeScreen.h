#pragma once
#pragma once

#pragma region Libararies and Namespaces

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

using namespace std;
using namespace sf;

#pragma endregion

class HomeScreen
{
private:
	Event event;
	Font font;
	Text uiText;

	void initWindow();
	void initFont();
	void initText();

public:
	RenderWindow* window;
	HomeScreen();
	virtual ~HomeScreen();
	void renderEndScreen(int points);
	void pollEvent();
	const bool running() const;
};