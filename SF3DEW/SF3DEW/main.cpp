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
#include <sstream>				// For stringstream

#include "Shader.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "AudioSource.hpp"
#include "Font.hpp"
#include "FontRenderer.hpp"
#include "Random.hpp"
#include "SystemTime.hpp"
#include "Timer.hpp"
#include "Material.hpp"
#include "GameObject.hpp"

#include "Application.hpp"
#include "ObjectRenderer.hpp"
#include "MeshRegistry.hpp"
#include "ShaderRegistry.hpp"
#include "TextureRegistry.hpp"
#include "MaterialRegistry.hpp"
#include "AudioRegistry.hpp"
#include "FontRegistry.hpp"

int main()
{
	// Make system time first!
	sfew::SystemTime systemTime;
	
	// Make the application
	std::unique_ptr<sfew::Application> app(new sfew::Application());
	app->Setup();

	// Construct registries
	std::unique_ptr<sfew::MeshRegistry> meshRegistry(new sfew::MeshRegistry());
	std::unique_ptr<sfew::ShaderRegistry> shaderRegistry(new sfew::ShaderRegistry());
	std::unique_ptr<sfew::TextureRegistry> textureRegistry(new sfew::TextureRegistry());
	std::unique_ptr<sfew::MaterialRegistry> materialRegistry(new sfew::MaterialRegistry());
	std::unique_ptr<sfew::AudioRegistry> audioRegistry(new sfew::AudioRegistry());
	std::unique_ptr<sfew::FontRegistry> fontRegistry(new sfew::FontRegistry());


	// Create SFML window
	//sf::RenderWindow window(sf::VideoMode(800, 600), "SF3DEW Test", sf::Style::Close | sf::Style::Titlebar);
	//window.setVerticalSyncEnabled(true);
	//sf::Vector2u winSize = window.getSize();


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
	materialRegistry->Load();


	// Experiment: Test transform objects
	std::unique_ptr<sfew::Transform> theTransform(new sfew::Transform());
	std::unique_ptr<sfew::Transform> secondTransform(new sfew::Transform());
	secondTransform->SetPosition(sfew::Vector3(-2.0f, 0.0f, 0.1f));


	// Experiment: Test ObjectRenderers
	std::weak_ptr<sfew::Mesh> cubeMesh = sfew::MeshRegistry::GetByName("OctohedronMesh");
	std::weak_ptr<sfew::Mesh> prismMesh = sfew::MeshRegistry::GetByName("CubeMesh");
	std::unique_ptr<sfew::ObjectRenderer> entityOne(new sfew::ObjectRenderer(cubeMesh, sfew::MaterialRegistry::GetByName("OrangePatches") ));
	std::unique_ptr<sfew::ObjectRenderer> entityTwo(new sfew::ObjectRenderer(prismMesh, sfew::MaterialRegistry::GetByName("GameOver") ));


	// Experiment: Test camera object
	//std::unique_ptr<sfew::Camera> theCamera(new sfew::Camera());
	std::weak_ptr<sfew::Camera> theCamera = sfew::Camera::GetInstance();
	theCamera._Get()->SetName("Main Camera");
	theCamera._Get()->SetAspectRatio(
		sfew::Application::GetWindowSize().x,
		sfew::Application::GetWindowSize().y
	);
	float camStart = 1.2f;
	theCamera._Get()->SetPosition(sfew::Vector3(camStart, camStart, camStart));
	theCamera._Get()->LookAtPoint(sfew::Vector3(0.0f, 0.0f, 0.0f));
	theCamera._Get()->SetUpDirection(sfew::Transform::WorldUp());

	shaderRegistry->UpdateCameraDataInShaders();


	// Experiment: Testing AudioSource
	audioRegistry->Load();

	//sfew::AudioRegistry::GetByName("PlayerLaserSnd")._Get()->Play();
	//sfew::AudioRegistry::GetByName("ItemGetSnd")._Get()->Play();

	sfew::AudioRegistry::GetByName("RollingMus")._Get()->SetVolume(20.0f);
	sfew::AudioRegistry::GetByName("RollingMus")._Get()->Play();


	// Testing Font object
	fontRegistry->Load();

	// Experiment: testing FontRenderer
	std::unique_ptr<sfew::FontRenderer> testLabel(
		new sfew::FontRenderer(
			sfew::FontRegistry::GetByName("Mars")._Get()->GetReference() 
		)
	);
	testLabel->SetTextString("SF3DEW");
	testLabel->SetFontSize(48);
	testLabel->SetColor(0.0f, 0.5f, 0.7f, 1.0f);
	testLabel->SetStyle(sf::Text::Style::Regular);
	testLabel->SetPosition(10, 10);


	// Experiment: tesing Timers
	// Move the center object up every 5 seconds with lambda!
	std::unique_ptr<sfew::Timer> theTimer(new sfew::Timer(sf::seconds(5.0f), [&theTransform](){theTransform->Translate(sfew::Vector3(0.0f, 0.5f, 0.0f));} ));
	theTimer->SetLooping(true);


	// Experiment: testing SystemTime
	std::cout << "Load: " << sfew::SystemTime::GetGameRunTime().asSeconds() << std::endl;
	

	// TESTING GROUNDS
	std::unique_ptr<sfew::GameObject> go(new sfew::GameObject());
	go->AddComponent(sfew::ComponentType::Audio);
	std::weak_ptr<sfew::AudioComponent> audioComp = stdext::dynamic_pointer_cast<sfew::AudioComponent>( go->GetComponent(sfew::ComponentType::Audio) );
	audioComp._Get()->GetAudioSource()._Get()->Play();
	go->AddComponent(sfew::ComponentType::ObjectRenderer);
	std::weak_ptr<sfew::ObjectRendererComponent> rend = stdext::dynamic_pointer_cast<sfew::ObjectRendererComponent>( go->GetComponent(sfew::ComponentType::ObjectRenderer) );
	go->GetTransform()._Get()->SetPosition(sfew::Vector3(-3.0f, 0.0f, -3.0f));
	rend._Get()->GetRenderer()._Get()->GetMaterial()._Get()->SetColor(sfew::Vector4(236/255.0f, 157/255.0f, 162/255.0f, 1.0f));

	// Second Game Object
	std::unique_ptr<sfew::GameObject> fontGo(new sfew::GameObject());
	fontGo->AddComponent(sfew::ComponentType::FontRenderer);

	// START GAME LOOP
	std::stringstream fpsStr;
	bool isRunning = true;
	std::weak_ptr<sf::RenderWindow> theWindow = sfew::Application::GetWindow();
	while(isRunning)
	{
		// START THE UPDATE LOOP

		// Update the delta time and timer (mandatory)
		systemTime.Update();
		theTimer->Update();

		sf::Event event;
		while(theWindow._Get()->pollEvent(event))
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
		camStart += 0.0009f;
		theCamera._Get()->SetPosition(sfew::Vector3(camStart, camStart, camStart));

		// Update GameObject
		go->GetTransform()._Get()->Rotate(sfew::Vector3(0.0f, 10.0f, 0.0f));
		go->Update();

		// Update ObjectRenderers
		theTransform->Rotate(sfew::Vector3(0.0f, 1.0f, 0.0f));
		entityOne->UpdateModelMatrix(theTransform->GenerateModelMatrix() );
		entityTwo->UpdateModelMatrix(secondTransform->GenerateModelMatrix() );

		// Update font renderer
		float fpsVal = sfew::SystemTime::GetFPS();
		fpsStr.str(std::string());
		fpsStr << "FPS: " << fpsVal;
		testLabel->SetTextString(fpsStr.str());

		// START OF DRAW LOOP

		shaderRegistry->UpdateCameraDataInShaders();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw objects

		// Draw 3D
		entityOne->Draw();
		entityTwo->Draw();
		rend._Get()->GetRenderer()._Get()->Draw();

		// Draw font
		testLabel->Draw();

		// Swap render buffers
		theWindow._Get()->display();
	}

	sfew::AudioRegistry::GetByName("PlayerLaserSnd")._Get()->Play();
	sf::sleep(sfew::AudioRegistry::GetByName("PlayerLaserSnd")._Get()->GetDuration());

	// END OF PROGRAM
	
	// Unload all resources from all registries
	fontRegistry->Unload();
	audioRegistry->Unload();
	materialRegistry->Unload();
	textureRegistry->Unload();
	shaderRegistry->Unload();
	meshRegistry->Unload();

	app->Cleanup();

	return 0;
}