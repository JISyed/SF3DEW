#include "DemoScene.hpp"
#include "PrefabricationRegistry.hpp"
#include "Camera.hpp"
#include "GameObjectContainer.hpp"
#include "RendererContainer.hpp"
#include "TimerContainer.hpp"
#include "PhysicsEntityContainer.hpp"

// System includes not needed in header
#include <iostream>

// SFEW includes not needed in header
#include "SceneRegistry.hpp"

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
			
			// Cube object
			auto cubePrefab = PrefabricationRegistry::Get<prefab::CubePrefab>();
			auto cubeObject = cubePrefab._Get()->MakeObject();

			// FPS Text display object
			auto fpsPrefab = PrefabricationRegistry::Get<prefab::FpsPrefab>();
			auto fpsObject = fpsPrefab._Get()->MakeObject();

			// Octohedron object
			auto octoPrefab = PrefabricationRegistry::Get<prefab::OctoPrefab>();
			auto octoObject = octoPrefab._Get()->MakeObject();

			std::weak_ptr<sfew::Timer> reloadTimer = sfew::TimerContainer::Create(
				sf::seconds(5.0f),
				[]()
				{
					SceneRegistry::LoadScene<sfew::scene::ExampleScene>();
				}
			);

			return true;
		}

		// Properties =========================================

		// Helpers =========================================


	} // namespace sfew::scene
} // namespace sfew