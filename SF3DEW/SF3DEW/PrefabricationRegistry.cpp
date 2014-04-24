#include "PrefabricationRegistry.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static data ========================================

	PrefabricationRegistry* PrefabricationRegistry::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	PrefabricationRegistry::PrefabricationRegistry()
	{
		if(PrefabricationRegistry::_instance != NULL)
		{
			std::cout << "ERROR: PrefabricationRegistry being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		PrefabricationRegistry::_instance = this;
	}

	// Dtor
	PrefabricationRegistry::~PrefabricationRegistry()
	{
		// Clear the internal singleton
		PrefabricationRegistry::_instance = NULL;
	}

	// Routines =========================================

	// Load all the resources
	bool PrefabricationRegistry::Load()
	{
		// Load all the custom prefabs here
		addPrefab<prefab::ExamplePrefab>();
		addPrefab<prefab::CubePrefab>();
		addPrefab<prefab::OctoPrefab>();
		addPrefab<prefab::FpsPrefab>();

		// Loading successful
		_resourcesLoaded = true;
		return _resourcesLoaded;
	}

	// Unload all the resources
	void PrefabricationRegistry::Unload()
	{
		// Mark the resources as unloaded
		_resourcesLoaded = false;

		// Skip unloading of list if empty
		if(_resourceList.empty()) return;

		// Empty the list
		_resourceList.clear();
	}

	// Helpers =========================================

	// STATIC: Was this object instantiated?
	bool PrefabricationRegistry::verifyInstantiation()
	{
		if(PrefabricationRegistry::_instance == NULL)
		{
			std::cout << "ERROR: PrefabricationRegistry not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew