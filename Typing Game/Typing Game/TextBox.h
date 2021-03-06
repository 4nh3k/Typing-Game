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

class TextBox
{
public:
	TextBox();
	Text text;
	//TextBox(int size, Color color, bool selected);
	bool isDone;
	void setSelected(bool sel);
	string getText();
	void updateText(Event event);
	void renderText(RenderWindow &window); 
	void setstr(string x);

private:
	Font font;
	ostringstream strtext;
	RectangleShape border;
	bool hasLimit, selected;
	string preText;
	int limit; //bao nhieeu ddaay nhir
	void initVariables();
	void initFont();
	void initText();
	void initBorder(); 

	bool valid(int x);
	void checkText();
	void inputLogic(int charType);
	void delLastChar();

};