#include "ExamplePrefab.hpp"
#include "GameObjectContainer.hpp"
#include "MaterialRegistry.hpp"
#include "MeshRegistry.hpp"
#include "AudioRegistry.hpp"
#include "FontRegistry.hpp"
#include "SceneRegistry.hpp"
#include "PrefabricationRegistry.hpp"

// System Includes not needed in header


// SFEW Includes not needed in header


namespace sfew
{
	namespace prefab
	{
		// Ctor/Dtor ========================================

		ExamplePrefab::ExamplePrefab()
		{
			SetName("Example");
		}

		ExamplePrefab::~ExamplePrefab()
		{
			
		}

		// Routines =========================================

		std::weak_ptr<GameObject> ExamplePrefab::MakeObject()
		{
			// Create GameObject and name it
			std::weak_ptr<GameObject> go = GameObjectContainer::Create();
			go._Get()->SetName("Example");

			// Setup other properties
			go._Get()->AddComponent<FontRendererComponent>();
			auto fontCmpt = go._Get()->GetComponent<FontRendererComponent>();
			fontCmpt._Get()->GetRenderer()._Get()->SetTextString("Example");
			fontCmpt._Get()->GetRenderer()._Get()->SetPosition(10, 60);

			return go;
		}

		// Properties =========================================

		// Helpers =========================================


	} // namespace sfew::prefab
} // namespace sfew