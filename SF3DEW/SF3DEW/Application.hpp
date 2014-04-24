// Application
// Delegates the life time of the game and loads everything
// Would have been ProgramCtrlr in BlockDodger
//
// Written by Jibran Syed (4-12-2014)

#ifndef SFEW_APP_H
#define SFEW_APP_H

#include <memory>
#include <string>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ISystemObject.hpp"

#include "SystemTime.hpp"
#include "Camera.hpp"

#include "MeshRegistry.hpp"
#include "ShaderRegistry.hpp"
#include "TextureRegistry.hpp"
#include "MaterialRegistry.hpp"
#include "AudioRegistry.hpp"
#include "FontRegistry.hpp"
#include "PrefabricationRegistry.hpp"
#include "SceneRegistry.hpp"

#include "TimerContainer.hpp"
#include "PhysicsEntityContainer.hpp"
#include "RendererContainer.hpp"
#include "GameObjectContainer.hpp"

namespace sfew
{
	class Application : sf::NonCopyable, public ISystemObject
	{
	public:

		// Ctor/Dtor ======================

		Application();
		~Application();

		// System Routines ================

		virtual bool Setup();		// Run at the begining of the program
		virtual bool Update();		// Run every loop
		virtual bool Cleanup();		// Run at the end of the program

		// Routines =======================

		bool MainLoop();			// The main app loop

		// Static Routines ================

		static void Quit();

		// Properties =====================

		static std::weak_ptr<sf::RenderWindow> GetWindow();
		static sf::Vector2u GetWindowSize();

	private:

		// Helpers ========================

		static bool verifyInstantiation();
		void setupCamera();		// Setup the camera's default setting
		void setupWindow();		// Setup the SFML Window

		// Data ===========================

		// Loop
		bool _isRunning;		// Is the app still running?

		// Window
		sf::Vector2u _windowSize;						// Size of the window in pixels
		std::shared_ptr<sf::RenderWindow> _window;		// Represents a window on the desktop

		// System Objects
		std::unique_ptr<SystemTime> _systemTime;	// Handles app time data
		std::weak_ptr<Camera> _camera;				// Represents a camera to render 3D

		// Registries
		std::unique_ptr<MeshRegistry> _meshRegistry;				// Registry for Meshes
		std::unique_ptr<ShaderRegistry> _shaderRegistry;			// Registry for Shaders
		std::unique_ptr<TextureRegistry> _textureRegistry;			// Registry for Textures
		std::unique_ptr<MaterialRegistry> _materialRegistry;		// Registry for Materials
		std::unique_ptr<AudioRegistry> _audioRegistry;				// Registry for AudioSources
		std::unique_ptr<FontRegistry> _fontRegistry;				// Registry for Fonts
		std::unique_ptr<PrefabricationRegistry> _prefabRegistry;	// Registry for Prefabrications
		std::unique_ptr<SceneRegistry> _sceneRegistry;				// Registry for Scenes

		// Containers
		std::unique_ptr<TimerContainer> _timerContainer;			// Container for Timers
		std::unique_ptr<PhysicsEntityContainer> _physicsContainer;	// Container for PhysicsEntities
		std::unique_ptr<RendererContainer> _rendererContainer;		// Container for ObjectRenderers and FontRenderers
		std::unique_ptr<GameObjectContainer> _gameObjectContainer;	// Container for GameObjects


		// Singleton Data =================

		static Application* _instance;	// Internal pointer to singleton
		
	};

	
} // namespace sfew

#endif