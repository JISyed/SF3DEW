#include "DemoScene.hpp"
#include "PrefabricationRegistry.hpp"
#include "Camera.hpp"
#include "GameObjectContainer.hpp"
#include "RendererContainer.hpp"
#include "TimerContainer.hpp"
#include "PhysicsEntityContainer.hpp"
#include "AudioRegistry.hpp"

// System includes not needed in header
#include <iostream>

// SFEW includes not needed in header
#include "Random.hpp"
#include "SceneRegistry.hpp"

namespace sfew
{
	namespace scene
	{
		// Ctor/Dtor ========================================

		// Ctor
		DemoScene::DemoScene()
		{
			
		}

		// Ctor
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
			AudioRegistry::StopEverything();

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

			return true;
		}

	} // namespace sfew::scene
} // namespace sfew