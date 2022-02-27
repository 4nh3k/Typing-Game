#include "Obstacle.h"

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(Texture& texture, int speed, Vector2f pos, String txt, Font &font)
{
	init(font);
	setOrigin(Vector2f(0, 0));
	setPosition(pos);
	setTexture(texture);
	textureSize = texture.getSize();
	this->pos = pos;
	this->speed = speed;
	this->text.setString(txt);
	this->text.setPosition(pos.x, pos.y - 50);
	setScale(2.f, 2.f);
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update(float deltaTime)
{
	this->move(-(speed * deltaTime), 0);
	this->text.move(-(speed * deltaTime), 0);
}

void Obstacle::render(RenderWindow* window)
{
	window->draw(*this);
	window->draw(this->text);
}


void Obstacle::init(Font &font)
{
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(Color(101, 193, 140));
}
