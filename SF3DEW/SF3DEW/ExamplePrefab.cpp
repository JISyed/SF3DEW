#include "ExamplePrefab.hpp"
#include "GameObjectContainer.hpp"

// System Includes not needed in header


// SFEW Includes not needed in header


namespace sfew
{
	namespace prefab
	{
		// Ctor/Dtor ========================================

		ExamplePrefab::ExamplePrefab()
		{
			
		}

		ExamplePrefab::~ExamplePrefab()
		{
			
		}

		// Routines =========================================

		std::weak_ptr<GameObject> ExamplePrefab::MakeObject()
		{
			std::weak_ptr<GameObject> go = GameObjectContainer::Create();

			return go;
		}

		// Properties =========================================

		// Helpers =========================================


	} // namespace sfew::prefab
} // namespace sfew