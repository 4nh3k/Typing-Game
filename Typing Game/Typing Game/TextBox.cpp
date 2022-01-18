#include "TextBox.h"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define SPACE_KEY 32
#define sz(a) (int)a.size()

using namespace std;
using namespace sf;

TextBox::TextBox()
{
	initVariables();
	initFont();
	initText();
}

void TextBox::setSelected(bool sel)
{
	selected = sel;
	if (!sel) text.setString(strtext.str());
	else text.setString(strtext.str() + "_");
}

string TextBox::getText()
{
	return strtext.str();
}

void TextBox::updateText(Event event)
{
	if (!selected) return;
	int charType = event.text.unicode;
	if (charType < 128)
	{
		if (!hasLimit) inputLogic(charType);
		else 
			if (sz(strtext.str()) < limit || charType == DELETE_KEY || charType == SPACE_KEY)
				inputLogic(charType);
	} 
}

void TextBox::renderText(RenderWindow &window)
{
	string temp = text.getString();
	window.draw(text);
}


void TextBox::initVariables()
{
	strtext.str("");
	hasLimit = true;
	limit = 25;
	selected = false;
}

void TextBox::initFont()
{
	font.loadFromFile("textBoxFont/arial.ttf");
}

void TextBox::initText()
{
	text.setFont(font);
	if (selected) text.setString("_");
	else text.setString("");
	text.setCharacterSize(25);
	text.setFillColor(Color::Black);
	text.setPosition(Vector2f(300.f, 300.f));
}

bool TextBox::valid(int x)
{
	if ((x >= 65 && x <= 90) || (x >= 97 && x <= 122)) return true;
	if (x == DELETE_KEY || x == SPACE_KEY) return true;
	if (x == 44 || x == 46 || x == 58 || x == 59) return true;
	return false;
}

void TextBox::checkText()
{
	cout << strtext.str() << '\n';
}

void TextBox::inputLogic(int charType)
{
	if (charType == SPACE_KEY)
	{
		checkText();
		strtext.str("");
		text.setString("_");
		return;
	}
	if (charType != DELETE_KEY && charType != ENTER_KEY) strtext << static_cast<char>(charType);
	else if (charType == DELETE_KEY && sz(strtext.str()) > 0) delLastChar();
	text.setString(strtext.str() + "_");
}

void TextBox::delLastChar()
{
	string t = strtext.str();
	strtext.str("");
	strtext << t.substr(0, sz(t) - 1);
}

