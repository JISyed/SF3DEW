#include "OctoPrefab.hpp"
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
		OctoPrefab::OctoPrefab()
		{
			
		}

		// Dtor
		OctoPrefab::~OctoPrefab()
		{
			
		}

		// Routines =========================================

		std::weak_ptr<GameObject> OctoPrefab::MakeObject()
		{
			// Create GameObject and name it
			std::weak_ptr<GameObject> go = GameObjectContainer::Create();
			go._Get()->SetName("Octo");

			// Setup other properties here
			go._Get()->AddComponent<sfew::ObjectRendererComponent>();
			auto renderer = go._Get()->GetComponent<sfew::ObjectRendererComponent>();
			renderer._Get()->GetRenderer()._Get()->SetMesh(sfew::MeshRegistry::GetByName("OctohedronMesh"));
			renderer._Get()->GetRenderer()._Get()->SetMaterial(sfew::MaterialRegistry::GetByName("OrangePatches"));

			// Return weak pointer
			return go;
		}

	} // namespace sfew::prefab
} // namespace sfew