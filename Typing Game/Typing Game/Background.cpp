#include "Background.h"
#include <iostream>
Background::Background()
{
}

Background::Background(sf::Texture &texture, int SPEED, sf::Vector2f pos)
{
	this->setOrigin(sf::Vector2f(0, 0));
	this->setPosition(pos);
	this->setTexture(texture);
	this->SPEED = SPEED;
	this->pos = pos;
	textureSize = texture.getSize();
	cmp = 0 - textureSize.x;
	std::cout << cmp;
}

Background::~Background()
{
}

void Background::Update(float deltaTime)
{
	if (this->getPosition().x < cmp)
	{
		//std::cout << "wtf";
		this->setPosition(sf::Vector2f(textureSize.x, pos.y));
	}
	this->move(-(SPEED * deltaTime), 0);
}
