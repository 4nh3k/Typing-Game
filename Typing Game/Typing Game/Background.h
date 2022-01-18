#pragma once
#include "SFML/Graphics.hpp"

class Background : public sf::Sprite
{
public:
	Background();
	Background(sf::Texture &texture, int SPEED,sf::Vector2f pos);
	~Background();
	void Update(float deltaTime);

private:
	int SPEED;
	int cmp;
	sf::Vector2u textureSize;
	sf::Texture texture;
	sf::Vector2f pos;
};
