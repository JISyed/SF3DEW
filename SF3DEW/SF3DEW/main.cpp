#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>				// For ifstream
#include <iostream>				// For cout
#include <string>
#include <vector>
#include <memory>				// For unique_ptr, share_ptr, and weak_ptr
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
#include "ObjectRenderer.hpp"
#include "MeshRegistry.hpp"
#include "ShaderRegistry.hpp"
#include "TextureRegistry.hpp"

int main()
{
	// Make system time first!
	sfew::SystemTime systemTime;

	// Construct registries
	std::unique_ptr<sfew::MeshRegistry> meshRegistry(new sfew::MeshRegistry());
	std::unique_ptr<sfew::ShaderRegistry> shaderRegistry(new sfew::ShaderRegistry());
	std::unique_ptr<sfew::TextureRegistry> textureRegistry(new sfew::TextureRegistry());

	// Create SFML window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SF3DEW Test", sf::Style::Close | sf::Style::Titlebar);
	window.setVerticalSyncEnabled(true);
	sf::Vector2u winSize = window.getSize();

	// OpenGL setup
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_CULL_FACE); glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background

	// Experiment: Test mesh object
	meshRegistry->Load();

	// Experiment: Test shader object
	shaderRegistry->Load();
	meshRegistry->SetupAllVertexFormats();

	// Experiment: Test texture object
	textureRegistry->Load();

	// Experiment: Test Material object
	std::shared_ptr<sfew::Material> theMaterial(new sfew::Material(sfew::ShaderRegistry::GetByName("BasicShader"), 
																   sfew::TextureRegistry::GetByName("Patches")) );

	// Experiment: Test transform objects
	std::unique_ptr<sfew::Transform> theTransform(new sfew::Transform());
	std::unique_ptr<sfew::Transform> secondTransform(new sfew::Transform());
	secondTransform->SetPosition(sfew::Vector3(-2.0f, 0.0f, 0.1f));

	// Experiment: Test ObjectRenderers
	std::weak_ptr<sfew::Mesh> cubeMesh = sfew::MeshRegistry::GetByName("OctohedronMesh");
	std::weak_ptr<sfew::Mesh> prismMesh = sfew::MeshRegistry::GetByName("CubeMesh");
	std::unique_ptr<sfew::ObjectRenderer> entityOne(new sfew::ObjectRenderer(cubeMesh, theMaterial));
	std::unique_ptr<sfew::ObjectRenderer> entityTwo(new sfew::ObjectRenderer(prismMesh, theMaterial));

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

	musRolling->SetVolume(1.0f);
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
	// Move the center object up every 5 seconds with lambda!
	std::unique_ptr<sfew::Timer> theTimer(new sfew::Timer(sf::seconds(5.0f), [&theTransform](){theTransform->Translate(sfew::Vector3(0.0f, 0.5f, 0.0f));} ));
	theTimer->SetLooping(true);

	// START GAME LOOP
	std::stringstream fpsStr;
	bool isRunning = true;
	while(isRunning)
	{
		// START THE UPDATE LOOP

		// Update the delta time and timer (mandatory)
		systemTime.Update();
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

		// Update objects

		// Move camera
		//camStart += 0.0004f;
		//theCamera->SetPosition(sfew::Vector3(camStart, camStart, camStart));
		//theMaterial->SetUniform("view", theCamera->GenerateViewMatrix());

		theTransform->Rotate(sfew::Vector3(0.0f, 1.0f, 0.0f));
		entityOne->UpdateModelMatrix(theTransform->GenerateModelMatrix() );
		entityTwo->UpdateModelMatrix(secondTransform->GenerateModelMatrix() );

		// Update font renderer
		float fpsVal = sfew::SystemTime::GetFPS();
		fpsStr.str(std::string());
		fpsStr << "FPS: " << fpsVal;
		testLabel->SetTextString(fpsStr.str());

		// START OF DRAW LOOP

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw objects

		// Draw 3D
		entityOne->Draw();
		entityTwo->Draw();

		// Draw font
		testLabel->Draw();

		window.display();
	}

	//sndLaser->Play();
	//sf::sleep(sndLaser->GetDuration());
	//sf::sleep(sf::seconds(2.0f));

	// END OF PROGRAM
	
	// Unload all resources from all registries
	textureRegistry->Unload();
	shaderRegistry->Unload();
	meshRegistry->Unload();

	return 0;
}