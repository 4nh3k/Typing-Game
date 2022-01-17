#pragma once
#pragma region Libararies and Namespaces

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include "Animation.h"

using namespace std;
using namespace sf;

#pragma endregion

class Game
{
private:
	// something for window
	RenderWindow* window;
	Event event;
	Font font;
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	Texture run;
	Animation player;
	float deltaTime;
	
	// Game logic
	unsigned points;
	bool isEnd;

	// functions for game initialization
	void initVariables();
	void initWindow();
	void initFontandText();

	// functions for game running
	void pollEvents();
	void updateMousePos();
	void updateText();
	void renderText();

public:
	//instructor, destructor
	Game();
	virtual ~Game();
	void update();
	void render();
	void setDeltaTime(float deltaTime);
	const bool isRunning() const;
	const bool endGame() const;
};