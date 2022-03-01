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
#include <sstream>
#include "Animation.h"
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
	Event event;
	Font font;
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;
	Texture background;
	Texture human;
	Texture player;
	Animation Player;
	Background b1;
	Background b2;
	Obstacle ob;
	deque <Obstacle> obs;
	bool hasStart;
	Text uiText;
	// Game logic
	unsigned health;
	int SPEED;
	int maxObs;
	int spawnObTimer, spawnObTimerMax, timerMin, timerMax;
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
	void updateBackground();
	void renderText();
	void renderBackground();
	void renderObstacles();
	void spawnOb();
	void updateObstacle();

	//others
	int Rand(int l, int r);
public:
	RenderWindow* window;
	unsigned points;

	//instructor, destructor
	Game();
	virtual ~Game();
	void update();
	void render();
	void setDeltaTime(float deltaTime);
	const bool isRunning() const;
	const bool endGame() const;
};