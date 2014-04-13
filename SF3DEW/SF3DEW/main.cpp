#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>				// For ifstream
#include <iostream>				// For cout
#include <string>
#include <vector>
#include <memory>				// For unique_ptr
#include <time.h>				// THIS SHOULD BE TEMPORARY
#include <sstream>				// For stringstream

#include "Shader.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "AudioSource.hpp"
#include "FontRenderer.hpp"
#include "Random.hpp"
#include "SystemTime.hpp"
#include "Timer.hpp"
#include "Material.hpp"

void exampleCallback()
{
	std::cout << "Yeah!" << std::endl;
}

int main()
{
	// Make system time first!
	sfew::SystemTime systemTime;

	sf::RenderWindow window(sf::VideoMode(800, 600), "SF3DEW Test", sf::Style::Close | sf::Style::Titlebar);
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
	
	// CUBE
	/*
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
	//*/

	// TETRAHEDRON
	/*
	GLfloat vertices[] = {
		-0.5f, -0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,	// L
		 0.0f,  0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f,	// T
		 0.5f, -0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,	// R

		-0.5f, -0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,	// L
		 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f,	// F
		 0.0f,  0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	// T

		 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f,	// F
		 0.5f, -0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,	// R
		 0.0f,  0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	// T

		-0.5f, -0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,	// L
		 0.5f, -0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,	// R
		 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 5.0f, 1.0f	// F
	};
	//*/

	// OCTOHEDRON
	/*
	GLfloat vertices[] = {
		 0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
		 0.0f,  0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f,
		 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,

		-0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,
		 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
		 0.0f,  0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f,

		 0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
		 0.0f,  0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,
		 0.0f,  0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f,

		-0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,
		 0.0f,  0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f,
		 0.0f,  0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,

		 0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
		 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,
		 0.0f, -0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f,

		-0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,
		 0.0f, -0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f,
		 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,

		 0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
		 0.0f, -0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f,
		 0.0f,  0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,

		-0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
		 0.0f,  0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,
		 0.0f, -0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f
	};
	//*/

	// TRIANGLE PRISM
	GLfloat vertices[] = {
		-0.5f,  0.5f,  0.1f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // LO 
		 0.0f, -1.4f,  0.1f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, // BO
		 0.5f,  0.5f,  0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // RO

		-0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // LI
		 0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // RI
		 0.0f, -1.4f, -0.1f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, // BI

		-0.5f,  0.5f,  0.1f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // LO
		-0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 0.2f, 1.0f, // LI
		 0.0f, -1.4f,  0.1f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BO

		-0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 0.2f, 1.0f, // LI
		 0.0f, -1.4f, -0.1f, 1.0f, 1.0f, 1.0f, 0.2f, 0.0f, // BI
		 0.0f, -1.4f,  0.1f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BO

		 0.0f, -1.4f,  0.1f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BO
		 0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 0.2f, 1.0f, // RI
		 0.5f,  0.5f,  0.1f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // RO

		 0.0f, -1.4f,  0.1f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BO
		 0.0f, -1.4f, -0.1f, 1.0f, 1.0f, 1.0f, 0.2f, 0.0f, // BI
		 0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 0.2f, 1.0f, // RI

		-0.5f,  0.5f,  0.1f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // LO
		 0.5f,  0.5f,  0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // RO
		 0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.2f, // RI

		 0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.2f, // RI
		-0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 0.0f, 0.2f, // LI
		-0.5f,  0.5f,  0.1f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f  // LO 
	};

	std::vector<float> vertexData(vertices, vertices + sizeof(vertices) / sizeof(float));
	std::unique_ptr<sfew::Mesh> theMesh(new sfew::Mesh(vertexData));
	theMesh->SetName("Rectangle Mesh");

	// Experiment: Test shader object
	std::shared_ptr<sfew::Shader> theShader(new sfew::Shader("./Shaders/basic.vert", "./Shaders/basic.frag") );
	theShader->SetName("Basic Shader");
	theShader->SetUniform("brightnessRatio", 1.0f);
	float t = (float) clock() / (float) CLOCKS_PER_SEC;
	float delta = (sin(t * 4.0f) + 1.0f)/2.0f;
	theShader->SetUniform("meshColor", 1.0f, 1.0f, 1.0f, 1.0f);

	// Experiment: Test texture object
	std::shared_ptr<sfew::Texture> theTexture(new sfew::Texture("./Textures/texPatches.png"));
	theTexture->SetName("Patches Texture");

	// Experiment: Test Material object
	std::unique_ptr<sfew::Material> theMaterial(new sfew::Material(theShader, theTexture));

	// Experiment: Test transform objects
	std::unique_ptr<sfew::Transform> theTransform(new sfew::Transform());
	theMaterial->SetUniform("model", theTransform->GenerateModelMatrix());
	std::unique_ptr<sfew::Transform> secondTransform(new sfew::Transform());
	secondTransform->SetPosition(sfew::Vector3(-2.0f, 0.0f, 0.1f));
	theMaterial->SetUniform("model", secondTransform->GenerateModelMatrix());

	// Experiment: Test camera object
	std::unique_ptr<sfew::Camera> theCamera(new sfew::Camera());
	theCamera->SetName("Main Camera");
	theCamera->SetAspectRatio(winSize.x, winSize.y);
	float camStart = 1.2f;
	theCamera->SetPosition(sfew::Vector3(camStart, camStart, camStart));
	theCamera->LookAtPoint(sfew::Vector3(0.0f, 0.0f, 0.0f));
	theCamera->SetUpDirection(sfew::Transform::WorldUp());

	theMaterial->SetUniform("view", theCamera->GenerateViewMatrix());
	theMaterial->SetUniform("projection", theCamera->GenerateProjectionMatrix());

	// Experiment: Testing AudioSource
	std::unique_ptr<sfew::AudioSource> sndLaser(new sfew::AudioSource("./Audio/sndPlayerLaser.wav", sfew::AudioType::Sound));
	std::unique_ptr<sfew::AudioSource> sndItem(new sfew::AudioSource("./Audio/sndItemGet.wav", sfew::AudioType::Sound));
	std::unique_ptr<sfew::AudioSource> musRolling(new sfew::AudioSource("./Audio/rolling_by_madgarden.ogg", sfew::AudioType::Music));

	//sndLaser->Play();
	//sndItem->Play();

	musRolling->SetVolume(10.0f);
	musRolling->Play();

	// Load a font with SFML
	sf::Font testFont;
	if(!testFont.loadFromFile("./Fonts/Mars_1_0_0_6.otf"))
	{
		std::cout << "Warning! Font not found!" << std::endl;
	}

	// Experiment: testing FontRenderer
	std::unique_ptr<sfew::FontRenderer> testLabel(new sfew::FontRenderer(window, testFont));
	testLabel->SetTextString("A Video Game!");
	testLabel->SetFontSize(48);
	testLabel->SetColor(0.0f, 0.5f, 0.7f, 1.0f);
	testLabel->SetStyle(sf::Text::Style::Regular);
	testLabel->SetPosition(10, 10);

	// Experiment: testing SystemTime (delta should be 0 here)
	std::cout << "Run: " << sfew::SystemTime::GetGameRunTime().asSeconds() << std::endl;
	std::cout << "Delta: " << sfew::SystemTime::GetDeltaTime().asSeconds() << std::endl;

	// Experiment: tesing Timers
	//std::unique_ptr<sfew::Timer> theTimer(new sfew::Timer(sf::seconds(5.0f), std::bind(&exampleCallback)));
	
	// Move the center object up every 5 seconds with lambda!
	std::unique_ptr<sfew::Timer> theTimer(new sfew::Timer(sf::seconds(5.0f), [&theTransform](){theTransform->Translate(sfew::Vector3(0.0f, 0.5f, 0.0f));} ));
	theTimer->SetLooping(true);

	// START GAME LOOP
	std::stringstream fpsStr;
	bool isRunning = true;
	while(isRunning)
	{
		// Update the delta time and timer (mandatory)
		systemTime.Loop();
		theTimer->Update();

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
		//theMaterial->SetUniform("triangleColor", delta, delta, delta);

		// Move camera
		//camStart += 0.0004f;
		//theCamera->SetPosition(sfew::Vector3(camStart, camStart, camStart));
		//theMaterial->SetUniform("view", theCamera->GenerateViewMatrix());

		// Update font renderer
		float fpsVal = sfew::SystemTime::GetFPS();
		fpsStr.str(std::string());
		fpsStr << "FPS: " << fpsVal;
		testLabel->SetTextString(fpsStr.str());

		// Draw 3D
		theMaterial->Use();
		theMesh->MakeActiveMeshToDraw();

		theTransform->Rotate(sfew::Vector3(0.0f, 1.0f, 0.0f));
		theMaterial->SetUniform("model", theTransform->GenerateModelMatrix());

		glDrawArrays(GL_TRIANGLES, 0, theMesh->GetNumberOfVertices());

		theMaterial->SetUniform("model", secondTransform->GenerateModelMatrix());

		glDrawArrays(GL_TRIANGLES, 0, theMesh->GetNumberOfVertices());

		// Draw font
		testLabel->Draw();

		window.display();
	}

	//sndLaser->Play();
	//sf::sleep(sndLaser->GetDuration());
	//sf::sleep(sf::seconds(2.0f));

	return 0;
}