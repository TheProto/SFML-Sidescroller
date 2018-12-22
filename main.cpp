#include "Box2D/Box2D.h"
#include <iostream>
#include <SFML/Graphics.hpp>

//#include "StateMachine.h"
//#include "AssetManager.h"
//#include "InputManager.h"

#include "Engine/Game.h"

int main(int argc, char* argv[])
{
	ProtoEngine::Game(800, 600, "SFML Starter");
	/*
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			printf("Test commit!\n");

			sf::sleep(sf::seconds(3));
			window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	*/



	return EXIT_SUCCESS;
	system("PAUSE");

	return 0;
} 