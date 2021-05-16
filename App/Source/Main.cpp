#include "pch.h"

#include <glad.h>
#include <SFML/Graphics.hpp>

#include "Utils/Log.h"

int main()
{
	sf::Window window(sf::VideoMode(1280, 720),
		"SFML OpenGL(glad) Integration!",
		sf::Style::Default,
		sf::ContextSettings(24));
	window.setVerticalSyncEnabled(true);

	LOG("Testing logging!");
	ASSERT(true, "Window cannot be set to active!");
	
	gladLoadGL();
	
	bool isRunning = true;
	while (isRunning)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		// Draw
		glClearColor(1.0f, 0.0f, 0.0f ,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		window.display();
	}
}
