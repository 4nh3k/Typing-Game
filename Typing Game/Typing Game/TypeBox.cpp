#include "TypeBox.h"
#define DELETE_KEY 8
#define ENTER_KEY 13
#define SPACE_KEY 32
#define sz(a) (int)a.size()

TypeBox::TypeBox(Vector2f pos, Color color, string name)
{
	initVariables();
	initFont();
	this->name.setString(name);
	initText(pos);
	initBorder(pos, color);
}

void TypeBox::setSelected(bool sel)
{
	selected = sel;
	if (!sel) text.setString(strtext.str());
	else text.setString(strtext.str() + '_');
}

string TypeBox::getText()
{
	return string(strtext.str());
}

void TypeBox::updateText(Event event)
{
	if (!selected) return;
	int charType = event.text.unicode;
	if (charType < 128)
	{
		if (!hasLimit) inputLogic(charType);
		else
			if (charType == ENTER_KEY) setSelected(false);
			else
			if (sz(strtext.str()) < limit || charType == DELETE_KEY)
				inputLogic(charType);
	}
}

void TypeBox::renderText(RenderWindow& window)
{
	//string temp = text.getString();
	window.draw(border);
	window.draw(text);
	window.draw(name);
}

void TypeBox::setStr(string s)
{
	strtext.str("");
	text.setString("");
}

FloatRect TypeBox::getBounds()
{
	return border.getGlobalBounds();
}

void TypeBox::initVariables()
{
	strtext.str("");
	hasLimit = true;
	limit = 15;
	selected = false;
}

void TypeBox::initFont()
{
	font.loadFromFile("textBoxFont/arial.ttf");
}

void TypeBox::initText(Vector2f pos)
{
	text.setFont(font);
	if (selected) text.setString("_");
	else text.setString("");
	text.setCharacterSize(22);
	text.setFillColor(Color::Black);
	text.setPosition(pos.x + 1.f, pos.y + 0.5f);

	name.setFont(font);
	name.setCharacterSize(23);
	name.setFillColor(Color(82, 74, 78));
	name.setOrigin(name.getLocalBounds().width, 0);
	name.setPosition(pos.x - 13.f, pos.y + 4.f);
}

void TypeBox::initBorder(Vector2f pos, Color color)
{
	border.setPosition(pos);
	border.setSize(Vector2f(300.f, 40.f));
	border.setFillColor(color);
	border.setOutlineThickness(5.f);
	border.setOutlineColor(Color::White);
}

void TypeBox::inputLogic(int charType)
{
	if (charType == ENTER_KEY)
	{
		setSelected(false);
	}
	if (charType != DELETE_KEY && charType != SPACE_KEY) strtext << static_cast<char>(charType);
	else if (charType == DELETE_KEY && sz(strtext.str()) > 0) delLastChar();
	text.setString(strtext.str() + "_");
}

void TypeBox::delLastChar()
{
	string t = strtext.str();
	strtext.str("");
	strtext << t.substr(0, sz(t) - 1);
}
