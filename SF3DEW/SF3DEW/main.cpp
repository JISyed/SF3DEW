#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>				// For ifstream
#include <iostream>				// For cout
#include <string>
#include <vector>
#include <memory>				// For unique_ptr
#include <time.h>

#include "Shader.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

int main()
{
	sf::Window window(sf::VideoMode(800, 600), "SF3DEW Test", sf::Style::Close | sf::Style::Titlebar);
	window.setVerticalSyncEnabled(true);
	sf::Vector2u winSize = window.getSize();

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);

	// Experiment: Test mesh object
	float vertices[] = {
		// X     Y     R     G     B     U     V
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right

		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Bottom-left
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f  // Top-left
	};
	std::vector<float> vertexData(vertices, vertices + sizeof(vertices) / sizeof(float));
	std::unique_ptr<sfew::Mesh> theMesh(new sfew::Mesh(vertexData));
	theMesh->SetName("Rectangle");

	// Experiment: Test shader object
	std::unique_ptr<sfew::Shader> theShader(new sfew::Shader("./Shaders/basic.vert", "./Shaders/basic.frag") );
	theShader->SetName("Basic Shader");
	theShader->SetUniform("brightnessRatio", 1.0f);
	float t = (float) clock() / (float) CLOCKS_PER_SEC;
	float delta = (sin(t * 4.0f) + 1.0f)/2.0f;
	theShader->SetUniform("triangleColor", delta, delta, delta);

	// Experiment: Test texture object
	std::unique_ptr<sfew::Texture> theTexture(new sfew::Texture());
	theTexture->UseTexture();

	// Experiment: Test camera object
	/*
	std::unique_ptr<sfew::Camera> theCamera(new sfew::Camera());
	theCamera->SetName("Main Camera");
	theCamera->SetAspectRatio(winSize.x, winSize.y);
	sfew::Matrix4 viewMatrix = theCamera->GenerateViewMatrix();
	theShader->SetUniform("view", viewMatrix);
	sfew::Matrix4 projectionMatrix = theCamera->GenerateProjectionMatrix();
	theShader->SetUniform("proj", projectionMatrix);
	*/

	theShader->UseShader();

	bool isRunning = true;
	while(isRunning)
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				isRunning = false; break;
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape) isRunning = false; break;
			default:
				break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		t = (float) clock() / (float) CLOCKS_PER_SEC;
		delta = (sin(t * 4.0f) + 1.0f)/2.0f;
		theShader->SetUniform("triangleColor", delta, delta, delta);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.display();
	}

	return 0;
}