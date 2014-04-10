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
#include <time.h>				// THIS SHOULD BE TEMPORARY

#include "Shader.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "AudioSource.hpp"

int main()
{
	sf::Window window(sf::VideoMode(800, 600), "SF3DEW Test", sf::Style::Close | sf::Style::Titlebar);
	window.setVerticalSyncEnabled(true);
	sf::Vector2u winSize = window.getSize();

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_CULL_FACE); glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Experiment: Test mesh object
	GLfloat vertices[] = {
		// X     Y      Z     R     G     B     U     V
		// Back
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // TL 1 1
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BL 1 0
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // BR 0 0
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // BR 0 0
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // TR 0 1
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // TL 1 1
		
		// Front
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BL
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // BR
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // TR
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // TR
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // TL
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BL

		// Left
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // TL 0 1
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // TR 1 1
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BR 1 0
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BR 1 0
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // BL 0 0
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // TL 0 1
		
		// Right
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // BR
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // TR
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // TL
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // TL
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BL
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // BR

		// Down
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // M 0 1
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // K 1 1
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // J 1 0
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // J 1 0
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // L 0 0
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // M 0 1

		// Up
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
	};
	std::vector<float> vertexData(vertices, vertices + sizeof(vertices) / sizeof(float));
	std::unique_ptr<sfew::Mesh> theMesh(new sfew::Mesh(vertexData));
	theMesh->SetName("Rectangle Mesh");

	// Experiment: Test shader object
	std::unique_ptr<sfew::Shader> theShader(new sfew::Shader("./Shaders/basic.vert", "./Shaders/basic.frag") );
	theShader->SetName("Basic Shader");
	theShader->SetUniform("brightnessRatio", 1.0f);
	float t = (float) clock() / (float) CLOCKS_PER_SEC;
	float delta = (sin(t * 4.0f) + 1.0f)/2.0f;
	theShader->SetUniform("triangleColor", 1.0f, 1.0f, 1.0f);

	// Experiment: Test transform objects
	std::unique_ptr<sfew::Transform> theTransform(new sfew::Transform());
	theShader->SetUniform("model", theTransform->GenerateModelMatrix());
	std::unique_ptr<sfew::Transform> secondTransform(new sfew::Transform());
	secondTransform->SetPosition(sfew::Vector3(-2.0f, 0.0f, 0.1f));
	theShader->SetUniform("model", secondTransform->GenerateModelMatrix());

	// Experiment: Test texture object
	std::unique_ptr<sfew::Texture> theTexture(new sfew::Texture("./Textures/texPatches.png"));
	theTexture->SetName("Patches Texture");
	theTexture->UseTexture();

	// Experiment: Test camera object
	std::unique_ptr<sfew::Camera> theCamera(new sfew::Camera());
	theCamera->SetName("Main Camera");
	theCamera->SetAspectRatio(winSize.x, winSize.y);
	theCamera->SetPosition(sfew::Vector3(1.2f, 1.2f, 1.2f));
	theCamera->LookAtPoint(sfew::Vector3(0.0f, 0.0f, 0.0f));
	theCamera->SetUpDirection(sfew::Transform::WorldUp());

	theShader->SetUniform("view", theCamera->GenerateViewMatrix());
	theShader->SetUniform("projection", theCamera->GenerateProjectionMatrix());
	
	// SFML audio test
	
	// Load two sound buffers
	/*
	sf::SoundBuffer sndBufLaser;
	if(!sndBufLaser.loadFromFile("./Audio/sndPlayerLaser.wav"))
	{
		std::cout << "Warning! Sound file does not exist!" << std::endl;
	}
	sf::SoundBuffer sndBufItem;
	if(!sndBufItem.loadFromFile("./Audio/sndItemGet.wav"))
	{
		std::cout << "Warning! Sound file does not exist!" << std::endl;
	}
	sf::Sound sndLaserii;
	sndLaserii.setBuffer(sndBufLaser);
	sf::Sound sndItemii;
	sndItemii.setBuffer(sndBufItem);

	sndLaserii.play();
	sndItemii.play();

	sf::Music musRollingii;
	if(!musRollingii.openFromFile("./Audio/rolling_by_madgarden.ogg"))
	{
		std::cout << "Warning! Music file does not exist!" << std::endl;
	}
	musRollingii.setLoop(true);
	musRollingii.play();
	*/

	// Experiment: Testing AudioSource
	std::unique_ptr<sfew::AudioSource> sndLaser(new sfew::AudioSource("./Audio/sndPlayerLaser.wav", sfew::AudioType::Sound));
	std::unique_ptr<sfew::AudioSource> sndItem(new sfew::AudioSource("./Audio/sndItemGet.wav", sfew::AudioType::Sound));
	std::unique_ptr<sfew::AudioSource> musRolling(new sfew::AudioSource("./Audio/rolling_by_madgarden.ogg", sfew::AudioType::Music));

	sndLaser->Play();
	sndItem->Play();
	musRolling->Play();

	// START GAME LOOP
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

		//t = (float) clock() / (float) CLOCKS_PER_SEC;
		//delta = (sin(t * 4.0f) + 1.0f)/2.0f;
		//theShader->SetUniform("triangleColor", delta, delta, delta);

		theShader->UseShader();
		theMesh->MakeActiveMeshToDraw();

		theTransform->Rotate(sfew::Vector3(0.0f, 1.0f, 0.0f));
		theShader->SetUniform("model", theTransform->GenerateModelMatrix());

		glDrawArrays(GL_TRIANGLES, 0, theMesh->GetNumberOfVertices());

		theShader->SetUniform("model", secondTransform->GenerateModelMatrix());

		glDrawArrays(GL_TRIANGLES, 0, theMesh->GetNumberOfVertices());

		window.display();
	}

	//musRollingii.stop();

	//sndLaserii.play();

	//sf::sleep(sndBufLaser.getDuration());

	musRolling->Stop();
	sndLaser->Play();
	sf::sleep(sndLaser->GetDuration());

	return 0;
}