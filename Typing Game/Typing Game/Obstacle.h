#pragma once
#pragma region Libararies and Namespaces

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;
using namespace sf;

#pragma endregion

class Obstacle : public sf::Sprite
{
public:
	Obstacle();
	Obstacle(Texture& texture, int speed, Vector2f pos, String txt, Font &font);
	~Obstacle();
	void Update(float deltaTime);
	void render(RenderWindow* window);
	void init(Font &f);

private:
	int speed;
	Vector2u textureSize;
	Texture texture;
	Text text;
	Vector2f pos;
};