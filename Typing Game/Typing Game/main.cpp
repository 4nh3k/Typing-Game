#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
using sf::Vector2f;
using sf::Event;
using std::cout;
using sf::Keyboard;

int const WINDOW_WIDTH = 700;
int const WINDOW_HEIGHT = 550;


int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Typing Corona", sf::Style::Close);
	
	sf::Clock clock;
	float deltaTime = 0.f;
	sf::Texture run;
	run.loadFromFile("../Data/run.png");

	Animation Player(run, sf::Vector2i(3, 1), 0.1f);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			
		}
		
		Player.Update(deltaTime);
		//ve gi thi cung ve duoi cai nay
		window.clear(sf::Color::White);

		window.draw(Player);
		// end the current frame
		window.display();
	}
    return 0;
}