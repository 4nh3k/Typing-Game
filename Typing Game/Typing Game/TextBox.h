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

using namespace std;
using namespace sf;

#pragma endregion

class TextBox
{
public:
	TextBox();
	Text text;
	//TextBox(int size, Color color, bool selected);

	void setSelected(bool sel);
	string getText();
	void updateText(Event event);
	void renderText(RenderWindow &window); 

private:
	Font font;
	ostringstream strtext;
	bool hasLimit, selected;
	int limit;

	void initVariables();
	void initFont();
	void initText();

	bool valid(int x);
	void checkText();
	void inputLogic(int charType);
	void delLastChar();

};