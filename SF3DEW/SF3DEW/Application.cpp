#include "Application.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static Data ======================================

	Application* Application::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	Application::Application() : _isRunning(true)
	{
		// Create system time
		_systemTime = std::unique_ptr<SystemTime>(new SystemTime());

		// Check for multiple Application instances
		if(Application::_instance != NULL)
		{
			std::cout << "ERROR: Application being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		Application::_instance = this;

		// Construct camera
		_camera = Camera::GetInstance();

		// Construct registries
		_meshRegistry = std::unique_ptr<sfew::MeshRegistry>(new sfew::MeshRegistry());
		_shaderRegistry = std::unique_ptr<sfew::ShaderRegistry>(new sfew::ShaderRegistry());
		_textureRegistry = std::unique_ptr<sfew::TextureRegistry>(new sfew::TextureRegistry());
		_materialRegistry = std::unique_ptr<sfew::MaterialRegistry>(new sfew::MaterialRegistry());
		_audioRegistry = std::unique_ptr<sfew::AudioRegistry>(new sfew::AudioRegistry());
		_fontRegistry = std::unique_ptr<sfew::FontRegistry>(new sfew::FontRegistry());
		_prefabRegistry = std::unique_ptr<sfew::PrefabricationRegistry>(new sfew::PrefabricationRegistry());
		_sceneRegistry = std::unique_ptr<sfew::SceneRegistry>(new sfew::SceneRegistry());

		// Constuct the containers
		_timerContainer = std::unique_ptr<sfew::TimerContainer>(new sfew::TimerContainer());
		_physicsContainer = std::unique_ptr<sfew::PhysicsEntityContainer>(new sfew::PhysicsEntityContainer());
		_rendererContainer = std::unique_ptr<sfew::RendererContainer>(new sfew::RendererContainer());
		_gameObjectContainer = std::unique_ptr<sfew::GameObjectContainer>(new sfew::GameObjectContainer());
	}

	// Dtor
	Application::~Application()
	{
		// Clear the internal singleton
		Application::_instance = NULL;
	}

	// System Routines ====================================

	bool Application::Setup()
	{
		// Make the window
		setupWindow();

		// Setup System Time
		_systemTime->Setup();

		// Setup containters
		_timerContainer->Setup();
		_physicsContainer->Setup();
		_rendererContainer->Setup();
		_gameObjectContainer->Setup();

		// Setup the registries
		_meshRegistry->Load();
		_shaderRegistry->Load();
		_meshRegistry->SetupAllVertexFormats();
		_textureRegistry->Load();
		_materialRegistry->Load();
		_audioRegistry->Load();
		_fontRegistry->Load();
		_prefabRegistry->Load();
		_sceneRegistry->Load();

		// Setup camera
		setupCamera();

		return true;
	}

	bool Application::Update()
	{
		// Not used. See MainLoop()
		return true;
	}

	bool Application::Cleanup()
	{
		// Unload all the objects from all containers
		_gameObjectContainer->Cleanup();
		_rendererContainer->Cleanup();
		_physicsContainer->Cleanup();
		_timerContainer->Cleanup();

		// Unload all resources from all registries
		_sceneRegistry->Unload();
		_prefabRegistry->Unload();
		_fontRegistry->Unload();
		_audioRegistry->Unload();
		_materialRegistry->Unload();
		_textureRegistry->Unload();
		_shaderRegistry->Unload();
		_meshRegistry->Unload();

		// Cleanup SystemTime
		_systemTime->Cleanup();

		return true;
	}

	// Routines =========================================

	// The main app loop
	bool Application::MainLoop()
	{
		sf::Event event;
		while(_isRunning)
		{
			// START THE MAIN LOOP

			// Update the delta time, timers, and scene loader
			_systemTime->Update();
			_sceneRegistry->loadSceneIfRequested();
			_timerContainer->Update();

			// Check if the window was requested to be closed
			while(_window->pollEvent(event))
			{
				switch(event.type)
				{
				case sf::Event::Closed:
					_isRunning = false; break;
				case sf::Event::KeyPressed:
					if(event.key.code == sf::Keyboard::Escape) _isRunning = false; break;
				default:
					break;
				}
			}

			// UPDATE
			_physicsContainer->Update();
			_gameObjectContainer->Update();

			// DRAW
			_shaderRegistry->UpdateCameraDataInShaders();
			_rendererContainer->Draw();

			// END OF MAIN LOOP
		}

		return true;
	}
	
	// Static Routines =======================================

	// STATIC:
	void Application::Quit()
	{
		// Check if Application exists
		if(!Application::verifyInstantiation()) return;

		// The app will leave the main loop
		Application::_instance->_isRunning = false;
	}

	// Properties =========================================

	// STATIC:
	std::weak_ptr<sf::RenderWindow> Application::GetWindow()
	{
		if(!Application::verifyInstantiation()) 
		{
			return std::weak_ptr<sf::RenderWindow>();
		}

		return Application::_instance->_window;
	}

	// STATIC:
	sf::Vector2u Application::GetWindowSize()
	{
		if(!Application::verifyInstantiation())
		{
			return sf::Vector2u();
		}

		return Application::_instance->_windowSize;
	}

	// Helpers =========================================

	// STATIC: Was this object instantiated?
	bool Application::verifyInstantiation()
	{
		if(Application::_instance == NULL)
		{
			std::cout << "ERROR: SystemTime not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

	// Setup the camera's default setting
	void Application::setupCamera()
	{
		// Required aspect ratio setup
		_camera._Get()->SetAspectRatio(
			sfew::Application::GetWindowSize().x,
			sfew::Application::GetWindowSize().y
		);

		// Set Camera's name
		_camera._Get()->SetName("Main Camera");
		
		// Set Camera's initial position
		float camStart = 1.4f;
		_camera._Get()->SetPosition(sfew::Vector3(camStart, camStart, camStart));
		
		// Setup Camera's inital look at point
		_camera._Get()->LookAtPoint(sfew::Vector3(0.0f, 0.0f, 0.0f));
		
		// Setup Camera's up orientation
		_camera._Get()->SetUpDirection(sfew::Transform::WorldUp());

		// Required sending of camera data to shaders
		_shaderRegistry->UpdateCameraDataInShaders();
	}

	// Setup the SFML Window
	void Application::setupWindow()
	{
		_window = std::shared_ptr<sf::RenderWindow>(
			new sf::RenderWindow(
				sf::VideoMode(800, 600), 
				"SF3DEW Test", 
				sf::Style::Close | sf::Style::Titlebar
			)
		);
		_window->setVerticalSyncEnabled(true);
		_windowSize = _window->getSize();
	}

} // namespace sfew