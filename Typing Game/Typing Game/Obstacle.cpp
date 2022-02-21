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
	this->speed = speed;
	this->text.setString(txt);
	this->text.setPosition(pos.x, pos.y - 80);
	textureSize = texture.getSize();
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update(float deltaTime)
{
	//cout << "!!!!!\n";
	this->move(-(speed * deltaTime), 0);
	this->text.move(-(speed * deltaTime), 0);

}

void Obstacle::render(RenderWindow* window)
{
	window->draw(*this);
	//string temp = text.getString();
	//cout << temp << '\n';
	window->draw(this->text);
}


void Obstacle::init(Font &font)
{
	text.setFont(font);
	text.setCharacterSize(52);
	text.setFillColor(Color::Blue);
}
