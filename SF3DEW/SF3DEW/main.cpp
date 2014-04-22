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


	// Experiment: Test camera object
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

	sfew::AudioRegistry::GetByName("RollingMus")._Get()->SetVolume(20.0f);
	sfew::AudioRegistry::GetByName("RollingMus")._Get()->Play();


	// Testing Font object
	fontRegistry->Load();



	// GAMEOBJECT TESTING GROUNDS

	// Pink sound cube object
	auto go = sfew::GameObjectContainer::Create();
	go._Get()->SetName("SoundCube");
	go._Get()->AddComponent<sfew::AudioComponent>();
	auto audioComp = go._Get()->GetComponent<sfew::AudioComponent>();
	audioComp._Get()->GetAudioSource()._Get()->Play();
	go._Get()->AddComponent<sfew::ObjectRendererComponent>();
	auto rend = go._Get()->GetComponent<sfew::ObjectRendererComponent>();
	go._Get()->GetTransform()._Get()->SetPosition(sfew::Vector3(-3.0f, 0.0f, -3.0f));
	rend._Get()->GetRenderer()._Get()->GetMaterial()._Get()->SetColor(sfew::Vector4(236/255.0f, 157/255.0f, 162/255.0f, 1.0f));

	// Font Game Object
	auto fontGo = sfew::GameObjectContainer::Create();
	fontGo._Get()->SetName("Font");
	fontGo._Get()->AddComponent<sfew::FontRendererComponent>();
	auto fontDrawer = fontGo._Get()->GetComponent<sfew::FontRendererComponent>();
	fontDrawer._Get()->GetRenderer()._Get()->SetPosition(400, 10);

	// Cube object
	auto cubeObj = sfew::GameObjectContainer::Create();
	cubeObj._Get()->SetName("Cube");
	cubeObj._Get()->AddComponent<sfew::ObjectRendererComponent>();
	auto cubeRenderer = cubeObj._Get()->GetComponent<sfew::ObjectRendererComponent>();
	cubeRenderer._Get()->GetRenderer()._Get()->SetMesh(sfew::MeshRegistry::GetByName("CubeMesh"));
	cubeRenderer._Get()->GetRenderer()._Get()->SetMaterial(sfew::MaterialRegistry::GetByName("GameOver"));
	cubeObj._Get()->GetTransform()._Get()->SetPosition(sfew::Vector3(-2.0f, 0.0f, 0.1f));

	// FPS Text display object
	auto fpsDisplayer = sfew::GameObjectContainer::Create();
	fpsDisplayer._Get()->SetName("FPS");
	fpsDisplayer._Get()->AddCustomComponent<sfew::component::FpsUpdaterCmpt>();

	// Octohedron object
	auto octoObj = sfew::GameObjectContainer::Create();
	octoObj._Get()->SetName("Octo");
	octoObj._Get()->AddComponent<sfew::ObjectRendererComponent>();
	auto octoRenderer = octoObj._Get()->GetComponent<sfew::ObjectRendererComponent>();
	octoRenderer._Get()->GetRenderer()._Get()->SetMesh(sfew::MeshRegistry::GetByName("OctohedronMesh"));
	octoRenderer._Get()->GetRenderer()._Get()->SetMaterial(sfew::MaterialRegistry::GetByName("OrangePatches"));

	// Physics Object1
	auto physicsObj1 = sfew::GameObjectContainer::Create();
	physicsObj1._Get()->SetName("Physics1");
	physicsObj1._Get()->AddComponent<sfew::ObjectRendererComponent>();
	physicsObj1._Get()->GetTransform()._Get()->SetPosition(sfew::Vector3(0.0f, 0.0f, 0.0f));
	physicsObj1._Get()->AddComponent<sfew::PhysicsComponent>();
	auto physicsComp1 = physicsObj1._Get()->GetComponent<sfew::PhysicsComponent>();
	physicsComp1._Get()->GetPhysicsEntity()._Get()->SetVelocity(sfew::Vector3(0.0f, 0.0f, 0.0f));
	physicsComp1._Get()->GetPhysicsEntity()._Get()->SetCollisionGroup(sfew::PhysicsCollisionGroups::GroupA);
	physicsComp1._Get()->GetPhysicsEntity()._Get()->SetRadius(0.5);
	physicsComp1._Get()->GetPhysicsEntity()._Get()->SetRotationalVelocity(sfew::Vector3(0.0f, 20.0f, 0.0f));
	physicsComp1._Get()->GetPhysicsEntity()._Get()->SetRotationalAcceleration(sfew::Vector3(0.0f, 20.0f, 0.0f));
	physicsComp1._Get()->GetPhysicsEntity()._Get()->SetAngularDrag(1.0f);
	physicsObj1._Get()->AddCustomComponent<sfew::component::ExampleCmpt>();

	// Physics Object2 (moves)
	auto physicsObj2 = sfew::GameObjectContainer::Create();
	physicsObj2._Get()->SetName("Physics2");
	physicsObj2._Get()->AddComponent<sfew::ObjectRendererComponent>();
	physicsObj2._Get()->GetTransform()._Get()->SetPosition(sfew::Vector3(0.0f, 0.0f, -10.0f));
	physicsObj2._Get()->AddComponent<sfew::PhysicsComponent>();
	auto physicsComp2 = physicsObj2._Get()->GetComponent<sfew::PhysicsComponent>();
	physicsComp2._Get()->GetPhysicsEntity()._Get()->SetVelocity(sfew::Vector3(0.0f, 0.0f, 0.0f));
	physicsComp2._Get()->GetPhysicsEntity()._Get()->SetAcceleration(sfew::Vector3(0.0f, 0.0f, 2.0f));
	physicsComp2._Get()->GetPhysicsEntity()._Get()->SetCollisionGroup(sfew::PhysicsCollisionGroups::GroupB);
	physicsComp2._Get()->GetPhysicsEntity()._Get()->SetRadius(0.5);
	physicsObj2._Get()->AddCustomComponent<sfew::component::ExampleCmpt>();

	// Surrender pointers (only needed if everything is in main() )
	go.reset();
	fontGo.reset();
	fpsDisplayer.reset();
	octoObj.reset();
	cubeObj.reset();
	rend.reset();
	fontDrawer.reset();
	audioComp.reset();
	octoRenderer.reset();
	physicsComp1.reset();
	physicsObj1.reset();
	physicsObj2.reset();
	physicsComp2.reset();

	// Experiment: tesing Timers
	// Move the center object up every 5 seconds with lambda!
	auto octoTransform = sfew::GameObjectContainer::GetByName("Octo")._Get()->GetTransform();
	std::weak_ptr<sfew::Timer> theTimer = sfew::TimerContainer::Create(
		sf::seconds(5.0f), 
		[octoTransform]()
		{
			octoTransform._Get()->Translate(sfew::Vector3(0.0f, 0.5f, 0.0f));
		} 
	);
	theTimer._Get()->SetLooping(true);

	// Yet another timer for deleting something
	std::weak_ptr<sfew::Timer> deleteTimeCountdown = sfew::TimerContainer::Create(
		sf::seconds(10.0f), 
		[]()
		{
			auto aGameObject = sfew::GameObjectContainer::GetByName("Cube");
			if(!aGameObject.expired())
			{
				aGameObject._Get()->Destroy();
			}
		} 
	);

	// Surrender Timer pointers
	theTimer.reset();
	deleteTimeCountdown.reset();

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

	} // END OF GAME LOOP


	// END OF PROGRAM
	
	// Unload all the objects from all containers
	gameObjectContainer->Cleanup();
	rendererContainer->Cleanup();
	physicsEntityContainer->Cleanup();
	timerContainer->Cleanup();

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