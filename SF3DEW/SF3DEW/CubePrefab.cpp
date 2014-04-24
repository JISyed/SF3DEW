#include "CubePrefab.hpp"
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
		CubePrefab::CubePrefab()
		{
			
		}

		// Dtor
		CubePrefab::~CubePrefab()
		{
			
		}

		// Routines =========================================

		std::weak_ptr<GameObject> CubePrefab::MakeObject()
		{
			// Create GameObject and name it
			std::weak_ptr<GameObject> go = GameObjectContainer::Create();
			go._Get()->SetName("Cube");

			// Setup other properties here
			go._Get()->AddComponent<ObjectRendererComponent>();
			auto cubeRenderer = go._Get()->GetComponent<ObjectRendererComponent>();
			cubeRenderer._Get()->GetRenderer()._Get()->SetMesh(MeshRegistry::GetByName("CubeMesh"));
			cubeRenderer._Get()->GetRenderer()._Get()->SetMaterial(MaterialRegistry::GetByName("WhitePatches"));
			go._Get()->GetTransform()._Get()->SetPosition(Vector3(-2.0f, 0.0f, 0.1f));

			// Return weak pointer
			return go;
		}

	} // namespace sfew::prefab
} // namespace sfew