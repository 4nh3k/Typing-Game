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

class TypeBox
{
public:
	TypeBox(Vector2f pos, Color color, string name);
	void setSelected(bool sel);
	string getText();
	void updateText(Event event);
	void renderText(RenderWindow& window);
	void setStr(string s);
	FloatRect getBounds();
private:
	Font font;
	Text text, name;
	ostringstream strtext;
	RectangleShape border;
	bool selected;
	bool hasLimit;
	int limit;
	void initVariables();
	void initFont();
	void initText(Vector2f pos);
	void initBorder(Vector2f pos, Color color);

	void inputLogic(int charType);
	void delLastChar();
};