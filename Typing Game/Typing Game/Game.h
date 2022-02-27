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
#include <deque>
#include <random>
#include <chrono>
#include <cassert>
#include "Background.h"
#include "Obstacle.h"

#define sz(a) (int)a.size()
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
	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;
	Texture background;
	Texture human;
	Background b1;
	Background b2;
	Obstacle ob;
	deque <Obstacle> obs;

	// Game logic
	unsigned points;
	int maxObs;
	int spawnObTimer, spawnObTimerMax;
	bool isEnd;
	float deltaTime;
	vector <string> texts;
	int numOfTexts;

	// functions for game initialization
	void initVariables();
	void initWindow();
	void initFontandText();

	// functions for game running
	void pollEvents();
	void updateMousePos();
	void updateText();
	void renderText();
	void renderBackground();
	void renderObstacles();
	void spawnOb();
	void updateObstacle();

	//others
	int Rand(int l, int r);
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