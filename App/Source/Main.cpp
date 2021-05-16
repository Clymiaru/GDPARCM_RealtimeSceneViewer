#include "pch.h"
#include <glad.h>
#include <SFML/Graphics.hpp>

#include <imgui-SFML.h>


#include "Utils/Log.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720),
		"SFML OpenGL(glad) Integration!",
		sf::Style::Default,
		sf::ContextSettings(24));
	window.setVerticalSyncEnabled(true);

	LOG("Testing logging!");
	ASSERT(true, "Window cannot be set to active!");
	
	gladLoadGL();

	ImGui::SFML::Init(window);
	
	bool isRunning = true;
	while (isRunning)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
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
		//ImGui::ShowDemoWindow();
		
		glClearColor(1.0f, 0.0f, 0.0f ,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui::SFML::Render(window);
		window.display();
	}
}
