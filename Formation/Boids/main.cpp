#include <iostream>
#include <vector>
#include "Boid.h"
#include "Pvector.h"
#include "spring.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <string>
using namespace std;

/*
Brief description of Boid Class:
// This file acts as the main for our boids project. Here, we utilize the SFML
// library, import boids and flock classes, and run the program.-
*/

int main()
{


	//Gets the resolution, size, and bits per pixel for the screen of the PC that is running this program.
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	const int window_height = desktop.height;
	const int window_width = desktop.width;

	//Having the style of "None" gives a false-fullscreen effect for easier closing and access.
	//No FPS limit of V-sync setting needed for it may cause unnecessary slowdown.
	sf::RenderWindow window(sf::VideoMode(desktop.width / 2, desktop.height / 2, desktop.bitsPerPixel), "Boids", sf::Style::None); 
	sf::RenderWindow& w = window;

	Spring mySpring = Spring();
	sf::Clock Clock;
	//sf::CircleShape springTop;
	//sf::CircleShape springBot;

	


	while (window.isOpen())
	{	
		//Event used to close program when window is closed
		sf::Event event;
		while (window.pollEvent(event))
		{
			//"close requested" event: we close the window
			//Implemented alternate ways to close the window. (Pressing the escape, X, and BackSpace key also close the program.)
			if ((event.type == sf::Event::Closed) || 
				(event.type == sf::Event::KeyPressed &&
				 event.key.code == sf::Keyboard::Escape) ||
				(event.type == sf::Event::KeyPressed &&
				 event.key.code == sf::Keyboard::BackSpace) ||
				(event.type == sf::Event::KeyPressed &&
				 event.key.code == sf::Keyboard::X))
			{
				window.close();
			}


			
			float ElapsedTime = Clock.getElapsedTime().asMilliseconds();

			mySpring.TimeStep(ElapsedTime);
			//

		}

		//check for mouse click, draws and adds boid to flock if so.

		//Clears previous frames of visualization to not have clutter. (And simulate animation)
		window.clear();
		


		mySpring.DrawState(w);

		//Updates the window with current values of any data that was modified.
		window.display();

	//This loop continues until window is closed. Continues the process of updating, drawing, rendering the boids, and the window.
	}
	return 0;

}