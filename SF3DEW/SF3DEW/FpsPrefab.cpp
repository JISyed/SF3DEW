#include "FpsPrefab.hpp"
#include "GameObjectContainer.hpp"
#include "MaterialRegistry.hpp"
#include "MeshRegistry.hpp"
#include "AudioRegistry.hpp"
#include "FontRegistry.hpp"
#include "SceneRegistry.hpp"
#include "PrefabricationRegistry.hpp"
#include "ShaderRegistry.hpp"
#include "TextureRegistry.hpp"

// SFEW Includes not needed in header
#include "Random.hpp"

namespace sfew
{
	namespace prefab
	{
		// Ctor/Dtor ========================================

		// Ctor
		FpsPrefab::FpsPrefab()
		{
			
		}

		// Dtor
		FpsPrefab::~FpsPrefab()
		{
			
		}

		// Routines =========================================

		std::weak_ptr<GameObject> FpsPrefab::MakeObject()
		{
			// Create GameObject and name it
			std::weak_ptr<GameObject> go = GameObjectContainer::Create();
			go._Get()->SetName("FPS");

			// Setup other properties here
			go._Get()->AddCustomComponent<sfew::component::FpsUpdaterCmpt>();

			// Return weak pointer
			return go;
		}

	} // namespace sfew::prefab
} // namespace sfew