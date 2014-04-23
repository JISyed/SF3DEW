#include "ExampleScene.hpp"
#include "PrefabricationRegistry.hpp"
#include "GameObjectContainer.hpp"
#include "RendererContainer.hpp"
#include "TimerContainer.hpp"
#include "PhysicsEntityContainer.hpp"

// System includes not needed in header


// SFEW includes not needed in header


namespace sfew
{
	namespace scene
	{
		// Ctor/Dtor ========================================

		ExampleScene::ExampleScene()
		{
			
		}

		ExampleScene::~ExampleScene()
		{
			
		}

		// Routines =========================================

		// Clears current scene and loads
		bool ExampleScene::Load()
		{
			// It is recommended to implement the scene loading in LoadActive()

			// Clear current scene


			// Load Scene
			bool status = LoadAdditive();

			return status;
		}

		// Loads without clearing current scene
		bool ExampleScene::LoadAdditive()
		{
			// Load the desired GameObjects here



			return true;
		}

		// Properties =========================================

		// Helpers =========================================


	} // namespace sfew::scene
} // namespace sfew