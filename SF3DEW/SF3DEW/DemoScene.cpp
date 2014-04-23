#include "DemoScene.hpp"
#include "PrefabricationRegistry.hpp"
#include "GameObjectContainer.hpp"
#include "RendererContainer.hpp"
#include "TimerContainer.hpp"
#include "PhysicsEntityContainer.hpp"

// System includes not needed in header
#include <iostream>

// SFEW includes not needed in header


namespace sfew
{
	namespace scene
	{
		// Ctor/Dtor ========================================

		DemoScene::DemoScene()
		{
			
		}

		DemoScene::~DemoScene()
		{
			
		}

		// Routines =========================================

		// Clears current scene and loads
		bool DemoScene::Load()
		{
			// It is recommended to implement the scene loading in LoadActive()

			// Clear current scene
			PhysicsEntityContainer::RemoveEverything();
			RendererContainer::RemoveEverything();
			TimerContainer::RemoveEverything();
			GameObjectContainer::RemoveEverything();

			// Load Scene
			bool status = LoadAdditive();

			return status;
		}

		// Loads without clearing current scene
		bool DemoScene::LoadAdditive()
		{
			// Load the desired GameObjects here


			return true;
		}

		// Properties =========================================

		// Helpers =========================================


	} // namespace sfew::scene
} // namespace sfew