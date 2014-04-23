#include <SFML/System.hpp>		// For sf::sleep
#include <iostream>				// For cout
#include <memory>				// For unique_ptr, share_ptr, and weak_ptr

#include "Application.hpp"
#include "Camera.hpp"
#include "Random.hpp"
#include "SystemTime.hpp"

#include "ObjectRenderer.hpp"
#include "MeshRegistry.hpp"
#include "ShaderRegistry.hpp"
#include "TextureRegistry.hpp"
#include "MaterialRegistry.hpp"
#include "AudioRegistry.hpp"
#include "FontRegistry.hpp"
#include "PrefabricationRegistry.hpp"
#include "SceneRegistry.hpp"

#include "GameObjectContainer.hpp"
#include "PhysicsEntityContainer.hpp"
#include "RendererContainer.hpp"
#include "TimerContainer.hpp"

int main()
{
	// Make system time first!
	sfew::SystemTime systemTime;
	

	// Make the application
	std::unique_ptr<sfew::Application> app(new sfew::Application());
	app->Setup();

	// Print the OpenGL version
	sfew::RendererContainer::PrintOpenGLVersion();

	// Construct registries
	std::unique_ptr<sfew::MeshRegistry> meshRegistry(new sfew::MeshRegistry());
	std::unique_ptr<sfew::ShaderRegistry> shaderRegistry(new sfew::ShaderRegistry());
	std::unique_ptr<sfew::TextureRegistry> textureRegistry(new sfew::TextureRegistry());
	std::unique_ptr<sfew::MaterialRegistry> materialRegistry(new sfew::MaterialRegistry());
	std::unique_ptr<sfew::AudioRegistry> audioRegistry(new sfew::AudioRegistry());
	std::unique_ptr<sfew::FontRegistry> fontRegistry(new sfew::FontRegistry());
	std::unique_ptr<sfew::PrefabricationRegistry> prefabRegistry(new sfew::PrefabricationRegistry());
	std::unique_ptr<sfew::SceneRegistry> sceneRegistry(new sfew::SceneRegistry());

	// Constuct the containers
	std::unique_ptr<sfew::TimerContainer> timerContainer(new sfew::TimerContainer());
	std::unique_ptr<sfew::PhysicsEntityContainer> physicsEntityContainer(new sfew::PhysicsEntityContainer());
	std::unique_ptr<sfew::RendererContainer> rendererContainer(new sfew::RendererContainer());
	std::unique_ptr<sfew::GameObjectContainer> gameObjectContainer(new sfew::GameObjectContainer());
	timerContainer->Setup();
	physicsEntityContainer->Setup();
	rendererContainer->Setup();
	gameObjectContainer->Setup();


	// Experiment: Test mesh object
	meshRegistry->Load();

	// Experiment: Test shader object
	shaderRegistry->Load();
	meshRegistry->SetupAllVertexFormats();

	// Experiment: Test texture object
	textureRegistry->Load();

	// Experiment: Test Material object
	materialRegistry->Load();

	// Experiment: Testing AudioSource
	audioRegistry->Load();

	// Testing Font object
	fontRegistry->Load();

	// Loading prefabs and scenes
	prefabRegistry->Load();
	sceneRegistry->Load();


	// Experiment: Test camera object
	std::weak_ptr<sfew::Camera> theCamera = sfew::Camera::GetInstance();
	theCamera._Get()->SetName("Main Camera");
	theCamera._Get()->SetAspectRatio(
		sfew::Application::GetWindowSize().x,
		sfew::Application::GetWindowSize().y
	);
	float camStart = 1.4f;
	theCamera._Get()->SetPosition(sfew::Vector3(camStart, camStart, camStart));
	theCamera._Get()->LookAtPoint(sfew::Vector3(0.0f, 0.0f, 0.0f));
	theCamera._Get()->SetUpDirection(sfew::Transform::WorldUp());
	shaderRegistry->UpdateCameraDataInShaders();


	// GAMEOBJECT TESTING GROUNDS

	// Cube object
	auto cubePrefab = sfew::PrefabricationRegistry::Get<sfew::prefab::CubePrefab>();
	auto cubeObject = cubePrefab._Get()->MakeObject();

	// FPS Text display object
	auto fpsPrefab = sfew::PrefabricationRegistry::Get<sfew::prefab::FpsPrefab>();
	auto fpsObject = fpsPrefab._Get()->MakeObject();

	// Octohedron object
	auto octoPrefab = sfew::PrefabricationRegistry::Get<sfew::prefab::OctoPrefab>();
	auto octoObject = octoPrefab._Get()->MakeObject();

	// Experiment: testing SystemTime
	std::cout << "Load: " << sfew::SystemTime::GetGameRunTime().asSeconds() << std::endl;


	// START GAME LOOP
	std::stringstream fpsStr;
	bool isRunning = true;
	std::weak_ptr<sf::RenderWindow> theWindow = sfew::Application::GetWindow();
	while(isRunning)
	{
		// START THE UPDATE LOOP

		// Update the delta time and timer (mandatory)
		systemTime.Update();
		timerContainer->Update();

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

		// ACTUAL UPDATE
		physicsEntityContainer->Update();
		gameObjectContainer->Update();

		// START OF DRAW LOOP

		shaderRegistry->UpdateCameraDataInShaders();
		rendererContainer->Draw();

		// End of Drawing

		// Load a new scene if one was requested
		sceneRegistry->loadSceneIfRequested();

	} // END OF GAME LOOP


	// END OF PROGRAM
	
	// Unload all the objects from all containers
	gameObjectContainer->Cleanup();
	rendererContainer->Cleanup();
	physicsEntityContainer->Cleanup();
	timerContainer->Cleanup();

	// Unload all resources from all registries
	sceneRegistry->Unload();
	prefabRegistry->Unload();
	fontRegistry->Unload();
	audioRegistry->Unload();
	materialRegistry->Unload();
	textureRegistry->Unload();
	shaderRegistry->Unload();
	meshRegistry->Unload();

	app->Cleanup();

	return 0;
}